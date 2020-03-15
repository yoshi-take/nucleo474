//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"
#include <stdio.h>

#include "hal/hal_tim.h"
#include "hal/hal_led.h"
#include "hal/hal_dist.h"
#include "hal/hal_gyro.h"

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
PRIVATE	VUSHORT		uc_Msec;				// 内部時計[msec]
PRIVATE	VUCHAR		uc_Sec;					// 内部時計[sec]
PRIVATE	VUCHAR		uc_Min;					// 内部時計[min]
PRIVATE VULONG			ul_Wait;				// 1msecのwaitに使用する カウンタ[msec]
PUBLIC	VUCHAR			uc_CntSec;			// 減速時にループから抜け出せなくなったとき用[sec]

PUBLIC int16_t 				counter=0;

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
PUBLIC void BlinkTest( void ){
	// 変数counterは外部変数として定義してあるものとする。
	  counter++;

	  if( counter > 999 ){
		  LED_onAll();
	  } else {
		  LED_offAll();
	  }

	  if( counter > 1999 ) counter = 0;
}


// *************************************************************************
//   機能			： 割り込み関数、システム用（msecタイマ）
//   注意			： なし
//   メモ			： MTU1のTGRA割り込み、1msec毎に関数が実行される。
//   引数			： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.2.6			TKR			新規
// *************************************************************************/
PUBLIC void INTC_sys(void){

	/* ---------- */
	/*  内部時計  */
	/* ---------- */
	uc_Msec++;					// msec
	if( uc_Msec > 999 ){		// msec → sec
		uc_Msec  = 0;
		uc_Sec++;

		//if( uc_CntSec != TIME_THRE_WAIT )uc_CntSec++;	// 減速チェック時以外ではカウントしない

	}
	if( uc_Sec > 59 ){			// sec → min
		uc_Sec = 0;
		uc_Min++;
	}

	/* ----------------------- */
	/*  S/Wウェイト・カウンタ  */
	/* ----------------------- */
	ul_Wait++;
	ul_Wait %= 6000000;			// 10 min (= 6000000 カウント) で 0 クリア

	//CTRL_pol();

	return;
}


// *************************************************************************
//   機能			： 割り込み関数、センサ用
//   注意			： なし
//   メモ			： TIM7割り込み、0.25msec毎に関数が実行される。
//					： 正常にマイコンが動作している場合、250usec周期で
//					： 距離センサ0 → 距離センサ1 → ジャイロセンサ の順でスキャンする。
//					： 従って、1センサのスキャン周期は1msecとなる。
//   引数			： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.2.6			TKR			新規
// *************************************************************************/
PUBLIC void INTC_sen( void )
{
	static UCHAR	i = 0;

	/* センサ処理  */
	switch( i ){
		case 0:		// ジャイロセンサ
//			GYRO_Pol();		// 先に平均値からジャイロの値を算出する
//			GYRO_getVal();
			break;

		case 1:		// 前壁センサ
			DIST_Pol_Front();
			break;

		case 2:		// 加速度センサ
			//GYRO_getAccVal();		// フェイルセーフ用
			break;

		case 3:		// 横壁センサ
			DIST_Pol_Side();
			break;


	}

	i = ( i + 1 ) % 4;			// roop

	return;
}


// *************************************************************************
//   機能		： TIM6の動作開始
//   注意		： なし
//   メモ		： 制御の割り込み(1msec)
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
//		v1.0		2020.2.6			TKR				新規
// *************************************************************************/
PUBLIC void TIM6_Start( void ){
	LL_TIM_EnableIT_UPDATE(TIM6);
	LL_TIM_EnableCounter(TIM6);
}

// *************************************************************************
//   機能		： TIM7の動作開始
//   注意		： なし
//   メモ		： センサの割り込み(0.25msec)
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
//		v1.0		2020.2.6			TKR				新規
// *************************************************************************/
PUBLIC void TIM7_Start( void ){
	LL_TIM_EnableIT_UPDATE(TIM7);
	LL_TIM_EnableCounter(TIM7);
}



// *************************************************************************
//   機能		： 指定したフリーカウント間、S/Wウェイトする。
//   注意		： なし
//   メモ		： ul_cnt: カウント値
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.2.09			TKR			新規
// *************************************************************************/
PUBLIC void TIME_waitFree( ULONG ul_cnt )
{
	while( ul_cnt-- );			// 0になるまでディクリメント
}
