LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gorn

BASE_PATH := $(LOCAL_PATH)/../../..
PLATFORM_DIR_FILTER := ! \( -path \*/platform/\* ! -regex .\*/platform/android/\*.\* \)

#Recursive include all .cpp files in the SRC directory
FILE_LIST := $(shell find $(BASE_PATH)/src -type f -iname \*.cpp $(PLATFORM_DIR_FILTER) )
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(shell find $(BASE_PATH)/lib/platform/android/jniobject -type f -iname \*.ccp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES += $(BASE_PATH)/src
LOCAL_C_INCLUDES += $(BASE_PATH)/lib
LOCAL_C_INCLUDES += $(BASE_PATH)/lib/platform/android

LOCAL_CFLAGS := -DGORN_PLATFORM_ANDROID -DGLM_FORCE_RADIANS
LOCAL_CPPFLAGS := -fexceptions -std=c++11

DEBUG := $(strip $(NDK_DEBUG))
ifeq ($(DEBUG),1)
	LOCAL_EXPORT_CFLAGS += -DANDROID_DEBUG_LEVEL=ANDROID_LOG_VERBOSE -DDEBUG
	LOCAL_EXPORT_CFLAGS += -O0 -g -ggdb
else
	LOCAL_EXPORT_CFLAGS += -DNDEBUG
	LOCAL_EXPORT_CFLAGS += -Ofast
endif

LOCAL_WHOLE_STATIC_LIBRARIES := gorn

LOCAL_LDLIBS := -llog -lGLESv2 -landroid -lz

include $(BUILD_SHARED_LIBRARY)
