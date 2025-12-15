#pragma once

#include <map>
#include <wx/colour.h>

#include <PropertyInfo.h>

class PropertyCollection {
public:
	PropertyCollection() = default;

	void addProperty(const PropertyInfo& prop);
	void removeProperty(const wxString& name);
	bool hasProperty(const wxString& name) const;

	std::optional<PropertyInfo> getProperty(const wxString& name) const;
	const std::map<wxString, PropertyInfo>& getAllProperties() const { return _properties; }

	int getInt(const wxString& name, int defaultValue = 0) const;
	double getDouble(const wxString& name, double defaultValue = 0.0) const;
	bool getBool(const wxString& name, bool defaultValue = false) const;
	wxColour getColor(const wxString& name, const wxColour& defaultValue = wxColour(0, 0, 0)) const;
	wxString getString(const wxString& name, const wxString& defaultValue = wxEmptyString) const;

	size_t count() const { return _properties.size(); }
	bool isEmpty() const { return _properties.empty(); }
	void clear() { _properties.clear(); }

    void merge(const PropertyCollection& other);
    static PropertyCollection merge(const PropertyCollection& base,
        const PropertyCollection & override);

	static PropertyCollection parse(const pugi::xml_node& node);

private:
	std::map<wxString, PropertyInfo> _properties;
};
