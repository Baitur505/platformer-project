#include "level_controller.h"

LevelController& LevelController::get_instance() {
    static LevelController instance;
    return instance;
}

LevelController::~LevelController() {
    unload_level(); // Ensure cleanup on destruction
}

void LevelController::reset_level_index() {
    level_index = 0;
}

bool LevelController::is_inside_level(int row, int column) const {
    return row >= 0 && row < current_level.rows &&
           column >= 0 && column < current_level.columns;
}

bool LevelController::is_colliding(Vector2 pos, char look_for) const {
    Rectangle entity_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    // Check tiles
    for (int row = static_cast<int>(pos.y) - 1; row <= static_cast<int>(pos.y); ++row) {
        for (int column = static_cast<int>(pos.x) - 1; column <= static_cast<int>(pos.x); ++column) {
            if (!is_inside_level(row, column)) continue;

            char cell = current_level.data[row * current_level.columns + column];
            if (cell == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(entity_hitbox, block_hitbox)) {
                    return true;
                }
            }
        }
    }
    return false;
}

char& LevelController::get_collider(Vector2 pos, char look_for) {
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    for (int row = static_cast<int>(pos.y) - 1; row <= static_cast<int>(pos.y); ++row) {
        for (int column = static_cast<int>(pos.x) - 1; column <= static_cast<int>(pos.x); ++column) {
            if (!is_inside_level(row, column)) continue;

            char& cell = current_level.data[row * current_level.columns + column];
            if (cell == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return cell;
                }
            }
        }
    }

    return current_level.data[static_cast<int>(pos.y) * current_level.columns + static_cast<int>(pos.x)];
}

void LevelController::copy_level_data(const Level& source) {
    size_t size = source.rows * source.columns;
    level_data = new char[size];

    for (size_t i = 0; i < size; ++i) {
        level_data[i] = source.data[i];
    }

    current_level = {source.rows, source.columns, level_data};
}

void LevelController::load_level(int offset) {
    level_index += offset;

    if (level_index >= LEVEL_COUNT) {
        game_state = VICTORY_STATE;
        create_victory_menu_background();
        level_index = 0;
        return;
    }

    unload_level();

    Player::get_instance().spawn_player();
    EnemiesController::get_instance().spawn_enemies(); // spawn entities for current level

    derive_graphics_metrics_from_loaded_level();

    timer = MAX_LEVEL_TIME; // reset timer
}

void LevelController::unload_level() {
    delete[] level_data;
    level_data = nullptr;
}

char& LevelController::get_cell(size_t row, size_t column) {
    return current_level.data[row * current_level.columns + column];
}

void LevelController::set_cell(size_t row, size_t column, char value) {
    current_level.data[row * current_level.columns + column] = value;
}
