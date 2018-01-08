#ifndef __AIR_PLANE_H__
#define __AIR_PLANE_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using std::string;

class AirPlane : public Sprite {

public:
    virtual bool init();
    CREATE_FUNC(AirPlane);
    static void AsyncPreloadResource();

public:
    inline float getPositionLeftSide() const
    { return getPositionX() - (getContentSize().width * getScale() * getAnchorPoint().x); }
    inline float getPositionRightSide() const
    { return getPositionX() + (getContentSize().width * getScale() * getAnchorPoint().x); }

    void normalizePosition();

    virtual void setPosition(const Vec2 &pos);
    virtual void setPosition(float x, float y);
    virtual void setPositionX(float x);

private:
    using Sprite::setAnchorPoint;
    void initPhysicsBody();
    float getNormalizePositionX(float x);

};

#endif // __AIR_PLANE_H__
