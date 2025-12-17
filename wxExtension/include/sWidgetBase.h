#pragma once

#include <wx/window.h>
#include <wx/colour.h>
#include <wx/font.h>
#include "WidgetStyleInfo.h"
#include "PropertyCollection.h"
#include <Structs.h>

class sWidgetBase {
public:
    sWidgetBase(wxWindow* owner, const WidgetStyleInfo& styleInfo);
    virtual ~sWidgetBase() = default;

    void setStyle(const WidgetStyleInfo& styleInfo);
    const WidgetStyleInfo& getStyle() const { return m_styleInfo; }

    void setState(WidgetState state);
    WidgetState getCurrentState() const { return m_currentState; }


    const wxColour& getBackgroundColour() const { return m_backgroundColor; }
    const wxColour& getForegroundColour() const { return m_foregroundColor; }
    const wxColour& getBorderColour() const { return m_borderColor; }

    const CornerRadius& getCornerRadius() const { return m_cornerRadius; }
    const Thickness& getBorderThickness() const { return m_borderThickness; }
    const Thickness& getPadding() const { return m_padding; }

    const wxFont& getFont() const { return m_font; }

    double getOpacity() const { return m_opacity; }
    wxString getTextAlign() const { return m_textAlign; }


    wxColour getBackgroundColourForState(WidgetState state) const;
    wxColour getForegroundColourForState(WidgetState state) const;
    wxColour getBorderColourForState(WidgetState state) const;
    CornerRadius getCornerRadiusForState(WidgetState state) const;
    Thickness getBorderThicknessForState(WidgetState state) const;

protected:
    virtual void applyStateProperties();

    void updatePropertiesFromCollection(const PropertyCollection& props);

    CornerRadius extractCornerRadius(const PropertyCollection& props) const;
    Thickness extractBorderThickness(const PropertyCollection& props) const;
    Thickness extractPadding(const PropertyCollection& props) const;
    wxFont extractFont(const PropertyCollection& props) const;


    wxWindow* m_owner;

    WidgetStyleInfo m_styleInfo;
    WidgetState m_currentState;

    wxColour m_backgroundColor;
    wxColour m_foregroundColor;
    wxColour m_borderColor;
    CornerRadius m_cornerRadius;
    Thickness m_borderThickness;
    Thickness m_padding;
    wxFont m_font;
    double m_opacity;
    wxString m_textAlign;
    wxString m_cursor;
};

