# Usage
Chassisの使用方法。

## Omni \<int N>
N輪オムニの制御を行うクラス。[More...](./ref/Omni.md)
|返り値|メンバ関数|
|---|---|
||[Omni](Omni.md#omni)(F f)|
||callback関数をセットする。|
|int|[size](Omni.md#size)()|
||モータ数を返す。|
|void|[calc](Omni.md#calc)(Velocity vel)|
||モータへのPWM出力を計算する。|
||その後callback関数にPWM出力を渡す。|

## Mecanum
メカナムの制御を行うクラス。[More...](./ref/Mecanum.md)
|返り値|メンバ関数|
|---|---|
||Mecanum(F f)|
||callback関数をセットする。|
|int|size()|
||モータ数を返す。|
|void|calc(Velocity vel)|
||モータへのPWM出力を計算する。|
||その後callback関数にPWM出力を渡す。|

## Odom
N個のエンコーダでオドメトリを行うクラス。[More...](./ref/Odom.md)
|返り値|メンバ関数|
|---|---|
||Odom()|
||現在位置を初期化。|
|int|size()|
||エンコーダ数を返す。|
|void|integrate(int dif_val[N])|
||エンコーダの変位の変化量を積分し、自己位置を計算する。|
|Coodinate|get()|
||推定された自己位置を返す。|
|void|set(Coodinate pos)|
||自己位置を更新する。|

## Chassis \<class T>
T型の自動制御を行うクラス。[More...](./ref/Chassis.md)
T型はOmni, Mecanumクラス、またはそれらと同じように扱えるクラス。
|返り値|メンバ関数|
|---|---|
||Chassis(F f, PidGain vel_gain, PidGain pos_gain)|
||T型をfで初期化し変位と速度のPIDゲインをセットする。|
|void|move(Velocity tag_vel, Velocity now_vel, chrono::microseconds delta_time)|
||手動操縦用。|
||速度のPID制御を行い、出力をT型のcalcに渡す|
|void|auto_move(Coodinate dst, Coodinate pos, chrono::microseconds delta_time)|
||自動制御用。|
||変位のPID制御を行い、出力をT型のcalcに渡す。|

## Pid \<class T>
T型のPID制御を行うクラス。[More...](./ref/Pid.md)
|返り値|メンバ関数|
|---|---|
||Pid(PidGain pid_gain)|
||ゲインをセットする。|
|T|calc(T dst, T now, std::chrono::microseconds delta_time)|
||目標値、現在値、経過時間からPID制御の計算を行う。|
|void|refresh()|
||I値をリセットする。|
|void|set_pid_gain(PidGain pid_gain)|
||ゲインをセットし、refreshを呼び出す。|

## Coodinate, Velocity
座標, 速度を表す構造体。
```C++:CoodinateUnit.h
CoodinateUnit {
  float x_milli;
  float y_milli;
  float ang_rad;
};
```
