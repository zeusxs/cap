#pragma once

#include "tclap/CmdLine.h"

class Command {
public:
    Command();
    
    void parse(int argc, char **argv);
    
    std::string device();
    std::string filter();
    std::string ip();
    unsigned short port();

private:
    TCLAP::CmdLine cmd;

    /* capture device */
    TCLAP::ValueArg<std::string> DEVICE_;
    
    /* capture port */
    TCLAP::ValueArg<std::string> DIRECTION_;
};
