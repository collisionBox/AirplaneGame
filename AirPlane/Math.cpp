#include "Math.h"
#include <math.h>

//-------------------------------------------------------------------------------
	// @brief ベクトル同士の加算
	//-------------------------------------------------------------------------------
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = lhs.x + rhs.x;
	ret.y = lhs.y + rhs.y;
	ret.z = lhs.z + rhs.z;
	return ret;
}
//-------------------------------------------------------------------------------
// @brief ベクトル同士の減算
//-------------------------------------------------------------------------------
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = lhs.x - rhs.x;
	ret.y = lhs.y - rhs.y;
	ret.z = lhs.z - rhs.z;
	return ret;
}
//-------------------------------------------------------------------------------
// @brief ベクトルのスカラー倍
//-------------------------------------------------------------------------------
VECTOR operator*(float s, const VECTOR& rhs)
{
	VECTOR ret;
	ret.x = s * rhs.x;
	ret.y = s * rhs.y;
	ret.z = s * rhs.z;
	return ret;
}
//-------------------------------------------------------------------------------
// @brief ベクトルのスカラー倍
//-------------------------------------------------------------------------------
VECTOR operator*(const VECTOR& lhs, float s)
{
	VECTOR ret;
	ret.x = s * lhs.x;
	ret.y = s * lhs.y;
	ret.z = s * lhs.z;
	return ret;
}
//-------------------------------------------------------------------------------
// @brief ベクトル×ベクトル.
//-------------------------------------------------------------------------------
VECTOR operator*(const VECTOR& lhs, VECTOR rhs)
{
	VECTOR ret;
	ret.x = lhs.x * rhs.x;
	ret.y = lhs.y * rhs.y;
	ret.z = lhs.z * rhs.z;
	return ret;
}
//-------------------------------------------------------------------------------
// @brief += VECTORの演算子
//-------------------------------------------------------------------------------
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

