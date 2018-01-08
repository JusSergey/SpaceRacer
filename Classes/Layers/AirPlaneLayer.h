#ifndef __AIR_PLANE_LAYER__
#define __AIR_PLANE_LAYER__

#include "cocos2d.h"
#include "Objects/AirPlane.h"
USING_NS_CC;

class AirPlaneLayer : public Layer {
public:
    virtual bool init();
    CREATE_FUNC(AirPlaneLayer);

    void accelerationEvent(Acceleration *accel);
    void stopPlayer();

private:
    void initAirPlanePlayer();

private:
    AirPlane *_player;

};

#endif // __AIR_PLANE_LAYER__
