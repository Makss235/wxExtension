#include "StateProperties.h"

const std::map<wxString, WidgetState> StateProperties::_stringToWidgetStateMap = {
	{ "normal", WidgetState::Normal },
	{ "hover", WidgetState::Hover },
	{ "active", WidgetState::Active },
	{ "focus", WidgetState::Focus },
	{ "disabled", WidgetState::Disabled },
	{ "checked", WidgetState::Checked }
};

WidgetState StateProperties::stringToWidgetState(const wxString& stateString) {
	return _stringToWidgetStateMap.at(stateString);
}

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
