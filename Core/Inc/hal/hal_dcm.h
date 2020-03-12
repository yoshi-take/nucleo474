#ifndef		__HAL_DCM_H
#define		__HAL_DCM_H

#ifdef	__cplusplus
extern	"C"	{
#endif

//**************************************************
// インクルードファイル（include）
//**************************************************
#include "typedefine.h"

//**************************************************
// 定義（define）
//**************************************************

//**************************************************
// 列挙体（enum）
//**************************************************
/* モータID */
typedef enum{
	DCM_R = 0,					// 右モータ
	DCM_L,						// 左モータ
	DCM_SUC,					// 吸引モータ
	DCM_MAX,
}enDCM_ID;

/* 回転方向 */
typedef	enum{
	CW	=0,						// 時計回り
	CCW,						// 反時計回り
}enROT_DIR;

//**************************************************
// 構造体（struct）
//**************************************************

//**************************************************
// グローバル変数
//**************************************************

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
PUBLIC void DCM_setDirCw( enDCM_ID en_id );
PUBLIC void DCM_setDirCcw( enDCM_ID en_id );
PUBLIC void DCM_staMot( enDCM_ID en_id );
PUBLIC void DCM_stopMot( enDCM_ID en_id);
PUBLIC void DCM_setPwmDuty( enDCM_ID en_id, unsigned short us_duty);

#ifdef	__cplusplus
}
#endif

#endif
