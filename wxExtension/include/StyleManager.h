#pragma once

#include <wx/wx.h>
#include <vector>

class StyleManager {
public:
	std::vector<wxString> stylesheetFilePaths;

	static StyleManager* get();

	void initStyles();

private:
	static StyleManager* _instance;

	//std::vector<StyleInfo*>* _styleInfos;

	StyleManager();
};

