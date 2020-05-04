#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "tsocket.h"
#include "socket_exception.h"

using net::SocketException;
using net::ConnectException;

namespace net {

TSocket::TSocket() {
    fd_ = socket(PF_INET, SOCK_STREAM, 0);
}

void TSocket::setflag(int flag)
{
    int opt = fcntl(fd_, F_GETFL);

    if (opt == -1) {
        throw SocketException("fcntl", strerror(errno));
    }

    opt |= flag;

    int retval = fcntl(fd_, F_SETFL, opt);
    
    if (retval == -1) {
        throw SocketException("fcntl", strerror(errno));
    }
}

void TSocket::unsetflag(int flag)
{
    int opt = fcntl(fd_, F_GETFL);

    if (opt == -1) {
        throw SocketException("fcntl", strerror(errno));
    }

    opt &= ~flag;

    int retval = fcntl(fd_, F_SETFL, opt);
    
    if (retval == -1) {
        throw SocketException("fcntl", strerror(errno));
    }
}

void TSocket::setblock(bool on)
{
    if (on) {
        unsetflag(O_NONBLOCK);
    } else {
        setflag(O_NONBLOCK);
    }
}

void TSocket::setkeepalive()
{
}

void TSocket::connect(const std::string &ip, const unsigned short port)
{
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    int retval = ::connect(fd_, (struct sockaddr*)&addr, sizeof(addr));
    if (retval == -1) {
        throw SocketException("connect", strerror(errno));
    }
}

void TSocket::send(const std::string &data) {
    size_t need = data.size();
    size_t nsend = 0;

    while (need != 0) {
        const char *buffer = data.c_str() + nsend;

        ssize_t retval = ::send(fd_, buffer, need, 0);
        
        if (retval == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                retval = 0;
            } else if (errno == ECONNRESET || errno == EISCONN) {
                throw ConnectException("send", strerror(errno));
            } else {
                throw SocketException("send", strerror(errno));
            }
        }

        need -= retval;
        nsend += retval;
    }
}

std::string TSocket::recv(size_t len) 
{
    static const size_t MAX_BUFFER_LEN = 1 << 16;
    static char buffer[MAX_BUFFER_LEN + 1] = {0};

    size_t need = len;
    size_t nread = 0;

    std::string data = "";

    while (need != 0) {
        ssize_t retval = ::recv(fd_, buffer, MAX_BUFFER_LEN, 0);

        if (retval == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                retval = 0;
            } else if (errno == ECONNREFUSED || errno == ENOTCONN) {
                throw ConnectException("recv", strerror(errno));
            } else {
                throw SocketException("recv", strerror(errno));
            }
        }
        
        buffer[retval] = '\0';
        data += buffer;
        need -= retval;
    }

    return data;
}

std::string TSocket::recvall()
{
    static const size_t MAX_BUFFER_LEN = 1 << 16;
    static char buffer[MAX_BUFFER_LEN + 1] = {0};

    std::string data = "";
    while (true) {
        ssize_t retval = ::recv(fd_, buffer, MAX_BUFFER_LEN, 0);

        if (retval == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            } else if (errno == ECONNREFUSED || errno == ENOTCONN) {
                throw ConnectException("recv", strerror(errno));
            } else {
                throw SocketException("recv", strerror(errno));
            }
        }
        
        buffer[retval] = '\0';
        data += buffer;
    }
    
    return data;
}

void TSocket::close() {
    ::close(fd_);
}

};

