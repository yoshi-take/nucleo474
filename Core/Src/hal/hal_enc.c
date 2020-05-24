//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義
#include <stdio.h>

#include "hal/hal_enc.h"
#include "hal/hal_dcm.h"

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
extern	SPI_HandleTypeDef hspi1;

PRIVATE UINT 	enc_Abs_R		= 0;		//	絶対角（0~16383）
PRIVATE UINT 	enc_Abs_L			= 0;		//	絶対角（0~16383）
PRIVATE UINT	enc_Abs_Bef_R		= 0;
PRIVATE UINT	enc_Abs_Bef_L		= 0;


//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
PUBLIC SHORT ENC_getCnt( enENC_ID en_id ){

	SHORT	tx_data[2];
	SHORT	rx_data[2];

	tx_data[0]	= 0x3FFF;
	tx_data[1]	= 0x0000;		// ダミー

	if( en_id == ENC_R ){		// 右
		 LL_GPIO_ResetOutputPin(CS_R_GPIO_Port, CS_R_Pin);
		 HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 1, 1);
		 LL_GPIO_SetOutputPin(CS_R_GPIO_Port, CS_R_Pin);
	}else{								// 左
		LL_GPIO_ResetOutputPin(CS_L_GPIO_Port, CS_L_Pin);
		HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 1, 1);
		LL_GPIO_SetOutputPin(CS_L_GPIO_Port, CS_L_Pin);
	}

	rx_data[0] = rx_data[0] &0x3FFF;

	return	rx_data[0];
}

// *************************************************************************
//   機能		： エンコーダのカウント値（パルス数）を取得する
//   注意		： なし
//   メモ		： 中間値からの差分
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12
// *************************************************************************/
PUBLIC void ENC_Check( void ) {
	while(1){
		printf("ENC_R:%5d ENC_L:%5d\n\r",ENC_getCnt(ENC_R),ENC_getCnt(ENC_L));
		LL_mDelay(100);
	}
}


// *************************************************************************
//   機能		： エンコーダのカウント値（パルス数）を取得する
//   注意		： なし
//   メモ		： 中間値からの差分
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2013.12.03		外川			新規
//		v2.0		2018.9.9			吉田			1717仕様に変更
//		v3.0		2020.5.24			TKR			ハーフ仕様に変更
// *************************************************************************/
PUBLIC void ENC_GetDiv( LONG* p_r, LONG* p_l )
{
	LONG tmpErr_R = 0;
	LONG tmpErr_L = 0;

	ENC_clr();		// 絶対角の取得

	tmpErr_R	= (LONG)(enc_Abs_R - enc_Abs_Bef_R);
	tmpErr_L	= (LONG)(enc_Abs_L - enc_Abs_Bef_L);

	enc_Abs_Bef_R	= enc_Abs_R;
	enc_Abs_Bef_L	= enc_Abs_L;

	/* 右側 */
	if(ENC_getSignRot(ENC_R) == 0){	// 正方向に回転
		if(tmpErr_R < 0){
			tmpErr_R = tmpErr_R + ENC_RESET_VAL;
		}else{
			// オーバーフローしていないので何もしない
		}
	}else if(ENC_getSignRot(ENC_R) == 1){	// 負方向に回転
		if(tmpErr_R > 0){
			tmpErr_R = tmpErr_R - ENC_RESET_VAL;
		}else{
			// オーバーフローしていないので何もしない
		}
	}

	/* 左側 */
	if(ENC_getSignRot(ENC_L) == 0){	// 正方向に回転
		if(tmpErr_L < 0){
			tmpErr_L = tmpErr_L + ENC_RESET_VAL;
		}else{
			// オーバーフローしていないので何もしない
		}
	}else if(ENC_getSignRot(ENC_L) == 1){	// 負方向に回転
		if(tmpErr_L > 0){
			tmpErr_L = tmpErr_L - ENC_RESET_VAL;
		}else{
		// オーバーフローしていないので何もしない
		}
	}

	*p_r	= tmpErr_R;
	*p_l = tmpErr_L;
}

// *************************************************************************
//   機能		： エンコーダのカウントをクリア
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.4.14			TKR			新規
// *************************************************************************/
PUBLIC void ENC_clr( void )
{
	enc_Abs_R = ENC_getCnt(ENC_R);
	enc_Abs_L = ENC_getCnt(ENC_L);
}


// *************************************************************************
//   機能		： エンコーダのカウント方向を取得する
//   注意		： なし
//   メモ		：
//   引数		：
//   返り値	： 0：正		1：負
// **************************    履    歴    *******************************
// 		v1.0		2020.5.24			TKR			新規
// *************************************************************************/
PUBLIC BOOL ENC_getSignRot(enENC_ID en_id){

/*
	if(en_id ==ENC_R){
		if((en_Type == 6)||(((en_Type == 7)||(en_Type == 8)||(en_Type == 9))&&(en_Turntype == Right)){
			return	1;
		}else{
			return	0;
		}
	}else if(en_id ==ENC_L){
		if((en_Type == 6)||(((en_Type == 7)||(en_Type == 8)||(en_Type == 9))&&(en_Turntype == Left)){
			return	1;
		}else{
			return	0;
		}
	}
*/
}
