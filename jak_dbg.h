#ifndef jak_dbg_h
#define jak_dbg_h

/**
 * @file
 * @brief Debugging macros
 *
 * This file contains useful macros for debugging purposes and for error handling
 * using the jump technique:
 * check if a condition is true else jump to the cleanup part of the function
 * (normally somewhere at the bottom)
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"




#include <stdio.h>
#include <errno.h>
#include <string.h>

#define jak_print(...) fprintf( stderr, ##__VA_ARGS__ )
#ifdef  JAK_DBG_IOS
#include <os/log.h>
#undef jak_print
#define jak_print(...) os_log(OS_LOG_DEFAULT, ##__VA_ARGS__)
#endif
#ifdef JAK_DBG_ANDROID
#include <android/log.h>
#ifndef JAK_DBG_ANDROID_TAG
#define JAK_DBG_ANDROID_TAG "jak_dbg"
#endif
#undef jak_print
#define jak_print(...) __android_log_print(ANDROID_LOG_ERROR, JAK_DBG_ANDROID_TAG, ##__VA_ARGS__)
#endif

#ifdef NDEBUG
#define debug(M)
#define debug_v(M, ...)
#else
#define debug(M) jak_print( "DEBUG %s:%d: " M "\n", __FILE__, __LINE__)
#define debug_v(M, ...) jak_print( "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno==0 ? "None" : strerror(errno))

#define log_err(M) jak_print( "[ERROR] (%s:%d) " M "\n", __FILE__, __LINE__)
#define log_err_v(M, ...) jak_print( "[ERROR] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define log_warn(M) jak_print( "[WARN] (%s:%d) " M "\n", __FILE__, __LINE__)
#define log_warn_v(M, ...) jak_print( "[WARN] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define log_info(M) jak_print( "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__)
#define log_info_v(M, ...) jak_print( "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define log_err_empty() jak_print( "[ERROR] (%s:%d: errno: %s)\n", __FILE__, __LINE__, clean_errno())

#define check(A, B) if(!(A)) { log_err_empty(); errno=0; goto B; }

#define check_msg(A, B, M ) if(!(A)) { \
	jak_print( "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno() ); \
			errno=0; goto B; }
#define check_msg_v(A, B, M, ...) if(!(A)) { \
	jak_print( "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__ ); \
			errno=0; goto B; }

#define check_r(A, B, R) if(!(A)) { res = R; log_err_empty(); errno=0; goto B; }
#define check_r_msg(A, B, R, M ) if(!(A)) { res = R; \
	jak_print( "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno() ); \
			errno=0; goto B; }
#define check_r_msg_v(A, B, R, M, ...) if(!(A)) { res = R; \
	jak_print( "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__ ); \
			errno=0; goto B; }


#ifdef JAK_DBG_TIME_PROFILING
#include <sys/time.h>
#define log_time() { \
        struct timeval tms; \
        gettimeofday(&tms, NULL); \
        long unsigned micros = tms.tv_sec * 1000000; \
        micros += tms.tv_usec; \
        debug_v( "Time was %lu", micros ); \
}
#endif




#pragma clang diagnostic pop
#pragma GCC diagnostic pop


#endif
