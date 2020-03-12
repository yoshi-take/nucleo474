//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義
#include <stdio.h>

#include "hal/hal_tof.h"

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
extern	I2C_HandleTypeDef hi2c1;
PRIVATE CHAR	txBuffer[2]	= {ADR_TOF_MEASURE,ADR_TOF_ID};		// [1]：ToFのID	[0]：ToFのコマンド
PRIVATE CHAR	txID				= ADR_TOF_ID << 1;								// ToFのID（シフトする必要有）

PRIVATE CHAR		rxBuffer[2];		// 受信バッファ(2Byte)

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
PUBLIC SHORT TOF_getData(void){

	SHORT	s_value	= 0;
	HAL_I2C_Master_Transmit(&hi2c1, txID, txBuffer, 2, 1000);				// ID送信→コマンド送信→ID送信
	HAL_I2C_Master_Receive(&hi2c1, txID,rxBuffer, 2, 1000);				// 受信

	s_value		= (SHORT)(rxBuffer[1] | (rxBuffer[0] << 8) );					// 受信したデータの結合

	return s_value;
}

PUBLIC void TOF_check(void){

	printf("s_value = %d \n\r",TOF_getData());

}

