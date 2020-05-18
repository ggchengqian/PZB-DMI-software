/*******************************************************
* XDS PZB系统DMI软件
* -----------------------------------------------------
* Filename: #include "recvdata.h"
* Creation Date: 2020-04-01
* Created By: chengqian
* Description:	CRC校验
* -----------------------------------------------------
********************************************************/

#ifndef CRC_H
#define CRC_H
#include "stdint.h"

uint32_t ccitt_crc8(uint8_t *ptr, uint32_t len);

#endif
