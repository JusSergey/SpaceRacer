#include "BackgroundLayer.h"
#include "Constants.h"
#include <vector>
using std::vector;

enum LocalLevel {
    BackSkin,
    Stars,
    Sky
};

#define ITERATION_SKY for (Sprite* &sky : {_skyies[0], _skyies[1]})

bool BackgroundLayer::init()
{
    if (!Layer::init())
        return false;

    initBackgroundSprite();
    initBackgroundSkyies();
    initBackgroundStars();

    return true;
}

void BackgroundLayer::initBackgroundStars()
{
    for (int i = 0; i < 64; ++i) {
        Sprite *star = Sprite::create("star.png");

        const float scl = cocos2d::random(0.02, 0.10);
        star->setScale(scl);
        star->setOpacity(0xff * cocos2d::rand_0_1());

        star->setColor(Color3B(cocos2d::random(int(0xff*0.4), 0xff),
                               cocos2d::random(int(0xff*0.4), 0xff),
                               cocos2d::random(int(0xff*0.4), 0xff)));

        star->setPosition(cocos2d::random(0.f, DesignResolSize.width),
                          cocos2d::random(0.f, DesignResolSize.height));

        addChild(star, LocalLevel::Stars);
    }
}

void BackgroundLayer::initBackgroundSprite()
{
    _backSprite = Sprite::create("back.png");

    static const vector<Color3B> colors {
        Color3B(0xFF, 0x00, 0xBF),
        Color3B(0x64, 0x2E, 0xFE),
        Color3B(0x00, 0xff, 0xbf),
        Color3B(0x6A, 0x08, 0x88),
        Color3B::MAGENTA
    };

    _backSprite->setColor(colors[cocos2d::random(size_t(0u), colors.size()-1)]);
    _backSprite->setPosition(DesignResolSize / 2);
    addChild(_backSprite, LocalLevel::BackSkin);
}

void BackgroundLayer::initBackgroundSkyies()
{
    for (int i = 0; i < 2; ++i) {
        Sprite* &sky = _skyies[i];
        sky = Sprite::create("sky.png");
        auto conSize = sky->getContentSize();
        sky->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
        sky->setPosition(DesignResolSize.width * 0.5f, conSize.height * i);

        addChild(sky, LocalLevel::Sky);
    }
}

void BackgroundLayer::runningActionToMoveSky(float dt)
{
    for (int i = 0; i < 2; ++i) {
        auto sky = _skyies[i];
        auto conSize = sky->getContentSize().height;

        auto getposy = [](float posy, float skyHeight) -> float {
            return (posy <= -skyHeight ? skyHeight : posy);
        };

        sky->setPositionY(getposy(sky->getPositionY()-1, conSize));

    }
}

void BackgroundLayer::startRunningSky()
{
    const float Time = 5; // sec
    const float h = _skyies[0]->getContentSize().height;
    schedule(schedule_selector(BackgroundLayer::runningActionToMoveSky),
             1.f / (h / Time));

}
