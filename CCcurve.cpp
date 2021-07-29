/**
 *  @file   CCcurve.h
 *  @brief  Cccurve Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "CCcurve.h"

cccurve::cccurve() {
  Color = 1;
  Lweight = 1;
  Symbol = 1;
  Nbins = 1;

  Status = 0;

  Type = 'p';

  X = 0;
  Y = 0;

  Xsize = 0;
  Ysize = 0;

  Xmin = 0;
  Xmax = 1;
  Ymin = 0;
  Ymax = 1;
}

cccurve::~cccurve() {
  delete[] X;
  delete[] Y;
}

cccurve::cccurve(cccurve const &other) {
  X = new float[other.Xsize];
  Y = new float[other.Ysize];
  for (int i = 0; i < other.Xsize; i++)
    X[i] = other.X[i];
  for (int i = 0; i < other.Ysize; i++)
    Y[i] = other.Y[i];

  Color = other.Color;
  Lweight = other.Lweight;
  Status = other.Status;
  Type = other.Type;
  Symbol = other.Symbol;
  Nbins = other.Nbins;
  Status = other.Status;
  Xsize = other.Xsize;
  Ysize = other.Ysize;
  Xmin = other.Xmin;
  Xmax = other.Xmax;
  Ymin = other.Ymin;
  Ymax = other.Ymax;
}

cccurve &cccurve::operator=(cccurve const &other) {
  if (this != &other) {
    delete[] X;
    delete[] Y;

    X = new float[other.Xsize];
    Y = new float[other.Ysize];

    for (int i = 0; i < other.Xsize; i++)
      X[i] = other.X[i];
    for (int i = 0; i < other.Ysize; i++)
      Y[i] = other.Y[i];

    Color = other.Color;
    Lweight = other.Lweight;
    Status = other.Status;
    Type = other.Type;
    Symbol = other.Symbol;
    Nbins = other.Nbins;
    Status = other.Status;
    Xsize = other.Xsize;
    Ysize = other.Ysize;
    Xmin = other.Xmin;
    Xmax = other.Xmax;
    Ymin = other.Ymin;
    Ymax = other.Ymax;
  }
  return (*this);
}

void cccurve::x(int size, float *x) {
  delete[] X;
  X = new float[size];
  for (int i = 0; i < size; i++)
    X[i] = x[i];
  Xsize = size;

  float min_max_x[2];
  Status += minmax(size, X, min_max_x);

  Xmin = min_max_x[0];
  Xmax = min_max_x[1];
}

float *cccurve::x() { return (X); }

float *cccurve::y() { return (Y); }

void cccurve::y(int size, float *y) {
  delete[] Y;
  Y = new float[size];
  for (int i = 0; i < size; i++)
    Y[i] = y[i];
  Ysize = size;

  float min_max_y[2];
  Status += minmax(size, Y, min_max_y);

  Ymin = min_max_y[0];
  Ymax = min_max_y[1];
}
