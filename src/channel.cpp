#include <iostream>

#include "log.h"
#include "channel.h"

using net::SocketException;
using net::ConnectException;

Channel::Channel(const std::string &ip, const unsigned short port) :
    ip_(ip), port_(port)
{
    
}

bool Channel::open()
{
    try {
        sock_.connect(ip_, port_);
        sock_.setblock(false);
    } catch (const SocketException &e) {
        CAP_E(e.what());
        return false;
    }

    return true;
}

void Channel::close()
{
    sock_.close();
}

bool Channel::put(const std::string &data)
{
    try {
        sock_.send(data);
    } catch (const SocketException &e) {
        CAP_E(e.what());
        return false;
    }
    return true;
}

std::string Channel::get()
{
    std::string data = "";

    try {
        data = sock_.recvall();
    } catch (const SocketException &e) {
        CAP_E(e.what());
    }

    return data;
}

