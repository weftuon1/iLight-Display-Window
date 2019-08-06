/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */

/**
 * \defgroup	EMBARC_APP_TMPL		embARC Template Example
 * \ingroup	EMBARC_APPS_TOTAL
 * \ingroup	EMBARC_APPS_BOARD_EMSK
 * \ingroup	EMBARC_APPS_BAREMETAL
 * \brief	embARC Example for template
 *
 * \details
 * ### Extra Required Tools
 *
 * ### Extra Required Peripherals
 *
 * ### Design Concept
 *
 * ### Usage Manual
 *
 * ### Extra Comments
 *
 */

/**
 * \file
 * \ingroup	EMBARC_APP_TMPL
 * \brief	main source of template example
 */

/**
 * \addtogroup	EMBARC_APP_TMPL
 * @{
 */
/* embARC HAL */
#include "embARC.h"
#include "embARC_debug.h"
#include <stdio.h>


#define DBG(fmt, ...)   printf(fmt, ##__VA_ARGS__)

enum
{
    kUartId = BOARD_CONSOLE_UART_ID,
    kBaudRate = BOARD_CONSOLE_UART_BAUD,
    kReceiveBufferSize = 128,
};

static void processReceive(void);
static void processTransmit(void);

static const uint8_t *sTransmitBuffer = NULL;
static uint16_t sTransmitLength = 0;

static uint8_t sReceiveBuffer[kReceiveBufferSize];
static uint16_t sReceiveHead = 0;

static DEV_UART *consoleUart;

void otPlatUartEnable(void)
{
    int32_t stateUart = 0;
    //otError error = OT_ERROR_DROP;

    /* UART in embARC */
    //consoleUart = uart_get_dev(BOARD_CONSOLE_UART_ID);
    consoleUart = uart_get_dev(DFSS_UART_2_ID);
    io_arduino_config(ARDUINO_PIN_0, ARDUINO_UART, IO_PINMUX_ENABLE);


    //otEXPECT_ACTION(!(consoleUart == NULL), DBG("Console UART is missing.\r\n"));

    stateUart = consoleUart->uart_open(BOARD_CONSOLE_UART_BAUD);

    if (stateUart == E_OPNED)
    {
        consoleUart->uart_control(UART_CMD_SET_BAUD, (void *)(BOARD_CONSOLE_UART_BAUD));
        //error = OT_ERROR_NONE;
        DBG("Set Console UART Baudrate to %d.\r\n", BOARD_CONSOLE_UART_BAUD);
    }
    else if (stateUart == E_OK)
    {
        //error = OT_ERROR_NONE;
        DBG("Open Console UART Successfully.\r\n");
    }
    else
    {
        DBG("Open Console UART Error.\r\n");
    }

exit:

    return; //error;

}

void otPlatUartSend(const uint8_t *aBuf, uint16_t aBufLength)
{
    //otError error = OT_ERROR_NONE;

    //otEXPECT_ACTION(sTransmitBuffer == NULL, error = OT_ERROR_BUSY);

    sTransmitBuffer = aBuf;
    sTransmitLength = aBufLength;

exit:
    return;// error;
}

void processReceive(void)
{

    int32_t rdAvail = 0;
    uint16_t remaining;

    consoleUart->uart_control(UART_CMD_GET_RXAVAIL, (void *)(&rdAvail));
    //otEXPECT_ACTION(rdAvail > 0, ;);

    remaining = kReceiveBufferSize - sReceiveHead;

    if (rdAvail >= remaining)
    {
        consoleUart->uart_read((void *)(sReceiveBuffer + sReceiveHead), (uint32_t)remaining);
        otPlatUartSend(sReceiveBuffer + sReceiveHead, remaining);
        sReceiveHead = 0;
        rdAvail -= (int32_t)remaining;
    }

    while (rdAvail >= kReceiveBufferSize)
    {
        consoleUart->uart_read((void *)(sReceiveBuffer + sReceiveHead), (uint32_t)kReceiveBufferSize);
        otPlatUartSend(sReceiveBuffer + sReceiveHead, kReceiveBufferSize);
        rdAvail -= kReceiveBufferSize;
    }

    if (rdAvail > 0)
    {
        consoleUart->uart_read((void *)(sReceiveBuffer + sReceiveHead), (uint32_t)rdAvail);
        otPlatUartSend(sReceiveBuffer + sReceiveHead, rdAvail);
        sReceiveHead += (uint16_t)rdAvail;
    }

exit:
    return;
}

/* void otPlatUartDisable(void)
{
    return OT_ERROR_NONE;
}*/




void processTransmit(void)
{
   // otEXPECT_ACTION(sTransmitBuffer != NULL, ;);

    consoleUart->uart_write((void *)sTransmitBuffer, (int32_t)sTransmitLength);

    sTransmitBuffer = NULL;
   // otPlatUartSendDone();

exit:
    return;
}

void arcUartProcess(void)
{
    processReceive();
    processTransmit();
}

/** main entry */
int main(void)
{

	//EMBARC_PRINTF("Hello embARC from template example\r\n");
    //for(int i=0;i<11;i++)printf("%d\r\n", i);

	otPlatUartEnable();
	/* char mTxBuffer[128];
	
	mTxBuffer[0]='t';
	mTxBuffer[1]='t';
	mTxBuffer[2]='t';
	mTxBuffer[3]='t';*/


	otPlatUartSend("hihi", 4);
	processTransmit();
	 while(1){
		processReceive();
		//otPlatUartSend(sReceiveBuffer, );
    	processTransmit();
	}

	return E_SYS;
}

/** @} */