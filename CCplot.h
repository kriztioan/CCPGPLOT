/**
 *  @file   CCplot.h
 *  @brief  Ccplot Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CCPLOT_H_
#define CCPLOT_H_

#include "CCcurve.h"
#include <cstring>
#include <string>

class ccplot {

public:
  ccplot();
  ~ccplot();
  ccplot(ccplot const &other);
  ccplot &operator=(ccplot const &other);

  cccurve &operator[](unsigned index);
  cccurve operator[](unsigned index) const;

  void clear();

  void boxcolor(int bc);
  void title(const char *t);
  void xlabel(const char *xl);
  void ylabel(const char *yl);

  void xlayout(const char *xl);
  void ylayout(const char *yl);

  char const *title();
  char const *xlabel();
  char const *ylabel();

  char const *xlayout();
  char const *ylayout();

  void xlimits(float minx, float maxx);
  void ylimits(float miny, float maxy);

  float xmin();
  float xmax();
  float ymin();
  float ymax();

  int boxcolor();

  void add(cccurve &c);

  int size();

  cccurve *curves();

private:
  cccurve *Curves;

  int Boxcolor, Size;

  float Xmin, Xmax, Ymin, Ymax;

  char *Title, *Xlabel, *Ylabel,

      *Xlayout, *Ylayout;
};

inline void ccplot::clear() {
  delete[] Curves;
  Size = 0;
  Curves = 0;
}

inline void ccplot::boxcolor(int bc) { Boxcolor = bc; }

inline int ccplot::boxcolor() { return (Boxcolor); }

inline void ccplot::title(const char *t) {
  delete[] Title;
  Title = strcpy(new char[strlen(t) + 1], t);
}

inline char const *ccplot::title() { return (Title); }

inline void ccplot::xlabel(const char *xl) {
  delete[] Xlabel;
  Xlabel = strcpy(new char[strlen(xl) + 1], xl);
}

inline char const *ccplot::xlabel() { return (Xlabel); }

inline void ccplot::ylabel(const char *yl) {
  delete[] Ylabel;
  Ylabel = strcpy(new char[strlen(yl) + 1], yl);
}

inline char const *ccplot::ylabel() { return (Ylabel); }

inline void ccplot::xlayout(const char *xl) {
  delete[] Xlayout;
  Xlayout = strcpy(new char[strlen(xl) + 1], xl);
}

inline char const *ccplot::xlayout() { return (Xlayout); }

inline void ccplot::ylayout(const char *yl) {
  delete[] Ylayout;
  Ylayout = strcpy(new char[strlen(yl) + 1], yl);
}

inline char const *ccplot::ylayout() { return (Ylayout); }

inline float ccplot::xmin() { return (Xmin); }

inline float ccplot::xmax() { return (Xmax); }

inline float ccplot::ymin() { return (Ymin); }

inline float ccplot::ymax() { return (Ymax); }

inline void ccplot::xlimits(float minx, float maxx) {
  Xmin = minx;
  Xmax = maxx;
}

inline void ccplot::ylimits(float miny, float maxy) {
  Ymin = miny;
  Ymax = maxy;
}

inline cccurve *ccplot::curves() { return (Curves); }

inline int ccplot::size() { return (Size); }

#endif // CCPLOT_H_
