#pragma once
#include <iostream>

#include <vector>
#include <string>
#include <sstream>
#include <bitset>

#include "globals.hpp"
#include "utils/globals.hpp"

template <typename S>
inline std::string to_string(S &s)
{
  return s.str();
}

template <typename T>
std::string convert(T inp)
{
  using namespace std;

  return to_string(inp);
}

inline std::string convert(std::string inp)
{
  return inp;
}
inline std::string convert(const char *inp)
{
  return inp;
}
inline std::string convert(bitmask inp)
{
  std::bitset<64> bit(inp);
  std::stringstream ss;
  ss << bit;
  return ss.str();
}

inline std::string convert(bool inp)
{
  return inp ? "TRUE" : "FALSE";
}


#define DEBUG_VAL(x) std::cout << "[DEBUG] :  " << #x << "(" << convert(x) << ")" << "\n";
//#define DEBUG_VALS(...) DEBUG_VAL(__VA_ARGS__)

#define DEBUG(x) std::cout << "[DEBUG] :  " << convert(x) << "\n";

#define DEBUG_SPACE() std::cout << "\n";

#define DEBUG_LINE() std::cout << " --- --- --- --- --- --- \n";
