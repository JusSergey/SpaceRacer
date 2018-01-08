#include "Stone.h"
#include "MyBodyParser.h"
#include "Constants.h"

bool Stone::init()
{
    auto tex = TextureCache::getInstance()->getTextureForKey(getPathFromType(_type));
    if (!Sprite::initWithTexture(tex))
        return false;

    setColor(Color3B(
                 0xff * cocos2d::random(0.5, 1.0),
                 0xff * cocos2d::random(0.5, 1.0),
                 0xff * cocos2d::random(0.5, 1.0)
                 ));

    _visibleSize = Director::getInstance()->getVisibleSize();

    initPhysicsBody();

    return true;
}

Stone *Stone::createRandom(float speed)
{
    using Enum_T = std::underlying_type<Type>::type;

    Enum_T value = cocos2d::random(static_cast<Enum_T>(Type::__Begin)+1,
                                   static_cast<Enum_T>(Type::__End)-1);

    return Stone::create(static_cast<Type>(value), speed);
}

Stone *Stone::create(Stone::Type type, float speed)
{
    Stone *pRet = new(std::nothrow) Stone();
    if (pRet)
    {
        pRet->_speed = speed;
        pRet->_type = type;
    }
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

void Stone::AsyncPreloadResource()
{
    auto texCache = TextureCache::getInstance();
    for (auto i : {Type::Big, Type::Medium, Type::Small}){
        log("path[%s]", getPathFromType(i).c_str());
        texCache->addImage(getPathFromType(i));
    }

    MyBodyParser::getInstance()->parseJsonFile("stones/bodies.json");
}

std::string Stone::getNameFromType(Stone::Type type)
{
    return string("stone_") + StringUtils::toString(static_cast<std::underlying_type<Type>::type>(type));
}

void Stone::initPhysicsBody()
{
    auto parser = MyBodyParser::getInstance();
    auto pBody = parser->bodyFormJson(this, getNameFromType(_type), PHYSICSBODY_MATERIAL_DEFAULT);
    setPhysicsBody(pBody);
    pBody->setAngularVelocity(cocos2d::random(-2.f, 2.f));
}

std::string Stone::getPathFromType(Stone::Type type)
{
    return string("stones/") + getNameFromType(type) + ".png";
}

bool Stone::setSpeed(float newSpeed, float randMin, float randMax)
{
    auto pBody = getPhysicsBody();

    if (pBody) {
        log("set pbody");
        _speed = newSpeed;
        const float randDt = cocos2d::random(randMin, randMax);
        pBody->setVelocity({0, -((DesignResolSize.height / 8) * _speed * randDt)});
        return true;
    }

    return false;
}

bool Stone::setAngular(float angular)
{
    auto pBody = getPhysicsBody();

    if (pBody) {
        pBody->setAngularVelocity(angular);
        return true;
    }

    return false;
}

bool Stone::setRandAngular(float min, float max)
{
    return setAngular(cocos2d::random(min, max));
}
