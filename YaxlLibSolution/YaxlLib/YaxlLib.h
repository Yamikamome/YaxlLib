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
#include "Yaxl/Core/Audio/YaxlAudio.h"
#include "Yaxl/Core/Collider/2D/BoxCollider2D.h"
#include "Yaxl/Core/Collider/2D/CircleCollider2D.h"
#include "Yaxl/Core/Collider/2D/RectCollider2D.h"
#include "Yaxl/Core/Input/YaxlInput.h"
#include "Yaxl/Core/Time/YaxlTime.h"
#include "Yaxl/Core/Transform/YaxlTransform.h"
#include "Yaxl/Core/Transform/YaxlTransform2D.h"

/*
*	グラフィック
*/
#include "Yaxl/Graphics/YaxlGraphics.h"
#include "Yaxl/Graphics/YaxlShader.h"
#include "Yaxl/Graphics/YaxlTexture.h"

/*
*	数学系
*/
#include "Yaxl/Math/YaxlColor.h"
#include "Yaxl/Math/YaxlMath.h"
#include "Yaxl/Math/YaxlMatrix3x3.h"
#include "Yaxl/Math/YaxlMatrix4x4.h"
#include "Yaxl/Math/YaxlQuaternion.h"
#include "Yaxl/Math/YaxlRandom.h"
#include "Yaxl/Math/YaxlRect.h"
#include "Yaxl/Math/YaxlVector2.h"
#include "Yaxl/Math/YaxlVector3.h"
#include "Yaxl/Math/YaxlVector4.h"

#endif