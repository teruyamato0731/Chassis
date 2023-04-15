#ifndef RCT_FLOAT_CMP
#define RCT_FLOAT_CMP
/// @file
/// @brief 浮動小数点数の比較を行う float_cmp を提供する。
/// @copyright Copyright (c) 2022-2023 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).
#include <algorithm>
#include <cfloat>
#include <cmath>

namespace rct {

namespace impl {

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

}  // namespace impl

}  // namespace rct


#endif  // RCT_FLOAT_CMP
