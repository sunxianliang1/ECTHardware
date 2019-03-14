
#include "DSP28_Device.h"

struct CPUTIMER_VARS CpuTimer0;
struct CPUTIMER_VARS CpuTimer1;
struct CPUTIMER_VARS CpuTimer2;

//---------------------------------------------------------------------------
// InitCpuTimers: 
//---------------------------------------------------------------------------
// This function initializes all three CPU timers to a known state.
//初始化CPU定时器，共3个32位定时器

void InitCpuTimers(void)
{
	// Initialize address pointers to respective timer registers:
	CpuTimer0.RegsAddr = &CpuTimer0Regs;
	CpuTimer1.RegsAddr = &CpuTimer1Regs;
	CpuTimer2.RegsAddr = &CpuTimer2Regs;

	// Initialize timer period to maximum:	
	CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
	CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
	CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;

	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):	
	CpuTimer0Regs.TPR.all  = 0;
	CpuTimer0Regs.TPRH.all = 0;
	
	// Make sure timers are stopped:///定时器停止状态位
	CpuTimer0Regs.TCR.bit.TSS = 1;             
	CpuTimer1Regs.TCR.bit.TSS = 1;             
	CpuTimer2Regs.TCR.bit.TSS = 1;             

	// Reload all counter registers with period values:
	CpuTimer0Regs.TCR.bit.TRB = 1;             
	CpuTimer1Regs.TCR.bit.TRB = 1;             
	CpuTimer2Regs.TCR.bit.TRB = 1;             
	
	// Reset interrupt counters:
	CpuTimer0.InterruptCount = 0;
	CpuTimer1.InterruptCount = 0;
	CpuTimer2.InterruptCount = 0;
}	
	
//---------------------------------------------------------------------------
// ConfigCpuTimer: 
//---------------------------------------------------------------------------
// This function initializes the selected timer to the period specified
// by the "Freq" and "Period" parameters. The "Freq" is entered as "MHz"
// and the period in "uSeconds". The timer is held in the stopped state
// after configuration.
//

void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
	Uint32 	temp;///定时器计数值
	
	// Initialize timer period:	
	Timer->CPUFreqInMHz = Freq;
	Timer->PeriodInUSec = Period;
	temp = (long) (Freq * Period);
	Timer->RegsAddr->PRD.all = temp-1;

	// Set pre-scale counter to divide by 1 (SYSCLKOUT):	
	Timer->RegsAddr->TPR.all  = 0;
	Timer->RegsAddr->TPRH.all  = 0;
	
	// Initialize timer control register:
//	Timer->RegsAddr->TCR.bit.POL = 0;      // 0 = Pulse Low
//	Timer->RegsAddr->TCR.bit.TOG =	0;     // 0 = No Toggle, POL bit defines action
	Timer->RegsAddr->TCR.bit.TSS = 1;      // 1 = Stop timer, 0 = Start/Restart Timer 
	Timer->RegsAddr->TCR.bit.TRB = 1;      // 1 = reload timer
//	Timer->RegsAddr->TCR.bit.FRCEN = 0;    // Force output enable (not used)
//	Timer->RegsAddr->TCR.bit.PWIDTH = 7;   // 7+1 = 8 SYSCLKOUT cycle pulse width 
	Timer->RegsAddr->TCR.bit.SOFT = 1;
	Timer->RegsAddr->TCR.bit.FREE = 0;     // Timer Free Run
	Timer->RegsAddr->TCR.bit.TIE = 1;      // 0 = Disable/ 1 = Enable Timer Interrupt
	
	// Reset interrupt counter:
	Timer->InterruptCount = 0;
}

//===========================================================================
// No more.
//===========================================================================
