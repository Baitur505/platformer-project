#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "globals.h"
#include "player_controller.h"

class Player {
public:
    static Player& get_instance() {
        static Player instance;
        return instance;
    }

    // Basic stat methods
    void reset_player_stats() {
        lives = MAX_LIVES;
        level_scores.fill(0);
    }

    void increment_score() {
        PlaySound(coin_sound);
        level_scores[level_index]++;
    }

    int get_total_player_score() const {
        int sum = 0;
        for (int score : level_scores)
            sum += score;
        return sum;
    }

    int get_player_lives() const { return lives; }


    void Player::move_player_horizontally(float delta) {
        PlayerController::move_horizontally(*this, delta);
    }

    void Player::update_player_gravity() {
        PlayerController::update_gravity(*this);
    }

    void Player::update_player() {
        PlayerController::update(*this);
    }

    void Player::spawn_player() {
        y_velocity = 0;

        for (size_t row = 0; row < current_level.rows; ++row) {
            for (size_t column = 0; column < current_level.columns; ++column) {
                char cell = get_level_cell(row, column);
                if (cell == PLAYER) {
                    position.x = column;
                    position.y = row;
                    set_level_cell(row, column, AIR);
                    return;
                }
            }
        }
    }

    void Player::kill_player() {
        PlaySound(player_death_sound);
        game_state = DEATH_STATE;
        lives--;
        level_scores[level_index] = 0;
    }

    Vector2 get_player_pos() const { return position; }
    void set_position(Vector2 pos) { position = pos; }

    float get_player_y_velocity() const { return y_velocity; }
    void set_player_y_velocity(float vel) { y_velocity = vel; }

    bool is_player_on_ground() const { return on_ground; }
    void set_player_on_ground(bool val) { on_ground = val; }

    bool is_looking_forward() const { return looking_forward; }
    void set_looking_forward(bool val) { looking_forward = val; }

    bool is_moving() const { return moving; }
    void set_moving(bool val) { moving = val; }

    int get_time_to_coin_counter() const { return time_to_coin_counter; }
    void increment_time_to_coin_counter(int v) { time_to_coin_counter += v; }
    void reset_time_to_coin_counter() { time_to_coin_counter = 0; }

private:
    Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    float y_velocity = 0;
    Vector2 position = {0, 0};

    bool on_ground = false;
    bool looking_forward = true;
    bool moving = false;

    int lives = MAX_LIVES;
    std::array<int, LEVEL_COUNT> level_scores{};
    int time_to_coin_counter = 0;

    static constexpr int MAX_LIVES = 3;
};
inline Player::Player() {}

#endif
