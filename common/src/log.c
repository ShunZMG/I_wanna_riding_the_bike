#include "log.h"

inline void log_info(const char* msg){
    if(__loglevel >= LOG_INFO)
        printf("[INFO]:%s\n", msg);
}

inline void log_warn(const char* msg){
    if(__loglevel >= LOG_WARN)
        printf("[WARN]:%s\n", msg);
}

inline void log_error(const char* msg){
    if(__loglevel >= LOG_ERROR){
        #if defined(MSGBOX_LOG)
        if(SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", msg, NULL) == -1)
            log_debug("message box called failed");
        #endif
        printf("[ERROR]:%s\n", msg);
    }
}

inline void log_debug(const char* msg){
    if(__loglevel >= LOG_DEBUG)
        printf("[DEBUG]:%s\n", msg);
}

void setLogLevel(log_level level){
    if(level!=LOG_WARN && level!=LOG_INFO && level!=LOG_DEBUG && level!=LOG_ERROR && level!=LOG_OFF)
        printf("[LOG SYSTEM ERROR]: set log level error\n");
    else
        __loglevel = level;
}

log_level getLogLevel(){
    return __loglevel;
}