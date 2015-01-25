LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := gorn_triangle

BASE_PATH := $(LOCAL_PATH)/../../..
PLATFORM_DIR_FILTER := ! \( -path \*/platform/\* ! -regex .\*/platform/android/\*.\* \)
FILE_LIST := $(shell find $(BASE_PATH) -type f -iname \*.cpp $(PLATFORM_DIR_FILTER) )
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_WHOLE_STATIC_LIBRARIES := gorn gorn_queue

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(BASE_PATH)/../..)
$(call import-module,proj.android/gorn/jni)
