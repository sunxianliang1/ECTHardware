
#include "DSP28_Device.h"

//---------------------------------------------------------------------------
// InitSPI: 
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//



void InitSci(void)
{
	// Initialize SCI-A:
	
	EALLOW;
	GpioMuxRegs.GPFMUX.all = 0x0030;//使能SCITXD，SCIRXD管脚
	EDIS;	

   
	//SciaRegs.SCIFFTX.all = 0xE040;
	//SciaRegs.SCIFFRX.all = 0x2021;
	//SciaRegs.SCIFFCT.all = 0x0;
	
	SciaRegs.SCICTL1.bit.SWRESET=0;//复位SCI
	/* loopback   8 bit data */
	SciaRegs.SCICCR.all = 0x07;	// 1 bit stop, disable parity, idle mode, 8 bits data 
	
	SciaRegs.SCICTL1.all = 0x03; // 读写使能 
	SciaRegs.SCICTL2.all = 0x03; //读写中断时能
	
//	SciaRegs.SCIHBAUD = 0x01;//设置波特率
//	SciaRegs.SCILBAUD = 0xE7;//设置波特率  9600
	SciaRegs.SCIHBAUD = 0x00;
	SciaRegs.SCILBAUD = 0xF3; //设置波特率  19200

	
	SciaRegs.SCICTL1.all = 0x23;//使能SCI，使能发送器接收器
	PieCtrl.PIEIER9.bit.INTx1=1; //使能PIE中断SCIARXINT

	//tbd...
 	

	// Initialize SCI-B:

	//tbd...
}
/*
int SciaTx_Ready(void)
{
	unsigned int i;
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	return(i);
}
*/


