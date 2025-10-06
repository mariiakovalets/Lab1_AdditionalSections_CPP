#pragma once
#include <iostream>

struct DominoTile {
    int a;
    int b;
    DominoTile(int x = 0, int y = 0);

    bool operator==(const DominoTile& other) const;

    friend std::ostream& operator<<(std::ostream& os, const DominoTile& t);
};