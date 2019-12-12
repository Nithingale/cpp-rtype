/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** HandleConnectionSystem.hpp
*/

#ifndef RTYPE_HANDLECONNECTIONSYSTEM_HPP
#define RTYPE_HANDLECONNECTIONSYSTEM_HPP

#include "ASystem.hpp"

namespace ecs
{
    class HandleConnectionSystem : public ASystem {
    public:
        explicit HandleConnectionSystem(std::shared_ptr<EntityAdmin> admin);
        void update(float dt) override;
    };
}

#endif