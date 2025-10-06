#pragma once
#include "dominoBag.h"
#include <optional>

enum class Compatibility {
    NotCompatible,
    Right,
    Left,
    Both
};

class DominoGame {
private:
    int left_end;
    int right_end;
    DominoBag dealer;
    int counter;
    bool game_started;
    int n_value;

public:
    explicit DominoGame(int n);

    int play_game();
    Compatibility is_compatible(const DominoTile& tile) const;

    int get_counter() const { return counter; }
    void reset();
};