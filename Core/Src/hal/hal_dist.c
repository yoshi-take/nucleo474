//**************************************************
// インクルードファイル（include）
//**************************************************
#include <hal/hal_dist.h>
#include "main.h"
#include "typedefine.h"
#include <stdio.h>

#include "app/mode.h"
#include "hal/hal_led.h"
#include "hal/hal_tim.h"
#include "parameter.h"


//**************************************************
// 定義（define）
//**************************************************
#define ADC_CONVERT_DATA_BUFFR_SIZE	((uint32_t)4)

//**************************************************
// 列挙体（enum）
//**************************************************

//**************************************************
// 構造体（struct）
//**************************************************
/* 距離センサ情報（前壁のみ、データフラッシュ用構造体としても使用する） */
typedef struct{
	SHORT		s_wallHit;					///< @var : 壁に当たっていてもおかしくない値         ( AD 値 ) （前壁とマウス間が約2mmの時の値）
	SHORT		s_skewErr1;					///< @var : 斜め走行時の補正閾値1                    ( AD 値 )
	SHORT		s_skewErr2;					///< @var : 斜め走行時の補正閾値2                    ( AD 値 )
	SHORT		s_skewErr3;					///< @var : 斜め走行時の補正閾値3                    ( AD 値 )
}stDIST_FRONT_SEN;

/* 距離センサ情報（全センサ共通） */
typedef struct{
	SHORT		s_now;						// LED 点灯中の距離センサの現在値           		( AD 値 )
	SHORT		s_old;						// LED 点灯中の距離センサの1つ前の値        		( AD 値 )
	SHORT		s_limit;						// 距離センサの閾値                        					( AD 値 ) ( この値より大きい場合、壁ありと判断する )
	SHORT		s_ref;						// 区画の中心に置いた時の距離センサの基準値 	( AD 値 )
	SHORT		s_offset;					// LED 消灯中の距離センサの値               			( AD 値 )
	SHORT		s_ctrl;						// 制御有効化する際の閾値                   				( AD 値 ) 主に前壁で使用
	SHORT		s_noCtrl;					// 壁に近すぎるため制御無効化する際の閾値   		( AD 値 ) 主に前壁で使用
}stDIST_SEN;

/* 距離センサ情報（全センサ共通、データフラッシュ用構造体のみに使用） */
typedef struct{
	SHORT		s_ref;						// 区画の中心に置いた時の距離センサの基準値 	( AD 値 )
	SHORT		s_limit;						// 距離センサの閾値                         				( AD 値 ) ( この値より大きい場合、壁ありと判断する )
	SHORT		s_ctrl;						// 制御有効化する際の閾値                   				( AD 値 ) 主に前壁で使用
	SHORT		s_noCtrl;					// 壁に近すぎるため制御無効化する際の閾値   		( AD 値 ) 主に前壁で使用
}stDIST_SEN_DATA;

/* データフラッシュのバックアップ or 復帰用 */
#if 0
typedef struct{
	stDIST_SEN_DATA		st_common[DIST_SEN_MAX];			// センサデータ(全センサ共通)
	stDIST_FRONT_SEN	st_front[DIST_SEN_L_FRONT+1];		// センサデータ(前壁のみ)
}stDIST_FLASH;
#endif
/* 壁センサのログ用 */
typedef struct {
	SHORT		s_frontR;
	SHORT		s_frontL;
	SHORT		s_sideR;
	SHORT		s_sideL;
}stDIST_SEN_LOG;
//**************************************************
// グローバル変数
//**************************************************
uint16_t	adcConverterData[ADC_CONVERT_DATA_BUFFR_SIZE]	= {4,4,4,4};



//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************

