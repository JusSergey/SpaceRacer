#ifndef __PRESENT_SCENE_H__
#define __PRESENT_SCENE_H__

#include "cocos2d.h"
#include "Layers/StonesLayer.h"

USING_NS_CC;

class PresentScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(PresentScene);

private:
    void initLabel();
    void gotoGameScene();

};

#endif // __PRESENT_SCENE_H__
