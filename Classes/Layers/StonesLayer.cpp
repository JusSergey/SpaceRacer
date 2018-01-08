#include "StonesLayer.h"
#include "Constants.h"
#include <vector>
#include <chrono>
#include <ratio>
using std::vector;
using namespace std;

// on "init" you need to initialize your instance
bool StonesLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    initMapCounterStones();

    schedule(schedule_selector(StonesLayer::schCallbackControllerStones), 1.f / 5);

    return true;
}

void StonesLayer::schCallbackControllerStones(float dt)
{
    removeStonesController();
    addStonesController();
    calculatorStonesInSidesController();
    addingSpeed(dt);
}

void StonesLayer::addingSpeed(float dt)
{
    _runningSpeed = _timeBeginForStart / sqrt(_timeBeginForStart / 8);

    _timeBeginForStart += dt/300;
}

void StonesLayer::removeStonesController()
{
    for (auto iter = _stones.begin(); iter != _stones.end(); ++iter) {
        const Vec2 &pos = (*iter)->getPosition();
        const Size &size= (*iter)->getContentSize();

        if((pos.x + size.width) < 0 ||
           (pos.x - size.width) > DesignResolSize.width ||
           (pos.y + size.width) < 0)
        {
            auto tmp = iter;
            ++iter;
            (*tmp)->removeFromParentAndCleanup(true);
            log("remove stone[0x%x]", *tmp);
            _stones.erase(tmp);
            break;
        }
    }
    executeAfterRemoveStone();
}

void StonesLayer::executeAfterRemoveStone()
{
}

void StonesLayer::executeAfterAddStone()
{
}

void StonesLayer::calculatorStonesInSidesController()
{
    initMapCounterStones();

    for (Stone *stone : _stones) {
        ++_countStonedInSide[getSideFromPosition(stone->getPositionX())];
    }
}

void StonesLayer::addStonesController()
{
    if (duration_cast<milliseconds>(steady_clock::now() - timeLastAddingStone).count() > (3000.f/_runningSpeed)) {
        timeLastAddingStone = steady_clock::now();
        lastSide = getSideFromPosition(addStone()->getPositionX());
        executeAfterAddStone();
    }
}

void StonesLayer::initMapCounterStones()
{
    _countStonedInSide.clear();
    _countStonedInSide.insert({
            make_pair(Side::Left,   0),
            make_pair(Side::Center, 0),
            make_pair(Side::Right,  0)
        });
}

Stone *StonesLayer::addStone()
{
    Stone *stone = Stone::createRandom();

    std::pair<Side, int> nextStoneSize {Side::Undefined, INT32_MAX};
    for (auto p : _countStonedInSide)
        if (p.second < nextStoneSize.second && p.first != lastSide)
            nextStoneSize = p;

    float stonePosX = 0;
    switch (nextStoneSize.first) {
    case Side::Left: stonePosX  =cocos2d::random(0.f, DesignResolSize.width*0.333f); break;
    case Side::Center: stonePosX=cocos2d::random(DesignResolSize.width*0.333f, DesignResolSize.width*0.666f); break;
    case Side::Right: stonePosX =cocos2d::random(DesignResolSize.width*0.666f, DesignResolSize.width*1.f); break;
    default: log("undef behav");
    }

    const Vec2 pos(stonePosX, DesignResolSize.height + stone->getContentSize().height);
    log("add stone [%f, %f]", pos.x, pos.y);

    stone->setPosition(pos);

    addChild(stone);
    stone->setRandAngular();
    stone->setSpeed(_runningSpeed, 0.8f, 1.2f);

    _stones.push_back(stone);

    lastSide = nextStoneSize.first;

    return stone;
}

StonesLayer::Side StonesLayer::getSideFromPosition(float positionX)
{
    if (positionX < DesignResolSize.width * 0.333f) return Side::Left;
    if (positionX > DesignResolSize.width * 0.666f) return Side::Right;

    return Side::Center;
}
