/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** PlayMenu.hpp
*/

#ifndef RTYPE_PLAYMENU_HPP
#define RTYPE_PLAYMENU_HPP

#include <utility>
#include <vector>
#include "Component/Button.hpp"
#include "Component/Image.hpp"
#include "IScene.hpp"

namespace Client {
    class PlayMenu : public IScene {
    public:
        PlayMenu(Client::IScene *prev = nullptr);
        ~PlayMenu() override;
        void event(Client::IScene *&self, sf::Event &event, Client::KeyBind &keyBind, Client::Network &network, Client::Window &window) override;
        void update(Client::IScene *&self, Client::Network &network, Client::Window &window) override;
        void render(Client::Window &window) override;
    private:
        void back(Client::IScene *&self);
        Client::IScene *_prev;
        std::vector<Client::Image *> _images;
        std::vector<std::pair<Client::Button *, void (Client::PlayMenu::*)(Client::IScene *&)>> _buttons;
        sf::Clock _clock;
        float _quitRefTime;
    };
}

#endif