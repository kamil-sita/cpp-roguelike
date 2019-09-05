#ifndef ROGUELIKE_ROOMGROUP_H
#define ROGUELIKE_ROOMGROUP_H

#include <cmath>
#include "Room.h"

class RoomGroup {
    std::vector<Room> rooms;
    double distance(sf::Vector2<double> a, sf::Vector2<double> b);
public:
    RoomGroup(const RoomGroup& r1, const RoomGroup& r2);
    RoomGroup(const Room& r);

    sf::Vector2<double> getApproximateCenterOfRooms() const;

    double getApproximateDistance(const RoomGroup& rc);

    std::pair<Room, Room> getClosestRooms(const RoomGroup& rc);
};


#endif
