#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <wx/wx.h>

#include <StyleSheetInfo.h>

class StyleManager {
public:
	std::vector<wxString> styleSheetFilePaths;
	std::unique_ptr<StyleSheetInfo> defaultStyleSheet;
	std::vector<std::unique_ptr<StyleSheetInfo>> userStyleSheets;

	static StyleManager* get();

	void initDefaultStyle();
	void initUserStyles();

private:
	StyleManager();
	~StyleManager();

	wxString _defStyleSheetFileName;

	

	static StyleManager* _instance;
};

