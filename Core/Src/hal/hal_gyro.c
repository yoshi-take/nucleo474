//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義
#include <stdio.h>

#include "hal/hal_spi.h"
#include "hal/hal_gyro.h"

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
/* ジャイロセンサ */
PUBLIC CHAR c_GyroVal_Lo;								// ジャイロセンサ値(下位)
PUBLIC CHAR c_GyroVal_Hi;									// ジャイロセンサ値(上位)
PUBLIC volatile FLOAT  f_NowGyroAngle;		 		// ジャイロセンサの現在角度
PUBLIC volatile FLOAT  f_NowGyroAngleSpeed;		// ジャイロセンサの現在角速度

PUBLIC CHAR 	c_AccelVal_Lo;								// 加速度センサ値(下位)
PUBLIC CHAR 	c_AccelVal_Hi;								// 加速度センサ値(上位)
PUBLIC volatile FLOAT  	f_NowAccel;						// 進行方向の現在加速度
PRIVATE SHORT	c_AccelValBuf[10];							// 加速度センサのバッファ

PUBLIC	CHAR c_WhoamiVal;

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
// *************************************************************************
//   機能		： ジャイロの設定書き込み
//   注意		： なし
//   メモ		： なし
//   引数		： レジスタ，データ
//   返り値	： なし
// **************************    履    歴    *******************************
//		v1.0		2020.3.12			TKR				新規
// *************************************************************************/
PUBLIC void GYRO_Write(CHAR reg, CHAR data){

	CHAR	tx_data[2];
	CHAR	rx_data[2];

	tx_data[0]	= reg & 0x7F;
	tx_data[1]	= data;

	SPI_Communication(SPI2, tx_data, rx_data, 2,CS_GYRO_GPIO_Port, CS_GYRO_Pin);

}

// *************************************************************************
//   機能		： ジャイロの設定読み込み
//   注意		： なし
//   メモ		： なし
//   引数		： レジスタ，読み出す値（ポインタ）
//   返り値	：	なし
// **************************    履    歴    *******************************
//		v1.0		2020.3.12			TKR				新規
// *************************************************************************/
PUBLIC void GYRO_Read(CHAR reg, CHAR *p_SpiRcvData){

	CHAR	tx_data[2];
	CHAR	rx_data[2];

	tx_data[0]	= reg | 0x80;
	tx_data[1]	= 0x00;				// ダミー

	SPI_Communication(SPI2, tx_data, rx_data, 2,CS_GYRO_GPIO_Port, CS_GYRO_Pin);

	*p_SpiRcvData	= rx_data[1];
}

