#include <exception>
#include <string>

namespace net {
class SocketException : public std::exception {
public:
    SocketException(std::string apiname, std::string error) {
        message = "[SocketException]" + apiname + ":" + error;
    }

    virtual const char *what() const throw() {
        return message.c_str();
    }

protected:
    std::string message;
};

class ConnectException : public SocketException {
public:
    ConnectException(std::string apiname, std::string error) : 
        SocketException(apiname, error) {
        message = "[ConnectException]" + apiname + ":" + error;
    }
};

};
