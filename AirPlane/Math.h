#pragma once
#include "DxLib.h"
#include "Math.h"

// @brief ベクトル同士の加算
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

// @brief ベクトル同士の減算
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

// @brief ベクトルのスカラー倍
VECTOR operator*(float s, const VECTOR& rhs);

// @brief ベクトルのスカラー倍
VECTOR operator*(const VECTOR& lhs, float s);

VECTOR operator*(const VECTOR& lhs, VECTOR rhs);

// @brief += VECTORの演算子
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

// @brief *= VECTORのスカラー倍の複合代入演算子
VECTOR operator*=(VECTOR& lhs, float rhs);

// @brief ベクトルを割る.
VECTOR Division(const VECTOR& In, float num);

// @brief ２つのベクトルの角度はほぼ同じか
bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);

// @brief nowVecからdirVecの最短の回転方向を調べる（Y軸回転を想定)
float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);

// @brief nowVecから aimVecに向かってdegreeVerociyの速度でY回転する.
VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity);

// @brief 度数法→弧度法
float ToRadian(float degree);

// @brief ベクトルの大きさを求める.
float VectorSize(VECTOR& vec);


// 参考サイト:http://noa1105.seesaa.net/article/239449116.html
typedef struct
{
	float t;// real.
	float x;
	float y;
	float z;
} QUATERNION;

// @brief クォータニオンの計算.
QUATERNION operator*(QUATERNION q1, QUATERNION q2);

// @brief 回転クォータニオン.
QUATERNION CreateRotationQuaternion(float radian, VECTOR Axis);

// @brief 位置クォータニオン.
QUATERNION CreateXYZToQuaternion(float PosX, float PosY, float PosZ);
QUATERNION CreateXYZToQuaternion(VECTOR pos);

// @brief クォータニオンから回転行列へ.
MATRIX QuaternionToMatrix(QUATERNION q);

// MATRIX to VECTOR
VECTOR ToXAxis(MATRIX mat);
VECTOR ToYAxis(MATRIX mat);
VECTOR ToZAxis(MATRIX mat);

float QSize(QUATERNION in);

QUATERNION QNorm(QUATERNION in);

VECTOR QtoV(QUATERNION in);// 駄目だ！.

const MATRIX InitMat = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

VECTOR MtoV(MATRIX mat);

// @brief mat * mat
MATRIX operator*(MATRIX lhs, MATRIX rhs);

MATRIX operator*=(MATRIX lhs, MATRIX rhs);
