/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** main.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include "INetwork.hpp"
#include "Network.hpp"
#include "Game/GameSprite.hpp"

void handle_events(Client::INetwork *network, sf::RenderWindow &window)
{
    sf::Event event{};

    while (window.pollEvent(event))
        if (event.type == sf::Event::Closed)
            window.close();
    static const std::vector<std::pair<sf::Keyboard::Key, std::string>> keys = {
        {sf::Keyboard::Left, "left"},
        {sf::Keyboard::Right, "right"},
        {sf::Keyboard::Up, "up"},
        {sf::Keyboard::Down, "down"},
        {sf::Keyboard::Space, "space"}
    };
    for (auto &key : keys)
        if (sf::Keyboard::isKeyPressed(key.first))
            network->send(key.second.c_str(), key.second.length());
}

void handleServerInstructions(Client::GameSprite &gameSprite, sf::RenderWindow &window, const char *data,
                              std::unordered_map<int, std::pair<Client::GameSprite::Type, sf::Sprite>> &toDraw)
{
    std::string dataStr(data);

    size_t semiColonIdx = dataStr.find(';');
    size_t dotIdx = dataStr.find(':');
    size_t comaIdx = dataStr.find(',');
    if (semiColonIdx == std::string::npos || dotIdx == std::string::npos || comaIdx == std::string::npos)
        return;

    int id = std::stoi(dataStr);
    std::string typeStr = dataStr.substr(semiColonIdx + 1, dotIdx - semiColonIdx - 1);
    const auto &pair = toDraw.find(id);
    if (pair == toDraw.end() || gameSprite.getType(typeStr) != pair->second.first)
        toDraw[id] = std::make_pair(gameSprite.getType(typeStr), gameSprite.getSpriteOfType(typeStr));
    toDraw.at(id).second.setPosition(std::stof(data + dotIdx + 1) * 10, std::stof(data + comaIdx + 1) * 10);
}

int display(Client::INetwork *network)
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "r_type");
    Client::GameSprite gameSprite;
    std::unordered_map<int, std::pair<Client::GameSprite::Type, sf::Sprite>> toDraw;
    char data[1024] = {0};

    window.setVerticalSyncEnabled(true);
    while (window.isOpen()) {
        handle_events(network, window);
        std::size_t received = 0;
        network->receive(&data, sizeof(data), received);
        window.clear();
        handleServerInstructions(gameSprite, window, data, toDraw);
        if (!toDraw.empty()) {
            for (const auto &sprite : toDraw)
                window.draw(sprite.second.second);
            window.display();
        }
    }
    delete network;
    std::cout << "client closed" << std::endl;
    return 0;
}

int main()
{
    Client::INetwork *network = new Client::Network("127.0.0.1", 1234);
    return display(network);
}
