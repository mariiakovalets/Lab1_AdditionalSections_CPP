#include "dominoTile.h"

DominoTile::DominoTile(int x, int y) {
    if (x <= y) { a = x; b = y; }
    else { a = y; b = x; }
}

bool DominoTile::operator==(const DominoTile& other) const {
    return a == other.a && b == other.b;
}

std::ostream& operator<<(std::ostream& os, const DominoTile& t) {
    os << "[" << t.a << ":" << t.b << "]";
    return os;
}