#ifndef __STONE_H__
#define __STONE_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using std::string;

class Stone : public Sprite {

public:
    enum Type : int {
        __Begin, Big = 1, Medium, Small, __End
    };

public:
    virtual bool init();
    static Stone *createRandom(float speed = 1);
    static Stone *create(Type type, float speed = 1);
    static void AsyncPreloadResource();
    static string getNameFromType(Type type);
    static string getPathFromType(Type type);

    bool setSpeed(float newSpeed, float randMin = 1, float randMax = 1);
    bool setAngular(float angular);
    bool setRandAngular(float min = -0.5f, float max = 0.5f);

protected:
    using Sprite::getPhysicsBody;

private:
    void initPhysicsBody();

private:
    Size _visibleSize;
    Type _type;
    float _speed;

public:
    inline Type getType() const
    { return _type; }

};

#endif // __STONE_H__
