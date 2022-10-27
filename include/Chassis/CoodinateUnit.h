#ifndef COODINATE_UNIT_H_
#define COODINATE_UNIT_H_

#include <chrono>
#include <cmath>

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

template<int M, int N>
const CoodinateUnit<M>& unit_cast(const CoodinateUnit<N>& obj) {
  return reinterpret_cast<const CoodinateUnit<M>&>(obj);
}
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

using Coodinate = CoodinateUnit<0>;
using Velocity = CoodinateUnit<-1>;
template<int N>
constexpr float distance(const CoodinateUnit<N>& p1, const CoodinateUnit<N>& p2) {
  return std::hypot(p1.x_milli - p2.x_milli, p1.y_milli - p2.y_milli);
}

#endif  // COODINATE_UNIT_H_
