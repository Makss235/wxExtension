#include "PropertyInfo.h"

const std::map<wxString, PropertyType> PropertyInfo::_nameToTypeMap = {
	{ "background-color", PropertyType::Color },
	{ "foreground-color", PropertyType::Color },
	{ "border-color", PropertyType::Color },
	{ "outline-color", PropertyType::Color },

	{ "font-size", PropertyType::Double },
	{ "font-family", PropertyType::String },
	{ "font-weight", PropertyType::String },
	{ "font-style", PropertyType::String },

	{ "border-style", PropertyType::String },
	{ "text-align", PropertyType::String },
	{ "cursor", PropertyType::String },

	{ "border-radius", PropertyType::CornerRadius },
	{ "border-width", PropertyType::Thickness },
	{ "padding", PropertyType::Thickness },
	{ "margin", PropertyType::Thickness },

	{ "min-width", PropertyType::Double },
	{ "min-height", PropertyType::Double },
	{ "max-width", PropertyType::Double },
	{ "max-height", PropertyType::Double },
	{ "width", PropertyType::Double },
	{ "height", PropertyType::Double },

	{ "opacity", PropertyType::Double },
	{ "z-index", PropertyType::Int },

	{ "visible", PropertyType::Bool },
	{ "enabled", PropertyType::Bool }
};

const std::map<wxString, PropertyType> PropertyInfo::_typeStringToTypeMap = {
	{ "int", PropertyType::Int },
	{ "double", PropertyType::Double },
	{ "bool", PropertyType::Bool },
	{ "string", PropertyType::String },
	{ "color", PropertyType::Color },
	{ "corner-radius", PropertyType::CornerRadius },
	{ "thickness", PropertyType::Thickness }
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

std::optional<wxString> PropertyInfo::getStringValue() const{
	if (!isStringValue()) {
		return std::nullopt;
	}
	return std::get<wxString>(_value);
}

std::optional<wxColour> PropertyInfo::getColorValue() const {
	if (!isColorValue()) {
		return std::nullopt;
	}
	return std::get<wxColour>(_value);
}

std::optional<CornerRadius> PropertyInfo::getCornerRadiusValue() const {
	if (!isCornerRadiusValue()) {
		return std::nullopt;
	}
	return std::get<CornerRadius>(_value);
}

std::optional<Thickness> PropertyInfo::getThicknessValue() const {
	if (!isThicknessValue()) {
		return std::nullopt;
	}
	return std::get<Thickness>(_value);
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
		value = parseIntValue(rawValue).value_or(0);
		break;
	case PropertyType::Double:
		value = parseDoubleValue(rawValue).value_or(0.0);
		break;
	case PropertyType::Bool:
		value = parseBoolValue(rawValue).value_or(false);
		break;
	case PropertyType::String:
		value = rawValue;
		break;
	case PropertyType::Color:
		value = parseColorValue(rawValue).value_or(wxColour(0.0));
		break;
	case PropertyType::CornerRadius:
		value = parseCornerRadiusValue(rawValue).value_or(CornerRadius(0.0));
		break;
	case PropertyType::Thickness:
		value = parseThicknessValue(rawValue).value_or(Thickness(0.0));
		break;
	default:
		value = std::nullopt;
		break;
	}

	return value;
}

std::optional<int> PropertyInfo::parseIntValue(const wxString& rawValue) {
	try {
		return std::stoi(rawValue.ToStdString());;
	}
	catch (...) {
		return std::nullopt;
	}
}

std::optional<double> PropertyInfo::parseDoubleValue(const wxString& rawValue) {
	try {
		return std::stod(rawValue.ToStdString());;
	}
	catch (...) {
		return std::nullopt;
	}
}

std::optional<bool> PropertyInfo::parseBoolValue(const wxString& rawValue) {
	return rawValue == "true" || rawValue == "1";
}

std::optional<wxColour> PropertyInfo::parseColorValue(const wxString& rawValue) {
	wxColour color;
	return color.Set(rawValue) ? color : std::optional<wxColour>(std::nullopt);
}

std::optional<CornerRadius> PropertyInfo::parseCornerRadiusValue(const wxString& rawValue) {
	std::vector<double> values = parseNumericVector(rawValue);

	if (values.size() == 1) {
		return CornerRadius(values[0]);
	}
	else if (values.size() == 2) {
		return CornerRadius(values[0], values[1], values[0], values[1]);
	}
	else if (values.size() == 4) {
		return CornerRadius(values[0], values[1], values[2], values[3]);
	}

	return std::nullopt;
}

std::optional<Thickness> PropertyInfo::parseThicknessValue(const wxString& rawValue) {
	std::vector<double> values = parseNumericVector(rawValue);

	if (values.size() == 1) {
		return Thickness(values[0]);
	}
	else if (values.size() == 2) {
		return Thickness(values[0], values[1], values[0], values[1]);
	}
	else if (values.size() == 4) {
		return Thickness(values[0], values[1], values[2], values[3]);
	}

	return std::nullopt;
}

std::vector<double> PropertyInfo::parseNumericVector(const wxString& rawValue) {
	wxString trimmed = rawValue;
	trimmed.Trim(true).Trim(false);

	if (trimmed.empty()) {
		return std::vector<double>();
	}

	wxStringTokenizer tokenizer(trimmed, ",");
	std::vector<double> values;

	while (tokenizer.HasMoreTokens()) {
		wxString token = tokenizer.GetNextToken().Trim(true).Trim(false);
		values.push_back(parseDoubleValue(token).value_or(0.0));
	}

	return values;
}
