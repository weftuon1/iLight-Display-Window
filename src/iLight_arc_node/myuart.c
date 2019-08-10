#include    "myuart.h"

void UartEnable(void)
{
    int32_t stateUart = 0;

    /* UART in embARC */
    /*Impement for Uart2*/
    Uart = uart_get_dev(DFSS_UART_2_ID);
    io_arduino_config(ARDUINO_PIN_0, ARDUINO_UART, IO_PINMUX_ENABLE);

    stateUart = Uart->uart_open(UART_BAUDRATE_115200);

    if (stateUart == E_OPNED)
    {
        Uart->uart_control(UART_CMD_SET_BAUD, (void *)(UART_BAUDRATE_115200));
        
        printf("Set UART Baudrate to %d.\r\n", UART_BAUDRATE_115200);
    }
    else if (stateUart == E_OK)
    {
        printf("Open UART Successfully.\r\n");
    }
    else
    {
        printf("Open UART Error.\r\n");
    }

exit:

    return;

}

void UartSend(const uint8_t *aBuf, uint16_t aBufLength)
{

    sTransmitBuffer = aBuf;
    sTransmitLength = aBufLength;

exit:
    return;
}

void processReceive(void)
{

    int32_t rdAvail = 0;
    uint16_t remaining;

    Uart->uart_control(UART_CMD_GET_RXAVAIL, (void *)(&rdAvail));

    remaining = kReceiveBufferSize - sReceiveHead;

    if (rdAvail >= remaining)
    {
        Uart->uart_read((void *)(sReceiveBuffer + sReceiveHead), (uint32_t)remaining);
        UartSend(sReceiveBuffer + sReceiveHead, remaining);
        sReceiveHead = 0;
        rdAvail -= (int32_t)remaining;
    }

    while (rdAvail >= kReceiveBufferSize)
    {
        Uart->uart_read((void *)(sReceiveBuffer + sReceiveHead), (uint32_t)kReceiveBufferSize);
        UartSend(sReceiveBuffer + sReceiveHead, kReceiveBufferSize);
        rdAvail -= kReceiveBufferSize;
    }

    if (rdAvail > 0)
    {
        Uart->uart_read((void *)(sReceiveBuffer + sReceiveHead), (uint32_t)rdAvail);
        UartSend(sReceiveBuffer + sReceiveHead, rdAvail);
        sReceiveHead += (uint16_t)rdAvail;
    }

exit:
    return;
}

void processTransmit(void)
{

    Uart->uart_write((void *)sTransmitBuffer, (int32_t)sTransmitLength);

    sTransmitBuffer = NULL;

exit:
    return;
}

void arcUartProcess(void)
{
    processReceive();
    processTransmit();
}


void UART2GotLine(uint8_t *line, uint32_t len) {
	//int32_t width, hight;
	sscanf((const char*) line, "%ld,%ld", &width, &height);
	
}

void processReceiveFromRPi(void)
{

    int32_t rdAvail = 0;
    uint16_t len;
    uint32_t sReceivePos=0;

    
//printf("before loop\r\n");
    while(1){
//printf("first loop\r\n");
        while(rdAvail==0){
            Uart->uart_control(UART_CMD_GET_RXAVAIL, (void *)(&rdAvail));
        }
//printf("read %d\r\n", rdAvail);
        Uart->uart_read((void *)(sReceiveBuffer + sReceivePos), 1);
        /*For debug*/
        UartSend((sReceiveBuffer + sReceivePos), 1);
        processTransmit();

        sReceivePos += 1;
        if(sReceivePos==kReceiveBufferSize)sReceivePos=0;

        len=sReceivePos-1;
//printf("read %c\r\n", sReceiveBuffer[sReceivePos-1]);
        if(sReceiveBuffer[sReceivePos-1]== 'a'){
//printf("got enter \r\n");
            sReceiveBuffer[sReceivePos-1]='\0';
            if(sReceivePos>0){
                if (sReceiveBuffer[sReceivePos-2] == '\r') {
                    sReceiveBuffer[sReceivePos-2] = '\0';
                    len--;
                }
            }
            UART2GotLine(sReceiveBuffer, len);
            //sReceivePos = 0;
            break;
        }
    }

exit:
    return;
}

uint32_t get_width(){
printf("w=%d\r\n", width);
    return width;
}

uint32_t get_height(){
printf("h=%d\r\n", height);
    return height;
}