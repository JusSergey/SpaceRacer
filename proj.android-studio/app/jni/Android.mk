LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH))

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
$(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
$(LOCAL_PATH)/../../../Classes/GameScene.cpp \
$(LOCAL_PATH)/../../../Classes/MyBodyParser.cpp \
$(LOCAL_PATH)/../../../Classes/Scenes/PresentScene.cpp \
$(LOCAL_PATH)/../../../Classes/Objects/Stone.cpp \
$(LOCAL_PATH)/../../../Classes/Layers/StonesLayer.cpp \
$(LOCAL_PATH)/../../../Classes/Layers/AirPlaneLayer.cpp \
$(LOCAL_PATH)/../../../Classes/Layers/BackgroundLayer.cpp \
$(LOCAL_PATH)/../../../Classes/Objects/AirPlane.cpp

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_WHOLE_STATIC_LIBRARIES += PluginAdMob
LOCAL_WHOLE_STATIC_LIBRARIES += sdkbox

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./sdkbox)
$(call import-module, ./pluginadmob)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
