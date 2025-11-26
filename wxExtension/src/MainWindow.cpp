#include "MainWindow.h"

MainWindow::MainWindow() :
    wxFrame(nullptr, wxID_ANY, caption,
        wxDefaultPosition, wxSize(900, 800)) {
    InitializeComponent();
}

void MainWindow::InitializeComponent() {
    wxPanel* panel = new wxPanel(this);
    wxButton* button = new wxButton(panel, wxID_ANY, "Click me!", wxPoint(50, 50));

    button->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        wxMessageBox("Hello from wxWidgets!");
        });
}
