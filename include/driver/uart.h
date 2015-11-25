#ifndef UART_APP_H
#define UART_APP_H

#include "uart_register.h"
#include "ets_sys.h"

#define UART0               0
#define UART1               1

#define UART_TX_BUFFER_SIZE 256   //Ring buffer length of tx buffer
#define UART_RX_BUFFER_SIZE 256   //Ring buffer length of rx buffer

#define UART_BUFF_EN        0     //use uart buffer  , FOR UART0
#define UART_SELFTEST       0     //set 1:enable the loop test demo for uart buffer, FOR UART0

#define UART_HW_RTS         0     //set 1: enable uart hw flow control RTS, PIN MTDO, FOR UART0
#define UART_HW_CTS         0     //set1: enable uart hw flow contrl CTS , PIN MTCK, FOR UART0

typedef enum {
	FIVE_BITS = 0x0, SIX_BITS = 0x1, SEVEN_BITS = 0x2, EIGHT_BITS = 0x3
} UartBitsNum4Char;

typedef enum {
	ONE_STOP_BIT = 0x1, ONE_HALF_STOP_BIT = 0x2, TWO_STOP_BIT = 0x3
} UartStopBitsNum;

typedef enum {
	NONE_BITS = 0x2, ODD_BITS = 1, EVEN_BITS = 0
} UartParityMode;

typedef enum {
	STICK_PARITY_DIS = 0, STICK_PARITY_EN = 1
} UartExistParity;

typedef enum {
	UART_None_Inverse = 0x0,
	UART_Rxd_Inverse = UART_RXD_INV,
	UART_CTS_Inverse = UART_CTS_INV,
	UART_Txd_Inverse = UART_TXD_INV,
	UART_RTS_Inverse = UART_RTS_INV,
} UART_LineLevelInverse;

typedef enum {
	BIT_RATE_300 = 300,
	BIT_RATE_600 = 600,
	BIT_RATE_1200 = 1200,
	BIT_RATE_2400 = 2400,
	BIT_RATE_4800 = 4800,
	BIT_RATE_9600 = 9600,
	BIT_RATE_19200 = 19200,
	BIT_RATE_38400 = 38400,
	BIT_RATE_57600 = 57600,
	BIT_RATE_74880 = 74880,
	BIT_RATE_115200 = 115200,
	BIT_RATE_230400 = 230400,
	BIT_RATE_460800 = 460800,
	BIT_RATE_921600 = 921600,
	BIT_RATE_1843200 = 1843200,
	BIT_RATE_3686400 = 3686400,
} UartBautRate;

typedef enum {
	NONE_CTRL, HARDWARE_CTRL, XON_XOFF_CTRL
} UartFlowCtrl;

typedef enum {
	USART_HardwareFlowControl_None = 0x0,
	USART_HardwareFlowControl_RTS = 0x1,
	USART_HardwareFlowControl_CTS = 0x2,
	USART_HardwareFlowControl_CTS_RTS = 0x3
} UART_HwFlowCtrl;

typedef enum {
	EMPTY, UNDER_WRITE, WRITE_OVER
} RcvMsgBuffState;

typedef struct {
	uint32 TrxBuffSize;
	uint8 *pTrxBuff;
} TrxMsgBuff;

typedef enum {
	BAUD_RATE_DET, WAIT_SYNC_FRM, SRCH_MSG_HEAD, RCV_MSG_BODY, RCV_ESC_CHAR,
} RcvMsgState;

typedef struct {
	uint32 RcvBuffSize;
	uint8 *pRcvMsgBuff;
	uint8 *pWritePos;
	uint8 *pReadPos;
	uint8 TrigLvl; //JLU: may need to pad
	RcvMsgBuffState BuffState;
} RcvMsgBuff;

typedef struct {
	UartBautRate baut_rate;
	UartBitsNum4Char data_bits;
	UartExistParity exist_parity;
	UartParityMode parity;
	UartStopBitsNum stop_bits;
	UartFlowCtrl flow_ctrl;
	RcvMsgBuff rcv_buff;
	TrxMsgBuff trx_buff;
	RcvMsgState rcv_state;
	int received;
	int buff_uart_no;  //indicate which uart use tx/rx buffer
} UartDevice;

void uart_init(UartBautRate baund_rate);
LOCAL void ICACHE_FLASH_ATTR uart_config();
LOCAL void uart_rx_intr_handler(void *pt);
LOCAL STATUS uart_tx_one_char(uint8 ch);
uint8_t uart_getchar();

#endif
