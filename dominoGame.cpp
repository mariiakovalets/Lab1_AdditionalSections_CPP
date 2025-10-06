#include "dominoGame.h"

DominoGame::DominoGame(int n)
    : dealer(n), counter(0), game_started(false), n_value(n), right_end(n), left_end(n) {
}

void DominoGame::reset() {
    dealer.reset(n_value);
    counter = 0;
    game_started = false;
}

Compatibility DominoGame::is_compatible(const DominoTile& tile) const {
    if (!game_started) {
        return Compatibility::Left;
    }
    bool canLeft = (tile.a == left_end || tile.b == left_end);
    bool canRight = (tile.a == right_end || tile.b == right_end);
    
    if (canLeft && canRight) {
        return (left_end <= right_end) ? Compatibility::Left : Compatibility::Right;
    }
    if (canLeft) return Compatibility::Left;
    if (canRight) return Compatibility::Right;

    return Compatibility::NotCompatible;
}

int DominoGame::play_game() {
    reset();

    while (!dealer.empty()) {
        DominoTile tile = dealer();
        Compatibility comp = is_compatible(tile);

        if (comp == Compatibility::NotCompatible) {
            return counter;
        }

        if (!game_started) {
            left_end = tile.a;
            right_end = tile.b;
            game_started = true;
            counter = 1;
            continue;
        }
        if (comp == Compatibility::Left) {
            left_end = (tile.a == left_end) ? tile.b : tile.a;
        }
        else {
            right_end = (tile.a == right_end) ? tile.b : tile.a;
        }

        counter++;
    }

    return counter;
}