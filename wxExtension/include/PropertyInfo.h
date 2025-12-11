#pragma once

#include <variant>
#include <optional>
#include <map>

#include <pugixml.hpp>

#include <wx/string.h>
#include <wx/colour.h>

enum class PropertyType {
	Int,
	Double,
	Color,
	String,
	Other
};

using valueVariant = std::variant<
	int,
	double,
	bool,
	wxColour, 
	wxString
>;

class PropertyInfo {
public:
	PropertyInfo();
	PropertyInfo(const wxString& name, PropertyType type, const valueVariant& value);
	PropertyInfo(const wxString& name, const valueVariant& value);
	~PropertyInfo() = default;



	static PropertyInfo parse(const pugi::xml_node& propNode);
	static PropertyInfo parse(const wxString& name, const wxString& rawType, const wxString& rawValue);

private:
	wxString _name;
	PropertyType _type;
	valueVariant _value;

	static const std::map<wxString, PropertyType> _nameToTypeMap;
	static const std::map<wxString, PropertyType> _typeStringToTypeMap;

	static PropertyType parseType(const wxString& rawType);
	static PropertyType parseTypeFromName(const wxString& name);
	static std::optional<valueVariant> parseValue(PropertyType type, const wxString& rawValue);
};

