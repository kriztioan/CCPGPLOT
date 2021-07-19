/**
 *  @file   minmax.cpp
 *  @brief  Try to Provide Valid Plot Range
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-18
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#include <cmath>

enum MIN_MAX { MIN, MAX };

int minmax(int n, float *array, float *min_max) {

  int i = 0, nan = 0;
  while (!finite(array[i])) {
    ++nan;
    ++i;
  }

  min_max[MIN] = array[i];
  min_max[MAX] = array[i];

  for (i; i < n; i++) {
    if (finite(array[i])) {
      if (array[i] < min_max[MIN]) {
        min_max[MIN] = array[i];
      } else if (array[i] > min_max[MAX]) {
        min_max[MAX] = array[i];
      }
    } else {
      ++nan;
    }
  }

  if (min_max[MIN] == min_max[MAX]) {
    min_max[MIN] = 0.95f * min_max[MIN];
    min_max[MAX] = 1.05f * min_max[MAX];
  } else {
    min_max[MIN] = min_max[MIN] - fabs(min_max[MIN] - min_max[MAX]) * 0.05f;
    min_max[MAX] = min_max[MAX] + fabs(min_max[MIN] - min_max[MAX]) * 0.05f;
  }

  return (nan);
}
