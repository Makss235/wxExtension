#include "sWidgetBase.h"

sWidgetBase::sWidgetBase(wxWindow* owner, const WidgetStyleInfo& styleInfo) : 
	m_owner(owner), m_styleInfo(styleInfo), m_currentState(WidgetState::Normal) {
	applyStateProperties();
}

void sWidgetBase::setStyle(const WidgetStyleInfo& styleInfo) {
	m_styleInfo = styleInfo;
	applyStateProperties();
	if (m_owner) {
		m_owner->Refresh();
	}
}

void sWidgetBase::setState(WidgetState state) {
	if (m_currentState != state) {
		m_currentState = state;
		applyStateProperties();
		if (m_owner) {
			m_owner->Refresh();
		}
	}
}

void sWidgetBase::applyStateProperties() {
	std::optional<PropertyCollection> props = m_styleInfo.getStateProperties(m_currentState);
	if (props.has_value()) {
		updatePropertiesFromCollection(props.value());
	}
}

void sWidgetBase::updatePropertiesFromCollection(const PropertyCollection& props) {
	m_backgroundColor = props.getColor("background-color", wxColour(255, 255, 255));
	m_foregroundColor = props.getColor("foreground-color", wxColour(0, 0, 0));
	m_borderColor = props.getColor("border-color", wxColour(0, 0, 0));
	m_outlineColor = props.getColor("outline-color", wxColour(0, 0, 0));

	m_font = extractFont(props);

	m_cornerRadius = props.getCornerRadius("border-radius", CornerRadius(0.0));
	m_borderThickness = props.getThickness("border-width", Thickness(0.0));
	m_padding = props.getThickness("padding", Thickness(0.0));
	m_margin = props.getThickness("margin", Thickness(0.0));

	m_borderStyle = props.getString("border-style", "solid");
	m_textAlign = props.getString("text-align", "center");
	m_cursor = props.getString("cursor", "pointer");

	m_minWidth = props.getDouble("min-width", 0.0);
	m_minHeight = props.getDouble("min-height", 0.0);
	m_maxWidth = props.getDouble("max-width", wxDefaultSize.GetWidth());
	m_maxHeight = props.getDouble("max-height", wxDefaultSize.GetHeight());
	m_width = props.getDouble("width", wxDefaultSize.GetWidth());
	m_height = props.getDouble("height", wxDefaultSize.GetHeight());

	m_opacity = props.getDouble("opacity", 1.0);
	m_zIndex = props.getInt("z-index", 0);

	m_visible = props.getBool("visible", true);
	m_enabled = props.getBool("enabled", true);
}

wxFont sWidgetBase::extractFont(const PropertyCollection& props) const {
	wxString family = props.getString("font-family", "Segoe UI");
	double size = props.getDouble("font-size", 14.0);
	wxString weight = props.getString("font-weight", "normal");
	wxString style = props.getString("font-style", "normal");

	wxFont font(wxFontInfo(static_cast<int>(size)).FaceName(family));

	if (weight == "bold") {
		font.SetWeight(wxFONTWEIGHT_BOLD);
	}
	else if (weight == "light") {
		font.SetWeight(wxFONTWEIGHT_LIGHT);
	}
	else {
		font.SetWeight(wxFONTWEIGHT_NORMAL);
	}

	if (style == "italic") {
		font.SetStyle(wxFONTSTYLE_ITALIC);
	}
	else {
		font.SetStyle(wxFONTSTYLE_NORMAL);
	}

	return font;
}
