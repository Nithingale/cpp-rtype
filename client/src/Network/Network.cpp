/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** Created by Arthamios, modified by Vleb
*/

#include <iostream>
#include "Network.hpp"

Client::Network::Network(const std::string &serverIp, const uint16_t &clientPort) :
    _socket(), _serverIp(serverIp), _active(true), _receiver(&Client::Network::receiver, this)
{
    _socket.bind(clientPort);
    this->send(Client::Packet(PACKET_CONNECT).getRaw());
    _receiver.launch();
}

Client::Network::~Network()
{
    _mutex.lock();
    _active = false;
    _mutex.unlock();
    this->send(Client::Packet(PACKET_DISCONNECT).getRaw());
    _receiver.terminate();
}

void Client::Network::send(const void *data, const uint64_t &size)
{
    _socket.send(data, size, _serverIp, SERVER_PORT);
}

void Client::Network::send(const Client::RawPacket *packet)
{
    this->send(packet, sizeof(Client::RawPacket));
}

std::pair<std::string, uint16_t> Client::Network::receive(void *data, const uint64_t &size, uint64_t &received)
{
    sf::IpAddress connectionAddr;
    uint16_t connectionPort;
    _socket.receive(data, size, received, connectionAddr, connectionPort);
    return std::pair<std::string, uint16_t>(connectionAddr.toString(), connectionPort);
}

Client::Packet Client::Network::findReceived(const uint32_t &id)
{
    for (int i = 0; i < _buffer.size(); i++) {
        if (_buffer[i].id == id) {
            Client::Packet packet(_buffer[i]);
            _buffer.erase(_buffer.begin() + i);
            return packet;
        }
    }
    throw std::runtime_error("\'Client::Network::findReceived\': No packet found.");
}

Client::Packet Client::Network::findReceived(const std::string &payload)
{
    for (int i = 0; i < _buffer.size(); i++) {
        std::string packetPayload;
        std::copy(_buffer[i].payload.begin(), _buffer[i].payload.end(), packetPayload.begin());
        if (packetPayload == payload) {
            Client::Packet packet(_buffer[i]);
            _buffer.erase(_buffer.begin() + i);
            return packet;
        }
    }
    throw std::runtime_error("\'Client::Network::findReceived\': Packet not found: " + payload);
}

void Client::Network::receiver()
{
    Client::RawPacket packet;
    while (_active) {
        uint64_t received = 0;
        do {
            this->receive(&packet, sizeof(Client::RawPacket), received);
        } while (!received || packet.magic != MAGIC_NB);
        std::cout << "Received: \'" << packet.payload.data() << "\' on ID: " << packet.id << std::endl;
        _mutex.lock();
        _buffer.push_back(packet);
        _mutex.unlock();
    }
}