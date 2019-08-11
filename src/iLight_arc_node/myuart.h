#ifndef _MYUART_H_
#define _MYUART_H_

#include "embARC.h"
#include "embARC_debug.h"
#include <stdio.h>

#define kReceiveBufferSize  128

static const uint8_t *sTransmitBuffer = NULL;
static uint16_t sTransmitLength = 0;

static uint8_t sReceiveBuffer[kReceiveBufferSize];
static uint16_t sReceiveHead = 0;

static DEV_UART *Uart;

uint32_t x, y;

void UartEnable(void);
void UartSend(const uint8_t *aBuf, uint16_t aBufLength);
void processReceive(void);
void processTransmit(void);
void arcUartProcess(void);
void UART2GotLine(uint8_t *line, uint32_t len);
void processReceiveFromRPi(void);
uint32_t get_x();
uint32_t get_y();

#endif