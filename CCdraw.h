/**
 *  @file   CCdraw.h
 *  @brief  Ccdraw Class Definition
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/
#ifndef CCDRAW_H_
#define CCDRAW_H_

#include "CCplot.h"

#include <string>

std::string itostr(int i);

class ccdraw {
public:
  ccdraw();
  ~ccdraw();

  void open(const char *device = "/XWINDOW");
  void open(int id);

  void retain();
  void release();

  void add(ccplot &p);

  void paint();
  void mulipages();

  void window(float X, float Y);
  void surface(float procentX, float procentY);
  void pages(int pagesX, int pagesY);

  int size();

private:
  ccplot *plots;

  int deviceID, Nhardcopies,

      Size,

      PagesX, PagesY;

  float WindowX, WindowY,

      SurfaceX, SurfaceY;

  bool KeepAlive;
};

inline int ccdraw::size() { return (Size); }

inline void ccdraw::retain() { KeepAlive = true; }

inline void ccdraw::release() { KeepAlive = false; }

#endif // End of CCDRAW_
