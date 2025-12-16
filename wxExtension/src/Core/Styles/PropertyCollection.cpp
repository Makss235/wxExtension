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
	if (hasProperty(name)) {
		return _properties.at(name);
	}
	else {
		return std::nullopt;
	}
}

int PropertyCollection::getInt(const wxString& name, int defaultValue) const {
	auto it = _properties.find(name);
	if (it != _properties.end()) {
		auto val = it->second.getIntValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	return defaultValue;
}

double PropertyCollection::getDouble(const wxString& name, double defaultValue) const {
	auto it = _properties.find(name);
	if (it != _properties.end()) {
		auto val = it->second.getDoubleValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	return defaultValue;
}

bool PropertyCollection::getBool(const wxString& name, bool defaultValue) const {
	auto it = _properties.find(name);
	if (it != _properties.end()) {
		auto val = it->second.getBoolValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	return defaultValue;
}

wxColour PropertyCollection::getColor(const wxString& name, const wxColour& defaultValue) const {
	auto it = _properties.find(name);
	if (it != _properties.end()) {
		auto val = it->second.getColorValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	return defaultValue;
}

wxString PropertyCollection::getString(const wxString& name, const wxString& defaultValue) const {
	auto it = _properties.find(name);
	if (it != _properties.end()) {
		auto val = it->second.getStringValue();
		return val.has_value() ? val.value() : defaultValue;
	}
	return defaultValue;
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
