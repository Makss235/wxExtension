#pragma once

#include <wx/textctrl.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include <sWidgetBase.h>
#include <GraphicsUtils.h>

class sTextCtrl : public wxTextCtrl, public sWidgetBase {
public:
    sTextCtrl(
        wxWindow* parent,
        wxWindowID id,
        const wxString& value = wxEmptyString,
        const WidgetStyleInfo& styleInfo = WidgetStyleInfo(),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxASCII_STR(wxTextCtrlNameStr)
    );

    virtual ~sTextCtrl() = default;

protected:
    virtual void applyStateProperties() override;

    void OnPaint(wxPaintEvent& evt);
    void OnMouseEnter(wxMouseEvent& evt);
    void OnMouseLeave(wxMouseEvent& evt);
    void OnSetFocus(wxFocusEvent& evt);
    void OnKillFocus(wxFocusEvent& evt);
    void OnText(wxCommandEvent& evt);
    void OnEnabled(wxCommandEvent& evt);

    virtual void Render(wxAutoBufferedPaintDC& dc);

    void UpdateTextColor();
    void UpdateBackgroundColor();
    void UpdateFont();

    virtual bool Enable(bool enable = true) override;

private:
    wxColour m_cachedTextColor;
    wxColour m_cachedBgColor;

    wxDECLARE_EVENT_TABLE();
};