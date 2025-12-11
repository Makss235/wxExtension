#include "App.h"

#include <MainWindow.h> 
#include <StyleManager.h>

#include <variant>
#include <string>

bool App::OnInit() {
	StyleManager::get()->initStyles();

    InitializeComponent();

    return true;
}

void App::InitializeComponent() {
    MainWindow* mw = new MainWindow();
    mw->Show();
}
