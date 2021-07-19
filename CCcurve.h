/**
 *  @file   CCcurve.h
 *  @brief  Cccurve Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CCCURVE_H_
#define CCCURVE_H_

int minmax(int n, float *array, float *min_max);
#include <iostream>

class cccurve {

public:
  cccurve();
  ~cccurve();
  cccurve(cccurve const &other);
  cccurve &operator=(cccurve const &other);

  void color(int c);
  void lweight(int lw);
  void symbol(int s);
  void nbins(int n);
  void type(char t);

  int color();
  int lweight();
  int symbol();
  int nbins();
  int size();

  int status();

  char type();

  void x(int size, float *x);
  void y(int size, float *y);

  float *x();
  float *y();

  float xmin();
  float xmax();
  float ymin();
  float ymax();

private:
  int Color, Lweight, Symbol, Nbins,

      Xsize, Ysize,

      Status;

  char Type;

  float *X, *Y, Xmin, Xmax, Ymin, Ymax;
};

inline void cccurve::color(int c) { Color = c; }

inline int cccurve::color() { return (Color); }

inline void cccurve::lweight(int lw) { Lweight = lw; }

inline int cccurve::lweight() { return (Lweight); }

inline void cccurve::type(char t) { Type = t; }

inline char cccurve::type() { return (Type); }

inline void cccurve::symbol(int s) { Symbol = s; }

inline int cccurve::symbol() { return (Symbol); }

inline void cccurve::nbins(int n) { Nbins = n; }

inline int cccurve::nbins() { return (Nbins); }

inline int cccurve::size() { return (Xsize); }

inline int cccurve::status() { return (Status); }

inline float cccurve::xmin() { return (Xmin); }

inline float cccurve::xmax() { return (Xmax); }

inline float cccurve::ymin() { return (Ymin); }

inline float cccurve::ymax() { return (Ymax); }

#endif // End of CCCURVE_H_
