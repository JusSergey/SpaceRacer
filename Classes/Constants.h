#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#define PLATFORM_DESKTOP
#endif

static const cocos2d::Size ReadResolSize(800, 1280);

#ifdef PLATFORM_DESKTOP
static const cocos2d::Size DesignResolSize(500, 700);
#else
static const cocos2d::Size DesignResolSize(ReadResolSize);
#endif

#endif // __CONSTANTS_H__
