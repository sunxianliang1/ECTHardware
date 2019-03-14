
/****************************************************************************
*
*文件名：DSP28_Gpio.c
*
*功  能：2812通用输入输出口GPIO的初始化函数
*
*作  者: likyo from hellodsp
*
****************************************************************************/

#include "DSP28_Device.h"

/****************************************************************************
*
*名    称：InitGpio()
*
*功    能：初始化Gpio，使得Gpio的引脚处于已知的状态，例如确定其功能是特定功能
*          还是通用I/O。如果是通用I/O，是输入还是输出，等等。
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitGpio(void)
{

     EALLOW;
	 
     GpioMuxRegs.GPAMUX.all=0x0000;     
     GpioMuxRegs.GPADIR.all=0xFFFF;    	// upper byte as output/low byte as input
     GpioMuxRegs.GPAQUAL.all=0x0000;	// Input qualifier disabled

// Set GPIO B port pins, configured as GPIO
// Input Qualifier =0, none
// Set bits to 1 to configure peripherals signals on the pins
     GpioMuxRegs.GPBMUX.all=0x0000; 
     GpioMuxRegs.GPBDIR.all=0xFFFF;  
     GpioMuxRegs.GPBQUAL.all=0x0000;	// Input qualifier disabled

     GpioMuxRegs.GPFMUX.all=0x0FFF; 
     GpioMuxRegs.GPFDIR.all=0xF000;  
     //GpioMuxRegs.GPFQUAL.all=0x0000;	// Input qualifier disabled

     GpioMuxRegs.GPEMUX.all=0x0000; 
     GpioMuxRegs.GPEDIR.all=0xFFFF;  
     GpioMuxRegs.GPEQUAL.all=0x0000;	// Input qualifier disabled       
     EDIS;

}	
	
//===========================================================================
// No more.
//===========================================================================
