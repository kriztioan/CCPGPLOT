/**
 *  @file   itostr.cpp
 *  @brief  Integer to Std::string
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include <sstream>

std::string itostr(int i) {
  std::ostringstream str;
  str << i;
  return (str.str());
}
