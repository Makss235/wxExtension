#include "WidgetStyleInfo.h"

WidgetStyleInfo::WidgetStyleInfo() : WidgetStyleInfo(wxEmptyString, wxEmptyString) { }

WidgetStyleInfo::WidgetStyleInfo(const wxString& widgetType, const wxString& styleId) :
	_widgetType(widgetType), _styleId(styleId) { }

void WidgetStyleInfo::addStateProperties(WidgetState state, const PropertyCollection& props) {
    _stateProperties[state] = props;
}

void WidgetStyleInfo::removeState(WidgetState state) {
    if (hasState(state)) {
        _stateProperties.erase(state);
    }
}

bool WidgetStyleInfo::hasState(WidgetState state) const {
    return _stateProperties.find(state) != _stateProperties.end();
}

std::optional<PropertyCollection> WidgetStyleInfo::getStateProperties(WidgetState state) const {
    if (hasState(state)) {
        return _stateProperties.at(state);
    }
    else {
        return std::nullopt;
    }
}

WidgetStyleInfo WidgetStyleInfo::clone() const {
    WidgetStyleInfo copy;
    copy._widgetType = _widgetType;
    copy._styleId = _styleId;
    copy._stateProperties = _stateProperties;
    return copy;
}

void WidgetStyleInfo::merge(const WidgetStyleInfo& other) {
    if (!other._styleId.IsEmpty()) {
        _styleId = other._styleId;
    }
    if (!other._widgetType.IsEmpty()) {
        _widgetType = other._widgetType;
    }

    for (const auto& [state, props] : other._stateProperties) {
        if (hasState(state)) {
            _stateProperties[state].merge(props);
        }
        else {
            _stateProperties[state] = props;
        }
    }
}

WidgetStyleInfo WidgetStyleInfo::merge(const WidgetStyleInfo& baseStyle, const WidgetStyleInfo& overrideStyle) {
    WidgetStyleInfo result;

    result._widgetType = overrideStyle._widgetType.IsEmpty() ? baseStyle._widgetType : overrideStyle._widgetType;
    result._styleId = overrideStyle._styleId.IsEmpty() ? baseStyle._styleId : overrideStyle._styleId;

    PropertyCollection mergedNormalProps;

    std::optional<PropertyCollection> baseNormalProps = baseStyle.getStateProperties(WidgetState::Normal);
    if (baseNormalProps.has_value()) {
        mergedNormalProps = baseNormalProps.value();
    }

    std::optional<PropertyCollection> overrideNormalProps = overrideStyle.getStateProperties(WidgetState::Normal);
    if (overrideNormalProps.has_value()) {
        mergedNormalProps.merge(overrideNormalProps.value());
    }

    result._stateProperties[WidgetState::Normal] = mergedNormalProps;

    std::set<WidgetState> statesSet;
    for (const auto& [state, _] : baseStyle._stateProperties) {
        if (state != WidgetState::Normal) {
            statesSet.insert(state);
        }
    }
    for (const auto& [state, _] : overrideStyle._stateProperties) {
        if (state != WidgetState::Normal) {
            statesSet.insert(state);
        }
    }

    for (WidgetState state : statesSet) {
        PropertyCollection stateProps = mergedNormalProps;

        std::optional<PropertyCollection> baseStateProps = baseStyle.getStateProperties(state);
        if (baseStateProps.has_value()) {
            stateProps.merge(baseStateProps.value());
        }

        std::optional<PropertyCollection> overrideStateProps = overrideStyle.getStateProperties(state);
        auto overrideIt = overrideStyle._stateProperties.find(state);
        if (overrideStateProps.has_value()) {
            stateProps.merge(overrideStateProps.value());
        }

        result._stateProperties[state] = stateProps;
    }

    return result;
}

WidgetStyleInfo WidgetStyleInfo::parse(const pugi::xml_node& styleNode) {
    WidgetStyleInfo style;

    style._widgetType = styleNode.attribute("selector").as_string();
    style._styleId = styleNode.attribute("id").as_string();

    pugi::xml_node propertiesNode = styleNode.child("properties");
    if (propertiesNode) {
        PropertyCollection normalProps = PropertyCollection::parse(propertiesNode);
        style._stateProperties[WidgetState::Normal] = normalProps;
    }

    for (pugi::xml_node stateNode : styleNode.children("state")) {
        wxString stateStr = stateNode.attribute("name").as_string();
        WidgetState state = StateProperties::stringToWidgetState(stateStr);

        PropertyCollection stateProps;
        auto normalIt = style._stateProperties.find(WidgetState::Normal);
        if (normalIt != style._stateProperties.end()) {
            stateProps = normalIt->second;
        }

        PropertyCollection overrides = PropertyCollection::parse(stateNode);

        stateProps.merge(overrides);

        style._stateProperties[state] = stateProps;
    }

    return style;
}
