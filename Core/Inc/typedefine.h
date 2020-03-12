/*
 * typedefine.h
 *
 *  Created on: 2019/12/30
 *      Author: takeru
 */

#ifndef INC_TYPEDEFINE_H_
#define INC_TYPEDEFINE_H_

#ifdef	__cplusplus
extern	"C"{
#endif

/* -------------- */
/*  以下独自定義  */
/* -------------- */
/* ON/OFF */
#define 	ON					(1)
#define 	OFF					(0)

/* Hi/Lo */
#define 	HI					(1)
#define 	LO					(0)

/* スコープ設定 */
#define 	PUBLIC
#define 	PROTECTED
#define		PRIVATE				static

/* const、static、volatile */
#define CONST				const
#define STATIC				static
#define VOLATILE			volatile

/* 型定義 */
typedef unsigned char		UCHAR;
typedef char				CHAR;
typedef unsigned short		USHORT;
typedef short				SHORT;
typedef unsigned int        UINT;
typedef int                 INT;
typedef unsigned long		ULONG;
typedef long				LONG;
typedef float				FLOAT;
typedef double				DOUBLE;
typedef _Bool				BOOL;
typedef UCHAR*				PUCHAR;
typedef USHORT*				PUSHORT;
typedef ULONG*				PULONG;
typedef CHAR*				PCHAR;
typedef SHORT*				PSHORT;
typedef LONG*				PLONG;
typedef FLOAT*				PFLOAT;
typedef DOUBLE*				PDOUBLE;
typedef volatile CHAR		VCHAR;
typedef volatile UCHAR		VUCHAR;
typedef volatile SHORT		VSHORT;
typedef volatile USHORT	VUSHORT;
typedef volatile LONG		VLONG;
typedef volatile ULONG		VULONG;
typedef volatile FLOAT		VFLOAT;
typedef void *				PVOID;

/* BOOL */
#define		TRUE	(1)
#define		FALSE	(0)

#ifdef	__cplusplus
}
#endif




#endif /* INC_TYPEDEFINE_H_ */