// *************************************************************************
//   機能		： 距離センサ用（横壁）ポーリング関数
//   注意		： なし
//   メモ		： 割り込みから実行される
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2020.2.6			TKR				新規
// *************************************************************************/
PUBLIC void DIST_Pol_Side( void )
{
	/* 無発光時の値取得 */

	/* 横壁LED点灯 */
	LL_GPIO_SetOutputPin(IR_SIDE_R_GPIO_Port,IR_SIDE_R_Pin);
	LL_GPIO_SetOutputPin(IR_SIDE_L_GPIO_Port,IR_SIDE_L_Pin);

	/* 発光安定待ち */
	TIME_waitFree( SEN_WAIT_CNT );

	/* 発光時の値と無発光時の値で差分を取得 */

	/* ログ */
#if 0
	if(us_SenLogPt != DIST_LOG){

		/* ログ記録 */
		if( uc_sencycle == DIST_LOG_CYCLE ){
			st_DistSenLog[us_SenLogPt].s_sideR	= st_sen[DIST_SEN_R_SIDE].s_now;	// 右横壁
			st_DistSenLog[us_SenLogPt].s_sideL	= st_sen[DIST_SEN_L_SIDE].s_now;	// 左横壁
			uc_sencycle	= 0;
			us_SenLogPt++;
			if(us_SenLogPt == DIST_LOG)bl_senlog = FALSE;
		}
	}
#endif

	/* 横壁LED消灯 */
	LL_GPIO_ResetOutputPin(IR_SIDE_R_GPIO_Port,IR_SIDE_R_Pin);
	LL_GPIO_ResetOutputPin(IR_SIDE_L_GPIO_Port,IR_SIDE_L_Pin);
}

// *************************************************************************
//   機能		： 距離センサ用（横壁）ポーリング関数
//   注意		： なし
//   メモ		： 割り込みから実行される
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
//		v1.0		2020.2.6			TKR				新規
// *************************************************************************/
PUBLIC void DIST_Pol_Front( void )
{
	/* 無発光時の値取得 */

	/* 前壁LED点灯 */
	LL_GPIO_SetOutputPin(IR_FRONT_R_GPIO_Port,IR_FRONT_R_Pin);
	LL_GPIO_SetOutputPin(IR_FRONT_L_GPIO_Port,IR_FRONT_L_Pin);

	/* 発光安定待ち */
	TIME_waitFree( SEN_WAIT_CNT );

	/* 発光時の値と無発光時の値で差分を取得 */

	/* ログ */
#if 0
	if(us_SenLogPt != DIST_LOG){

		/* ログ記録 */
		if( uc_sencycle == DIST_LOG_CYCLE ){
			st_DistSenLog[us_SenLogPt].s_sideR	= st_sen[DIST_SEN_R_SIDE].s_now;	// 右横壁
			st_DistSenLog[us_SenLogPt].s_sideL	= st_sen[DIST_SEN_L_SIDE].s_now;	// 左横壁
			uc_sencycle	= 0;
			us_SenLogPt++;
			if(us_SenLogPt == DIST_LOG)bl_senlog = FALSE;
		}
	}
#endif
	/* 前壁LED消灯 */
	LL_GPIO_ResetOutputPin(IR_FRONT_R_GPIO_Port,IR_FRONT_R_Pin);
	LL_GPIO_ResetOutputPin(IR_FRONT_L_GPIO_Port,IR_FRONT_L_Pin);
}

// ADCの有効化，AD変換終了時のDMAの割り込みを有効化
PUBLIC void ADC1_Start(void){
	LL_DMA_EnableIT_TC(DMA1,LL_DMA_CHANNEL_1);
	LL_ADC_Enable(ADC1);
}

// ADC
PUBLIC void ADC1_Start_DMA1(void){
	ADC1_DMA1_ConvertStart();
}

// ADCのDMA変換を開始する
PUBLIC void ADC1_DMA1_ConvertStart(void){
	LL_DMA_DisableChannel(DMA1,LL_DMA_CHANNEL_1);

	LL_DMA_ConfigAddresses(DMA1,LL_DMA_CHANNEL_1,
											LL_ADC_DMA_GetRegAddr(ADC1,LL_ADC_DMA_REG_REGULAR_DATA),
											(uint32_t)&adcConverterData,LL_DMA_DIRECTION_PERIPH_TO_MEMORY);	// DMAのアドレスを決める

	LL_DMA_SetDataLength(DMA1,LL_DMA_CHANNEL_1,ADC_CONVERT_DATA_BUFFR_SIZE);	// データのアドレスの長さを決める

	LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);

	LL_ADC_REG_StartConversion(ADC1);		// AD変換の処理を始める

}

PUBLIC void ADC1_DMA1_TransferComplete_Callback(void){

	LL_ADC_ClearFlag_EOC(ADC1);
	printf("%d,%d,%d,%d\n\r",adcConverterData[0],adcConverterData[1],adcConverterData[2],adcConverterData[3]);
	ADC1_Start_DMA1();
}

