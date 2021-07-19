/**
 *  @file   CCplot.h
 *  @brief  Ccplot Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "CCplot.h"

ccplot::ccplot() {
  Curves = 0;

  Boxcolor = 1;
  Xmin = 0;
  Xmax = 1;
  Ymin = 0;
  Ymax = 1;

  Size = 0;

  Title = strcpy(new char[strlen("Simple plot") + 1], "Simple plot");
  Xlabel = strcpy(new char[strlen("X \\(2261)") + 1], "X \\(2261)");
  Ylabel = strcpy(new char[strlen("Y \\(2261)") + 1], "Y \\(2261)");

  Xlayout = strcpy(new char[strlen("BINTS") + 1], "BINTS");
  Ylayout = strcpy(new char[strlen("BINTSV") + 1], "BINTSV");
}

ccplot::~ccplot() {
  delete Title;
  delete Xlabel;
  delete Ylabel;

  delete Xlayout;
  delete Ylayout;

  delete[] Curves;
}

ccplot::ccplot(ccplot const &other) {
  Curves = new cccurve[other.Size];
  for (int i = 0; i < other.Size; i++)
    Curves[i] = other.Curves[i];

  Title = strcpy(new char[strlen(other.Title) + 1], other.Title);
  Xlabel = strcpy(new char[strlen(other.Xlabel) + 1], other.Xlabel);
  Ylabel = strcpy(new char[strlen(other.Ylabel) + 1], other.Ylabel);
  Xlayout = strcpy(new char[strlen(other.Xlayout) + 1], other.Xlayout);
  Ylayout = strcpy(new char[strlen(other.Ylayout) + 1], other.Ylayout);
}

ccplot &ccplot::operator=(ccplot const &other) {
  if (this != &other) {
    delete Title;
    Title = strcpy(new char[strlen(other.Title) + 1], other.Title);
    delete Xlabel;
    Xlabel = strcpy(new char[strlen(other.Xlabel) + 1], other.Xlabel);
    delete Ylabel;
    Ylabel = strcpy(new char[strlen(other.Ylabel) + 1], other.Ylabel);
    delete Xlayout;
    Xlayout = strcpy(new char[strlen(other.Xlayout) + 1], other.Xlayout);
    delete Ylayout;
    Ylayout = strcpy(new char[strlen(other.Ylayout) + 1], other.Ylayout);

    delete[] Curves;
    Curves = new cccurve[other.Size];
    for (int i = 0; i < other.Size; i++)
      Curves[i] = other.Curves[i];

    Boxcolor = other.Boxcolor;
    Size = other.Size;
    Xmin = other.Xmin;
    Xmax = other.Xmax;
    Ymin = other.Ymin;
    Ymax = other.Ymax;
  }
  return (*this);
}

cccurve &ccplot::operator[](unsigned index) { return (Curves[index]); }

cccurve ccplot::operator[](unsigned index) const { return (Curves[index]); }

void ccplot::add(cccurve &c) {

  cccurve *tmp = new cccurve[Size + 1];
  for (int i = 0; i < Size; i++)
    tmp[i] = Curves[i];
  tmp[Size++] = c;
  delete[] Curves;
  Curves = tmp;

  if (Size == 1) {
    Xmin = c.xmin();
    Xmax = c.xmax();
    Ymin = c.ymin();
    Ymax = c.ymax();
  } else {
    if (c.xmin() < Xmin)
      Xmin = c.xmin();
    if (c.xmax() > Xmax)
      Xmax = c.xmax();
    if (c.ymin() < Ymin)
      Ymin = c.ymin();
    if (c.ymax() > Ymax)
      Ymax = c.ymax();
  }
}
