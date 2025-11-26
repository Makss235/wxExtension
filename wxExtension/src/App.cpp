#include "App.h"

#include "MainWindow.h"

bool App::OnInit() {
    InitializeComponent();

    return true;
}

void App::InitializeComponent() {
    MainWindow* mw = new MainWindow();
    mw->Show();
}
