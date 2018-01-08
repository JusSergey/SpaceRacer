#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Layers/StonesLayer.h"
#include "Layers/AirPlaneLayer.h"
#include "Layers/BackgroundLayer.h"
#include "Constants.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    void initBackgroundLayer();
    void initStoneLayer();
    void initAirPlaneLayer();
    void initKeyboardController();
    void initAccel();

#ifdef PLATFORM_DESKTOP
    void initKeyboard();
#endif

private:
    Size _visibleSize;
    StonesLayer *_stoneLayer = nullptr;
    AirPlaneLayer *_airPlaneLayer = nullptr;
    BackgroundLayer *_backLayer = nullptr;

};

#endif // __GAME_SCENE_H__
