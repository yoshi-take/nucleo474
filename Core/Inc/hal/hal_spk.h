/*
 * hal_spk.h
 *
 *  Created on: May 24, 2020
 *      Author: TAKERU
 */

#ifndef INC_HAL_HAL_SPK_H_
#define INC_HAL_HAL_SPK_H_
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
#define A3 		(220)			// ラ
#define Bb3 		(233)			//
#define B3 		(247)			// シ
#define C4 		(262)			// ド
#define Cb4		(277)			//
#define D4 		(294)			// レ
#define Eb4 		(311)			//
#define E4 		(330)			// ミ
#define F4 		(349)			// ファ
#define Gb4		(370)			//
#define G4		(392)			// ソ
#define Ab4 		(415)			//
#define A4		(440)			// ラ
#define B4      	(494)           // シ
#define C5      	(523)           // ド
#define D5      	(587)           // レ
#define E5      	(659)           // ミ
#define F5      	(698)           // ファ
#define G5      	(784)           // ソ
#define A5      	(880)           // ラ
#define B_5    	(988)           // シ
#define C6      	(1047)          // ド
#define D6		(1175)          // レ
#define REST	(0)				// 休符

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
PUBLIC void SPK_on( uint16_t frq, float beat, int bpm );
PUBLIC void SPK_Off(void);
PUBLIC void SPK_debug( void );
PUBLIC void SPK_success( void );
PUBLIC	void SPK_alert( void );

#ifdef	__cplusplus
}
#endif


#endif /* INC_HAL_HAL_SPK_H_ */
