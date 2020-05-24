//**************************************************
// インクルードファイル（include）
//**************************************************
#include "main.h"
#include "typedefine.h"		// 型定義
#include <stdio.h>

#include "hal/hal_tof.h"

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
extern	I2C_HandleTypeDef hi2c1;
PRIVATE CHAR	txBuffer[2]	= {ADR_TOF_MEASURE,ADR_TOF_ID};		// [1]：ToFのID	[0]：ToFのコマンド
PRIVATE CHAR	txID				= ADR_TOF_ID << 1;								// ToFのID（シフトする必要有）

// VL6180X
PRIVATE uint8_t			address = ADR_VL6180X_ID<<1;
PRIVATE uint8_t			scaling;
PRIVATE uint8_t			ptp_offset;
PRIVATE uint16_t const	ScalerValues[] = {0, 253, 127, 84};

//PRIVATE uint16_t		io_timeout;
//PRIVATE BOOL		did_timeout;


//**************************************************
// プロトタイプ宣言（ファイル内で必要なものだけ記述）
//**************************************************

// *************************************************************************
//   機能		： ToFの値を取得する
//   注意		： なし
//   メモ		： MTOF171000C0
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12
// *************************************************************************/
PUBLIC SHORT TOF_getData(void){

#ifdef MTOF171000C0	//MTOF171000C0
	uint8_t		rxBuffer[2];		// 受信バッファ(2Byte)
	SHORT		s_value	= 0;

	HAL_I2C_Master_Transmit(&hi2c1, txID, txBuffer, 2, 1000);				// ID送信→コマンド送信→ID送信
	HAL_I2C_Master_Receive(&hi2c1, txID,rxBuffer, 2, 1000);				// 受信
/*
	HAL_I2C_Master_Transmit(&hi2c1, txID, 0xD3, 1, 1000);				// ID送信→コマンド送信→ID送信
	HAL_I2C_Master_Receive(&hi2c1, txID,rxBuffer, 2, 1000);				// 受信
*/
	s_value		= (SHORT)(rxBuffer[1] | (rxBuffer[0] << 8) );					// 受信したデータの結合

	return s_value;
#else
	// VL6180X
	ToF_writeReg(SYSRANGE__START, 0x01);
//	uint16_t		millis_start = millis();
	while ((ToF_readReg(RESULT__INTERRUPT_STATUS_GPIO) & 0x04) == 0){
//		if (io_timeout > 0 && ((uint16_t)millis() - millis_start) > io_timeout){
//			did_timeout = TRUE;
//			return 255;
//	    }
	  }
	  uint8_t range = ToF_readReg(RESULT__RANGE_VAL);
	  ToF_writeReg(SYSTEM__INTERRUPT_CLEAR, 0x01);
	  return		(SHORT)scaling *range;

#endif
}

// *************************************************************************
//   機能		： ToFの値を確認する
//   注意		： なし
//   メモ		： なし
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.3.12
// *************************************************************************/
PUBLIC void TOF_check(void){

	printf("s_value = %d \n\r",TOF_getData());

}

