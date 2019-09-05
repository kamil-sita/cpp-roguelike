#include "RoomGroup.h"

double RoomGroup::distance(sf::Vector2<double> a, sf::Vector2<double> b)  {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

RoomGroup::RoomGroup(const RoomGroup& r1, const RoomGroup& r2)  {
    for (const auto& room : r1.rooms) {
        rooms.push_back(room);
    }
    for (const auto& room : r2.rooms) {
        rooms.push_back(room);
    }
}

sf::Vector2<double> RoomGroup::getApproximateCenterOfRooms() const {

    double x = 0;
    double y = 0;
    for (const auto& room : rooms) {
        x += room.getPointInRoom().x;
        y += room.getPointInRoom().y;
    }
    x /= rooms.size();
    y /= rooms.size();
    return {x, y};
}

double RoomGroup::getApproximateDistance(const RoomGroup& rc)  {
    return distance(getApproximateCenterOfRooms(), rc.getApproximateCenterOfRooms());
}

std::pair<Room, Room> RoomGroup::getClosestRooms(const RoomGroup& rc)  {
    int closestLocal = 0;
    int closestOther = 0;
    double bestLength = std::numeric_limits<double>::max();

    for (int i = 0; i < rooms.size(); i++) {
        auto& r0 = rooms.at(i);
        for (int j = 0; j < rc.rooms.size(); j++) {
            auto& r1 = rc.rooms.at(j);
            double dist = distance({(double) r0.getPointInRoom().x, (double) r0.getPointInRoom().y}, {(double) r1.getPointInRoom().x, (double) r1.getPointInRoom().y});
            if (dist < bestLength) {
                closestLocal = i;
                closestOther = j;
            }
        }
    }

    return {rooms.at(closestLocal), rc.rooms.at(closestOther)};
}

RoomGroup::RoomGroup(const Room& r)  {
    rooms.push_back(r);
}