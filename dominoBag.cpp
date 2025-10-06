#include "dominoBag.h"
#include <stdexcept>
#include <algorithm>

DominoBag::DominoBag(int n) {
    if (n < 0) throw std::invalid_argument("n must be >= 0");
    generate_full_set(n);
    init_random();
}

void DominoBag::generate_full_set(int n) {
    tiles.clear();
    for (int i = 0; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            tiles.emplace_back(i, j);
        }
    }
}

void DominoBag::init_random() {
    std::random_device rd;
    std::seed_seq seeds{rd(), rd(), rd(), rd(), rd(), rd()};
    engine.seed(seeds); 
    std::shuffle(tiles.begin(), tiles.end(), engine);
}

DominoTile DominoBag::operator()() {
    if (tiles.empty()) throw std::runtime_error("No tiles left!");
    DominoTile t = tiles.back();
    tiles.pop_back();
    return t;
}

bool DominoBag::empty() const { return tiles.empty(); }
int DominoBag::size() const { return static_cast<int>(tiles.size()); }

void DominoBag::reset(int n) {
    if (n < 0) throw std::invalid_argument("n must be >= 0"); 
    generate_full_set(n);
    init_random();
}


