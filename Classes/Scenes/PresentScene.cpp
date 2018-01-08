#include "Scenes/PresentScene.h"
#include "GameScene.h"

Scene *PresentScene::createScene()
{
    return PresentScene::create();
}

bool PresentScene::init()
{
    if (!Scene::init())
        return false;

    initLabel();

    return true;
}

void PresentScene::initLabel()
{
    Label *hello = Label::createWithTTF("free game", "fonts/Marker Felt.ttf", 24);
    hello->setPosition(Director::getInstance()->getVisibleSize() / 2);

    auto call = CallFunc::create([this]{
        gotoGameScene();
    });

    auto action = Sequence::create(DelayTime::create(.5f), call, nullptr);

    addChild(hello);
    hello->runAction(action);
}

void PresentScene::gotoGameScene()
{
    _director->replaceScene(TransitionFade::create(1.f, GameScene::create()));
}
