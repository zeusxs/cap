#include <string>
#include <sstream>

#include <tins/tins.h>
#include <tins/tcp_ip/stream_follower.h>

#include "dispatch.h"

using Tins::Sniffer;
using Tins::TCPIP::StreamFollower;
using Tins::TCPIP::Stream;

class Captor {

public:
    Captor(const std::string &device, const std::string &ip, const unsigned short port);
    ~Captor();

    void setFilter(const std::string &filter);
    void start();

    static std::string streamClientEndpoint(Stream &stream);
    static std::string streamServerEndpoint(Stream &stream);
    static std::string streamIdentifier(Stream &stream);

    static void onNewStream(Captor *pthis, Stream &stream);
    static void onCapClientData(Captor *pthis, Stream &stream);
    static void onCapServerData(Captor *pthis, Stream &stream);
    static void onEndStream(Captor *pthis, Stream &stream);

    Dispatch dispatch_;

private:
    Sniffer sniff_;
    StreamFollower follower_;
};
