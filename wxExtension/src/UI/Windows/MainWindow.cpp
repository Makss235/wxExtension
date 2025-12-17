#include "MainWindow.h"

#include <sButton.h>
#include <StyleManager.h>

MainWindow::MainWindow() :
    wxFrame(nullptr, wxID_ANY, caption,
        wxDefaultPosition, wxSize(900, 800)) {
    InitializeComponent();
}

void MainWindow::InitializeComponent() {

    wxPanel* panel = new wxPanel(this);
    sButton* button = new sButton(panel, wxID_ANY, "Click me!", 
        StyleManager::get()->_defaultStyleSheet->getStyle("default-button").value(), wxPoint(50, 50));

    /*button->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        wxMessageBox("Hello from wxWidgets!");
        });*/
}
