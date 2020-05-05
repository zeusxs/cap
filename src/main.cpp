#include <string>
#include <iostream>
#include <exception>

#include "command.h"
#include "captor.h"

int main(int argc, char *argv[]) {
    Command cmd;
    
    std::string device;
    std::string filter;
    std::string ip;
    unsigned short port;

    try {
        cmd.parse(argc, argv);
        device = cmd.device();
        filter = cmd.filter();
        ip = cmd.ip();
        port = cmd.port();
    } catch (const TCLAP::ArgException &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    try {
        Captor cap(cmd.device(), cmd.ip(), cmd.port());
        cap.setFilter(cmd.filter());
        cap.start();
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
