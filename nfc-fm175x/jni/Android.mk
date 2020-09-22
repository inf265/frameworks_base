LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libnfc-fm175x
LOCAL_SRC_FILES := nfc-fm175x.cpp
#LOCAL_LDLIBS += -llog
include $(BUILD_SHARED_LIBRARY)
