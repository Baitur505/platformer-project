#ifndef LEVEL_CONTROLLER_H
#define LEVEL_CONTROLLER_H

#include "globals.h"
#include "player.h"
#include "raylib.h"

class LevelController {
public:
    struct Level {
        size_t rows;
        size_t columns;
        char* data;
    };

    static LevelController& get_instance();

    void reset_level_index();
    void load_level(int offset);
    void unload_level();

    bool is_inside_level(int row, int column) const;
    bool is_colliding(Vector2 pos, char look_for) const;
    char& get_collider(Vector2 pos, char look_for);

    char& get_cell(size_t row, size_t column);
    void set_cell(size_t row, size_t column, char value);

private:
    LevelController() = default;
    ~LevelController() = default;

    LevelController(const LevelController&) = delete;
    LevelController& operator=(const LevelController&) = delete;

    void copy_level_data(const Level& source);

    char* level_data = nullptr;
};

#endif // LEVEL_CONTROLLER_H
