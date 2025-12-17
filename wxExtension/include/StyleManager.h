#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <wx/wx.h>

#include <StyleSheetInfo.h>

class StyleManager {
public:
	std::vector<wxString> styleSheetFilePaths;

	static StyleManager* get();

	void initDefaultStyle();
	void initUserStyles();

	std::unique_ptr<StyleSheetInfo> _defaultStyleSheet;

private:
	StyleManager();
	~StyleManager();

	wxString _defStyleSheetFileName;

	//std::unique_ptr<StyleSheetInfo> _defaultStyleSheet;
	std::vector<std::unique_ptr<StyleSheetInfo>> _userStyleSheets;

	static StyleManager* _instance;
};

