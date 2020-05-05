#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <string>
#include <regex>

#include "tclap/CmdLine.h"
#include "command.h"

Command::Command():
    cmd("cap -d [device] [direction]", ' ', "1.0"),
    DEVICE_("d", "device", "capture net interface device\n\teg: 'eth0', 'eth1', 'lo'", true, "", "str"),
    DIRECTION_("i", "direction", "traffic flow direction\n\teg: 8000-127.0.0.1:9000", true, "", "str")
{
    cmd.add(DEVICE_);
    cmd.add(DIRECTION_);
}

void Command::parse(int argc, char **argv) 
{
    cmd.parse(argc, argv);
}

std::string Command::device() {
    return DEVICE_.getValue();
}

std::string Command::filter() {
    std::regex express(R"((\d*)-(.*):(\d*))");
    std::smatch sm;
    bool success = std::regex_match(DIRECTION_.getValue(), sm, express);
    
    if (!success) {
        throw TCLAP::ArgException("The direction format is valid!", "ArgException");
    }
    std::ostringstream output;
    output << "tcp port " << sm[1];
    return output.str();
}

std::string Command::ip() {
    std::regex express(R"((\d*)-(.*):(\d*))");
    std::smatch sm;
    bool success = std::regex_match(DIRECTION_.getValue(), sm, express);
    
    if (!success) {
        throw TCLAP::ArgException("The direction format valid!", "ArgException");
    }
    return sm[2];
}

unsigned short Command::port() {

    std::regex express(R"((\d*)-(.*):(\d*))");
    std::smatch sm;
    bool success = std::regex_match(DIRECTION_.getValue(), sm, express);
    
    if (!success) {
        throw TCLAP::ArgException("The direction format valid!", "ArgException");
    }
    return (unsigned short)std::stoul(sm[3]);
}
