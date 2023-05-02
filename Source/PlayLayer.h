#pragma once

#include <axmol.h>

#include "GroundLayer.h"
#include "MenuItemSpriteExtra.h"
#include "MenuLayer.h"
#include "PlayerObject.h"
#include "SimpleProgressBar.h"

#include "GJGameLevel.h"
#include "SpriteColor.h"
#include "UILayer.h"
#include "BaseGameLayer.h"

#include <vector>
#include <span>

class PlayLayer : public ax::Layer
{
  private:
	bool init(GJGameLevel* level);
	void onEnter() override;
	void onExit() override;
	void onDrawImGui();
	void onKeyPressed(ax::EventKeyboard::KeyCode keyCode, ax::Event* event);
	void onKeyReleased(ax::EventKeyboard::KeyCode keyCode, ax::Event* event);
	void createLevelEnd();

	void fillColorChannel(std::span<std::string_view> colorString, int id);

	ax::Sprite* m_pBG;
	GroundLayer *_bottomGround, *_ceiling;
	
	ax::Vec2 m_obCamPos;

	MenuItemSpriteExtra* backbtn;

	ax::DrawNode* dn;

	std::vector<GameObject*> _pObjects;

	std::vector<std::vector<GameObject*>> m_pSectionObjects;

	float m_fCameraYCenter;
	float m_lastObjXPos = 570.0f;
	bool m_bFirstAttempt = true;
	bool m_bMoveCameraX;
	bool m_bMoveCameraY;
	bool m_bShakingCamera;
	float m_fEndOfLevel = FLT_MAX;
	float m_fShakeIntensity = 1;

	int _prevSection, _nextSection;

	bool m_bIsJumpPressed;

	SimpleProgressBar* m_pBar;
	ax::Label* m_pPercentage;

	LevelSettings _levelSettings;

	//----IMGUI DEBUG MEMBERS----
	bool m_freezePlayer;
	bool m_platformerMode;

	bool m_bEndAnimation;

public:
	int _enterEffectID = 0;

	int _groundID = 1;
	int _bgID = 1;

	UILayer* m_pHudLayer;

	int _secondsSinceStart;
	int _attempts;
	int _jumps;
	bool _everyplay_recorded;

	std::vector<bool> _coinsCollected;

	PlayerObject* _player1;
	PlayerObject* _player2;

	bool _isDualMode;

	std::string _mainBatchNodeTexture = "GJ_GameSheet.png";
	std::string _main2BatchNodeTexture = "GJ_GameSheet02.png";

	ax::SpriteBatchNode *_mainBatchNodeB4, *_mainBatchNodeB3, *_mainBatchNodeB2, *_mainBatchNodeB1, *_mainBatchNodeT1,
		*_mainBatchNodeT2, *_mainBatchNodeT3;
	ax::SpriteBatchNode *_blendingBatchNodeB4, *_blendingBatchNodeB3, *_blendingBatchNodeB2, *_blendingBatchNodeB1,
		*_blendingBatchNodeT1, *_blendingBatchNodeT2, *_blendingBatchNodeT3;
	ax::SpriteBatchNode* _main2BatchNode;
	ax::SpriteBatchNode* _glowBatchNode;
	ax::ParticleBatchNode* _particleBatchNode;

	std::unordered_map<int, SpriteColor> m_pColorChannels, _originalColors;
	std::unordered_map<int, GroupProperties> _groups;

	AX_SYNTHESIZE(GJGameLevel*, _pLevel, Level);

	void destroyPlayer(PlayerObject* player);

	void loadLevel(std::string_view levelStr);

	void spawnCircle();
	void showEndLayer();
	void showCompleteText();

	void update(float delta);
	void updateCamera(float dt);
	void updateVisibility();
	void moveCameraToPos(ax::Vec2);
	void changeGameMode(GameObject* obj, PlayerObject* player, PlayerGamemode gameMode);
	void resetLevel();
	void exit();

	void tweenBottomGround(float y);
	void tweenCeiling(float y);

	// dt?
	void checkCollisions(PlayerObject* player, float delta);
	void renderRect(ax::Rect rect, ax::Color4B col);

	void applyEnterEffect(GameObject* obj);
	float getRelativeMod(ax::Vec2 objPos, float v1, float v2, float v3);
	
	bool isObjectBlending(GameObject* obj);

	int sectionForPos(float x);

	void changePlayerSpeed(int speed);
	void changeGravity(bool gravityFlipped);

	void incrementTime();

	ax::Color3B getLightBG();

	static ax::Scene* scene(GJGameLevel* level);
	static PlayLayer* create(GJGameLevel* level);

	static PlayLayer* getInstance();
};