#include "StyleManager.h"

StyleManager* StyleManager::_instance = nullptr;

StyleManager* StyleManager::get() {
	if (_instance == nullptr) {
		_instance = new StyleManager();
	}
	return _instance;
}

void StyleManager::initDefaultStyle() {
	defaultStyleSheet = std::make_unique<StyleSheetInfo>();
	defaultStyleSheet->loadFromFile(_defStyleSheetFileName);
}

void StyleManager::initUserStyles() {
	for (const auto& path : styleSheetFilePaths) {
		auto userSheet = std::make_unique<StyleSheetInfo>();
		if (userSheet->loadFromFile(path)) {
			userStyleSheets.push_back(std::move(userSheet));
		}
	}
}

StyleManager::StyleManager() {
	_defStyleSheetFileName = "default_style.xml";
	styleSheetFilePaths.push_back("styles.xml");

	initDefaultStyle();
	initUserStyles();
}

StyleManager::~StyleManager() {
	delete _instance;
}
