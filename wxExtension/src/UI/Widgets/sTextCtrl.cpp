#include "sTextCtrl.h"

wxBEGIN_EVENT_TABLE(sTextCtrl, wxTextCtrl)
EVT_PAINT(sTextCtrl::OnPaint)
EVT_ENTER_WINDOW(sTextCtrl::OnMouseEnter)
EVT_LEAVE_WINDOW(sTextCtrl::OnMouseLeave)
EVT_SET_FOCUS(sTextCtrl::OnSetFocus)
EVT_KILL_FOCUS(sTextCtrl::OnKillFocus)
EVT_TEXT(wxID_ANY, sTextCtrl::OnText)
//EVT_UPDATE_UI(wxID_ANY, sTextCtrl::OnEnabled)
wxEND_EVENT_TABLE()

sTextCtrl::sTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value,
    const WidgetStyleInfo& styleInfo, const wxPoint& pos, const wxSize& size,
    long style, const wxValidator& validator, const wxString& name)
    : wxTextCtrl(parent, id, value, pos, size, style | wxBORDER_NONE, validator, name),
    sWidgetBase(this, styleInfo),
    m_cachedTextColor(getForegroundColour()),
    m_cachedBgColor(getBackgroundColour())
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    UpdateTextColor();
    UpdateBackgroundColor();
    UpdateFont();

    SetMinSize(wxSize(getMinWidth(), getMinHeight()));
    SetMaxSize(wxSize(getMaxWidth(), getMaxHeight()));

    wxString cursorType = getCursor();
    if (cursorType == "pointer") {
        SetCursor(wxCURSOR_HAND);
    }
    else if (cursorType == "text") {
        SetCursor(wxCURSOR_IBEAM);
    }
    else if (cursorType == "default") {
        SetCursor(wxCURSOR_ARROW);
    }

    applyStateProperties();
}

void sTextCtrl::applyStateProperties() {
    sWidgetBase::applyStateProperties();

    SetMinSize(wxSize(getMinWidth(), getMinHeight()));
    SetMaxSize(wxSize(getMaxWidth(), getMaxHeight()));

    wxTextCtrl::Enable(isEnabled());
    wxTextCtrl::Show(isVisible());

    UpdateTextColor();
    UpdateBackgroundColor();
    UpdateFont();

    wxString cursorType = getCursor();
    if (cursorType == "pointer") {
        SetCursor(wxCURSOR_HAND);
    }
    else if (cursorType == "text") {
        SetCursor(wxCURSOR_IBEAM);
    }
    else if (cursorType == "default") {
        SetCursor(wxCURSOR_ARROW);
    }

    Refresh();
}

void sTextCtrl::OnPaint(wxPaintEvent& evt) {
    if (!isEnabled()) {
        evt.Skip();
        return;
    }

    wxAutoBufferedPaintDC dc(this);
    dc.Clear();
    Render(dc);

    evt.Skip();
}

void sTextCtrl::OnMouseEnter(wxMouseEvent& evt) {
    if (isEnabled()) {
        setState(WidgetState::Hover);
    }
    evt.Skip();
}

void sTextCtrl::OnMouseLeave(wxMouseEvent& evt) {
    if (isEnabled()) {
        if (HasFocus()) {
            setState(WidgetState::Focus);
        }
        else {
            setState(WidgetState::Normal);
        }
    }
    evt.Skip();
}

void sTextCtrl::OnSetFocus(wxFocusEvent& evt) {
    if (isEnabled()) {
        setState(WidgetState::Focus);
    }
    evt.Skip();
}

void sTextCtrl::OnKillFocus(wxFocusEvent& evt) {
    if (isEnabled()) {
        setState(WidgetState::Normal);
    }
    evt.Skip();
}

void sTextCtrl::OnText(wxCommandEvent& evt) {
    Refresh();
    evt.Skip();
}

void sTextCtrl::OnEnabled(wxCommandEvent& evt) {
    if (isEnabled() != IsEnabled()) {
        setState(isEnabled() ? WidgetState::Normal : WidgetState::Disabled);
    }
    evt.Skip();
}

