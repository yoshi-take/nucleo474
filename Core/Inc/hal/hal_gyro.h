#ifndef INC_HAL_HAL_GYRO_H_
#define INC_HAL_HAL_GYRO_H_

#ifdef	__cplusplus
extern	"C"	{
#endif

//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義
#include <stdio.h>

//**************************************************
// 定義（define）
//**************************************************
#define     SPI_WHO_AM_I        		( 0x75 )      // Who am I?

#define		SPI_PWR_MGMT_1		( 0x6b )		// [No.107]電源制御1
#define		SPI_CONFIG					( 0x1a )		// [No.26]コンフィグ

#define		SPI_FSYNC_INT				( 0x36 )		// [No.54]FSYNCコンフィグ
#define		SPI_INT_PIN_COMFIG	( 0x37 )		// [No.55]INT_PINコンフィグ

#define		SPI_SIGNAL_RESET		( 0x68 )		// [No.104]信号リセット
#define		SPI_USER_CONTROL		( 0x6a )		// [No.106]ユーザーコントロール
#define     	SPI_I2C_IF          			( 0x70 )		// [No.112]I2Cの無効
#define		SPI_GYRO_CFG				( 0x1b )		// [No.27]ジャイロセンサのコンフィグ
#define		SPI_ACC_CFG				( 0x1c )		// [No.28]加速度センサのコンフィグ
#define		SPI_GYRO_OFFSET_L		( 0x18 )	    // [No.24]ジャイロオフセット（下位）
#define		SPI_ACC_OFFSET_L		( 0x16 )		// [No.20]加速度オフセット（下位）
#define		SPI_SEN_ENB				( 0x23 )	    // センサ有効

#define		SPI_GYRO_Z_L				( 0x48 )		// ジャイロセンサの下位データ
#define		SPI_GYRO_Z_H				( 0x47 )		// ジャイロセンサの上位データ
#define		SPI_TEMP_L					( 0x42 )		// 温度センサの下位データ
#define		SPI_TEMP_H					( 0x41 )		// 温度センサの上位データ
#define		SPI_ACC_L					( 0x3e )		// 加速度センサの下位データ
#define		SPI_ACC_H					( 0x3d )		// 加速度センサの上位データ

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
PUBLIC void GYRO_Write(CHAR reg, CHAR data);
PUBLIC void GYRO_Read(CHAR reg, CHAR *p_SpiRcvData);
PUBLIC void GYRO_init( void );
PUBLIC FLOAT GYRO_getNowAngle( void );
PUBLIC FLOAT GYRO_getNowAngleSpeed( void );
PUBLIC FLOAT GYRO_getNowAccel( void );
PUBLIC void GYRO_clrAngle( void );
PUBLIC void GYRO_Pol( void );
PUBLIC	void GYRO_get_WHOAMI( void );
PUBLIC void GYRO_getVal( void );
PUBLIC void GYRO_getAccVal( void );

#endif /* INC_HAL_HAL_GYRO_H_ */
