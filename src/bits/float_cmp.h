#ifndef RCT_FLOAT_CMP
#define RCT_FLOAT_CMP

#include <algorithm>
#include <cfloat>
#include <cmath>

inline int float_cmp(const float a, const float b) {
  const auto eps = FLT_EPSILON * std::max({1.0f, std::abs(a), std::abs(b)});
  if(a > b + eps) {
    return 1;
  } else if(a < b - eps) {
    return -1;
  } else {
    return 0;
  }
}

#endif  // RCT_FLOAT_CMP
