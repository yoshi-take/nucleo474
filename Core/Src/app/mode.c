//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"
#include <stdio.h>

#include "parameter.h"
#include "app/mode.h"
#include "hal/hal_led.h"
#include "hal/hal_dcm.h"
#include "hal/hal_tof.h"
#include "hal/hal_gyro.h"
#include "hal/hal_enc.h"
#include "hal/hal_dist.h"
#include "hal/hal_spk.h"
#include "hal/hal_battery.h"


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
PRIVATE enMODE		en_Mode;				// 現在のモード
PRIVATE LONG			l_DiffCnt;			// パルスカウントの微分値
PRIVATE LONG			l_SumCnt;		// パルスカウントの積分値

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************

// *************************************************************************
//   機能		： モードの初期化。
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2021.1.1			TKR				新規
// *************************************************************************/
PUBLIC void MODE_init( void ){
	l_SumCnt 		= 0;
	l_DiffCnt			= 0;
}

// *************************************************************************
//   機能		： モードを実行する際に共通して行う処理
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2020.10.17			TKR				新規
// *************************************************************************/
PUBLIC	void MODE_exe_common( void ){


	ADC1_DMA1_ConvertStart();		// DMAの初期化
	TIM7_Start();							// センサの割り込み許可
	  // キャリブレーション動作入れる（いろんなセンサ）
}

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

	MODE_exe_common();

	switch( en_Mode ){

		case MODE_0:
			LED_onAll();
			LL_mDelay(500);
			LED_offAll();
			LL_mDelay(500);
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
			BAT_Check();
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
			 //ADC1_DMA1_ConvertStart();
			 printf("DMA check \n\r");
			DIST_Check();
			break;

		case MODE_10:
			printf("ToF_Data\n\r");
			while(1){
				printf("%d[mm]\n\r",ToF_readRangeContinuous());
				LL_mDelay(100);
			}
			break;

		case MODE_11:
			SPK_on(A4,16.0f,120);
			break;

		case MODE_12:
			DIST_Check();
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

// *************************************************************************
//   機能		： モードを減算変更する。
//   注意		： なし
//   メモ		： エンコーダでモード変更できるように追加
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2019.10.27			TKR				新規
// *************************************************************************/
PUBLIC void MODE_dec( void ){

	/* 最大値チェック */
	if( MODE_0 == en_Mode ){
		en_Mode = MODE_MAX;
	}

	en_Mode--;

	MODE_chg(en_Mode);		// モード変更

}

// *************************************************************************
//   機能		： モードの切り替えチェック
//   注意		： なし
//   メモ		：
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2021.1.1			TKR				新規
// *************************************************************************/
PUBLIC void MODE_chkMode( void ){

	LONG	l_dummy	= 0;

	ENC_GetDiv(&l_DiffCnt, &l_dummy);						// 差分の取得
	if(l_DiffCnt < abs((int)(l_DiffCnt)))l_DiffCnt = 0;	// 静止状態のときのオフセット値をカットする
	l_SumCnt	+= l_DiffCnt;

	if(l_SumCnt  > MODE_CHG_COUNT){		// プラスカウント
		l_SumCnt	= 0;
		MODE_inc();

	}else if(l_SumCnt < MODE_CHG_COUNT * (-1)){		// マイナスカウント
		l_SumCnt	= 0;
		MODE_dec();
	}

	l_DiffCnt	= 0;
}



