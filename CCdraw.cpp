/**
 *  @file   CCdraw.cpp
 *  @brief  Ccdraw Class Implementation
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include "CCdraw.h"

#include <cmath>
#include <cpgplot.h>
#include <cstdlib>

ccdraw::ccdraw() {
  plots = NULL;

  deviceID = -1;
  Nhardcopies = 0;

  Size = 0;

  PagesX = 1;
  PagesY = 1;

  WindowX = 9;
  WindowY = 0.9 * WindowX;

  SurfaceX = 0.15;
  SurfaceY = 0.15;

  KeepAlive = false;
}

ccdraw::~ccdraw() {
  if(plots)
    delete[] plots;

  if (deviceID != -1) {
    if (!KeepAlive)
      cpgclos();
  }
}

void ccdraw::add(ccplot &p) {
  ccplot *tmp = new ccplot[Size + 1];
  for (int i = 0; i < Size; i++)
    tmp[i] = plots[i];
  tmp[Size++] = p;
  delete[] plots;
  plots = tmp;
}

void ccdraw::open(const char *device) { deviceID = cpgopen(device); }

void ccdraw::open(int id) {

  deviceID = id;
  cpgslct(deviceID);
}

void ccdraw::pages(int pagesX, int pagesY) {
  PagesX = pagesX;
  PagesY = pagesY;
}

void ccdraw::window(float X, float Y) {
  WindowX = X;
  WindowY = Y;
}

void ccdraw::surface(float procentX, float procentY) {
  SurfaceX = procentX / 100.;
  SurfaceY = procentY / 100.;
}

void ccdraw::paint() {
  if (deviceID == -1)
    open();

  cpgpap(WindowX, WindowY / WindowX);
  cpgsvp(SurfaceX, 1. - SurfaceX, SurfaceY, 1. - SurfaceY);
  cpgscr(1, 0, 0, 0);
  cpgscr(0, 1, 1, 1);
  cpgask(false);
  char character;
  cpgsubp(PagesX, PagesY);
  int i = 0;
  while (i < Size) {
    float cursx = plots[i].xmin(), cursy = plots[i].ymin(),
          cursx1 = plots[i].xmax(), cursy1 = plots[i].ymax(), cursx0, cursy0,
          cursx10, cursy10;
    while (true) {
      cpgpage();
      cpgsci(plots[i].boxcolor());
      cpgswin(
          (cursx > cursx1 ? cursx1 : cursx), (cursx > cursx1 ? cursx : cursx1),
          (cursy > cursy1 ? cursy1 : cursy), (cursy > cursy1 ? cursy : cursy1));
      cpgbox(plots[i].xlayout(), 0.0, 0, plots[0].ylayout(), 0.0, 0);
      cpgmtxt("L", 4, 0.5, 0.5, plots[i].ylabel());
      cpgmtxt("B", 3, 0.5, 0.5, plots[i].xlabel());
      cpgmtxt("T", 3, 0.5, 0.5, plots[i].title());
      for (int j = 0; j < plots[i].size(); j++) {
        cpgsci(plots[i].curves()[j].color());
        switch (plots[i].curves()[j].type()) {
        case 'l': {
          cpgslw(plots[i].curves()[j].lweight());
          cpgsls(plots[i].curves()[j].symbol());
          int k = 0;
          while (!std::isfinite(plots[i].curves()[j].x()[k]) ||
                 !std::isfinite(plots[i].curves()[j].y()[k]))
            k++;
          float segment_x[2], segment_y[2];
          segment_x[0] = plots[i].curves()[j].x()[k];
          segment_y[0] = plots[i].curves()[j].y()[k++];
          for (; k < plots[i].curves()[j].size(); k++) {
            if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                std::isfinite(plots[i].curves()[j].y()[k])) {
              segment_x[1] = plots[i].curves()[j].x()[k];
              segment_y[1] = plots[i].curves()[j].y()[k];
              cpgline(2, segment_x, segment_y);
              segment_x[0] = segment_x[1];
              segment_y[0] = segment_y[1];
            }
          }
          cpgslw(1);
          cpgsls(1);
          break;
        }
        case 'h':
          cpghist(plots[i].curves()[j].size(), plots[i].curves()[j].x(),
                  plots[i].xmin(), plots[i].xmax(),
                  plots[i].curves()[j].nbins(), 3);
          break;
        case 'p':
        default:
          for (int k = 0; k < plots[i].curves()[j].size(); k++) {
            if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                std::isfinite(plots[i].curves()[j].y()[k]))
              cpgpt1(plots[i].curves()[j].x()[k], plots[i].curves()[j].y()[k],
                     plots[i].curves()[j].symbol());
          }
        };
      }
      cpgsci(2);
      cursx0 = cursx;
      cursy0 = cursy;
      cpgband(0, 0, cursx, cursy, &cursx, &cursy, &character);
      if (character == 'X') {
        i++;
        break;
      } else if (character == 'q') {
        if (!KeepAlive) {
          deviceID = -1;
          cpgclos();
        }
        return;
      } else if (character == 'D') {
        cursx = plots[i].xmin();
        cursx1 = plots[i].xmax();
        cursy = plots[i].ymin();
        cursy1 = plots[i].ymax();
      } else if (character == 'A') {
        cursx10 = cursx1;
        cursy10 = cursy1;
        cpgband(2, 0, cursx, cursy, &cursx1, &cursy1, &character);
        if (character == 'X') {
          i++;
          break;
        } else if (character == 'D') {
          cursx = plots[i].xmin();
          cursx1 = plots[i].xmax();
          cursy = plots[i].ymin();
          cursy1 = plots[i].ymax();
        } else if (character == 'q') {
          if (!KeepAlive) {
            cpgend();
            exit(0);
          }
          return;
        } else if (character != 'A') {
          cursx = plots[i].xmin();
          cursx1 = plots[i].xmax();
          cursy = plots[i].ymin();
          cursy1 = plots[i].ymax();
        }
      } else if (character == 's') {

        cursx = cursx0;
        cursy = cursy0;
        std::string file = "output." + itostr(Nhardcopies++) + ".ps/VCPS";
        cpgopen(file.c_str());

        cpgpap(WindowX, WindowY / WindowX);
        cpgsvp(SurfaceX, 1. - SurfaceX, SurfaceY, 1. - SurfaceY);
        cpgpage();
        cpgsci(plots[i].boxcolor());
        cpgmtxt("B", 3, 0.5, 0.5, plots[i].xlabel());
        cpgmtxt("T", 3, 0.5, 0.5, plots[i].title());
        cpgmtxt("L", 4, 0.5, 0.5, plots[i].ylabel());
        cpgswin((cursx > cursx1 ? cursx1 : cursx),
                (cursx > cursx1 ? cursx : cursx1),
                (cursy > cursy1 ? cursy1 : cursy),
                (cursy > cursy1 ? cursy : cursy1));
        cpgbox(plots[i].xlayout(), 0.0, 0, plots[0].ylayout(), 0.0, 0);
        for (int j = 0; j < plots[i].size(); j++) {
          cpgsci(plots[i].curves()[j].color());
          switch (plots[i].curves()[j].type()) {
          case 'l': {
            cpgslw(plots[i].curves()[j].lweight());
            cpgsls(plots[i].curves()[j].symbol());
            int k = 0;
            while (!std::isfinite(plots[i].curves()[j].x()[k]) ||
                   !std::isfinite(plots[i].curves()[j].y()[k]))
              k++;
            float segment_x[2], segment_y[2];
            segment_x[0] = plots[i].curves()[j].x()[k];
            segment_y[0] = plots[i].curves()[j].y()[k];
            for (; k < plots[i].curves()[j].size(); k++) {
              if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                  std::isfinite(plots[i].curves()[j].y()[k])) {
                segment_x[1] = plots[i].curves()[j].x()[k];
                segment_y[1] = plots[i].curves()[j].y()[k];
                cpgline(2, segment_x, segment_y);
                segment_x[0] = segment_x[1];
                segment_y[0] = segment_y[1];
              }
            }
            cpgslw(1);
            cpgsls(1);
            break;
          }
          case 'h':
            cpghist(plots[i].curves()[j].size(), plots[i].curves()[j].x(),
                    plots[i].xmin(), plots[i].xmax(),
                    plots[i].curves()[j].nbins(), 3);
            break;
          case 'p':
          default:
            for (int k = 0; k < plots[i].curves()[j].size(); k++) {
              if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                  std::isfinite(plots[i].curves()[j].y()[k]))
                cpgpt1(plots[i].curves()[j].x()[k], plots[i].curves()[j].y()[k],
                       plots[i].curves()[j].symbol());
            }
          };
        }

        cpgclos();
        cpgslct(deviceID);
        std::cout << "Saving to " << file.substr(0, file.find("/VCPS"))
                  << ".... Saved" << std::endl;
      } else if (character == ',') {
        if (i == 0)
          i = Size - 1;
        else
          i--;

        cursx = plots[i].xmin();
        cursx1 = plots[i].xmax();
        cursy = plots[i].ymin();
        cursy1 = plots[i].ymax();
      } else if (character == '.') {
        if (i == Size - 1)
          i = 0;
        else
          i++;

        cursx = plots[i].xmin();
        cursx1 = plots[i].xmax();
        cursy = plots[i].ymin();
        cursy1 = plots[i].ymax();

      } else if (character == '+' || character == '=') {
        WindowX *= 1.1;
        WindowY *= 1.1;
        cpgpap(WindowX, WindowY / WindowX);
        cpgsvp(SurfaceX, 1. - SurfaceX, SurfaceY, 1. - SurfaceY);
        cpgpage();
        cursx = cursx0;
        cursy = cursy0;
      } else if (character == '-') {
        WindowX *= 0.9;
        WindowY *= 0.9;
        cpgpap(WindowX, WindowY / WindowX);
        cpgsvp(SurfaceX, 1. - SurfaceX, SurfaceY, 1. - SurfaceY);
        cpgpage();
        cursx = cursx0;
        cursy = cursy0;
      } else {
        cursx = cursx0;
        cursy = cursy0;
      }
    }
  }
  // deviceID = -1;
  // cpgclos();
}

void ccdraw::mulipages() {
  if (deviceID == -1)
    open();

  cpgpap(WindowX, WindowY / WindowX);
  cpgsvp(SurfaceX, 1 - SurfaceX, SurfaceY, 1 - SurfaceY);
  cpgscr(1, 0, 0, 0);
  cpgscr(0, 1, 1, 1);
  float cursx, cursy;
  char character;
  cpgask(false);
  cpgsubp(PagesX, PagesY);
  int i = 0, margin = (PagesX * PagesY);
  while (i < Size) {
    int drawn = 0;
    for (; i < Size && i < margin; i++) {
      drawn++;
      cpgpage();
      cpgsci(plots[i].boxcolor());
      cpgswin(plots[i].xmin(), plots[i].xmax(), plots[i].ymin(),
              plots[i].ymax());
      cpgbox(plots[i].xlayout(), 0.0, 0, plots[0].ylayout(), 0.0, 0);
      cpgmtxt("L", 4, 0.5, 0.5, plots[i].ylabel());
      cpgmtxt("B", 3, 0.5, 0.5, plots[i].xlabel());
      cpgmtxt("T", 3, 0.5, 0.5, plots[i].title());
      for (int j = 0; j < plots[i].size(); j++) {
        cpgsci(plots[i].curves()[j].color());
        switch (plots[i].curves()[j].type()) {
        case 'l': {
          cpgslw(plots[i].curves()[j].lweight());
          cpgsls(plots[i].curves()[j].symbol());
          int k = 0;
          while (!std::isfinite(plots[i].curves()[j].x()[k]) ||
                 !std::isfinite(plots[i].curves()[j].y()[k]))
            k++;
          float segment_x[2], segment_y[2];
          segment_x[0] = plots[i].curves()[j].x()[k];
          segment_y[0] = plots[i].curves()[j].y()[k++];
          for (; k < plots[i].curves()[j].size(); k++) {
            if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                std::isfinite(plots[i].curves()[j].y()[k])) {
              segment_x[1] = plots[i].curves()[j].x()[k];
              segment_y[1] = plots[i].curves()[j].y()[k];
              cpgline(2, segment_x, segment_y);
              segment_x[0] = segment_x[1];
              segment_y[0] = segment_y[1];
            }
          }
          cpgslw(1);
          cpgsls(1);
          break;
        }
        case 'h':
          cpghist(plots[i].curves()[j].size(), plots[i].curves()[j].x(),
                  plots[i].xmin(), plots[i].xmax(),
                  plots[i].curves()[j].nbins(), 3);
          break;
        case 'p':
        default:
          for (int k = 0; k < plots[i].curves()[j].size(); k++) {
            if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                std::isfinite(plots[i].curves()[j].y()[k]))
              cpgpt1(plots[i].curves()[j].x()[k], plots[i].curves()[j].y()[k],
                     plots[i].curves()[j].symbol());
          }
        };
      }
    }
    cpgband(0, 0, cursx, cursy, &cursx, &cursy, &character);
    if (character == 'X')
      margin += (PagesX * PagesY);
    else if (character == ',') {
      if (i != drawn) {
        i = i - drawn - (PagesX * PagesY);
        margin -= (PagesX * PagesY);
      } else
        i -= (drawn);
    } else if (character == '.') {
      if (i != Size)
        margin += (PagesX * PagesY);
      else
        i -= (drawn);
    } else if (character == 's') {
      std::string file = "output." + itostr(Nhardcopies++) + ".ps/VCPS";
      cpgopen(file.c_str());
      cpgsubp(PagesX, PagesY);
      cpgpap(WindowX, WindowY / WindowX);
      cpgsvp(SurfaceX, 1 - SurfaceX, SurfaceY, 1 - SurfaceY);
      i -= drawn;
      for (; (i < margin) && (i < Size); i++) {
        cpgpage();
        cpgsci(plots[i].boxcolor());
        cpgswin(plots[i].xmin(), plots[i].xmax(), plots[i].ymin(),
                plots[i].ymax());
        cpgbox(plots[i].xlayout(), 0.0, 0, plots[0].ylayout(), 0.0, 0);
        cpgmtxt("L", 4, 0.5, 0.5, plots[i].ylabel());
        cpgmtxt("B", 3, 0.5, 0.5, plots[i].xlabel());
        cpgmtxt("T", 3, 0.5, 0.5, plots[i].title());
        for (int j = 0; j < plots[i].size(); j++) {
          cpgsci(plots[i].curves()[j].color());
          switch (plots[i].curves()[j].type()) {
          case 'l': {
            cpgslw(plots[i].curves()[j].lweight());
            cpgsls(plots[i].curves()[j].symbol());
            int k = 0;
            while (!std::isfinite(plots[i].curves()[j].x()[k]) ||
                   !std::isfinite(plots[i].curves()[j].y()[k]))
              k++;
            float segment_x[2], segment_y[2];
            segment_x[0] = plots[i].curves()[j].x()[k];
            segment_y[0] = plots[i].curves()[j].y()[k++];
            for (; k < plots[i].curves()[j].size(); k++) {
              if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                  std::isfinite(plots[i].curves()[j].y()[k])) {
                segment_x[1] = plots[i].curves()[j].x()[k];
                segment_y[1] = plots[i].curves()[j].y()[k];
                cpgline(2, segment_x, segment_y);
                segment_x[0] = segment_x[1];
                segment_y[0] = segment_y[1];
              }
            }
            cpgslw(1);
            cpgsls(1);
            break;
          }
          case 'h':
            cpghist(plots[i].curves()[j].size(), plots[i].curves()[j].x(),
                    plots[i].xmin(), plots[i].xmax(),
                    plots[i].curves()[j].nbins(), 3);
            break;
          case 'p':
          default:
            for (int k = 0; k < plots[i].curves()[j].size(); k++) {
              if (std::isfinite(plots[i].curves()[j].x()[k]) &&
                  std::isfinite(plots[i].curves()[j].y()[k]))
                cpgpt1(plots[i].curves()[j].x()[k], plots[i].curves()[j].y()[k],
                       plots[i].curves()[j].symbol());
            }
          };
        }
      }
      cpgclos();
      cpgslct(deviceID);
      std::cout << "Saving to " << file.substr(0, file.find("/VCPS"))
                << ".... Saved" << std::endl;
      i -= drawn;
    } else if (character == 'q') {
      if (!KeepAlive) {
        deviceID = -1;
        cpgclos();
      }
      return;
    } else if (character == '+' || character == '=') {
      WindowX *= 1.1;
      WindowY *= 1.1;
      cpgpap(WindowX, WindowY / WindowX);
      cpgsvp(SurfaceX, 1. - SurfaceX, SurfaceY, 1. - SurfaceY);
      cpgpage();
      i -= drawn;
    } else if (character == '-') {
      WindowX *= 0.9;
      WindowY *= 0.9;
      cpgpap(WindowX, WindowY / WindowX);
      cpgsvp(SurfaceX, 1. - SurfaceX, SurfaceY, 1. - SurfaceY);
      cpgpage();
      i -= drawn;
    } else
      i -= drawn;
  }
  deviceID = -1;
  cpgclos();
}
