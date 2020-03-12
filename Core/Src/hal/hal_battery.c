//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"				// 型定義
#include <stdio.h>

#include "hal/hal_battery.h"		// BATT
#include "hal/hal_led.h"			// LED

//**************************************************
// 定義（define）
//**************************************************
#define	BAT_LOW			(7800.0f)		// 残量やばい：3.6V(1cell)

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

PUBLIC void hal_ADC3Start(void){
	 LL_ADC_Enable(ADC3);
}

PUBLIC USHORT hal_ADC3SingleConversion(void){
	USHORT data;
	LL_ADC_REG_StartConversion(ADC3);
	while(LL_ADC_IsActiveFlag_EOC(ADC3) ==0 ){
		// 変換待ち
	}
	LL_ADC_ClearFlag_EOC(ADC3);
	data	= LL_ADC_REG_ReadConversionData12(ADC3);

	return data;
}

// *************************************************************************
//   機能		： バッテリ電圧を取得する
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値	： 電圧[mV]
// **************************    履    歴    *******************************
// 		v1.0		2019.4.2			TKR			新規
// *************************************************************************/
PUBLIC FLOAT BAT_getLv( void ){
#if 0
	FLOAT f_val		= (FLOAT)( us_BatLvAve + 1 );

	return ( f_val / 4096 * 3300 * 4.0f );
#endif
}

// *************************************************************************
//   機能		： バッテリ監視用ポーリング関数
//   注意		： なし
//   メモ		： 割り込みから実行される
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.2.5			TKR			新規
// *************************************************************************/
PUBLIC void BAT_Pol( void )
{
#if 0
	static	USHORT	us_BatLv[5] = { 4095, 4095, 4095, 4095, 4095 };		// バッテリレベル
	FLOAT	f_temp	= 0;

	/*  平均値を取得するため、データのバッファ処理を行う  */
	us_BatLv[4] = us_BatLv[3];
	us_BatLv[3] = us_BatLv[2];
	us_BatLv[2] = us_BatLv[1];
	us_BatLv[1] = us_BatLv[0];

	/* 最新の値を格納 */
	//us_BatLv[0]

	/* 電圧平均化 */
	us_BatLvAve = ( us_BatLv[0] + us_BatLv[1] + us_BatLv[2] + us_BatLv[3] + us_BatLv[4] ) / 5;

	/* 電圧値取得 */
	f_temp	= BAT_getLv();

	/*  残量に応じてLEDを表示  */
	//if( f_temp < BAT_LOW )ブザー鳴らす
#endif
}

// *************************************************************************
//   機能		： バッテリ電圧を表示する
//   注意		： なし
//   メモ		： 割り込みから実行される
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.2.5			TKR			新規
// *************************************************************************/
PUBLIC void BAT_Check(void){
#if 0
	LED_onAll();

	while(1){
		printf("[電源電圧] %5.2f[V]\n\r",BAT_getLv()/1000);
		TIME_wait(500);
	}
#endif
}
