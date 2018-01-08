#include "AirPlaneLayer.h"
#include "Constants.h"

bool AirPlaneLayer::init()
{
    if (!Layer::init())
        return false;

    initAirPlanePlayer();

    return true;
}

template <typename T>
static bool getSigned(T value) {
    return value < static_cast<T>(0);
}

template <typename T>
static bool toSymbolValue(T value) {
    return (value < static_cast<T>(0) ? static_cast<T>(-1) : static_cast<T>(1));
}

void AirPlaneLayer::accelerationEvent(Acceleration *accel)
{
    auto pBody = _player->getPhysicsBody();

    if (!pBody)
        return;

    pBody->setVelocityLimit(500);

    if ((_player->getPositionLeftSide() > 3.f && _player->getPositionRightSide() < DesignResolSize.width - 3.f) ||
         _player->getPositionLeftSide() <=3.f && accel->x > 0.f ||
         _player->getPositionRightSide()>= DesignResolSize.width - 3.f && accel->x < 0.f)
    {
        if (std::abs(accel->x) < 0.1f) {
            pBody->setVelocity(Vec2(pBody->getVelocity().x * 0.4f, 0.f));
        } else {
            if (pBody->getVelocity().x < 0 && accel->x > 0 ||
                pBody->getVelocity().x > 0 && accel->x < 0)
            {
                Vec2 vel = pBody->getVelocity();
                vel.x = vel.x / std::abs(accel->x > 0 ? 1.f : -1.f);
                pBody->setVelocity(vel);
            }
            pBody->applyForce(Vec2(pBody->getMass() * 2500.f * accel->x, 0.f));
        }
    }
    else {
        stopPlayer();
    }
}

void AirPlaneLayer::stopPlayer()
{
    auto pBody = _player->getPhysicsBody();
    if (pBody)
        pBody->setVelocity(Vec2::ZERO);
}

void AirPlaneLayer::initAirPlanePlayer()
{
    _player = AirPlane::create();
    _player->setScale(0.6);
    const Vec2 pos(DesignResolSize.width / 2, _player->getContentSize().height * _player->getScale());
    _player->setPosition(pos);

    addChild(_player);
}
