#include "PropertyInfo.h"

const std::map<wxString, PropertyType> PropertyInfo::_nameToTypeMap = {
	{ "background-color", PropertyType::Color },
	{ "foreground-color", PropertyType::Color },
	{ "color", PropertyType::Color },
	{ "border-color", PropertyType::Color },
	{ "outline-color", PropertyType::Color },

	{ "font-family", PropertyType::String },
	{ "font-weight", PropertyType::String },
	{ "font-style", PropertyType::String },
	{ "border-style", PropertyType::String },
	{ "text-align", PropertyType::String },
	{ "cursor", PropertyType::String },

	{ "font-size", PropertyType::Double },
	{ "border-width", PropertyType::Double },
	{ "border-radius", PropertyType::Double },
	{ "border-radius-top-left", PropertyType::Double },
	{ "border-radius-top-right", PropertyType::Double },
	{ "border-radius-bottom-left", PropertyType::Double },
	{ "border-radius-bottom-right", PropertyType::Double },
	{ "padding", PropertyType::Double },
	{ "padding-left", PropertyType::Double },
	{ "padding-top", PropertyType::Double },
	{ "padding-right", PropertyType::Double },
	{ "padding-bottom", PropertyType::Double },
	{ "margin", PropertyType::Double },
	{ "margin-left", PropertyType::Double },
	{ "margin-top", PropertyType::Double },
	{ "margin-right", PropertyType::Double },
	{ "margin-bottom", PropertyType::Double },
	{ "min-width", PropertyType::Double },
	{ "min-height", PropertyType::Double },
	{ "max-width", PropertyType::Double },
	{ "max-height", PropertyType::Double },
	{ "width", PropertyType::Double },
	{ "height", PropertyType::Double },
	{ "opacity", PropertyType::Double },
	{ "outline-width", PropertyType::Double },
	{ "outline-offset", PropertyType::Double },

	{ "z-index", PropertyType::Int },

	{ "visible", PropertyType::Bool },
	{ "enabled", PropertyType::Bool }
};

const std::map<wxString, PropertyType> PropertyInfo::_typeStringToTypeMap = {
	{ "int", PropertyType::Int },
	{ "double", PropertyType::Double },
	{ "bool", PropertyType::Bool },
	{ "color", PropertyType::Color },
	{ "string", PropertyType::String }
};

PropertyInfo::PropertyInfo() : PropertyInfo("", PropertyType::String, "") { }

PropertyInfo::PropertyInfo(const wxString& name, PropertyType type, const valueVariant& value) :
	_name(name), _type(type), _value(value) { }

std::optional<int> PropertyInfo::getIntValue() const {
	if (!isIntValue()) {
		return std::nullopt;
	}
	return std::get<int>(_value);
}

std::optional<double> PropertyInfo::getDoubleValue() const {
	if (!isDoubleValue()) {
		return std::nullopt;
	}
	return std::get<double>(_value);
}

std::optional<bool> PropertyInfo::getBoolValue() const {
	if (!isBoolValue()) {
		return std::nullopt;
	}
	return std::get<bool>(_value);
}

std::optional<wxColour> PropertyInfo::getColorValue() const {
	if (!isColorValue()) {
		return std::nullopt;
	}
	return std::get<wxColour>(_value);
}

std::optional<wxString> PropertyInfo::getStringValue() const{
	if (!isStringValue()) {
		return std::nullopt;
	}
	return std::get<wxString>(_value);
}

PropertyInfo PropertyInfo::parse(const pugi::xml_node& propNode) {
	wxString name = propNode.attribute("name").as_string();
	wxString rawType = propNode.attribute("type").as_string();
	wxString rawValue = propNode.attribute("value").as_string();

	return parse(name, rawType, rawValue);
}

PropertyInfo PropertyInfo::parse(const wxString& name, const wxString& rawType, const wxString& rawValue) {
	PropertyType type;
	type = rawType.IsEmpty() ? parseTypeFromName(name) : parseType(rawType);

	std::optional<valueVariant> value = parseValue(type, rawValue);
	return value.has_value() ? PropertyInfo(name, type, value.value()) : 
		PropertyInfo(name, type, "");
}

std::optional<PropertyInfo> PropertyInfo::merge(const PropertyInfo& baseProp, const PropertyInfo& overrideProp) {
	if (baseProp.getName() != overrideProp.getName() || 
		baseProp.getType() != overrideProp.getType()) {
		return std::nullopt;
	}

	return overrideProp;
}

PropertyType PropertyInfo::parseType(const wxString& rawType) {
	auto it = _typeStringToTypeMap.find(rawType);
	return it != _typeStringToTypeMap.end() ? it->second : PropertyType::String;
}

PropertyType PropertyInfo::parseTypeFromName(const wxString& name) {
	auto it = _nameToTypeMap.find(name);
	return it != _nameToTypeMap.end() ? it->second : PropertyType::String;
}

std::optional<valueVariant> PropertyInfo::parseValue(PropertyType type, const wxString& rawValue) {
	std::optional<valueVariant> value;

	switch (type)
	{
	case PropertyType::Int:
		value = std::stoi(rawValue.ToStdString());
		break;
	case PropertyType::Double:
		value = std::stod(rawValue.ToStdString());
		break;
	case PropertyType::Color: {
		wxColour color = wxColour();
		value = color.Set(rawValue) ? color : wxColour(0, 0, 0);
		break;
	}
	case PropertyType::String:
		value = rawValue;
		break;
	default:
		break;
	}

	return value;
}
