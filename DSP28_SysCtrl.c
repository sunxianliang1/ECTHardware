
/****************************************************************************
*
*文件名：DSP28_SysCtrl.c
*
*功  能：对2812的系统控制模块进行初始化
*
*作  者: likyo from hellodsp
*
****************************************************************************/

#include "DSP28_Device.h"

/****************************************************************************
*
*名    称：InitSysCtrl()
*
*功    能：该函数对2812的系统控制寄存器进行初始化
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitSysCtrl(void)
{
   Uint16 i;
   EALLOW;
// On TMX samples, to get the best performance of on chip RAM blocks M0/M1/L0/L1/H0 internal
// control registers bit have to be enabled. The bits are in Device emulation registers.
   DevEmuRegs.M0RAMDFT = 0x0300;
   DevEmuRegs.M1RAMDFT = 0x0300;
   DevEmuRegs.L0RAMDFT = 0x0300;
   DevEmuRegs.L1RAMDFT = 0x0300;
   DevEmuRegs.H0RAMDFT = 0x0300;
   
           
// Disable watchdog module
   SysCtrlRegs.WDCR= 0x0068;

// Initalize PLL
   SysCtrlRegs.PLLCR = 0xA;
   // Wait for PLL to lock
   for(i= 0; i< 5000; i++){}
       
// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
   SysCtrlRegs.HISPCP.all = 0x0001;
   SysCtrlRegs.LOSPCP.all = 0x0002;	
// Peripheral clock enables set for the selected peripherals.   
   SysCtrlRegs.PCLKCR.bit.EVAENCLK=1;
   SysCtrlRegs.PCLKCR.bit.EVBENCLK=1;
   SysCtrlRegs.PCLKCR.bit.SCIENCLKA=1;
// SysCtrlRegs.PCLKCR.bit.SCIENCLKB=1;
		
   		
   EDIS;
	
}

/****************************************************************************
*
*名    称：KickDog()
*
*功    能：喂狗函数，当使用看门狗的时候，为了防止看门狗溢出，需要不断的给看门
*          狗"喂食"，给看门狗密钥寄存器周期性的写入0x55+0xAA序列，清除看门狗
*          计数器寄存器的值
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/


void KickDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}

//===========================================================================
// No more.
//===========================================================================
