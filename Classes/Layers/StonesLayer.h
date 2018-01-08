#ifndef __STONES_LAYER_H__
#define __STONES_LAYER_H__

#include "cocos2d.h"
#include "Objects/Stone.h"
#include <list>
#include <chrono>
#include <map>

USING_NS_CC;
using std::map;
using std::list;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::time_point;
using std::make_pair;

static constexpr float SPEED = 1.f;

class StonesLayer : public Layer
{
public:
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(StonesLayer);

private:
    float _runningSpeed = SPEED;
    steady_clock::time_point timeLastAddingStone = steady_clock::now();
    float _timeBeginForStart = 1.f;

private:
    list<Stone *> _stones;

private:
    enum class Side {
        Undefined, Left, Center, Right
    };
    map<Side, int> _countStonedInSide;
    Side lastSide = Side::Undefined;

private:
    void schCallbackControllerStones(float dt);
    void addingSpeed(float dt);
    void removeStonesController();
    void executeAfterRemoveStone();
    void executeAfterAddStone();
    void calculatorStonesInSidesController();
    void addStonesController();
    void initMapCounterStones();

    /* return stone which was added */
    Stone *addStone();

    Side getSideFromPosition(float positionX);

public:
    inline float getRunningSpeed() const
    { return _runningSpeed; }

    inline void setRunningSpeed(float count)
    { _runningSpeed = count; }

};

#endif // __STONES_LAYER_H__
