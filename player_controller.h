#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

class Player;

namespace PlayerController {
    void move_horizontally(Player& player, float delta);
    void update_gravity(Player& player);
    void update(Player& player);
}

#endif
