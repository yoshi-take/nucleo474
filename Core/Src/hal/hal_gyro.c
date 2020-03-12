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

//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************
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

	SHORT	us_dummy;
	/* パワーマネジメント1[No.107] */
		while(1){
			// 設定の書き込み
			SPI_staSetData(SPI_PWR_MGMT_1,0x01);
			SPI_Communication(SPI2, tx_data, rx_data, length, GPIOx, CS_PIN)
			TIME_wait(100);

			// レジスタチェック
			p_SpiRcvData		= &us_dummy;		// ダミー
			SPI_staGetData(SPI_PWR_MGMT_1);			// 読み出し
			TIME_wait(100);
			printf("SPI_PWR_MGMT_1:0x%x\n\r",us_dummy);
			if( us_dummy == 0x01 ){
				printf("SPI_PWR_MGMT_1:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_PWR_MGMT_1:failure\n\r");
			}
		}

		/* 信号リセット[No.104] */
		//while(1){
			// 設定の書き込み
			SPI_staSetData(SPI_SIGNAL_RESET,0x03);		// 加速度・温度リセット
			TIME_wait(100);
			while(1){
				if( en_SpiState == SPI_IDLE )break;		// SPI通信完了
			}

			// レジスタチェック
			//p_SpiRcvData		= &us_dummy;		// ダミー
			//SPI_staGetData(SPI_SIGNAL_RESET);			// 読み出し
			//TIME_wait(100);
			//printf("SPI_SIGNAL_RESET:0x%x\n\r",us_dummy);
			//if( us_dummy == 0x03 ){
			//	printf("SPI_SIGNAL_RESET:success\n\r");
			//	break;			// 所望の設定が書き込めていたらOK
			//}else{
			//	printf("SPI_SIGNAL_RESET:failure\n\r");
			//}

		//}

		/* コンフィグ[No.26] */
		while(1){
			// 設定の書き込み
			SPI_staSetData(SPI_CONFIG,0x00);
			TIME_wait(100);
			while(1){
				if( en_SpiState == SPI_IDLE )break;		// SPI通信完了
			}

			// レジスタチェック
			p_SpiRcvData		= &us_dummy;		// ダミー
			SPI_staGetData(SPI_CONFIG);				// 読み出し
			TIME_wait(100);
			printf("SPI_CONFIG:0x%x\n\r",us_dummy);
			if( us_dummy == 0x00 ){
				printf("SPI_CONFIG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_CONFIG:failure\n\r");
			}
		}

		/* FSYNCコンフィグ[No.54] */
		while(1){
			p_SpiRcvData		= &us_dummy;		// ダミー
			SPI_staGetData(SPI_FSYNC_INT);			// 読み出し用レジスタ
			TIME_wait(100);
			printf("SPI_FSYNC_INT:0x%x\n\r",us_dummy);
			while(1){
				if( en_SpiState == SPI_IDLE )break;	// SPI通信完了
			}
			if( (us_dummy>>7) == 0 ){
				printf("SPI_FSYNC_INT:success\n\r");
				break;			// 最上位ビットが0になっていることを確認
			}else{
				printf("SPI_FSYNC_INT:failure\n\r");
			}
		}

		/* INT_PINコンフィグ[No.55] */
		while(1){
			// 設定の書き込み
			SPI_staSetData(SPI_INT_PIN_COMFIG,0xe8);
			TIME_wait(100);
			while(1){
				if( en_SpiState == SPI_IDLE )break;		// SPI通信完了
			}

			// レジスタチェック
			p_SpiRcvData		= &us_dummy;		// ダミー
			SPI_staGetData(SPI_INT_PIN_COMFIG);		// 読み出し用レジスタ
			TIME_wait(100);
			printf("SPI_INT_PIN_COMFIG:0x%x\n\r",us_dummy);
			if( us_dummy == 0xe8 ){
				printf("SPI_INT_PIN_COMFIG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_INT_PIN_COMFIG:failure\n\r");
			}
		}

		/* SPI有効[No.106] */
		// 設定の書き込み
		SPI_staSetData(SPI_USER_CONTROL,0x01);		// ジャイロ・加速度・温度リセット
		TIME_wait(100);
		while(1){
			if( en_SpiState == SPI_IDLE )break;		// SPI通信完了
		}
		// レジスタチェック
		p_SpiRcvData		= &us_dummy;		// ダミー
		SPI_staGetData(SPI_USER_CONTROL);		// 読み出し用レジスタ
		TIME_wait(100);
		printf("SPI_USER_CONTROL:0x%x\n\r",us_dummy);

		/* SPI有効[No.112] */
		while(1){
			// 設定の書き込み
			SPI_staSetData(SPI_I2C_IF,0x40);			// SPI有効(I2Cを切る)
			TIME_wait(100);
			while(1){
				if( en_SpiState == SPI_IDLE )break;		// SPI通信完了
			}

			// レジスタチェック
			p_SpiRcvData		= &us_dummy;		// ダミー
			SPI_staGetData(SPI_I2C_IF);				// 読み出し用レジスタ
			TIME_wait(100);
			printf("SPI_I2C_IF:0x%x\n\r",us_dummy);
			if( us_dummy == 0x40 ){
				printf("SPI_I2C_IF:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_I2C_IF:failure\n\r");
			}
		}

		/* 精度(ジャイロ)[No.27] */
		while(1){
			// 設定の書き込み
			SPI_staSetData(SPI_GYRO_CFG,0x18);			// ±2000[dps]
			TIME_wait(100);
			while(1){
				if( en_SpiState == SPI_IDLE )break;		// SPI通信完了
			}

			// レジスタチェック
			p_SpiRcvData		= &us_dummy;		// ダミー
			SPI_staGetData(SPI_GYRO_CFG);			// 読み出し用レジスタ
			TIME_wait(100);
			printf("SPI_GYRO_CFG:0x%x\n\r",us_dummy);
			if( us_dummy == 0x18 ){
				printf("SPI_GYRO_CFG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_GYRO_CFG:failure\n\r");
			}
		}

		/* 精度(加速度)[No.28] */
		while(1){
			// 設定の書き込み
			SPI_staSetData(SPI_ACC_CFG,0x08);			// ±4[g]
			TIME_wait(100);
			while(1){
				if( en_SpiState == SPI_IDLE )break;		// SPI通信完了
			}

			// レジスタチェック
			p_SpiRcvData		= &us_dummy;		// ダミー
			SPI_staGetData(SPI_ACC_CFG);			// 読み出し用レジスタ
			TIME_wait(100);
			printf("SPI_ACC_CFG:0x%x\n\r",us_dummy);
			if( us_dummy == 0x08 ){
				printf("SPI_ACC_CFG:success\n\r");
				break;			// 所望の設定が書き込めていたらOK
			}else{
				printf("SPI_ACC_CFG:failure\n\r");
			}
		}


		while( 0x12 != s_WhoamiVal ){
			printf("failure\n\r");
			GYRO_get_WHOAMI();
		}
		if( 0x12 == s_WhoamiVal )printf("success\n\r");

}
