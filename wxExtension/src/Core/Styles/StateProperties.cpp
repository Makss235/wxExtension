#include "StateProperties.h"

StateProperties StateProperties::parse(const pugi::xml_node& node) {
	auto propNodes = node.children("set");

	PropertyCollection props;
	for (auto propNode : propNodes) {
		props.addProperty(PropertyInfo::parse(propNode));
	}

	StateProperties state;
	state.getProperties() = props;

	return state;
}