// *************************************************************************
//   機能		： ToFセンサの初期化
//   注意		： なし
//   メモ		： VL6180X
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC void ToF_init( void ){

#ifdef MTOF171000C0	//MTOF171000C0

#else
	// Store part-to-part range offset so it can be adjusted if scaling is changed
	  ptp_offset = ToF_readReg(SYSRANGE__PART_TO_PART_RANGE_OFFSET);

	  if (ToF_readReg(SYSTEM__FRESH_OUT_OF_RESET) == 1)
	  {
		  scaling = 1;

		  ToF_writeReg(0x207, 0x01);
		  ToF_writeReg(0x208, 0x01);
		  ToF_writeReg(0x096, 0x00);
		  ToF_writeReg(0x097, 0xFD); // RANGE_SCALER = 253
		  ToF_writeReg(0x0E3, 0x00);
		  ToF_writeReg(0x0E4, 0x04);
		  ToF_writeReg(0x0E5, 0x02);
		  ToF_writeReg(0x0E6, 0x01);
		  ToF_writeReg(0x0E7, 0x03);
		  ToF_writeReg(0x0F5, 0x02);
		  ToF_writeReg(0x0D9, 0x05);
		  ToF_writeReg(0x0DB, 0xCE);
		  ToF_writeReg(0x0DC, 0x03);
		  ToF_writeReg(0x0DD, 0xF8);
		  ToF_writeReg(0x09F, 0x00);
		  ToF_writeReg(0x0A3, 0x3C);
		  ToF_writeReg(0x0B7, 0x00);
		  ToF_writeReg(0x0BB, 0x3C);
		  ToF_writeReg(0x0B2, 0x09);
		  ToF_writeReg(0x0CA, 0x09);
		  ToF_writeReg(0x198, 0x01);
		  ToF_writeReg(0x1B0, 0x17);
		  ToF_writeReg(0x1AD, 0x00);
		  ToF_writeReg(0x0FF, 0x05);
		  ToF_writeReg(0x100, 0x05);
		  ToF_writeReg(0x199, 0x05);
		  ToF_writeReg(0x1A6, 0x1B);
		  ToF_writeReg(0x1AC, 0x3E);
		  ToF_writeReg(0x1A7, 0x1F);
		  ToF_writeReg(0x030, 0x00);

		  ToF_writeReg(SYSTEM__FRESH_OUT_OF_RESET, 0);

	  }else{		// Sensor has already been initialized, so try to get scaling settings by reading registers.

		  uint16_t s = ToF_readReg16bit(RANGE_SCALER);
		  if(s == ScalerValues[3]) { scaling = 3; }
		  else if (s == ScalerValues[2]) { scaling = 2; }
		  else	{ scaling = 1; }

	    // Adjust the part-to-part range offset value read earlier to account for
	    // existing scaling. If the sensor was already in 2x or 3x scaling mode,
	    // precision will be lost calculating the original (1x) offset, but this can
	    // be resolved by resetting the sensor and Arduino again.
	    ptp_offset *= scaling;
	  }
#endif
}

// *************************************************************************
//   機能		： ToFセンサのデフォルトの設定
//   注意		： なし
//   メモ		： VL6180X
//   引数		： なし
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC void ToF_ConfigureDefault( void ){
	// "Recommended : Public registers"

	  // readout__averaging_sample_period = 48
	  ToF_writeReg(READOUT__AVERAGING_SAMPLE_PERIOD, 0x30);

	  // sysals__analogue_gain_light = 6 (ALS gain = 1 nominal, actually 1.01 according to Table 14 in datasheet)
	  ToF_writeReg(SYSALS__ANALOGUE_GAIN, 0x46);

	  // sysrange__vhv_repeat_rate = 255 (auto Very High Voltage temperature recalibration after every 255 range measurements)
	  ToF_writeReg(SYSRANGE__VHV_REPEAT_RATE, 0xFF);

	  // sysals__integration_period = 99 (100 ms)
	  // AN4545 incorrectly recommends writing to register 0x040; 0x63 should go in the lower byte, which is register 0x041.
	  ToF_writeReg16bit(SYSALS__INTEGRATION_PERIOD, 0x0063);

	  // sysrange__vhv_recalibrate = 1 (manually trigger a VHV recalibration)
	  ToF_writeReg(SYSRANGE__VHV_RECALIBRATE, 0x01);


	  // "Optional: Public registers"

	  // sysrange__intermeasurement_period = 9 (100 ms)
	  ToF_writeReg(SYSRANGE__INTERMEASUREMENT_PERIOD, 0x09);

	  // sysals__intermeasurement_period = 49 (500 ms)
	  ToF_writeReg(SYSALS__INTERMEASUREMENT_PERIOD, 0x31);

	  // als_int_mode = 4 (ALS new sample ready interrupt); range_int_mode = 4 (range new sample ready interrupt)
	  ToF_writeReg(SYSTEM__INTERRUPT_CONFIG_GPIO, 0x24);


	  // Reset other settings to power-on defaults

	  // sysrange__max_convergence_time = 49 (49 ms)
	  ToF_writeReg(SYSRANGE__MAX_CONVERGENCE_TIME, 0x31);

	  // disable interleaved mode
	  ToF_writeReg(INTERLEAVED_MODE__ENABLE, 0);

	  // reset range scaling factor to 1x
	  ToF_setScaling(1);
}


