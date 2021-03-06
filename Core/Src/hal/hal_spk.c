//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義

#include "hal/hal_spk.h"

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
// *************************************************************************
//   機能		： SPKを鳴らす。
//   注意		： なし
//   メモ		： なし
//   引数		： 周波数(frq)，音符(beat)，テンポ(bpm)
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.3.24			TKR				新規
//		v2.0		2020.5.24			TKR				STM32仕様
// *************************************************************************/
PUBLIC void SPK_on( uint16_t frq, float beat, int bpm  ){

	/* 分周する値を求める */
	uint16_t scale = 0;
	scale	= 100000 / frq - 1;					// 100kHzから分周を行い所望の周波数を出力する
	LL_TIM_SetPrescaler(TIM2,scale);		// 分周値を設定

	/* PWM出力 */
	LL_TIM_OC_SetCompareCH3(TIM2, 849);		// 1700÷2-1（Duty比50%）
	LL_TIM_CC_EnableChannel(TIM2,LL_TIM_CHANNEL_CH3);
	LL_TIM_EnableCounter(TIM2);

	/* 60000(msec)÷bpm = 4分音符の長さ(msec) */
	LL_mDelay( (int)(60000.0f/bpm*4.0f/beat-10.0f ));

	/* PWM止める */
	LL_TIM_CC_DisableChannel(TIM2,LL_TIM_CHANNEL_CH3);		// TIM2 Channel3停止
}


// *************************************************************************
//   機能		： SPKを止める(テストver)。
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.3.31			TKR				新規
//		v2.0		2020.5.24			TKR				STM32仕様
// *************************************************************************/
PUBLIC void SPK_Off(void){

	LL_TIM_CC_DisableChannel(TIM2,LL_TIM_CHANNEL_CH3);		// PWMを止める

}

// *************************************************************************
//   機能		： SPKを使ったデバッグ用
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.11.15			TKR				新規
// *************************************************************************/
PUBLIC void SPK_debug( void ){
	SPK_on(A4,16.0f,240);
}

// *************************************************************************
//   機能		： Success音
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.11.25			TKR				新規
// *************************************************************************/
PUBLIC void SPK_success( void ){

	SPK_on(Eb4,16.0f,120);
	SPK_on(E4,16.0f,120);
	SPK_on(F4,16.0f,120);

}

// *************************************************************************
//   機能		： バッテリー切れの警告音
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2020.12.13			TKR				新規
// *************************************************************************/
PUBLIC void SPK_alert( void ){
	SPK_on(C4,16.0f,120);
}
