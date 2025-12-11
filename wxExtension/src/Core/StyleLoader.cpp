#include "StyleLoader.h"

void StyleLoader::loadStylesheetFromFile(wxString filePath) {
	/*std::vector<StyleInfo*>* styles = new std::vector<StyleInfo*>();*/

    pugi::xml_document xmlDoc;
    pugi::xml_parse_result result = xmlDoc.load_file(filePath.t_str());

	/*auto styleNodes = xmlDoc.children("style");
	for (auto styleNode : styleNodes) {
		StyleInfo* styleInfo = parseStyleNode(styleNode);
		styles->push_back(styleInfo);
	}

    return styles;*/

	auto hh = xmlDoc.child("properties");
	auto props1 = hh.children("set");

	std::vector<PropertyInfo> props;
	for (pugi::xml_node dd : props1)
	{
		PropertyInfo prop = PropertyInfo::parse(dd);
		props.push_back(prop);
	}
}
