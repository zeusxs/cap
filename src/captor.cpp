#include <iostream>
#include <sstream>
#include <functional>

#include "log.h"
#include "captor.h"

using std::ostringstream;

using Tins::PDU;
using Tins::Sniffer;
using Tins::TCPIP::StreamFollower;
using Tins::TCPIP::Stream;

std::string Captor::streamClientEndpoint(Stream &stream)
{
    ostringstream output_;
    output_.clear();
    if (stream.is_v6()) {
        output_ << stream.client_addr_v6();
    } else {
        output_ << stream.client_addr_v4();
    }
    output_ << ":" << stream.client_port();

    return output_.str();
}

std::string Captor::streamServerEndpoint(Stream &stream)
{
    ostringstream output_;
    output_.clear();
    if (stream.is_v6()) {
        output_ << stream.server_addr_v6();
    } else {
        output_ << stream.server_addr_v4();
    }
    output_ << ":" << stream.server_port();

    return output_.str();
}

std::string Captor::streamIdentifier(Stream &stream)
{
    ostringstream output_;

    output_ << Captor::streamClientEndpoint(stream) << " >> " << Captor::streamServerEndpoint(stream);

    return output_.str();
}

Captor::Captor(const std::string &device, const std::string &outip, const unsigned short outport) : 
    sniff_(device), dispatch_(outip, outport)
{
    auto onNewStream_ = std::bind(Captor::onNewStream, this, std::placeholders::_1);
    follower_.new_stream_callback(onNewStream_);
}

Captor::~Captor()
{
}

void Captor::onNewStream(Captor *pthis, Stream &stream)
{
    std::string stream_id = Captor::streamIdentifier(stream);
    CAP_I("[+] new connection:{}", stream_id);

    auto onCapClientData_ = std::bind(Captor::onCapClientData, pthis, std::placeholders::_1);
    stream.client_data_callback(onCapClientData_);

    auto onCapServerData_ = std::bind(Captor::onCapServerData, pthis, std::placeholders::_1);
    stream.server_data_callback(onCapServerData_);

    auto onEndStream_ = std::bind(Captor::onEndStream, pthis, std::placeholders::_1);
    stream.stream_closed_callback(onEndStream_);

    pthis->dispatch_.openChannel(stream_id);
}

void Captor::onCapClientData(Captor *pthis, Stream &stream)
{
    std::string stream_id = Captor::streamIdentifier(stream);
    auto payload = stream.client_payload();
    std::string data(payload.begin(), payload.end());
    CAP_I("[~] {} cap data {} bytes", stream_id, data.size());
    pthis->dispatch_.dispatch(stream_id, data);
}

void Captor::onCapServerData(Captor *pthis, Stream &stream)
{
    std::string stream_id = Captor::streamIdentifier(stream);
    pthis->dispatch_.clean(stream_id);
}

void Captor::onEndStream(Captor *pthis, Stream &stream)
{
    std::string stream_id = Captor::streamIdentifier(stream);
    CAP_I("[-] end connetion:{}", stream_id);
    pthis->dispatch_.closeChannel(stream_id);
}

void Captor::setFilter(const std::string &filter)
{
    sniff_.set_filter(filter);
}

void Captor::start() {
    sniff_.sniff_loop([&](PDU& packet) {
        follower_.process_packet(packet);
        return true;
    });
}
