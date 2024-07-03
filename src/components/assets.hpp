#ifndef ASSETS_H_
#define ASSETS_H_

#include "animation.hpp"

#include "olc/olcPixelGameEngine.h"
#include <map>

struct player_sheet{
  size_t sheet_identifier;
};


struct background_sheet{
  olc::Sprite sheet;

  olc::vi2d sprite_size;
  olc::vi2d current_pos;

  std::map<std::string, olc::vi2d> sheet_parts;
};

#endif // ASSETS_H_
