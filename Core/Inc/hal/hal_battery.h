/*
 * hal_battery.h
 *
 *  Created on: Jan 26, 2020
 *      Author: TAKERU
 */

#ifndef INC_HAL_HAL_BATTERY_H_
#define INC_HAL_HAL_BATTERY_H_

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

//**************************************************
// 構造体（struct）
//**************************************************

//**************************************************
// グローバル変数
//**************************************************

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
PUBLIC void hal_ADC3Start(void);
PUBLIC USHORT hal_ADC3SingleConversion(void);
PUBLIC	void BAT_init(void);
PUBLIC void BAT_Pol( void );
PUBLIC void BAT_Check( void );
PUBLIC FLOAT BAT_getLv( void );

#ifdef	__cplusplus
}
#endif

#endif /* INC_HAL_HAL_BATTERY_H_ */
