#pragma once
#include <vector>
#include <random>
#include "dominoTile.h"

class DominoBag {
private:
    std::vector<DominoTile> tiles; 
    std::mt19937 engine;
  
public:
  
    explicit DominoBag(int n);
    DominoTile operator()();

    bool empty() const;
    int size() const;
    void reset(int n);

private:
    void generate_full_set(int n);
    void init_random();
};

