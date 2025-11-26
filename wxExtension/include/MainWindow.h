#pragma once

#include "wx/wx.h"
#include "string.h"

class MainWindow : public wxFrame {
public:
	const std::string caption = "TestWindow";

	MainWindow();

private:
	void InitializeComponent();
};
