/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	upData.h
* filepath:	f:\draven\中控板\中控app版本\app
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/08/11
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/
#ifndef _UPDATA_H
#define _UPDATA_H


#define FLASH_SIZE      ((u32)8*1024)

#define BOOT            (u32)(0x8000+FLASH_SIZE-4)
typedef void			(*_fun)(void);

#define _run(x)         {void (*_run)(void)= (void(*)(void)) x; _run();}


void upData_CheckFrame(uint8_t *frame, uint8_t len);

#endif
/*
*********************************************************************
* -upData.h	<File end.>
* -f:\draven\中控板\中控app版本\app
*********************************************************************
*/

