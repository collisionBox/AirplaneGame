#include "DebugDraw.h"

namespace Debag
{
	//-----------------------------------------------------------------------------
	// @brief xz平面に原点中心にグリッド線を描画する
	// @param[in] groundSize xz平面に描画するグリッド平面の大きさ
	// @param[in] divideNum  グリッド平面を分割する個数
	//
	// @detail ワールド原点を中心に、縦横groundSizeの大きさをdivideNum分だけ分割
	// された縦横のグリッド線を描画する。
	//-----------------------------------------------------------------------------
	void DrawGrid(float groundSize, int divideNum)
	{
		VECTOR start, end;
		int lineColor = GetColor(0, 128, 0);
		start = end = VGet(0, 0, 0);

		float halfWidth = groundSize * 0.5f;              // グリッド線を引く範囲の半分の幅
		float addWidth = groundSize / (float)divideNum;  // グリッド線を引く間隔

		// 縦線を引く 
		start.z = -halfWidth;
		end.z = +halfWidth;
		for (int ix = 0; ix < divideNum + 1; ix++)
		{
			start.x = end.x = -halfWidth + ix * addWidth;
			DrawLine3D(start, end, lineColor);
		}

		// 横線
		start.x = -halfWidth;
		end.x = +halfWidth;
		for (int iz = 0; iz < divideNum + 1; iz++)
		{
			start.z = end.z = -halfWidth + iz * addWidth;
			DrawLine3D(start, end, lineColor);
		}
	}
}