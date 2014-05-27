LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libprotobuf-c-text
LOCAL_MODULE_TAGS := optional
#LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_CLASS := STATIC_LIBRARIES

LOCAL_STATIC_LIBRARIES := libc \
	libprotobuf-c

LOCAL_SRC_FILES := protobuf-c-text/generate.c
#$(call all-c-files-under,protobuf-c-text)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/protobuf-c-text

LOCAL_C_FLAGS := -std=c99 -pedantic -Wall -DHAVE_PROTOBUF_C_MESSAGE_CHECK

# Use this variable when building with NDK out of tree
#LOCAL_EXPORT_C_INCLUDES += $(LOCAL_PATH)
#LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)
LOCAL_COPY_HEADERS_TO := google/protobuf-c
LOCAL_COPY_HEADERS := protobuf-c-text/protobuf-c-text.h

# compile parse.re to parse.c using re2c
intermediates := $(local-intermediates-dir)
GEN := $(intermediates)/parse.c
$(GEN): PRIVATE_CUSTOM_TOOL = re2c -s -o $@ $<
$(GEN): $(LOCAL_PATH)/protobuf-c-text/parse.re
	$(transform-generated-source)
LOCAL_GENERATED_SOURCES += $(GEN)

include $(BUILD_STATIC_LIBRARY)

