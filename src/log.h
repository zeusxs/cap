#pragma once

#include <mutex>

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"


class Log {
public:
    static Log *getInstance();

    std::shared_ptr<spdlog::logger> getCapture();

private:
    static std::mutex mtx_;
    static Log *pinstance_;
    Log();
  
    std::shared_ptr<spdlog::logger> capture_;
};

/* capture DEBUG */
template<typename... Args>
inline void CAP_D(const char *format, const Args&... args) {
    Log::getInstance()->getCapture()->debug(format, args...);
}

/* capture INFO */
template<typename... Args>
inline void CAP_I(const char *format, const Args&... args) {
    Log::getInstance()->getCapture()->info(format, args...);
}

/* capture WARN */
template<typename... Args>
inline void CAP_W(const char *format, const Args&... args) {
    Log::getInstance()->getCapture()->warn(format, args...);
}

/* capture ERROR */
template<typename... Args>
inline void CAP_E(const char *format, const Args&... args) {
    Log::getInstance()->getCapture()->error(format, args...);
}

/* capture CRITICAL */
template<typename... Args>
inline void CAP_C(const char *format, const Args&... args) {
    Log::getInstance()->getCapture()->critical(format, args...);
}
