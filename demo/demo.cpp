/**
 *  @file   demo.cpp
 *  @brief  Demonstration of Using CCPGPLOT
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include <iostream>

#include "CCdraw.h"

int main() {

  ccdraw mydraw;
  ccplot myplot1, myplot2;
  cccurve mycurve;

  int size = 100;
  float a[size], b[size];
  for (int i = 0; i < size; i++) {
    a[i] = float(i);
    b[i] = a[i] * a[i];
  }

  mycurve.x(size, a);
  mycurve.y(size, b);
  mycurve.color(2);
  mycurve.type('l');
  mycurve.symbol(5);

  myplot1.add(mycurve);
  myplot1.title("A");

  mydraw.add(myplot1);

  size = 50;
  float c[size], d[size];
  for (int i = 0; i < size; i++) {
    c[i] = float(i) - float(size) / 2;
    d[i] = c[i] * c[i] * c[i] + 5. - 2 * c[i] * c[i];
  }

  mycurve.x(size, c);
  mycurve.y(size, d);
  mycurve.type('p');
  mycurve.color(4);

  myplot2.add(mycurve);
  myplot2.title("B");

  mydraw.add(myplot2);
  mydraw.paint();

  myplot1.clear();

  return (0);
}
