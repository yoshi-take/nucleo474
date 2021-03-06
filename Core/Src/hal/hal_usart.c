//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"
#include <stdio.h>


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

PUBLIC void USART_TransmitByte(CHAR ch){
	LL_USART_TransmitData8(USART1, ch);
	while(LL_USART_IsActiveFlag_TXE(USART1)==0);

}
