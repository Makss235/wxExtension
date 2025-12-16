#include "StyleSheetInfo.h"

std::optional<WidgetStyleInfo> StyleSheetInfo::getStyle(const wxString& styleId) const {
    if (hasStyle(styleId)) {
        return _styles.at(styleId);
    } 
    else {
        return std::nullopt;
    }
}

std::vector<WidgetStyleInfo> StyleSheetInfo::findStylesForWidget(const wxString& widgetType) const {
    std::vector<WidgetStyleInfo> result;

    for (const auto& [styleId, style] : _styles) {
        if (style.getWidgetType() == widgetType) {
            result.push_back(style);
        }
    }

    return result;
}

bool StyleSheetInfo::hasStyle(const wxString& styleId) const {
    return _styles.find(styleId) != _styles.end();
}

void StyleSheetInfo::clear() {
    _name.clear();
    _styles.clear();
}

bool StyleSheetInfo::loadFromFile(const wxString& filename) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.mb_str());

    return parseXML(doc);
}

bool StyleSheetInfo::loadFromString(const wxString& xmlContent) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xmlContent.mb_str());

    return parseXML(doc);
}

bool StyleSheetInfo::parseXML(const pugi::xml_document& doc) {
    clear();

    pugi::xml_node root = doc.child("stylesheet");
    if (!root) {
        return false;
    }

    _name = root.attribute("name").as_string();

    pugi::xml_node stylesNode = root.child("styles");
    if (stylesNode) {
        parseStyles(stylesNode);
    }

    return true;
}

void StyleSheetInfo::parseStyles(const pugi::xml_node& node) {
    for (pugi::xml_node styleNode : node.children("style")) {
        WidgetStyleInfo style = WidgetStyleInfo::parse(styleNode);

        wxString styleId = style.getStyleId();

        if (styleId.IsEmpty()) {
            continue;
        }

        _styles[styleId] = style;
    }
}
