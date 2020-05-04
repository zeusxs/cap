#pragma once

#include "tsocket.h"
#include "socket_exception.h"

class Channel {
public:
    Channel(const std::string &ip, const unsigned short port);
    
    bool open();

    void close();

    bool put(const std::string &data);
    std::string get();

private:
    std::string ip_;
    unsigned short port_;
    net::TSocket sock_;
};
