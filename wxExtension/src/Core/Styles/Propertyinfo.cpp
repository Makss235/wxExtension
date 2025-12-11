#include "PropertyInfo.h"

const std::map<wxString, PropertyType> PropertyInfo::_nameToTypeMap = {
	{ "background-color", PropertyType::Color },
	{ "foreground-color", PropertyType::Color },
	{ "font-family", PropertyType::String },
	{ "font-size", PropertyType::Double },
	{ "font-weight", PropertyType::String },
	{ "border-width", PropertyType::Double },
	{ "border-color", PropertyType::Color },
	{ "border-style", PropertyType::String },
	{ "border-radius", PropertyType::Double },
	{ "padding", PropertyType::Double },
	{ "margin", PropertyType::Double },
	{ "min-width", PropertyType::Double },
	{ "min-height", PropertyType::Double }
};

const std::map<wxString, PropertyType> PropertyInfo::_typeStringToTypeMap = {
	{ "int", PropertyType::Int },
	{ "double", PropertyType::Double },
	{ "color", PropertyType::Color },
	{ "string", PropertyType::String },
	{ "other", PropertyType::Other }
};

PropertyInfo::PropertyInfo() : PropertyInfo("", PropertyType::String, "") { }

PropertyInfo::PropertyInfo(const wxString& name, PropertyType type, const valueVariant& value) :
	_name(name), _type(type), _value(value) { }

PropertyInfo PropertyInfo::parse(const pugi::xml_node& propNode) {
	wxString name = propNode.attribute("name").as_string();
	wxString rawType = propNode.attribute("type").as_string();
	wxString rawValue = propNode.attribute("value").as_string();

	return parse(name, rawType, rawValue);
}

PropertyInfo PropertyInfo::parse(const wxString& name, const wxString& rawType, const wxString& rawValue) {
	PropertyType type;
	type = rawType.IsEmpty() ? parseTypeFromName(name) : parseType(rawType);

	if (type == PropertyType::Other) {
		type = parseTypeFromName(rawValue);
	}

	std::optional<valueVariant> value = parseValue(type, rawValue);
	return value.has_value() ? PropertyInfo(name, type, value.value()) : 
		PropertyInfo(name, type, "");
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
	case PropertyType::Other:
		value = rawValue;
		break;
	default:
		break;
	}

	return value;
}