// *************************************************************************
//   機能		： スケーリングのセット
//   注意		： なし
//   メモ		： VL6180X
//   引数		： スケール値
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC void ToF_setScaling(CHAR new_scaling){
	uint8_t const DefaultCrosstalkValidHeight = 20; // default value of SYSRANGE__CROSSTALK_VALID_HEIGHT

	// do nothing if scaling value is invalid
	if (new_scaling < 1 || new_scaling > 3) { return; }

	scaling = new_scaling;
	ToF_writeReg16bit(RANGE_SCALER, ScalerValues[scaling]);

	// apply scaling on part-to-part offset
	ToF_writeReg(SYSRANGE__PART_TO_PART_RANGE_OFFSET, ptp_offset / scaling);

	// apply scaling on CrossTalkValidHeight
	ToF_writeReg(SYSRANGE__CROSSTALK_VALID_HEIGHT, DefaultCrosstalkValidHeight / scaling);

	// This function does not apply scaling to RANGE_IGNORE_VALID_HEIGHT.

	// enable early convergence estimate only at 1x scaling
	uint8_t rce = ToF_readReg(SYSRANGE__RANGE_CHECK_ENABLES);
	ToF_writeReg(SYSRANGE__RANGE_CHECK_ENABLES, (rce & 0xFE) | (scaling == 1));
}


// *************************************************************************
//   機能		：ToFセンサの値を返す
//   注意		： なし
//   メモ		： VL6180X
//   引数		： なし
//   返り値	： 距離[mm]
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC SHORT ToF_readRangeContinuous( void ){

	ToF_writeReg(SYSRANGE__START, 0x01);

//	uint16_t		millis_start = millis();
	while ((ToF_readReg(RESULT__INTERRUPT_STATUS_GPIO) & 0x04) == 0){
//		if (io_timeout > 0 && ((uint16_t)millis() - millis_start) > io_timeout){
//			did_timeout = TRUE;
//			return 255;
//	    }
	  }

	  uint8_t range = ToF_readReg(RESULT__RANGE_VAL);
	  ToF_writeReg(SYSTEM__INTERRUPT_CLEAR, 0x01);

	  return		(SHORT)scaling *range;
}

// *************************************************************************
//   機能		： 8bitレジスタの書き込み
//   注意		： なし
//   メモ		： VL6180X
//   引数		： レジスタ(2byte)，書き込み値(1byte)
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC void ToF_writeReg( uint16_t reg, uint8_t value ){

	uint8_t		regBuff[3]	= {0,0,0};
	regBuff[0]	= (reg>>8) & 0xff;
	regBuff[1] = reg & 0xff;
	regBuff[2] = value;

	HAL_I2C_Master_Transmit(&hi2c1, address, regBuff, 3, 1000);

}

// *************************************************************************
//   機能		： 16bitレジスタの書き込み
//   注意		： なし
//   メモ		： VL6180X
//   引数		： レジスタ(2byte)，書き込み値(2byte)
//   返り値	： なし
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC void ToF_writeReg16bit( uint16_t reg, uint16_t value ){

	uint8_t		regBuff[4]	= {0,0,0,0};
	regBuff[0]	= (reg>>8) & 0xff;
	regBuff[1] = reg & 0xff;
	regBuff[2] = (value>>8) & 0xff;
	regBuff[3] = value & 0xff;

	HAL_I2C_Master_Transmit(&hi2c1, address, regBuff, 4, 100);

}

// *************************************************************************
//   機能		： 8bitレジスタの読み出し
//   注意		： なし
//   メモ		： VL6180X
//   引数		： レジスタ(2byte)
//   返り値	： 8bit
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC uint8_t ToF_readReg(uint16_t reg){

	uint8_t	recv = 0;
	uint8_t	regBuff[2];
	regBuff[0]	= (reg>>8) & 0xff;
	regBuff[1] = reg & 0xff;

	HAL_I2C_Master_Transmit(&hi2c1,address,regBuff,2,100);
	HAL_I2C_Master_Receive(&hi2c1,address, &recv, 1, 100);

	return recv;
}

// *************************************************************************
//   機能		： 16bitレジスタの読み出し
//   注意		： なし
//   メモ		： VL6180X
//   引数		： レジスタ(2byte)
//   返り値	： 16bit
// **************************    履    歴    *******************************
// 		v1.0		2020.4.18
// *************************************************************************/
PUBLIC uint16_t ToF_readReg16bit( uint16_t reg){

	uint8_t		recv[2]	= {0,0};					// 受信したデータを格納
	uint16_t	value		= 0;							// 受信したデータを連結させる

	uint8_t		regBuff[2]	= {0,0};				// 読み出し先のレジスタ
	regBuff[0]	= (reg>>8) & 0xff;
	regBuff[1] = reg & 0xff;

	HAL_I2C_Master_Transmit(&hi2c1,address,regBuff,2,100);
	HAL_I2C_Master_Receive(&hi2c1,address, recv ,2, 100);

	value		= (uint16_t)(recv[1] | (recv[0] << 8) );					// 受信したデータの結合

	return value;
}
