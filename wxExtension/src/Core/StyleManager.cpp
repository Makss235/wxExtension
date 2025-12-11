#include "StyleManager.h"

#include <StyleLoader.h>

StyleManager* StyleManager::_instance = nullptr;

StyleManager* StyleManager::get() {
	if (_instance == nullptr) {
		_instance = new StyleManager();
	}
	return _instance;
}

void StyleManager::initStyles() {
	StyleLoader* loader = new StyleLoader();

	for (int i = 0; i < stylesheetFilePaths.size(); i++) {
		loader->loadStylesheetFromFile(stylesheetFilePaths.at(i));
	}
}

StyleManager::StyleManager() {
	stylesheetFilePaths = std::vector<wxString>();
	stylesheetFilePaths.push_back("styles1.xml");
}
