#pragma once

#include <wx/button.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include <sWidgetBase.h>
#include <GraphicsUtils.h>

class sButton : public wxButton, public sWidgetBase {
public:
    sButton(
        wxWindow* parent,
        wxWindowID id,
        const wxString& label,
        const WidgetStyleInfo& styleInfo,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 0,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxASCII_STR(wxButtonNameStr)
    );

    virtual ~sButton() = default;

protected:
	virtual void applyStateProperties() override;

    void OnPaint(wxPaintEvent& evt);
    void OnMouseEnter(wxMouseEvent& evt);
    void OnMouseLeave(wxMouseEvent& evt);
    void OnLeftDown(wxMouseEvent& evt);
    void OnLeftUp(wxMouseEvent& evt);
    void OnSetFocus(wxFocusEvent& evt);
    void OnKillFocus(wxFocusEvent& evt);

    virtual void Render(wxAutoBufferedPaintDC& dc);

    wxDECLARE_EVENT_TABLE();
};