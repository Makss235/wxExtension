#include "MainWindow.h"

#include <sButton.h>
#include <sTextCtrl.h>
#include <StyleManager.h>

MainWindow::MainWindow() :
    wxFrame(nullptr, wxID_ANY, caption,
        wxDefaultPosition, wxSize(900, 800)) {
    InitializeComponent();
}

void MainWindow::InitializeComponent() {

    wxPanel* panel = new wxPanel(this, -1, wxPoint(50, 50));
    sButton* button = new sButton(panel, wxID_ANY, "Click me!",
        StyleManager::get()->defaultStyleSheet->getStyle("default-button").value(), wxPoint(50, 50));

    sTextCtrl* text = new sTextCtrl(panel, wxID_ANY, "Click me!",
        StyleManager::get()->defaultStyleSheet->getStyle("default-textctrl").value(), wxPoint(50, 50));

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(button);
	sizer->Add(text);

    panel->SetSizer(sizer);
}
