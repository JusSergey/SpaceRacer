#ifndef __BACKGROUND_LAYER__
#define __BACKGROUND_LAYER__

#include "cocos2d.h"
#include "Objects/AirPlane.h"
USING_NS_CC;

class BackgroundLayer : public Layer {
public:
    void startRunningSky();
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);

private:
    void initBackgroundStars();
    void initBackgroundSprite();
    void initBackgroundSkyies();
    void runningActionToMoveSky(float dt);

private:
    Sprite *_backSprite = nullptr;
    Sprite *_skyies[2]{nullptr};
};

#endif // __BACKGROUND_LAYER__
