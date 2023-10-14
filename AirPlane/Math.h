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

// @brief マトリクス同士の減算.
MATRIX operator-(const MATRIX& lhs, MATRIX rhs);

// @brief ベクトルを割る.
VECTOR Division(const VECTOR& In, float num);

// @brief ２つのベクトルの角度はほぼ同じか
bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);

// @brief nowVecからdirVecの最短の回転方向を調べる（Y軸回転を想定)
float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);

// @brief nowVecから aimVecに向かってdegreeVerociyの速度でY回転する.
VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity);

// @brief nowVecから aimVecに向かってradianVerociyの速度でY回転する.
VECTOR RotateForAimVecYAxisRad(const VECTOR& nowVec, const VECTOR& aimVec, float radianvVelocity);

// @brief 度数法→弧度法
float ToRadian(float degree);

// @breif 弧度法→度数法.
float ToDegree(float radian);


// 参考サイト:http://noa1105.seesaa.net/article/239449116.html
typedef struct
{
	float t;// real.
	float x;
	float y;
	float z;
} QUATERNION;

QUATERNION operator*(QUATERNION q1, QUATERNION q2);

QUATERNION CreateRotationQuaternion(float radian, VECTOR Axis);

QUATERNION CreateXYZToQuaternion(float PosX, float PosY, float PosZ);
QUATERNION CreateXYZToQuaternion(VECTOR pos);

MATRIX QuaternionToMatrix(QUATERNION q);

// MATRIX to VECTOR

VECTOR ToXAxis(MATRIX mat);
VECTOR ToYAxis(MATRIX mat);
VECTOR ToZAxis(MATRIX mat);

float QSize(QUATERNION in);

QUATERNION QNorm(QUATERNION in);

VECTOR GetTransMat2Vec(MATRIX matrix);

// @brief mat * mat
MATRIX operator*(MATRIX lhs, MATRIX rhs);

MATRIX operator*=(MATRIX lhs, MATRIX rhs);

// @brief MATRIX TO VECTOR pos.
VECTOR M2Pos(MATRIX matrix);

float FormedAngle(const VECTOR& v1, const VECTOR& v2);