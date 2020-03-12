#ifndef INC_HAL_HAL_TIM_H_
#define INC_HAL_HAL_TIM_H_

#ifdef	__cplusplus
extern	"C"	{
#endif

//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"

//**************************************************
// 定義（define）
//**************************************************

//**************************************************
// 列挙体（enum）
//**************************************************

//**************************************************
// 構造体（struct）
//**************************************************

//**************************************************
// グローバル変数
//**************************************************

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
PUBLIC void INTC_sys(void);
PUBLIC void INTC_sen( void );
PUBLIC void TIM6_Start( void );
PUBLIC void TIM7_Start( void );
PUBLIC void TIME_waitFree( ULONG ul_cnt );

PUBLIC void BlinkTest( void );

#ifdef	__cplusplus
}
#endif

#endif /* INC_HAL_HAL_TIM_H_ */
