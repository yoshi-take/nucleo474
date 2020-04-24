//**************************************************
// インクルードファイル（include）
//**************************************************
#include <hal/hal_battery.h>
#include "main.h"
#include "typedefine.h"
#include <stdio.h>

#include "app/mode.h"
#include "hal/hal_led.h"
#include "hal/hal_dcm.h"
#include "hal/hal_tof.h"
#include "hal/hal_gyro.h"
#include "hal/hal_enc.h"
#include "hal/hal_dist.h"


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
PRIVATE enMODE		en_Mode;		// 現在のモード

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************

// *************************************************************************
//   機能		： モードを実行する。
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.12.31			TKR				新規
// *************************************************************************/
PUBLIC void	MODE_exe( void ){

	switch( en_Mode ){

		case MODE_0:
			break;

		case MODE_1:
			 DCM_setDirCw(DCM_R);
			 DCM_setDirCcw(DCM_L);
			 DCM_setPwmDuty(DCM_R, 50);
			 DCM_setPwmDuty(DCM_L, 50);
			break;

		case MODE_2:
			printf("%3f\n\r",2.5);
			DCM_stopMot(DCM_L);
			LED_onAll();
			DCM_staMot(DCM_R);
			break;

		case MODE_3:
			DCM_stopMot(DCM_R);
			DCM_staMot(DCM_L);
			break;

		case MODE_4:
			hal_ADC3Start();

			while(1){
				printf("%d\n\r",hal_ADC3SingleConversion());
				LL_mDelay(500);
			}

			break;

		case MODE_5:
			while(1){
				TOF_getData();
				TOF_check();
				LL_mDelay(500);
			}
			break;

		case MODE_6:
			while(1){
				GYRO_get_WHOAMI();
				//printf("NowAngleSpeed:%5f\n\r",GYRO_getNowAngleSpeed());
				LL_mDelay(20);
			}
			break;

		case MODE_7:
			//ENC_getCnt(ENC_R);
			ENC_Check();
			break;

		case MODE_8:
			LL_GPIO_SetOutputPin(IR_SIDE_R_GPIO_Port, IR_SIDE_R_Pin);
			LL_GPIO_SetOutputPin(IR_SIDE_L_GPIO_Port, IR_SIDE_L_Pin);
			LL_GPIO_SetOutputPin(IR_FRONT_L_GPIO_Port, IR_FRONT_L_Pin);
			LL_GPIO_SetOutputPin(IR_FRONT_R_GPIO_Port, IR_FRONT_R_Pin);
			break;

		case MODE_9:
			ADC1_DMA1_TransferComplete_Callback();
			break;

		case MODE_10:
			while(1){
				printf("データ\n\r");
				printf("%d\n\r",ToF_readRangeContinuous());
				LL_mDelay(100);
			}
			break;

		case MODE_11:
			break;

		case MODE_12:
			break;

		case MODE_13:
			break;

		case MODE_14:
			break;

		case MODE_15:
			break;

		default:
			break;

	}

}

// *************************************************************************
//   機能		： 予約されたモードに変更する。
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.2.5			TKR				新規
// *************************************************************************/
PRIVATE void MODE_chg( enMODE en_mode ){

	LED_offAll();

	switch( en_mode ){

		case MODE_0:
//			SPK_on(A4,16.0f,120);
			break;

		case MODE_1:
			/*
			SPK_on(C4,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			break;

		case MODE_2:
			/*
			SPK_on(D4,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			break;

		case MODE_3:
			/*
			SPK_on(E4,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			break;

		case MODE_4:
			/*
			SPK_on(F4,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			break;

		case MODE_5:
			/*
			SPK_on(G4,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);

			break;

		case MODE_6:
			/*
			SPK_on(A4,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			break;

		case MODE_7:
			/*
			SPK_on(B4,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			break;

		case MODE_8:
			/*
			SPK_on(C5,16.0f,120);
			*/
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		case MODE_9:
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		case MODE_10:
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		case MODE_11:
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		case MODE_12:
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		case MODE_13:
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		case MODE_14:
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		case MODE_15:
			LL_GPIO_SetOutputPin(LED0_GPIO_Port, LED0_Pin);
			LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin);
			LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
			LL_GPIO_SetOutputPin(LED3_GPIO_Port, LED3_Pin);
			break;

		default:
			break;

	}

	en_Mode = en_mode;	// 現在のモード
}

// *************************************************************************
//   機能		： モードを加算変更する。
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.2.5			TKR				新規
// *************************************************************************/
PUBLIC void MODE_inc( void ){

	en_Mode++;

	/* 最大値チェック */
	if( MODE_MAX == en_Mode ){
		en_Mode = MODE_0;
	}

	MODE_chg(en_Mode);		// モード変更

}