//-------------------------------------------------------------------------------
// @brief *= VECTORのスカラー倍の複合代入演算子
//-------------------------------------------------------------------------------
VECTOR operator*=(VECTOR& lhs, float rhs)
{
	lhs = lhs * rhs;
	return lhs;
}
//-------------------------------------------------------------------------------
// @brief ベクトルを割る.
//-------------------------------------------------------------------------------
VECTOR Division(const VECTOR& In, float num)
{
	VECTOR vector;
	vector.x = In.x / num;
	vector.y = In.y / num;
	vector.z = In.z / num;
	return vector;
}
MATRIX operator-(const MATRIX& lhs, MATRIX rhs)
{
	MATRIX ans;
	ans.m[0][0] = lhs.m[0][0] - rhs.m[0][0];
	ans.m[0][1] = lhs.m[0][1] - rhs.m[0][1];
	ans.m[0][2] = lhs.m[0][2] - rhs.m[0][2];
	ans.m[0][3] = lhs.m[0][3] - rhs.m[0][3];
	ans.m[1][0] = lhs.m[1][0] - rhs.m[1][0];
	ans.m[1][1] = lhs.m[1][1] - rhs.m[1][1];
	ans.m[1][2] = lhs.m[1][2] - rhs.m[1][2];
	ans.m[1][3] = lhs.m[1][3] - rhs.m[1][3];
	ans.m[2][0] = lhs.m[2][0] - rhs.m[2][0];
	ans.m[2][1] = lhs.m[2][1] - rhs.m[2][1];
	ans.m[2][2] = lhs.m[2][2] - rhs.m[2][2];
	ans.m[2][3] = lhs.m[2][3] - rhs.m[2][3];
	ans.m[3][0] = lhs.m[3][0] - rhs.m[3][0];
	ans.m[3][1] = lhs.m[3][1] - rhs.m[3][1];
	ans.m[3][2] = lhs.m[3][2] - rhs.m[3][2];
	ans.m[3][3] = lhs.m[3][3] - rhs.m[3][3];
	return ans;
}
//-------------------------------------------------------------------------------
// @brief ２つのベクトルの角度はほぼ同じか
// @param[in] v1 調査したいベクトル1
// @param[in] v2 調査したいベクトル2
// @return 二つがほぼ同じ角度であれば true 異なればfalseを返す
//-------------------------------------------------------------------------------
bool IsNearAngle(const VECTOR& v1, const VECTOR& v2)
{
	float dot = VDot(v1, v2);
	if (dot > 0.999f)
	{
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------
// @param[in] nowVec 現在の方向ベクトル
// @param[in] dirVec 目標方向ベクトル
// @return float 時計回り方向の時は+1.0 反時計回り方向の時は -1.0を返す.
//-------------------------------------------------------------------------------
float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
{
	VECTOR axis;
	axis = VCross(nowVec, dirVec);
	if (axis.y < 0.0f)
	{
		return -1.0f;
	}
	return 1.0f;
}

//-------------------------------------------------------------------------------
// @brief nowVecから aimVecに向かってdegreeVerociyの速度でY回転する.
// @param[in] nowVec 現在の方向ベクトル
// @param[in] aimVec 目標方向ベクトル
//-------------------------------------------------------------------------------
VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity)
{
	// 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
	float rotRadian = (DX_PI_F * degreeVerocity / 180.0f);
	rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

	// Y軸回転行列を作成する
	MATRIX yrotMat = MGetRotY(rotRadian);

	// Y軸回転する
	VECTOR rotVec;
	rotVec = VTransform(nowVec, yrotMat);

	return rotVec;
}

//-------------------------------------------------------------------------------
// @brief nowVecから aimVecに向かってdegreeVerociyの速度でY回転する.
// @param[in] nowVec 現在の方向ベクトル
// @param[in] aimVec 目標方向ベクトル
//-------------------------------------------------------------------------------
VECTOR RotateForAimVecYAxisRad(const VECTOR& nowVec, const VECTOR& aimVec, float radianvVelocity)
{
	// 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
	radianvVelocity *= CalcRotationDirectionYAxis(nowVec, aimVec);

	// Y軸回転行列を作成する
	MATRIX yrotMat = MGetRotY(radianvVelocity);

	// Y軸回転する
	VECTOR rotVec;
	rotVec = VTransform(nowVec, yrotMat);

	return rotVec;
}


float ToRadian(float degree)
{
	return degree * DX_PI_F / 180.0f;
}

float ToDegree(float radian)
{
	return radian * (180 / DX_PI_F);
}

QUATERNION operator*(QUATERNION q1, QUATERNION q2)
{
	QUATERNION ans;
	float d1, d2, d3, d4;

	// tのパラメータの計算.
	d1 = q1.t * q2.t;
	d2 = -q1.x * q2.x;
	d3 = -q1.y * q2.y;
	d4 = -q1.z * q2.z;
	ans.t = d1 + d2 + d3 + d4;

	// xパラメータの計算.
	d1 = q1.t * q2.x;
	d2 = q2.t * q1.x;
	d3 = q1.y * q2.z;
	d4 = -q1.z * q2.y;
	ans.x = d1 + d2 + d3 + d4;

	// ｙパラメータの計算.
	d1 = q1.t * q2.y;
	d2 = q2.t * q1.y;
	d3 = q1.z * q2.x;
	d4 = -q1.x * q2.z;
	ans.y = d1 + d2 + d3 + d4;

	// zパラメータの計算.
	d1 = q1.t * q2.z;
	d2 = q2.t * q1.z;
	d3 = q1.x * q2.y;
	d4 = -q1.y * q2.x;
	ans.z = d1 + d2 + d3 + d4;

	return ans;
	
}
//-------------------------------------------------------------------------------
// @brief 指定軸を指定角回転させる
// @param[in] radian 回転させる角度
// @param[in] Axis 回転軸.
//-------------------------------------------------------------------------------
QUATERNION CreateRotationQuaternion(float radian, VECTOR Axis)
{
	QUATERNION ans;
	float norm;
	float ccc, sss;

	//初期化.
	ans.t = ans.x = ans.y = ans.z = 0.0f;

	// 正規化.
	norm = Axis.x * Axis.x + Axis.y * Axis.y + Axis.z * Axis.z;
	if (norm <= 0.0f)
	{
		return ans;
	}

	norm = 1.0f / sqrtf(norm);
	Axis.x *= norm;
	Axis.y *= norm;
	Axis.z *= norm;

	ccc = cosf(0.5f * radian);
	sss = sinf(0.5f * radian);

	ans.t = ccc;
	ans.x = sss * Axis.x;
	ans.y = sss * Axis.y;
	ans.z = sss * Axis.z;

	return ans;
}

QUATERNION CreateXYZToQuaternion(float PosX, float PosY, float PosZ)
{
	QUATERNION ans;

	ans.t = 0.0f;
	ans.x = PosX;
	ans.y = PosY;
	ans.z = PosZ;

	return ans;
}

QUATERNION CreateXYZToQuaternion(VECTOR pos)
{
	QUATERNION ans;

	ans.t = 0.0f;
	ans.x = pos.x;
	ans.y = pos.y;
	ans.z = pos.z;

	return ans;
}

MATRIX QuaternionToMatrix(QUATERNION q)
{
	MATRIX mat = MGetIdent();
	// x軸.
	mat.m[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat.m[0][1] = 2.0f * q.x * q.y + 2.0f * q.t * q.z;
	mat.m[0][2] = 2.0f * q.x * q.z - 2.0f * q.t * q.y;

	// y軸.
	mat.m[1][0] = 2.0f * q.x * q.y - 2.0f * q.t * q.z;
	mat.m[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	mat.m[1][2] = 2.0f * q.y * q.z + 2.0f * q.t * q.x;

	// z軸.
	mat.m[2][0] = 2.0f * q.x * q.z + 2.0f * q.t * q.y;
	mat.m[2][1] = 2.0f * q.y * q.z - 2.0f * q.t * q.x;
	mat.m[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;

	return mat;
}

// @brief マトリックスをX軸方向ベクトルに変換する
VECTOR ToXAxis(MATRIX mat)
{
	return VGet(mat.m[0][0], mat.m[0][1], mat.m[0][2]);
}

// @brief マトリックスをY軸方向ベクトルに変換する
VECTOR ToYAxis(MATRIX mat)
{
	return VGet(mat.m[1][0], mat.m[1][1], mat.m[1][2]);
}

// @brief マトリックスをZ軸方向ベクトルに変換する
VECTOR ToZAxis(MATRIX mat)
{
	return VGet(mat.m[2][0], mat.m[2][1], mat.m[2][2]);
}

float QSize(QUATERNION in)
{
	return sqrtf(in.t * in.t + in.x * in.x + in.y * in.y + in.z * in.z);
}

QUATERNION QNorm(QUATERNION in)
{
	float size;
	size = QSize(in);
	QUATERNION ans;
	ans.t = in.t / size;
	ans.x = in.x / size;
	ans.y = in.y / size;
	ans.z = in.z / size;
	
	return ans;
}

VECTOR GetTransMat2Vec(MATRIX matrix)
{
	VECTOR ret;
	ret.x = matrix.m[3][0];
	ret.y = matrix.m[3][1];
	ret.z = matrix.m[3][2];
	return ret;
}

MATRIX operator*(MATRIX lhs, MATRIX rhs)
{
	return MMult(lhs, rhs);
}
MATRIX operator*=(MATRIX lhs, MATRIX rhs)
{
	lhs = lhs * rhs;
	return lhs;
}
VECTOR M2Pos(MATRIX matrix)
{
	VECTOR ret;
	ret.x = matrix.m[3][0];
	ret.y = matrix.m[3][1];
	ret.z = matrix.m[3][2];
	
	return ret;
}

float FormedAngle(const VECTOR& v1, const VECTOR& v2)
{
	float dot = VDot(v1, v2);
	float sizeA = VSize(v1);
	float sizeB = VSize(v2);
	float ret = acosf(dot / (sizeA * sizeB));

	return ret;
}
