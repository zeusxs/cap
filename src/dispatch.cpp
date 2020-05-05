#include <utility>
#include "dispatch.h"

Dispatch::Dispatch(const std::string &ip, const unsigned short port):
    ip_(ip), port_(port)
{
}

void Dispatch::dispatch(const std::string &stream_id, const std::string &payload)
{
    auto iter = channel_hash_.find(stream_id);

    if (iter != channel_hash_.end()) {
        bool success = iter->second->put(payload);
        if (!success) {
            closeChannel(stream_id);
        }
    }
}

void Dispatch::openChannel(const std::string &stream_id)
{
    Channel *channel = new Channel(ip_, port_);
    
    if (channel == nullptr)
        return;
    
    auto retval = channel_hash_.insert(std::make_pair(stream_id, channel));
    
    if (retval.second) {
        bool success = channel->open();
        if (!success) {
            closeChannel(stream_id);
        }
    }
}

void Dispatch::closeChannel(const std::string &stream_id)
{
    auto iter = channel_hash_.find(stream_id);

    if (iter != channel_hash_.end()) {
        iter->second->close();
        channel_hash_.erase(iter);
    }
}
