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
	Bool,
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
	//PropertyInfo(const wxString& name, const valueVariant& value);
	~PropertyInfo() = default;

	const wxString& getName() const { return _name; }
	void setName(const wxString& name) { _name = name; }
	const PropertyType& getType() const { return _type; }
	void setType(const PropertyType& type) { _type = type; }

	std::optional<int> getIntValue() const;
	std::optional<double> getDoubleValue() const;
	std::optional<bool> getBoolValue() const;
	std::optional<wxColour> getColorValue() const;
	std::optional<wxString> getStringValue() const;

	void setValue(const valueVariant& value) { _value = value; }

	bool isIntValue() const { return _type == PropertyType::Int; }
	bool isDoubleValue() const { return _type == PropertyType::Double; }
	bool isBoolValue() const { return _type == PropertyType::Bool; }
	bool isColorValue() const { return _type == PropertyType::Color; }
	bool isStringValue() const { return _type == PropertyType::String; }

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

