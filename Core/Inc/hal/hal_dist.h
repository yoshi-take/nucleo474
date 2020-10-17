#ifndef INC_HAL_HAL_DIST_H_
#define INC_HAL_HAL_DIST_H_

#ifdef	__cplusplus
extern	"C"	{
#endif

//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"

//**************************************************
// 定義（define）
//**************************************************

//**************************************************
// 列挙体（enum）
//**************************************************
typedef enum{
	DIST_SEN_R_FRONT = 0,
	DIST_SEN_L_FRONT,
	//DIST_SEN_R_45,
	//DIST_SEN_L_45,
	DIST_SEN_R_SIDE,
	DIST_SEN_L_SIDE,
	DIST_SEN_MAX
}enDIST_SEN_ID;

//**************************************************
// 構造体（struct）
//**************************************************

//**************************************************
// グローバル変数
//**************************************************

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
PUBLIC SHORT DIST_getNowVal( enDIST_SEN_ID en_id );

PUBLIC void DIST_Pol_Side( void );
PUBLIC void DIST_Pol_Front( void );
PUBLIC void DIST_Check( void );

PUBLIC void ADC1_DMA1_ConvertStart(void);
PUBLIC void ADC1_DMA1_TransferComplete_Callback(void);

#ifdef	__cplusplus
}
#endif


#endif /* INC_HAL_HAL_DIST_H_ */
