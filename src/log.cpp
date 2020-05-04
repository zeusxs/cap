#include "log.h"

std::mutex Log::mtx_;
Log *Log::pinstance_ = nullptr;

Log::Log()
{
    spdlog::flush_every(std::chrono::seconds(1));
    capture_ = spdlog::basic_logger_mt<spdlog::async_factory>("capture", "capture.log");
    capture_->flush_on(spdlog::level::err);
}

Log *Log::getInstance()
{
    if (pinstance_ == nullptr) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (pinstance_ == nullptr) {
            pinstance_ = new Log();
        }
    }

    return pinstance_;
}

std::shared_ptr<spdlog::logger> Log::getCapture()
{
    return capture_;
}
