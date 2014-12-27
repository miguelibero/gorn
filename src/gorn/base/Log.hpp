

#define LOG_TAG "gorn"

#ifdef __ANDROID__

#include <android/log.h>

#define  LogDebug(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LogError(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#else

#define  LogDebug(...)  printf(__VA_ARGS__)
#define  LogError(...)  printf(__VA_ARGS__)


#endif