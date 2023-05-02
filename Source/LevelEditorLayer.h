#pragma once

#include <axmol.h>
#include "GJGameLevel.h"

class LevelEditorLayer : public ax::Layer {
private:
	bool init(GJGameLevel* level);
	void exit();

	AX_SYNTHESIZE(GJGameLevel*, _level, Level);

public:
	static ax::Scene* scene(GJGameLevel* level);
	static LevelEditorLayer* create(GJGameLevel* level);
	void onDrawImGui();
	// static LevelEditorLayer* getInstance();
};
