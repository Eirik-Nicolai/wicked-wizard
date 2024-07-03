#pragma once

#include "olc/olcPixelGameEngine.h"

#include "utils/debug.hpp"
#include "components/animation.hpp"


class AssetManager{
  public:
    AssetManager() = default;

    bool load(const std::string &path, size_t &indx);

    std::weak_ptr<olc::Decal> get(size_t indx);

  private:
    size_t sheet_amnt;
    std::shared_ptr<olc::Sprite> spritesheets[255];
    std::shared_ptr<olc::Decal> decs[255];
};

