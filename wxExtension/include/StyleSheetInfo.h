#pragma once

#include <WidgetStyleInfo.h>

class StyleSheetInfo {
public:
	StyleSheetInfo() = default;
	~StyleSheetInfo() = default;

	const wxString& getName() const { return _name; }
	void setName(const wxString& name) { _name = name; }

	std::optional<WidgetStyleInfo> getStyle(const wxString& styleId) const;
	std::vector<WidgetStyleInfo> findStylesForWidget(const wxString& widgetType) const;
	bool hasStyle(const wxString& styleId) const;

	bool isEmpty() const { return _styles.empty(); }
	void clear();

	bool loadFromFile(const wxString& filename);
	bool loadFromString(const wxString& xmlContent);

private:
	wxString _name;
	std::map<wxString, WidgetStyleInfo> _styles;

	bool parseXML(const pugi::xml_document& doc);
	//void parseVariables(const pugi::xml_node& node);
	void parseStyles(const pugi::xml_node& node);
};