// *************************************************************************
//   機能		： ジャイロの初期設定
//   注意		： なし
//   メモ		： 初回実行
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
//		v1.0		2020.3.4			TKR				新規
// *************************************************************************/
PUBLIC GYRO_init( void ){

	CHAR	c_dummy;		// 読み出し用

	/* パワーマネジメント1[No.107] */
		while(1){
			// 設定の書き込み
			GYRO_Write(SPI_PWR_MGMT_1, 0x01);

			// レジスタチェック
			GYRO_Read(SPI_PWR_MGMT_1,&c_dummy);		// 読み出し
			printf("SPI_PWR_MGMT_1 = 0x%x\n\r", c_dummy);
			if( c_dummy == 0x01 ){
				printf("SPI_PWR_MGMT_1:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_PWR_MGMT_1:failure\n\r");
			}
		}

		/* 信号リセット[No.104] */
		GYRO_Write(SPI_SIGNAL_RESET, 0x03);			// 加速度・温度リセット

		/* コンフィグ[No.26] */
		while(1){
			GYRO_Write(SPI_CONFIG, 0x00);				// 設定の書き込み

			// レジスタチェック
			GYRO_Read(SPI_CONFIG, &c_dummy);		// 読み出し
			printf("SPI_CONFIG:0x%x\n\r",c_dummy);
			if( c_dummy == 0x00 ){
				printf("SPI_CONFIG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_CONFIG:failure\n\r");
			}
		}

		/* FSYNCコンフィグ[No.54] */
		while(1){
			GYRO_Read(SPI_FSYNC_INT, &c_dummy);		// 読み出し
			if( (c_dummy>>7) == 0 ){
				printf("SPI_FSYNC_INT:success\n\r");
				break;			// 最上位ビットが0になっていることを確認
			}else{
				printf("SPI_FSYNC_INT:failure\n\r");
			}
		}

		/* INT_PINコンフィグ[No.55] */
		while(1){
			GYRO_Write(SPI_INT_PIN_COMFIG, 0xe8);			// 設定の書き込み

			// レジスタチェック
			GYRO_Read(SPI_INT_PIN_COMFIG, &c_dummy);
			printf("SPI_INT_PIN_COMFIG:0x%x\n\r",c_dummy);
			if( c_dummy == 0xe8 ){
				printf("SPI_INT_PIN_COMFIG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_INT_PIN_COMFIG:failure\n\r");
			}
		}

		/* SPI有効[No.106] */
		while(1){
			GYRO_Write(SPI_USER_CONTROL, 0x01);				// 設定の書き込み

			// レジスタチェック
			GYRO_Read(SPI_USER_CONTROL, &c_dummy);		// 読み出し
			printf("SPI_USER_CONTROL:0x%x\n\r",c_dummy);
			if( c_dummy == 0x01 ){
				printf("SPI_USER_CONTROL:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_USER_CONTROL:failure\n\r");
			}

		/* SPI有効[No.112] */
		while(1){
			GYRO_Write(SPI_I2C_IF, 0x40);				// 設定の書き込み

			// レジスタチェック
			GYRO_Read(SPI_I2C_IF, &c_dummy);	// 読み出し
			printf("SPI_I2C_IF:0x%x\n\r",c_dummy);
			if( c_dummy == 0x40 ){
				printf("SPI_I2C_IF:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_I2C_IF:failure\n\r");
			}
		}

		/* 精度(ジャイロ)[No.27] */
		while(1){
			GYRO_Write(SPI_GYRO_CFG, 0x18);		// 設定の書き込み

			// レジスタチェック
			GYRO_Read(SPI_GYRO_CFG, &c_dummy);
			printf("SPI_GYRO_CFG:0x%x\n\r",c_dummy);
			if( c_dummy == 0x18 ){
				printf("SPI_GYRO_CFG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_GYRO_CFG:failure\n\r");
			}
		}

		/* 精度(加速度)[No.28] */
		while(1){
			GYRO_Write(SPI_ACC_CFG, 0x08);			// ±4[g]

			// レジスタチェック
			GYRO_Read(SPI_ACC_CFG, &c_dummy);	// 読み出し
			printf("SPI_ACC_CFG:0x%x\n\r",c_dummy);
			if( c_dummy == 0x08 ){
				printf("SPI_ACC_CFG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_ACC_CFG:failure\n\r");
			}
		}

		while( 0x12 != c_WhoamiVal ){
			printf("failure\n\r");
			GYRO_get_WHOAMI();
		}
		if( 0x12 == c_WhoamiVal )printf("success\n\r");

}

// *************************************************************************
//   機能		： ジャイロの現在の角度を取得する
//   注意		： なし
//   メモ		： ☆
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			BAHARATから移植
// *************************************************************************/
PUBLIC FLOAT GYRO_getNowAngle( void )
{
	return f_NowGyroAngle;
}

// *************************************************************************
//   機能		： ジャイロの現在の角速度を取得する
//   注意		： なし
//   メモ		： ☆
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			BAHARATから移植
// *************************************************************************/
PUBLIC FLOAT GYRO_getNowAngleSpeed( void )
{
	return f_NowGyroAngleSpeed;
}

// *************************************************************************
//   機能		： ジャイロの現在の加速度を取得する
//   注意		： なし
//   メモ		： ☆
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			BAHARATから移植
// *************************************************************************/
PUBLIC FLOAT GYRO_getNowAccel( void )
{
	return f_NowAccel;
}

// *************************************************************************
//   機能		： ジャイロの累積角度をリセットする
//   注意		： なし
//   メモ		： ☆
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			BAHARATから移植
// *************************************************************************/
PUBLIC void GYRO_clrAngle( void )
{
	f_NowGyroAngle 		= 0;
	f_NowGyroAngleSpeed	= 0;
}

// *************************************************************************
//   機能		： ジャイロセンサ用ポーリング関数
//   注意		： 周期ハンドラから定期的に呼び出す
//   メモ		： 割り込みから実行される
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			BAHARATから移植
// *************************************************************************/
PUBLIC void GYRO_Pol( void )
{
	f_NowGyroAngle += f_NowGyroAngleSpeed / 1000;		// 角度更新   (0.001sec毎に加算するため)
}

// *************************************************************************
//   機能		： 君の名は？
//   注意		： コールバック関数は使わない
//   メモ		： ジャイロのデバッグ用
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			新規
// *************************************************************************/
PUBLIC	void GYRO_get_WHOAMI( void ){

	GYRO_Read(SPI_WHO_AM_I, &c_WhoamiVal);
	printf("Who am I = 0x%x\n\r",c_WhoamiVal);
}

// *************************************************************************
//   機能		： ジャイロセンサの値を取得する
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			新規
// *************************************************************************/
PUBLIC void GYRO_getVal( void ){

	SHORT	s_count;						// ICM20602から得られた角速度(カウント値)
	FLOAT	f_tempAngleSpeed;		// 角速度[dps]

	/* 読み出し */
	GYRO_Read(SPI_GYRO_Z_L, &c_GyroVal_Lo);
	GYRO_Read(SPI_GYRO_Z_H, &c_GyroVal_Hi);

	/* 角速度値 */
	s_count		= (SHORT)( (SHORT)(c_GyroVal_Lo) | (SHORT)(c_GyroVal_Hi<<8) );
	f_tempAngleSpeed	= (FLOAT)s_count / GYRO_SCALE_FACTOR;				// [カウント]→[dps]に変換

	/* SWフィルタを有効にする(後で書く) */
	if((SW_GYRO_FILTER_VAL_MIN<f_tempAngleSpeed)&&(f_tempAngleSpeed<SW_GYRO_FILTER_VAL_MAX)){
		f_tempAngleSpeed	= 0;
	}

	/* 角速度更新 */
	f_NowGyroAngleSpeed		= f_tempAngleSpeed;

}

// *************************************************************************
//   機能		： 加速度センサの値を取得する
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値		： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12			TKR			新規
// *************************************************************************/
PUBLIC void GYRO_getAccVal( void ){

	SHORT	s_count;						// ICM20602から得られた加速度(カウント値)
	FLOAT	f_tempAcc;					// 加速度[dps]

	/* 読み出し */
	GYRO_Read(SPI_ACC_L, &c_AccelVal_Lo);
	GYRO_Read(SPI_ACC_H, &c_AccelVal_Hi);

	/* 角速度値 */
	s_count		= (SHORT)( (SHORT)(c_AccelVal_Lo) | (SHORT)(c_AccelVal_Hi<<8) );
	f_tempAcc	= (FLOAT)s_count / ACC_SCALE_FACTOR;				// [カウント]→[dps]に変換

	/* SWフィルタを有効にする */
	if( (SW_ACC_FILTER_VAL_MIN<f_tempAcc) && (f_tempAcc<SW_ACC_FILTER_VAL_MAX) ){
		f_tempAcc	= 0;
	}

	/* 加速度更新 */
	f_NowAccel		= f_tempAcc * 9.8f;		// [m/s^2]

}
