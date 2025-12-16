#pragma once

#include <set>

#include <StateProperties.h>

class WidgetStyleInfo {
public:
    WidgetStyleInfo();
    explicit WidgetStyleInfo(const wxString& widgetType, const wxString& styleId);
    ~WidgetStyleInfo() = default;

    const wxString& getWidgetType() const { return _widgetType; }
    void setWidgetType(const wxString& widgetType) { _widgetType = widgetType; }
    const wxString& getStyleId() const { return _styleId; }
    void setStyleId(const wxString& styleId) { _styleId = styleId; }

    void addStateProperties(WidgetState state, const PropertyCollection& props);
    void removeState(WidgetState state);
    bool hasState(WidgetState state) const;

    std::optional<PropertyCollection> getStateProperties(WidgetState state) const;
    const std::map<WidgetState, PropertyCollection>& getAllProperties() const { return _stateProperties; }

    WidgetStyleInfo clone() const;
    void clearProperties() { _stateProperties.clear(); }

    void merge(const WidgetStyleInfo& other);
    static WidgetStyleInfo merge(const WidgetStyleInfo& baseStyle,
        const WidgetStyleInfo& overrideStyle);

    static WidgetStyleInfo parse(const pugi::xml_node& styleNode);

private:
    wxString _widgetType;
    wxString _styleId;
    std::map<WidgetState, PropertyCollection> _stateProperties;
};

