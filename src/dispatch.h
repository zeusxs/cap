#include <string>
#include <unordered_map>

#include "channel.h"

class Dispatch {
public:
    Dispatch(const std::string &ip, const unsigned short port);

    void dispatch(const std::string &stream_id, const std::string &payload);

    void openChannel(const std::string &stream_id);

    void closeChannel(const std::string &stream_id);

private:
    std::string ip_;
    unsigned short port_;
    std::unordered_map<std::string, Channel*> channel_hash_;
};

