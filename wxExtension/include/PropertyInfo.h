#pragma once

#include <variant>
#include <optional>
#include <map>

#include <pugixml.hpp>

#include <wx/string.h>
#include <wx/colour.h>
#include <wx/tokenzr.h>

#include <Structs.h>

enum class PropertyType {
	Int,
	Double,
	Bool,
	String,
	Color,
	CornerRadius,
	Thickness,
	None
};

using valueVariant = std::variant<
	int,
	double,
	bool,
	wxString,
	wxColour,
	CornerRadius,
	Thickness
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

	void setValue(const valueVariant& value) { _value = value; }
	const valueVariant& getValue() const { return _value; }

	std::optional<int> getIntValue() const;
	std::optional<double> getDoubleValue() const;
	std::optional<bool> getBoolValue() const;
	std::optional<wxString> getStringValue() const;
	std::optional<wxColour> getColorValue() const;
	std::optional<CornerRadius> getCornerRadiusValue() const;
	std::optional<Thickness> getThicknessValue() const;

	bool isIntValue() const { return _type == PropertyType::Int; }
	bool isDoubleValue() const { return _type == PropertyType::Double; }
	bool isBoolValue() const { return _type == PropertyType::Bool; }
	bool isStringValue() const { return _type == PropertyType::String; }
	bool isColorValue() const { return _type == PropertyType::Color; }
	bool isCornerRadiusValue() const { return _type == PropertyType::CornerRadius; }
	bool isThicknessValue() const { return _type == PropertyType::Thickness; }

	PropertyInfo clone() const { return PropertyInfo(_name, _type, _value); }
	bool isValid() const { return !_name.IsEmpty() && _type != PropertyType::None; }

	static PropertyInfo parse(const pugi::xml_node& propNode);
	static PropertyInfo parse(const wxString& name, const wxString& rawType, const wxString& rawValue);

	static std::optional<PropertyInfo> merge(const PropertyInfo& baseProp, const PropertyInfo & overrideProp);

private:
	wxString _name;
	PropertyType _type;
	valueVariant _value;

	static const std::map<wxString, PropertyType> _nameToTypeMap;
	static const std::map<wxString, PropertyType> _typeStringToTypeMap;

	static PropertyType parseType(const wxString& rawType);
	static PropertyType parseTypeFromName(const wxString& name);
	static std::optional<valueVariant> parseValue(PropertyType type, const wxString& rawValue);

	static std::optional<int> parseIntValue(const wxString& rawValue);
	static std::optional<double> parseDoubleValue(const wxString& rawValue);
	static std::optional<bool> parseBoolValue(const wxString& rawValue);
	static std::optional<wxColour> parseColorValue(const wxString& rawValue);
	static std::optional<CornerRadius> parseCornerRadiusValue(const wxString& rawValue);
	static std::optional<Thickness> parseThicknessValue(const wxString& rawValue);

	static std::vector<double> parseNumericVector(const wxString& rawValue);
};

