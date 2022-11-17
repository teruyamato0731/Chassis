#ifndef COODINATE_UNIT_H_
#define COODINATE_UNIT_H_
/// @file CoodinateUnit.h
/// @brief 座標、速度を表す構造体 CoodinateUnit を提供する。
#include <chrono>
#include <cmath>

namespace rct {

/// @defgroup unit
/// @brief 座標、速度を示す構造体を提供。 rct::Coodinate, rct::Velocity
/// @{

/// @brief 座標、速度を示す構造体。 rct::Coodinate, rct::Velocity @n
/// @brief CoodinateUnit同士の加減算とfloatとの乗除算が定義されている。 @n
/// @brief 下記を提供 rct::Coodinate, rct::Velocity
/// @sa Coodinate
/// @sa Velocity
/// @tparam N 時間の次元
template<int N>
struct CoodinateUnit {
  float x_milli;
  float y_milli;
  float ang_rad;
  static constexpr auto dimention() noexcept {
    return N;
  }
  CoodinateUnit& operator+=(const CoodinateUnit& obj) noexcept {
    this->x_milli += obj.x_milli;
    this->y_milli += obj.y_milli;
    this->ang_rad += obj.ang_rad;
    return *this;
  }
  CoodinateUnit& operator-=(const CoodinateUnit& obj) noexcept {
    this->x_milli -= obj.x_milli;
    this->y_milli -= obj.y_milli;
    this->ang_rad -= obj.ang_rad;
    return *this;
  }
  CoodinateUnit& operator*=(const float obj) noexcept {
    this->x_milli *= obj;
    this->y_milli *= obj;
    this->ang_rad *= obj;
    return *this;
  }
  CoodinateUnit& operator/=(const float obj) noexcept {
    this->x_milli /= obj;
    this->y_milli /= obj;
    this->ang_rad /= obj;
    return *this;
  }
};

/// @brief 座標を示す構造体
using Coodinate = CoodinateUnit<0>;
/// @brief 速度を示す構造体
using Velocity = CoodinateUnit<-1>;

template<int M, int N>
CoodinateUnit<M> unit_cast(const CoodinateUnit<N>& obj) {
  return *reinterpret_cast<const CoodinateUnit<M>*>(&obj);
}

/// @brief 2つの座標間の距離を計算する。
/// @param p1,p2 2つの座標
/// @return 2点間の距離[mm]
constexpr float distance(const Coodinate& p1, const Coodinate& p2) {
  return std::hypot(p1.x_milli - p2.x_milli, p1.y_milli - p2.y_milli);
}

/// @name operator
/// @brief 演算子を定義 CoodinateUnit同士の加減算, floatとの乗除算, chrono::microsecondsとの乗除算
/// @{
template<int N>
CoodinateUnit<N> operator+(const CoodinateUnit<N>& lhs, const CoodinateUnit<N>& rhs) {
  CoodinateUnit<N> nrv{lhs};
  nrv += rhs;
  return nrv;
};
template<int N>
CoodinateUnit<N> operator-(const CoodinateUnit<N>& lhs, const CoodinateUnit<N>& rhs) {
  CoodinateUnit<N> nrv{lhs};
  nrv -= rhs;
  return nrv;
};
template<int N>
CoodinateUnit<N> operator*(const CoodinateUnit<N>& lhs, const float rhs) {
  auto nrv{lhs};
  nrv *= rhs;
  return nrv;
};
template<int N>
CoodinateUnit<N> operator*(const float lhs, const CoodinateUnit<N>& rhs) {
  return rhs * lhs;
};
template<int N>
CoodinateUnit<N> operator/(const CoodinateUnit<N>& lhs, const float rhs) {
  auto nrv{lhs};
  nrv /= rhs;
  return nrv;
};
template<int N>
CoodinateUnit<N + 1> operator*(const CoodinateUnit<N>& obj, const std::chrono::microseconds& sec) {
  return unit_cast<N + 1>(obj * sec.count() * 1e-6);
}
template<int N>
CoodinateUnit<N + 1> operator*(const std::chrono::microseconds& sec, const CoodinateUnit<N>& obj) {
  return obj * sec;
}
template<int N>
CoodinateUnit<N - 1> operator/(const CoodinateUnit<N>& obj, const std::chrono::microseconds& sec) {
  return unit_cast<N - 1>(obj / sec.count() * 1e6);
}
/// @}

/// @}

}  // namespace rct

#endif  // COODINATE_UNIT_H_
