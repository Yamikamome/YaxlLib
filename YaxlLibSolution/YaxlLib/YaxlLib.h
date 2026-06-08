// -----------------------------------------------------------------------------------------
//  Author        : Yamikamome
//  Description	  : YaxlLibの全機能を一括インクルードできるヘッダー
// -----------------------------------------------------------------------------------------

#ifndef YAXL_LIB_H_
#define YAXL_LIB_H_

#include "YaxlLibLink.h"

/*
*	コア
*/
#include "Core/Input/YaxlInput.h"
#include "Core/Time/YaxlTime.h"

/*
*	グラフィック
*/
#include "Graphics/YaxlGraphicsDevice.h"

/*
*	数学系
*/
#include "Math/YaxlColor.h"
#include "Math/YaxlMath.h"
#include "Math/YaxlMatrix3x3.h"
#include "Math/YaxlMatrix4x4.h"
#include "Math/YaxlQuaternion.h"
#include "Math/YaxlRandom.h"
#include "Math/YaxlVector2.h"
#include "Math/YaxlVector3.h"
#include "Math/YaxlVector4.h"

#endif