//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義
#include <stdio.h>

#include "hal/hal_enc.h"

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


PUBLIC void ENC_GetDiv( LONG* p_r, LONG* p_l )
{

}
