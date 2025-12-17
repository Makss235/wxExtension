#include "sWidgetBase.h"

sWidgetBase::sWidgetBase(wxWindow* owner, const WidgetStyleInfo& styleInfo) : 
	m_owner(owner), m_styleInfo(styleInfo), m_currentState(WidgetState::Normal), 
	m_opacity(1.0), m_textAlign("center") {
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

wxColour sWidgetBase::getBackgroundColourForState(WidgetState state) const {
	std::optional<PropertyCollection> props = m_styleInfo.getStateProperties(state);
	if (props.has_value()) {
		return props->getColor("background-color", wxColour(255, 255, 255));
	}
	return wxColour(255, 255, 255);
}

wxColour sWidgetBase::getForegroundColourForState(WidgetState state) const {
	std::optional<PropertyCollection> props = m_styleInfo.getStateProperties(state);
	if (props.has_value()) {
		return props->getColor("foreground-color", wxColour(255, 255, 255));
	}
	return wxColour(255, 255, 255);
}

wxColour sWidgetBase::getBorderColourForState(WidgetState state) const {
	std::optional<PropertyCollection> props = m_styleInfo.getStateProperties(state);
	if (props.has_value()) {
		return props->getColor("border-color", wxColour(255, 255, 255));
	}
	return wxColour(255, 255, 255);
}

CornerRadius sWidgetBase::getCornerRadiusForState(WidgetState state) const {
	std::optional<PropertyCollection> props = m_styleInfo.getStateProperties(state);
	if (props.has_value()) {
		return extractCornerRadius(props.value());
	}
	return CornerRadius();
}

Thickness sWidgetBase::getBorderThicknessForState(WidgetState state) const {
	std::optional<PropertyCollection> props = m_styleInfo.getStateProperties(state);
	if (props.has_value()) {
		return extractBorderThickness(props.value());
	}
	return Thickness();
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

	m_cornerRadius = extractCornerRadius(props);
	m_borderThickness = extractBorderThickness(props);
	m_padding = extractPadding(props);

	m_font = extractFont(props);

	m_opacity = props.getDouble("opacity", 1.0);
	m_textAlign = props.getString("text-align", "center");
	m_cursor = props.getString("cursor", "pointer");
}

CornerRadius sWidgetBase::extractCornerRadius(const PropertyCollection& props) const {
	double general = props.getDouble("border-radius", 0.0);

	double tl = props.getDouble("border-radius-top-left", general);
	double tr = props.getDouble("border-radius-top-right", general);
	double bl = props.getDouble("border-radius-bottom-left", general);
	double br = props.getDouble("border-radius-bottom-right", general);

	return CornerRadius(tl, tr, bl, br);
}

Thickness sWidgetBase::extractBorderThickness(const PropertyCollection& props) const {
	double general = props.getDouble("border-width", 0.0);

	double left = props.getDouble("border-width-left", general);
	double top = props.getDouble("border-width-top", general);
	double right = props.getDouble("border-width-right", general);
	double bottom = props.getDouble("border-width-bottom", general);

	return Thickness(left, top, right, bottom);
}

Thickness sWidgetBase::extractPadding(const PropertyCollection& props) const {
	double general = props.getDouble("padding", 0.0);

	double left = props.getDouble("padding-left", general);
	double top = props.getDouble("padding-top", general);
	double right = props.getDouble("padding-right", general);
	double bottom = props.getDouble("padding-bottom", general);

	return Thickness(left, top, right, bottom);
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
