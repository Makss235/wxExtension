#include "PropertyCollection.h"

void PropertyCollection::addProperty(const PropertyInfo& prop) {
	_properties[prop.getName()] = prop;
}

void PropertyCollection::removeProperty(const wxString& name) {
	if (hasProperty(name)) {
		_properties.erase(name);
	}
}

bool PropertyCollection::hasProperty(const wxString& name) const {
	return _properties.find(name) != _properties.end();
}

std::optional<PropertyInfo> PropertyCollection::getProperty(const wxString& name) const {
	if (hasProperty(name))
		return _properties.at(name);
	else {
		return std::nullopt;
	}
}

int PropertyCollection::getInt(const wxString& name, int defaultValue) const {
	std::optional<PropertyInfo> prop = getProperty(name);
	if (prop.has_value()) {
		std::optional<int> val = prop.value().getIntValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	else {
		return defaultValue;
	}
}

double PropertyCollection::getDouble(const wxString& name, double defaultValue) const {
	std::optional<PropertyInfo> prop = getProperty(name);
	if (prop.has_value()) {
		std::optional<double> val = prop.value().getDoubleValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	else {
		return defaultValue;
	}
}

bool PropertyCollection::getBool(const wxString& name, bool defaultValue) const {
	std::optional<PropertyInfo> prop = getProperty(name);
	if (prop.has_value()) {
		std::optional<bool> val = prop.value().getBoolValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	else {
		return defaultValue;
	}
}

wxColour PropertyCollection::getColor(const wxString& name, const wxColour& defaultValue) const {
	std::optional<PropertyInfo> prop = getProperty(name);
	if (prop.has_value()) {
		std::optional<wxColour> val = prop.value().getColorValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	else {
		return defaultValue;
	}
}

wxString PropertyCollection::getString(const wxString& name, const wxString& defaultValue) const {
	std::optional<PropertyInfo> prop = getProperty(name);
	if (prop.has_value()) {
		std::optional<wxString> val = prop.value().getStringValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	else {
		return defaultValue;
	}
}

void PropertyCollection::merge(const PropertyCollection& other) {
	for (const auto& [name, prop] : other._properties) {
		_properties[name] = prop;
	}
}

PropertyCollection PropertyCollection::merge(const PropertyCollection& baseProps, const PropertyCollection& overrideProps) {
	PropertyCollection result;
	for (const auto& [name, prop] : baseProps._properties) {
		result._properties[name] = prop;
	}

	for (const auto& [name, prop] : overrideProps._properties) {
		result._properties[name] = prop;
	}

	return result;
}

PropertyCollection PropertyCollection::parse(const pugi::xml_node& node) {
	auto propNodes = node.children("set");

	PropertyCollection props;
	for (auto propNode : propNodes) {
		props.addProperty(PropertyInfo::parse(propNode));
	}

	return props;
}
