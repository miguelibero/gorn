LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gorn

BASE_PATH := $(LOCAL_PATH)/../../..
PLATFORM_DIR_FILTER := ! \( -path \*/platform/\* ! -regex .\*/platform/android/\*.\* \)

#Recursive include all .cpp files in the SRC directory
FILE_LIST := $(shell find $(BASE_PATH)/src -type f -iname \*.cpp $(PLATFORM_DIR_FILTER) )
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(shell find $(BASE_PATH)/lib/platform/android/jniobject -type f -iname \*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

INCLUDES += $(BASE_PATH)/src
INCLUDES += $(BASE_PATH)/lib
INCLUDES += $(BASE_PATH)/lib/platform/android

CFLAGS := -DGORN_PLATFORM_ANDROID -DGLM_FORCE_RADIANS
CPPFLAGS := -fexceptions -std=c++11 -Wno-extern-c-compat

DEBUG := $(strip $(NDK_DEBUG))
ifeq ($(DEBUG),1)
	CFLAGS += -DANDROID_DEBUG_LEVEL=ANDROID_LOG_VERBOSE -DDEBUG
	CFLAGS += -O0 -g -ggdb
else
	CFLAGS += -DNDEBUG
	CFLAGS += -Ofast
endif

LOCAL_C_INCLUDES += $(INCLUDES)
LOCAL_CFLAGS += $(CFLAGS)
LOCAL_CPPFLAGS += $(CPPFLAGS)
LOCAL_EXPORT_C_INCLUDES += $(INCLUDES)
LOCAL_EXPORT_CFLAGS += $(CFLAGS)
LOCAL_EXPORT_CPPFLAGS += $(CPPFLAGS)

LOCAL_EXPORT_LDLIBS := -llog -lGLESv2 -lEGL -landroid -lz

include $(BUILD_STATIC_LIBRARY)
