LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := app

BASE_PATH := $(LOCAL_PATH)/../../..
PLATFORM_DIR_FILTER := ! \( -path \*/platform/\* ! -regex .\*/platform/android/\*.\* \)

#Recursive include all .cpp files in the SRC directory
FILE_LIST := $(shell find $(BASE_PATH)/src -type f -iname \*.cpp $(PLATFORM_DIR_FILTER) )
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
#Compile entityx (maybe move to library)
FILE_LIST := $(shell find $(BASE_PATH)/lib/entityx -type f -iname \*.cc $(PLATFORM_DIR_FILTER) )
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

#Find all the headers directories inside SRC
LOCAL_C_INCLUDES += $(shell find $(BASE_PATH)/src -type d $(PLATFORM_DIR_FILTER) )
LOCAL_C_INCLUDES += $(BASE_PATH)/lib

LOCAL_CFLAGS := -DTARGET_OS_ANDROID
LOCAL_CPPFLAGS := -fexceptions -std=c++11 -gstabs+

DEBUG := $(strip $(NDK_DEBUG))
ifeq ($(DEBUG),1)
	LOCAL_EXPORT_CFLAGS += -DANDROID_DEBUG_LEVEL=ANDROID_LOG_VERBOSE -DDEBUG -DCOCOS2D_DEBUG=1
	LOCAL_EXPORT_CFLAGS += -O0 -g -ggdb
else
	LOCAL_EXPORT_CFLAGS += -DNDEBUG
	LOCAL_EXPORT_CFLAGS += -Ofast
endif

LOCAL_WHOLE_STATIC_LIBRARIES := app

LOCAL_LDLIBS := -llog -lGLESv2 -landroid -lz

include $(BUILD_SHARED_LIBRARY)
