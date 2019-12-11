/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** EntityAdmin.hpp
*/

#ifndef RTYPE_ENTITYADMIN_HPP
#define RTYPE_ENTITYADMIN_HPP

#include <memory>
#include <tuple>
#include "Types.hpp"
#include "ObjectPool.hpp"
#include "IEntity.hpp"

#include "CNetwork.hpp"

namespace ecs
{
    struct EntityAdmin {
        EntityAdmin() :
            network(1234),
            currentId(0)
        {
        }

        Pools pools{};
        std::vector<std::unique_ptr<IEntity>> entities;
        CNetwork network;
        unsigned int currentId;
    };
}

#endif
