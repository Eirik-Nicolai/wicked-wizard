#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "box2d/box2d.h"

struct box2d_ref{
  b2Body *ref;
  b2Vec2 size;
};

struct destructible{
  int shards;
};


#endif // PHYSICS_H_
