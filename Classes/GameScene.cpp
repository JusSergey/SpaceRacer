#include "GameScene.h"
#include "ZOrderLevels.h"

static constexpr int COUNT_UPDATES_ACCEL = 10;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!Scene::initWithPhysics())
        return false;

//    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);
    getPhysicsWorld()->setGravity(Vec2::ZERO);

    _visibleSize = Director::getInstance()->getVisibleSize();

    initBackgroundLayer();
    initStoneLayer();
    initAirPlaneLayer();
    initAccel();

#ifdef PLATFORM_DESKTOP
    initKeyboard();
#endif

    return true;
}

void GameScene::initBackgroundLayer()
{
    _backLayer = BackgroundLayer::create();
    _backLayer->setPosition(Vec2::ZERO);
    addChild(_backLayer, LEVELS::BACKGROUND_LAYER);
    _backLayer->startRunningSky();
}

void GameScene::initStoneLayer()
{
    _stoneLayer = StonesLayer::create();
    _stoneLayer->setRunningSpeed(1.8);
    _stoneLayer->setPosition(Vec2::ZERO);
    addChild(_stoneLayer, LEVELS::STONE_LAYER);
}

void GameScene::initAirPlaneLayer()
{
    _airPlaneLayer = AirPlaneLayer::create();
    _airPlaneLayer->setPosition(Vec2::ZERO);
    addChild(_airPlaneLayer, LEVELS::PLAYER_LAYER);
}

void GameScene::initKeyboardController()
{
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed;
    keyListener->onKeyReleased;

    _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void GameScene::initAccel()
{
    Device::setAccelerometerEnabled(true);
    Device::setAccelerometerInterval(1.f / COUNT_UPDATES_ACCEL);

    auto event = EventListenerAcceleration::create([this](Acceleration *accel, Event *) {
        _airPlaneLayer->accelerationEvent(accel);
    });

    _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
}

#ifdef PLATFORM_DESKTOP
void GameScene::initKeyboard()
{
    static const char *nameSch = "keys";

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *) -> void {

        schedule([=](float){
            Acceleration accel;
            switch (code) {
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                accel.x = -0.5;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                accel.x = 0.5;
                break;
            default:
                accel.x = 0.;
                break;
            }
            if (std::abs(accel.x) > 0.1)
                _airPlaneLayer->accelerationEvent(&accel);

        }, 1.f / COUNT_UPDATES_ACCEL, nameSch);
    };
    keyListener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event *) -> void {
        unschedule(nameSch);
        _airPlaneLayer->stopPlayer();
    };

    _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}
#endif
