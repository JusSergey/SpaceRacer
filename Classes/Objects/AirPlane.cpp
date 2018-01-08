#include "AirPlane.h"
#include "MyBodyParser.h"
#include "Constants.h"

bool AirPlane::init()
{
    if (!Sprite::initWithFile("stones/rocket.png")){
        log("init air plane failed");
        return false;
    }

    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    initPhysicsBody();

    return true;
}

void AirPlane::AsyncPreloadResource()
{
}

void AirPlane::normalizePosition()
{
    const float width_div_2 = getContentSize().width * getScale() / 2;

    if (getPositionX() - width_div_2 < 0){
        setPositionX(width_div_2);
        if (getPhysicsBody())
            getPhysicsBody()->setVelocity(Vec2::ZERO);
    }

    else if (getPositionX() + width_div_2 > DesignResolSize.width){
        setPositionX(DesignResolSize.width - width_div_2);
        if (getPhysicsBody())
            getPhysicsBody()->setVelocity(Vec2::ZERO);
    }

}

float AirPlane::getNormalizePositionX(float x)
{
    const float width_div_2 = getContentSize().width * getScale() / 2;
    const float rightPos = DesignResolSize.width - width_div_2;
    return x < width_div_2 ? width_div_2 : x > rightPos ? rightPos : x;
}

void AirPlane::setPosition(const Vec2 &pos)
{
    Node::setPosition(getNormalizePositionX(pos.x), pos.y);
}

void AirPlane::setPosition(float x, float y)
{
    Node::setPosition(getNormalizePositionX(x), y);
}

void AirPlane::setPositionX(float x)
{
    Node::setPositionX(getNormalizePositionX(x));
}

void AirPlane::initPhysicsBody()
{
    auto pBody = MyBodyParser::getInstance()->bodyFormJson(this, "rocket", PHYSICSBODY_MATERIAL_DEFAULT);
    setPhysicsBody(pBody);
}
