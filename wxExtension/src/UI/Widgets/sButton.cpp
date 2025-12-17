#include "sButton.h"

sButton::sButton(wxWindow* parent, wxWindowID id, const wxString& label, 
	const WidgetStyleInfo& styleInfo, const wxPoint& pos, const wxSize& size, 
	long style, const wxValidator& validator, const wxString& name) :
	wxButton(parent, id, label, pos, size, style | wxBORDER_NONE, validator, name), 
	sWidgetBase(this, styleInfo) {
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void sButton::applyStateProperties() {
	sWidgetBase::applyStateProperties();

	SetMinSize(wxSize(getMinWidth(), GetMinHeight()));
	SetMaxSize(wxSize(getMaxWidth(), GetMaxHeight()));
	SetSize(wxSize(getWidth(), getHeight()));
}

void sButton::OnPaint(wxPaintEvent& evt) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	Render(dc);
}

void sButton::OnMouseEnter(wxMouseEvent& evt) {
    setState(WidgetState::Hover);
}

void sButton::OnMouseLeave(wxMouseEvent& evt) {
    setState(WidgetState::Normal);
}

void sButton::OnLeftDown(wxMouseEvent& evt) {
    setState(WidgetState::Active);
    evt.Skip();
}

void sButton::OnLeftUp(wxMouseEvent& evt) {
    wxPoint mousePos = evt.GetPosition();
    wxSize size = GetSize();
    if (mousePos.x >= 0 && mousePos.x < size.x &&
        mousePos.y >= 0 && mousePos.y < size.y) {
        setState(WidgetState::Hover);
    }
    else {
        setState(WidgetState::Normal);
    }
    evt.Skip();
}

void sButton::OnSetFocus(wxFocusEvent& evt) {
    setState(WidgetState::Focus);
    evt.Skip();
}

void sButton::OnKillFocus(wxFocusEvent& evt) {
    setState(WidgetState::Normal);
    evt.Skip();
}

void sButton::Render(wxAutoBufferedPaintDC& dc) {
    wxSize size = GetSize();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc) return;

    const wxColour& bgColor = getBackgroundColour();
    const wxColour& fgColor = getForegroundColour();
    const wxColour& borderColor = getBorderColour();
    const CornerRadius& corners = getCornerRadius();
    const Thickness& borders = getBorderThickness();
    const Thickness& padding = getPadding();
    const wxFont& font = getFont();

    wxColour parentBg = GetParent() ? GetParent()->GetBackgroundColour() : *wxWHITE;
    GraphicsUtils::drawRoundedRect(gc, 0, 0, size.x, size.y,
        corners, borders, bgColor, borderColor, parentBg);

    delete gc;

    dc.SetFont(font);
    dc.SetTextForeground(fgColor);

    wxString label = GetLabel();
    wxSize textSize = dc.GetTextExtent(label);

    wxRect contentRect(static_cast<int>(padding.left), static_cast<int>(padding.top),
        size.x - static_cast<int>(padding.left + padding.right),
        size.y - static_cast<int>(padding.top + padding.bottom));

    wxString align = getTextAlign();
    int textX = contentRect.x;
    int textY = contentRect.y + (contentRect.height - textSize.y) / 2;

    if (align == "center") {
        textX = contentRect.x + (contentRect.width - textSize.x) / 2;
    }
    else if (align == "right") {
        textX = contentRect.x + contentRect.width - textSize.x;
    }

    dc.DrawText(label, textX, textY);
}

wxBEGIN_EVENT_TABLE(sButton, wxButton)
	EVT_PAINT(sButton::OnPaint)
	EVT_ENTER_WINDOW(sButton::OnMouseEnter)
	EVT_LEAVE_WINDOW(sButton::OnMouseLeave)
	EVT_LEFT_DOWN(sButton::OnLeftDown)
	EVT_LEFT_UP(sButton::OnLeftUp)
	EVT_SET_FOCUS(sButton::OnSetFocus)
	EVT_KILL_FOCUS(sButton::OnKillFocus)
wxEND_EVENT_TABLE()
