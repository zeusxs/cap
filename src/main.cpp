#include <string>
#include <iostream>
#include <exception>

#include "tclap/CmdLine.h"
#include "captor.h"

std::string getip(const std::string &address)
{
    auto iter = address.find(":");

    return address.substr(0, iter);
}

unsigned short getport(const std::string &address)
{
    auto iter = address.find(":");

    std::string port = address.substr(++iter, std::string::npos);

    return (unsigned short)std::stoul(port);
}

int main(int argc, char *argv[]) {
    TCLAP::CmdLine cmd("cap -d [device] -f [filter rules] -i [ip] -p [port]", ' ', "1.0");

    TCLAP::ValueArg<std::string> device("d", "device", "capture net interface device eg: 'eth0', 'eth1', 'lo'", true, "", "str");
    TCLAP::ValueArg<std::string> filter("f", "filter", "capture filter filter rule eg: 'tcp port 8000'", true, "", "str");
    TCLAP::ValueArg<std::string> ip("i", "ip", "output ip", true, "", "str");
    TCLAP::ValueArg<unsigned short> port("p", "port", "output port", true, 0, "int");

    cmd.add(port);
    cmd.add(ip);
    cmd.add(filter);
    cmd.add(device);

    try {
        cmd.parse(argc, argv);
    } catch (const TCLAP::ArgException &e) {
        std::cerr << e.error() << std::endl;
        return 1;
    }
    
    try {
        Captor cap(device.getValue(), ip.getValue(), port.getValue());
        cap.setFilter(filter.getValue());
        cap.start();
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
