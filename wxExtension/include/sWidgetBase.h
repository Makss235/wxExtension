#pragma once

#include <wx/window.h>
#include <wx/colour.h>
#include <wx/font.h>

#include <WidgetStyleInfo.h>
#include <PropertyCollection.h>

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
    const wxColour& getOutlineColour() const { return m_outlineColor; }

    const wxFont& getFont() const { return m_font; }

    const CornerRadius& getCornerRadius() const { return m_cornerRadius; }
    const Thickness& getBorderThickness() const { return m_borderThickness; }
    const Thickness& getPadding() const { return m_padding; }
    const Thickness& getMargin() const { return m_margin; }

	const wxString& getBorderStyle() const { return m_borderStyle; }
	const wxString& getTextAlign() const { return m_textAlign; }
	const wxString& getCursor() const { return m_cursor; }

    double getMinWidth() const { return m_minWidth; }
	double getMinHeight() const { return m_minHeight; }
	double getMaxWidth() const { return m_maxWidth; }
	double getMaxHeight() const { return m_maxHeight; }
	double getWidth() const { return m_width; }
	double getHeight() const { return m_height; }

    double getOpacity() const { return m_opacity; }
	int getZIndex() const { return m_zIndex; }

	bool isVisible() const { return m_visible; }
	bool isEnabled() const { return m_enabled; }

protected:
    virtual void applyStateProperties();
    void updatePropertiesFromCollection(const PropertyCollection& props);
    wxFont extractFont(const PropertyCollection& props) const;


    wxWindow* m_owner;

    WidgetStyleInfo m_styleInfo;
    WidgetState m_currentState;

    wxColour m_backgroundColor;
    wxColour m_foregroundColor;
    wxColour m_borderColor;
    wxColour m_outlineColor;

    wxFont m_font;

    CornerRadius m_cornerRadius;
    Thickness m_borderThickness;
    Thickness m_padding;
	Thickness m_margin;

    wxString m_borderStyle;
    wxString m_textAlign;
    wxString m_cursor;

    double m_minWidth;
    double m_minHeight;
    double m_maxWidth;
    double m_maxHeight;
    double m_width;
    double m_height;
    
    double m_opacity;
	int m_zIndex;
    
	bool m_visible;
	bool m_enabled;
};