void sTextCtrl::Render(wxAutoBufferedPaintDC& dc) {
    wxSize size = GetClientSize();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (!gc) return;

    const wxColour& bgColor = getBackgroundColour();
    const wxColour& borderColor = getBorderColour();
    const CornerRadius& corners = getCornerRadius();
    const Thickness& borders = getBorderThickness();
    const Thickness& padding = getPadding();

    wxColour parentBg = GetParent() ? GetParent()->GetBackgroundColour() : *wxWHITE;

    GraphicsUtils::drawRoundedRect(gc, 0, 0, size.x, size.y,
        corners, borders, bgColor, borderColor, parentBg);

    delete gc;

    int leftPadding = static_cast<int>(padding.left);
    int topPadding = static_cast<int>(padding.top);
    int rightPadding = static_cast<int>(padding.right);
    int bottomPadding = static_cast<int>(padding.bottom);

    wxRect textRect(
        leftPadding,
        topPadding,
        size.x - leftPadding - rightPadding,
        size.y - topPadding - bottomPadding
    );

    dc.SetTextForeground(m_cachedTextColor);
    dc.SetFont(sWidgetBase::m_font);

    wxString text = GetValue();
    if (!text.empty()) {
        wxSize textSize = dc.GetTextExtent(text);
        if (textSize.x > textRect.width) {
            int chars = text.length();
            while (chars > 0) {
                wxString truncated = text.Left(chars) + "...";
                wxSize truncatedSize = dc.GetTextExtent(truncated);
                if (truncatedSize.x <= textRect.width || chars == 1) {
                    text = truncated;
                    break;
                }
                chars--;
            }
        }

        wxString align = getTextAlign();
        int textX = textRect.x;
        textSize = dc.GetTextExtent(text);

        if (align == "center") {
            textX = textRect.x + (textRect.width - textSize.x) / 2;
        }
        else if (align == "right") {
            textX = textRect.x + textRect.width - textSize.x;
        }

        int textY = textRect.y + (textRect.height - textSize.y) / 2;
        dc.DrawText(text, textX, textY);
    }

    if (text.empty() && !GetHint().IsEmpty()) {
        wxString hint = GetHint();
        wxColour hintColor = m_cachedTextColor;
        hintColor = hintColor.ChangeLightness(150);

        dc.SetTextForeground(hintColor);

        wxSize hintSize = dc.GetTextExtent(hint);
        if (hintSize.x > textRect.width) {
            int chars = hint.length();
            while (chars > 0) {
                wxString truncated = hint.Left(chars) + "...";
                wxSize truncatedSize = dc.GetTextExtent(truncated);
                if (truncatedSize.x <= textRect.width || chars == 1) {
                    hint = truncated;
                    break;
                }
                chars--;
            }
        }

        hintSize = dc.GetTextExtent(hint);
        int hintX = textRect.x;
        wxString align = getTextAlign();

        if (align == "center") {
            hintX = textRect.x + (textRect.width - hintSize.x) / 2;
        }
        else if (align == "right") {
            hintX = textRect.x + textRect.width - hintSize.x;
        }

        int hintY = textRect.y + (textRect.height - hintSize.y) / 2;
        dc.DrawText(hint, hintX, hintY);
    }

    if (HasFocus() && isEnabled()) {
        wxColour focusColor = getOutlineColour();
        if (focusColor.IsOk()) {
            dc.SetPen(wxPen(focusColor, 2));
            dc.SetBrush(*wxTRANSPARENT_BRUSH);

            dc.DrawRoundedRectangle(
                1, 1,
                size.x - 2, size.y - 2,
                corners.topLeft > 0 ? corners.topLeft - 1 : 0
            );
        }
    }
}

void sTextCtrl::UpdateTextColor() {
    m_cachedTextColor = getForegroundColour();
}

void sTextCtrl::UpdateBackgroundColor() {
    m_cachedBgColor = getBackgroundColour();
    wxTextCtrl::SetBackgroundColour(m_cachedBgColor);
}

void sTextCtrl::UpdateFont() {
    wxTextCtrl::SetFont(sWidgetBase::m_font);
}

bool sTextCtrl::Enable(bool enable) {
    bool result = wxTextCtrl::Enable(enable);

    if (enable) {
        setState(WidgetState::Normal);
    }
    else {
        setState(WidgetState::Disabled);
    }

    return result;
}