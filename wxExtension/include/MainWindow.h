#pragma once

#include <wx/wx.h>

class MainWindow : public wxFrame {
public:
	const wxString caption = "TestWindow";

	MainWindow();

private:
	void InitializeComponent();
};
