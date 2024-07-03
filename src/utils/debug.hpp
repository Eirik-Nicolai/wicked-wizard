#pragma once
#include <iostream>

#include <vector>
#include <string>

#include "globals.hpp"
#include "components/statemachine.hpp"

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

#define DEBUG_VAL(x) std::cout << "[DEBUG] :  " << #x << "(" << convert(x) << ")" << "\n";
//#define DEBUG_VALS(...) DEBUG_VAL(__VA_ARGS__)

#define DEBUG(x) std::cout << "[DEBUG] :  " << convert(x) << "\n";

#define DEBUG_LINE() std::cout << " --- --- --- --- --- --- \n";
