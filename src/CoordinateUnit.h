#ifndef COORDINATE_UNIT_H_
#define COORDINATE_UNIT_H_
/// @file CoordinateUnit.h
/// @brief 座標、速度を表す構造体 CoordinateUnit を提供する。
/// @copyright Copyright (c) 2022 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE)
#include <chrono>
#include <cmath>

#include "bits/float_cmp.h"

namespace rct {

/// @addtogroup utility
/// @{

/// @defgroup unit unit
/// @brief 座標、速度を示す構造体を提供。 rct::Coordinate, rct::Velocity
/// @{

/// @brief 座標、速度を示す構造体。 rct::Coordinate, rct::Velocity @n
/// @brief CoordinateUnit同士の加減算とfloatとの乗除算が定義されている。 @n
/// @brief 下記を提供 rct::Coordinate, rct::Velocity
/// @sa Coordinate
/// @sa Velocity
/// @tparam N 時間の次元
template<int N>
struct CoordinateUnit {
  float x_milli;  ///< x変位[mm]
  float y_milli;  ///< y変位[mm]
  float ang_rad;  ///< 角変位[rad]

  /// @brief 時間の次元を取得する。
  /// @return CoordinateUnit クラスの templateパラメータである N 定数を返す。
  static constexpr auto dimension() noexcept {
    return N;
  }

  /// @{
  /// @brief 各種演算子を定義する。
  CoordinateUnit& operator+=(const CoordinateUnit& obj) noexcept {
    this->x_milli += obj.x_milli;
    this->y_milli += obj.y_milli;
    this->ang_rad += obj.ang_rad;
    return *this;
  }
  CoordinateUnit& operator-=(const CoordinateUnit& obj) noexcept {
    this->x_milli -= obj.x_milli;
    this->y_milli -= obj.y_milli;
    this->ang_rad -= obj.ang_rad;
    return *this;
  }
  CoordinateUnit& operator*=(const float obj) noexcept {
    this->x_milli *= obj;
    this->y_milli *= obj;
    this->ang_rad *= obj;
    return *this;
  }
  CoordinateUnit& operator/=(const float obj) noexcept {
    this->x_milli /= obj;
    this->y_milli /= obj;
    this->ang_rad /= obj;
    return *this;
  }
  /// @}
};

/// @brief 座標を示す構造体
using Coordinate = CoordinateUnit<0>;
/// @brief 速度を示す構造体
using Velocity = CoordinateUnit<-1>;

/// @brief CoordinateUnitをCoordinateUnitにキャストする。
/// @tparam M キャスト先の次元
/// @tparam N 引数のCoordinateUnitの次元
/// @param obj キャストするオブジェクト
/// @return キャスト後のオブジェクト
template<int M, int N>
CoordinateUnit<M> unit_cast(const CoordinateUnit<N>& obj) {
  return *reinterpret_cast<const CoordinateUnit<M>*>(&obj);
}

/// @brief 2つの座標間の距離を計算する。
/// @param p1,p2 2つの座標
/// @return 2点間の距離[mm]
constexpr float distance(const Coordinate& p1, const Coordinate& p2) {
  return std::hypot(p1.x_milli - p2.x_milli, p1.y_milli - p2.y_milli);
}

/// @brief 二点aとbの間を、時間tで線形補間 (linear interpolate) する。
/// @tparam T 任意の引数型 T型同士の加減算, floatとの乗算が定義されていることを要求する。
/// @param a 開始地点
/// @param b 目標地点
/// @param t 経過時間[%]
/// @return a + t * (b - a);
/// @note t == 0 の時 a, t == 1のとき bを返す。
template<class T>
constexpr T lerp(const T& a, const T& b, float t) noexcept {
  return a + t * (b - a);
}

/// @name operator
/// @brief 演算子を定義 CoordinateUnit同士の加減算, floatとの乗除算, chrono::microsecondsとの乗除算
/// @{
template<int N>
CoordinateUnit<N> operator+(const CoordinateUnit<N>& lhs, const CoordinateUnit<N>& rhs) {
  CoordinateUnit<N> nrv{lhs};
  nrv += rhs;
  return nrv;
};
template<int N>
CoordinateUnit<N> operator-(const CoordinateUnit<N>& lhs, const CoordinateUnit<N>& rhs) {
  CoordinateUnit<N> nrv{lhs};
  nrv -= rhs;
  return nrv;
};
template<int N>
CoordinateUnit<N> operator*(const CoordinateUnit<N>& lhs, const float rhs) {
  auto nrv{lhs};
  nrv *= rhs;
  return nrv;
};
template<int N>
CoordinateUnit<N> operator*(const float lhs, const CoordinateUnit<N>& rhs) {
  return rhs * lhs;
};
template<int N>
CoordinateUnit<N> operator/(const CoordinateUnit<N>& lhs, const float rhs) {
  auto nrv{lhs};
  nrv /= rhs;
  return nrv;
};
template<int N>
CoordinateUnit<N + 1> operator*(const CoordinateUnit<N>& obj, const std::chrono::microseconds& sec) {
  return unit_cast<N + 1>(obj * sec.count() * 1e-6);
}
template<int N>
CoordinateUnit<N + 1> operator*(const std::chrono::microseconds& sec, const CoordinateUnit<N>& obj) {
  return obj * sec;
}
template<int N>
CoordinateUnit<N - 1> operator/(const CoordinateUnit<N>& obj, const std::chrono::microseconds& sec) {
  return unit_cast<N - 1>(obj / sec.count() * 1e6);
}
template<int N>
bool operator==(const CoordinateUnit<N>& lhs, const CoordinateUnit<N>& rhs) {
  return impl::float_cmp(lhs.x_milli, rhs.x_milli) == 0 && impl::float_cmp(lhs.y_milli, rhs.y_milli) == 0 &&
         impl::float_cmp(lhs.ang_rad, rhs.ang_rad) == 0;
}
template<int N>
bool operator!=(const CoordinateUnit<N>& lhs, const CoordinateUnit<N>& rhs) {
  return !(lhs == rhs);
}
/// @}  operator

/// @}  unit

/// @}  utility

}  // namespace rct

#endif  // COORDINATE_UNIT_H_
