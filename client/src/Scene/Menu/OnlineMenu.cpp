/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** OnlineMenu.cpp
*/

#include "OnlineMenu.hpp"

Client::OnlineMenu::OnlineMenu(Client::IScene *prev) : _prev(prev), _components({
    new Client::Loader(1, 0, {0.5f, 0.5f}, "Menu/Loader.png"),
    new Client::Image(2, 0, {0.5f, 0.75f}, "Menu/WaitingMsg.png"),
    new Client::Fading(3, 1, 4.0f, 0.5f, true)
}), _clock(), _quitRefTime(-1), _next(nullptr)
{
}

Client::OnlineMenu::~OnlineMenu()
{
    delete _prev;
    for (auto &component : _components) {
        delete component;
    }
}

void Client::OnlineMenu::event(Client::IScene *&self, sf::Event &event, Client::KeyBind &keyBind, Client::Network &network, Client::Window &window)
{
}

void Client::OnlineMenu::update(Client::IScene *&self, Client::Network &network, Client::Window &window)
{
    for (auto &component : _components) {
        component->update(network, window);
    }
}

void Client::OnlineMenu::render(Client::Window &window)
{
    for (uint8_t layer = 0; layer < 255; layer++) {
        for (auto &component : _components) {
            component->render(window, layer);
        }
    }
}