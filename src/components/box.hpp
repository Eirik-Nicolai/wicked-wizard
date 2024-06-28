#ifndef BOX_H_
#define BOX_H_

struct Box
{
  float sx;
  float sy;
  float px;
  float py;
};

struct _solid{}; //cannot be walked through

struct _static{};

struct _asleep{};


#endif // BOX_H_
