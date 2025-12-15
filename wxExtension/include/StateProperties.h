#pragma once

#include <PropertyCollection.h>

enum class WidgetState {
    Normal,
    Hover,
    Active,
    Focus,
    Disabled,
    Checked
};

class StateProperties {
public:
    StateProperties() : StateProperties(WidgetState::Normal) { }
    explicit StateProperties(WidgetState state) : _state(state) { }
    ~StateProperties() = default;

    const WidgetState& getState() const { return _state; }
    void setState(const WidgetState& state) { _state = state; }

    PropertyCollection& getProperties() { return _properties; }
    const PropertyCollection& getProperties() const { return _properties; }

    static StateProperties parse(const pugi::xml_node& node);

private:
    WidgetState _state;
    PropertyCollection _properties;
};

