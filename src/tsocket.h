#pragma once

#include <string>

namespace net {

class TSocket {
public:
    TSocket();

    void setflag(int flag);
    
    void unsetflag(int flag);

    void setblock(bool on);

    void setkeepalive();

    void connect(const std::string &ip, const unsigned short port);

    void send(const std::string &data);

    std::string recv(size_t len);

    std::string recvall();

    int fileno();

    void close();
private:
    int fd_;
};

};
