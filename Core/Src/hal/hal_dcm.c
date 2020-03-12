//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義

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
PRIVATE	enROT_DIR	bl_Dcm_Rot_R;
PRIVATE	enROT_DIR	bl_Dcm_Rot_L;

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************


void TIM2_PWM_Start(void){

	LL_TIM_CC_EnableChannel(TIM3,LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(TIM3,LL_TIM_CHANNEL_CH2);
	LL_TIM_CC_EnableChannel(TIM4,LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(TIM4,LL_TIM_CHANNEL_CH2);

	LL_TIM_EnableCounter(TIM3);
	LL_TIM_EnableCounter(TIM4);
}

void TIM2_PWM_Out(uint32_t duty){

	if(duty>499)duty=499;
	LL_TIM_OC_SetCompareCH1(TIM3, duty);
	LL_TIM_OC_SetCompareCH2(TIM3, duty);
	LL_TIM_OC_SetCompareCH1(TIM4, duty);
	LL_TIM_OC_SetCompareCH2(TIM4, duty);

}

// *************************************************************************
//   機能		： DCMの回転方向をCWにする
//   注意		： なし
//   メモ		： なし
//   引数		： モータID
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.12.24			TKR			新規
// *************************************************************************/
PUBLIC void DCM_setDirCw( enDCM_ID en_id ){

	if( en_id == DCM_R ){
		bl_Dcm_Rot_R	= CW;

	}else if(en_id == DCM_L ){
		bl_Dcm_Rot_L	= CW;

	}
}

// *************************************************************************
//   機能		： DCMの回転方向をCCWにする
//   注意		： なし
//   メモ		： なし
//   引数		： モータID
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.12.24			TKR			新規
// *************************************************************************/
PUBLIC void DCM_setDirCcw( enDCM_ID en_id ){

	if( en_id == DCM_R ){
		bl_Dcm_Rot_R	= CCW;

	}else if(en_id == DCM_L ){
		bl_Dcm_Rot_L	= CCW;

	}
}


// *************************************************************************
//   機能		： DCMの動作開始する
//   注意		： なし
//   メモ		： なし
//   引数		： モータID
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.12.24			TKR			新規
// *************************************************************************/
PUBLIC void DCM_staMot( enDCM_ID en_id ){

	if( en_id == DCM_R ){	// 右
		if( bl_Dcm_Rot_R == CW ){	// 時計回り
			LL_TIM_CC_EnableChannel(TIM4,LL_TIM_CHANNEL_CH1);
			LL_TIM_CC_DisableChannel(TIM4,LL_TIM_CHANNEL_CH2);

		}else{		// 反時計回り
			LL_TIM_CC_DisableChannel(TIM4,LL_TIM_CHANNEL_CH1);
			LL_TIM_CC_EnableChannel(TIM4,LL_TIM_CHANNEL_CH2);

		}

		LL_TIM_EnableCounter(TIM4);

	}else if( en_id == DCM_L ){		// 左
		if( bl_Dcm_Rot_L == CW ){		// 時計回り
			LL_TIM_CC_EnableChannel(TIM3,LL_TIM_CHANNEL_CH1);
			LL_TIM_CC_DisableChannel(TIM3,LL_TIM_CHANNEL_CH2);

		}else{		// 反時計回り
			LL_TIM_CC_DisableChannel(TIM3,LL_TIM_CHANNEL_CH1);
			LL_TIM_CC_EnableChannel(TIM3,LL_TIM_CHANNEL_CH2);

		}

		LL_TIM_EnableCounter(TIM3);
	}

}

// *************************************************************************
//   機能		： DCMの動作を停止する
//   注意		： なし
//   メモ		： なし
//   引数		： モータID
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.12.31			TKR			新規
// *************************************************************************/
PUBLIC void DCM_stopMot( enDCM_ID en_id) {

	/* 停止設定 */
	if( en_id == DCM_R ){
		LL_TIM_CC_DisableChannel(TIM4,LL_TIM_CHANNEL_CH1);
		LL_TIM_CC_DisableChannel(TIM4,LL_TIM_CHANNEL_CH2);

	}else if( en_id == DCM_L){
		LL_TIM_CC_DisableChannel(TIM3,LL_TIM_CHANNEL_CH1);
		LL_TIM_CC_DisableChannel(TIM3,LL_TIM_CHANNEL_CH2);

	}

}


// *************************************************************************
//   機能		： DCMのPWM-Dutyを設定する
//   注意		： なし
//   メモ		： なし
//   引数		： モータID,duty比(0~100)
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2019.12.24			TKR			新規
// *************************************************************************/
PUBLIC void DCM_setPwmDuty( enDCM_ID en_id, unsigned short us_duty){

	if(us_duty>499)us_duty=499;

	if( en_id == DCM_R){	// 右
		LL_TIM_OC_SetCompareCH1(TIM4, us_duty);
		LL_TIM_OC_SetCompareCH2(TIM4, us_duty);

	}else if( en_id == DCM_L){		// 左
		LL_TIM_OC_SetCompareCH1(TIM3, us_duty);
		LL_TIM_OC_SetCompareCH2(TIM3, us_duty);
	}

}
