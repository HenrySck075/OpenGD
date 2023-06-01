#include "RewardUnlockLayer.h"

#include <MenuItemSpriteExtra.h>
#include "GameToolbox.h"
#include <ui/CocosGUI.h>
#include "ButtonSprite.h"
#include "2d/CCMenu.h"
#include "ccUTF8.h"
#include "base/CCDirector.h"
#include "GameManager.h"
#include "GJUserScore.h"
#include "2d/CCActionInterval.h"
#include <2d/CCActionEase.h>
#include "2d/CCActionInstant.h"
#include "AudioEngine.h"
#include "GJChestSprite.h"

USING_NS_AX;

RewardUnlockLayer* RewardUnlockLayer::create(int chestID)
{
	RewardUnlockLayer* pRet = new RewardUnlockLayer();

	if (pRet && pRet->init(chestID))
	{
		pRet->autorelease();
		return pRet;
	}

	AX_SAFE_DELETE(pRet);
	return nullptr;
}

bool RewardUnlockLayer::init(int chestID)
{
	if (!PopupLayer::init()) return false;
	const auto& winSize = Director::getInstance()->getWinSize();

	auto bg = ui::Scale9Sprite::create(GameToolbox::getTextureString("GJ_square02.png"));
	bg->setContentSize({ 340.0, 220.0 });
	bg->setPosition(winSize / 2);
	bg->setOpacity(0);
	bg->runAction(FadeIn::create(0.2));
	this->_mainLayer->addChild(bg);

	for (int i = 0; i < 4; i++)
	{
		auto rewardsCorners = Sprite::createWithSpriteFrameName("rewardCorner_001.png");
		this->_mainLayer->addChild(rewardsCorners);

		float xPosition = 145.0f;
		float yPosition = 85.0f;
		switch (i)
		{
			case 0:
				yPosition = -85.0f;
				xPosition = -145.0f;
				break;
			case 1:
				xPosition = -145.0f;
				rewardsCorners->setFlippedY(true);
				break;
			case 2:
				rewardsCorners->setFlippedX(true);
				rewardsCorners->setFlippedY(true);
				break;
			case 3:
				yPosition = -85.0;
				rewardsCorners->setFlippedX(true);
				break;
			default:
				yPosition = 85.0;
		}
		rewardsCorners->setOpacity(0);
		rewardsCorners->runAction(FadeIn::create(0.2));
		rewardsCorners->setPosition(winSize.width / 2 + xPosition, winSize.height / 2 + yPosition);
	}

	int offset;

	if (chestID == 1) {
      offset = 0.8;
    }
    else {
      offset = 1.0;
    }

	Vec2 position = {winSize.width / 2, winSize.height / 2 - 20.0f};

	auto chestShadow = Sprite::createWithSpriteFrameName("chest_shadow_001.png");
	chestShadow->setPosition(position.operator+=({0.0f, offset * -48.0f}));
	chestShadow->setScale(2);
	chestShadow->setOpacity(0);

	this->_mainLayer->addChild(chestShadow);

	chestShadow->runAction(FadeTo::create(0.4, 90));
	chestShadow->runAction(EaseBounceOut::create(ScaleTo::create(1.0, offset * 0.95)));

	auto chestSprite = GJChestSprite::create(chestID);
	chestSprite->setPosition(position.operator+({0.0, winSize.height}));
	this->_mainLayer->addChild(chestSprite);

	chestSprite->runAction(EaseBounceOut::create(MoveTo::create(1.0, position.operator+({0.0, chestSprite->getChildren().front()->getContentSize().x / 2 - 10})))); // these coords were hardcoded bc i couldnt figure them out
	chestSprite->runAction(Sequence::create(DelayTime::create(0.36f), CallFunc::create([=]() {AudioEngine::play2d("chestLand.ogg", false, 0.5f);}), 0));
	
	auto shake0 = DelayTime::create(1.2f);
	auto shake1 = MoveBy::create(0.05f, {-4.0f,0.0f});
	auto shake2 = MoveBy::create(0.05f, {4.0f,0.0f});
	auto shake3 = MoveBy::create(0.05f, {-4.0f,0.0f});
	auto shake4 = MoveBy::create(0.05f, {4.0f,0.0f});
	auto shake5 = MoveBy::create(0.05f, {-4.0f,0.0f});
	auto shake6 = MoveBy::create(0.05f, {4.0f,0.0f});
	auto shake7 = DelayTime::create(0.2f);
	auto shake8 = CallFunc::create([=]() { chestSprite->switchState(3, false); });
	
	chestSprite->runAction(Sequence::create(shake0, shake1, shake2, shake3, shake4, shake5, shake6, shake7, shake8, 0));
	
	return true;
}