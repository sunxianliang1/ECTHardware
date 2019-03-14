#include "DSP28_Device.h"
#include "common.h"
#include"math.h"

long AD_Data1=0;
long AC_Case[N]={0};


    unsigned int Sci_Bufdec[9];   //·ÅÖÃÉÏÎ»»ú´«ËÍ¹ıÀ´µÄÊı¾İ
 //unsigned int Sci_Bufdec; 
    unsigned int z;
    unsigned int Send_Flag;      //·¢ËÍ±êÖ¾Î»
	unsigned int Sci_VarRx[28],Sci_VarRx2[56],E_full[56],E_empty[56],BufH,BufL,BBufH,BBufL,BBuf,BBu,Gain,Error;  
    unsigned int crc=0,crcH=0,crcL=0;//´æ·ÅCRCĞ£ÑéÊı¾İ




///long AD_Data3[N]={0};
///long AD_Data4[N]={0};
///long AD_Data5[N]={0};
///long AD_Data6[N]={0};
///long AD_Data7[N]={0};
///long AD_Data8[N]={0};


volatile unsigned int * DA_CHA= (unsigned int *) 0x002000; //¶Ë¿ÚAÍ¨µÀµÄµØÖ·(8255)
volatile unsigned int * DA_CHB= (unsigned int *) 0x002001; //¶Ë¿ÚBÍ¨µÀµÄµØÖ·(8255)
volatile unsigned int * DA_CHC= (unsigned int *) 0x002003; //¿ØÖÆ×ÖÍ¨µÀµÄµØÖ·(8255)


volatile unsigned int * A0CH= (unsigned int *) 0x80000; //A0Í¨µÀµÄµØÖ·
///volatile unsigned int * A1CH= (unsigned int *) 0x80001; //A1Í¨µÀµÄµØÖ·
///volatile unsigned int * B0CH= (unsigned int *) 0x80002; //B0Í¨µÀµÄµØÖ·
///volatile unsigned int * B1CH= (unsigned int *) 0x80003; //B1Í¨µÀµÄµØÖ·
///volatile unsigned int * A0CH1= (unsigned int *) 0x90000; //A01Í¨µÀµÄµØÖ·
///volatile unsigned int * A1CH1= (unsigned int *) 0x90001; //A11Í¨µÀµÄµØÖ·
///volatile unsigned int * B0CH1= (unsigned int *) 0x90002; //B01Í¨µÀµÄµØÖ·
///volatile unsigned int * B1CH1= (unsigned int *) 0x90003; //B11Í¨µÀµÄµØÖ·
//volatile unsigned int * ExRamStart = (unsigned  int *)0x100000;///Íâ²¿RAMÆğÊ¼µØÖ·

long i=0;
///long Correlation_Shift=0;//´æ·ÅÏà¹Øº¯Êı×î´óÖµ¶ÔÓ¦µÄµãÊıÎ»ÒÆ
///double Correlation_Coefficient=0;//´æ·ÅÏà¹ØÏµÊı
double Capacitance=0;//´æ·ÅµçÈİÖµ


//º¯ÊıÉêÃ÷
void delay(unsigned int t);
void write_ad9833_d16(unsigned int x1,unsigned int x2);//ÏòAD9833Ğ´16Î»Êı¾İ²Ù×÷
void ad9833_data(double frequence1,double frequence2,double Phase1,double Phase2,unsigned int frequence_SFR,unsigned int WAVE_MODE);//ÏòAD9833Ğ´ÃüÁîºÍÊı¾İ£¨´®ĞĞ£©£¬//ÆµÂÊµ¥Î»ÎªMHz
//void ad5660_data(double voltage);//ÏòAD5660Ğ´ÃüÁîºÍÊı¾İ£¨´®ĞĞ£©£¬µ¥Î»V

void dac712_data(long voltage);//Ïòdac712Ğ´ÃüÁîºÍÊı¾İ£¨´®ĞĞ£©£¬µ¥Î»V

void data_acquire();//Êı¾İ²É¼¯
void rms_calculation(long x[],long y[]);//¼ÆËãĞÅºÅµÄ¾ù·½¸ùÖµ
///void correlation(long x[],long y[]);//Ïà¹Øº¯Êı
///void correlation_max(long x[]);//Ñ°ÕÒÏà¹Øº¯Êı×î´óÖµ¼°µãÊıÎ»ÒÆ
///void correlation_coefficient_calculation();//¼ÆËãÏà¹ØÏµÊı
void capacitance_calculation(long x[]);

void scia_init(void);

void getcheckcode(unsigned int x[],int num);//¼ÆËãCRCĞ£ÑéÊı¾İ²¢´æ·ÅÓÚcrc,num ±íÊ¾Êı×éxµÄÊı¾İ¸öÊı



void main()
{	 


	InitSysCtrl();/*³õÊ¼»¯ÏµÍ³*/
	DINT;//½ûÖ¹È«¾ÖÖĞ¶Ï
	IER = 0x0000;//½ûÖ¹CPUÖĞ¶Ï
	IFR = 0x0000;//Çå³ıËùÓĞCPUÖĞ¶Ï±êÖ¾
	InitPieCtrl();/*³õÊ¼»¯PIEÖĞ¶Ï*/
	InitPieVectTable();	/*³õÊ¼»¯PIEÖĞ¶ÏÊ¸Á¿±í*/
    InitSci(); /*³õÊ¼»¯SCIA¼Ä´æÆ÷*/
	InitGpio();

//	EINT;   // Enable Global interrupt INTM
//	ERTM;	// Enable Global realtime interrupt DBGM

	GpioDataRegs.GPBDAT.all=0xFFFF;
    GpioDataRegs.GPEDAT.bit.GPIOE1=0;

	ad9833_data(500000,500000,0,45,0,2);//ad9833³õÊ¼»¯

	///////¿ªÊ¼485²âÊÔ¹¤×÷±à³Ì//////
	for(i = 0; i < 8; i++)
    {
  	Sci_Bufdec[i] = 0;
    }
    

    z = 0;
    Send_Flag = 0;

	#if SCIA_INT
	/*ÉèÖÃÖĞ¶Ï·şÎñ³ÌĞòÈë¿ÚµØÖ·*/
	EALLOW;	
	PieVectTable.RXAINT = & SCIRXINTA_ISR;  //ÖØµã
	EDIS;   

	/*¿ªÖĞ¶Ï*/
	IER |= M_INT9;
	#endif


	EALLOW;	
	PieVectTable.TINT0 = & ISRTimer0;  //Ö¸Ïò¶¨Ê±Æ÷0µÄµØÖ·
	EDIS; 
    InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 150, 1750); //ÉèÖÃCPU£¬ºóÁ½¸ö²ÎÊıÎªÊ±ÖÓÆµÂÊ£¨MHz£©ºÍÖĞ¶ÏÊ±¼ä£¨us,ĞèÒª´óÓÚ30us£©£¬±¾³ÌĞòÖĞÖĞ¶ÏÊ±¼ä²»µÃµÍÓÚ2.5us
    IER |= M_INT1;//Âß¼­»ò£¬ÖĞ¶ÏÊ¹ÄÜ
	PieCtrl.PIEIER1.bit.INTx7=1;

	EINT;   // Enable Global interrupt INTM
	ERTM;	// Enable Global realtime interrupt DBGM

//¿ÕÂú¹ÜĞ´0
	for(i = 0; i < 55; i++)
    {
  	E_full[i] = 0;
	E_empty[i]= 0;
    }
    
///	ad5660_data(0.15);//ad5660³õÊ¼»¯
	
//	for	(i=0;i<0x4000;i++)		*(ExRamStart + i) = i;
///	ReceivedChar=0x11;

   BBuf=0x0080;
   BBufL=BBuf & 0x00FF;
   * DA_CHC=BBufL;              //8255ÊäÈë¿ØÖÆ×Ö


	while(1)
	{



//	dac712_data(10);
//	dac712_data(5);
//	dac712_data(0);
//	dac712_data(11);
//	dac712_data(15);
//	dac712_data(18);
//	dac712_data(19);


		Error=0x66;

		dac712_data(9905);//dac712³õÊ¼»¯0.09*16384/5
		GpioDataRegs.GPADAT.all=0x10;                    //case1
		delay(400);
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);

	    AD_Data1=* A0CH-32768;                
		AC_Case[0]=AD_Data1;                         //¸³Öµµ½case1ÊıÖĞ


		AD_Data1=0;
		

		dac712_data(5144);//ad5660³õÊ¼»¯1.76*16384/5
		GpioDataRegs.GPADAT.all=0x20;                    //case2
		delay(400);
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[1]=AD_Data1;                         //¸³Öµµ½case2ÊıÖĞ
		
	    AD_Data1=0;
		


		dac712_data(5341);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x30;                    //case3
		delay(400);
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[2]=AD_Data1;                         //¸³Öµµ½case3ÊıÖĞ
		

	   	AD_Data1=0;
		

		dac712_data(4358);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x40;                    //case4
		delay(400);		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[3]=AD_Data1;                         //¸³Öµµ½case4Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(4368);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x50;                    //case5
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[4]=AD_Data1;                         //¸³Öµµ½case5Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(4554);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x60;                    //case6
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[5]=AD_Data1;                         //¸³Öµµ½case6Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(9263);//ad5660³õÊ¼»¯3.43*16384/5
		GpioDataRegs.GPADAT.all=0x70;                    //case7
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[6]=AD_Data1;                         //¸³Öµµ½case7Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(10557);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x21;                    //case8
		delay(400);
	
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[7]=AD_Data1;                         //¸³Öµµ½case8Êı×éÖĞ
		


	   
		AD_Data1=0;
		

		dac712_data(5635);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x31;                    //case9
		delay(400);
	
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[8]=AD_Data1;                         //¸³Öµµ½case9Êı×éÖĞ
		


		AD_Data1=0;
		

		dac712_data(4455);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x41;                    //case10
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[9]=AD_Data1;                         //¸³Öµµ½case10Êı×éÖĞ
		


	   
		AD_Data1=0;
		

		dac712_data(4423);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x51;                    //case11
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[10]=AD_Data1;                         //¸³Öµµ½case11Êı×éÖĞ
		


	    
		AD_Data1=0;
		


		dac712_data(4456);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x61;                    //case12
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[11]=AD_Data1;                         //¸³Öµµ½case12Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(4588);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x71;                    //case13
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[12]=AD_Data1;                         //¸³Öµµ½case13Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(9932);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x32;                    //case14
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[13]=AD_Data1;                         //¸³Öµµ½case14Êı×éÖĞ
		


	   
		AD_Data1=0;
		

		dac712_data(4654);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x42;                    //case15
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
     	AC_Case[14]=AD_Data1;                         //¸³Öµµ½case15Êı×éÖĞ
		


	    
		AD_Data1=0;
		


		dac712_data(4490);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x52;                    //case16
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[15]=AD_Data1;                         //¸³Öµµ½case16Êı×éÖĞ
		


	    
		AD_Data1=0;
		


		dac712_data(4490);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x62;                    //case17
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[16]=AD_Data1;                         //¸³Öµµ½case17Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(4487);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x72;                    //case18
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[17]=AD_Data1;                         //¸³Öµµ½case18Êı×éÖĞ
		

	   
		AD_Data1=0;
		


		dac712_data(9105);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x43;                    //case19
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[18]=AD_Data1;                         //¸³Öµµ½case19Êı×éÖĞ
		


	    
		AD_Data1=0;
		


		dac712_data(4553);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x53;                    //case20
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[19]=AD_Data1;                         //¸³Öµµ½case20Êı×éÖĞ
		


	    
		AD_Data1=0;
		


		dac712_data(4381);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x63;                    //case21
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[20]=AD_Data1;                         //¸³Öµµ½case21Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(4346);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x73;                    //case22
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[21]=AD_Data1;                         //¸³Öµµ½case22Êı×éÖĞ
		


	   
		AD_Data1=0;
		

		dac712_data(10504);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x54;                    //case23
		delay(400);
	
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[22]=AD_Data1;                         //¸³Öµµ½case23Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(5175);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x64;                    //case24
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[23]=AD_Data1;                         //¸³Öµµ½case24Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(5373);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x74;                    //case25
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[24]=AD_Data1;                         //¸³Öµµ½case25Êı×éÖĞ
		


	   
		AD_Data1=0;
		

		dac712_data(10755);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x65;                    //case26
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[25]=AD_Data1;                         //¸³Öµµ½case26Êı×éÖĞ
		


	    
		AD_Data1=0;
		

		dac712_data(5687);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x75;                    //case27
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[26]=AD_Data1;                         //¸³Öµµ½case27Êı×éÖĞ
		


	    AD_Data1=0;
		

		dac712_data(9882);//ad5660³õÊ¼»¯
		GpioDataRegs.GPADAT.all=0x76;                    //case28
		delay(400);
		
		GpioDataRegs.GPBDAT.all=0x0000;//Æô¶¯ADCÊı¾İ×ª»»
		delay(10);
		GpioDataRegs.GPBDAT.all=0xFFFF;
		delay(80);
	    AD_Data1=* A0CH-32768;                
		AC_Case[27]=AD_Data1;                         //¸³Öµµ½case28Êı×éÖĞ
		


	 for(i=0;i<N;i++)
		{
        if (AC_Case[i]>4096 || AC_Case[i]<0) Error=44;     //ÅĞ¶ÏĞÅºÅÊÇ·ñÕı³£
		if (AC_Case[i]>2047) AC_Case[i]=AC_Case[i]-4096;
		}


	 for(i=0;i<28;i++)
		{
        Sci_VarRx[i]=AC_Case[i];
 		}


	 for(i=0;i<28;i++)
		{
        BufL=Sci_VarRx[i] & 0x00FF;
		BufH=Sci_VarRx[i]>>8;
		Sci_VarRx2[2*i]=BufH;
		Sci_VarRx2[2*i+1]=BufL;
 		}






      AD_Data1=0;
	
	GpioDataRegs.GPEDAT.bit.GPIOE2 = 0;
		 

		 
	}   
}



void delay(unsigned int t)
{
 	while(t>0)
    	t--;
}




//ÏòAD9833Ğ´16Î»Êı¾İ£¬ÑÏ¸ñ°´ÕÕÕâ¸öÊ±Ğò£¬²»ÄÜËæÒâĞŞ¸Ä·ñÔò±Ø³ö´í
//GpioDataRegs.GPBDAT.bit.GPIOB3¹«ÓÃÊı¾İÊäÈë¶ËDATA
//GpioDataRegs.GPBDAT.bit.GPIOB4µÚÒ»¸ö´®ĞĞÊ±ÖÓÊäÈë¶ËSLCK1
//GpioDataRegs.GPBDAT.bit.GPIOB5µÚ¶ş¸ö´®ĞĞÊ±ÖÓÊäÈë¶ËSLCK2
//GpioDataRegs.GPBDAT.bit.GPIOB6µÍµçÆ½ÓĞĞ§¿ØÖÆÊäÈë¶ËFSYNC
void write_ad9833_d16(unsigned int x1,unsigned int x2)
{
	int i,w;
	delay(5);
	GpioDataRegs.GPBDAT.bit.GPIOB4=1;
	delay(5);
	GpioDataRegs.GPBDAT.bit.GPIOB5=1;
	delay(5);
	GpioDataRegs.GPBDAT.bit.GPIOB6=1;
	delay(5);
	GpioDataRegs.GPBDAT.bit.GPIOB6=0;
	delay(5);
	w=x1;
	for(i=15;i>=0;i--)
	{	
		
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB3=(w>>i)&0x0001;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB4=0;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB4=1;
		delay(5);
	
	}
	w=x2;
	for(i=15;i>=0;i--)
	{
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB3=(w>>i)&0x0001;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB5=0;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB5=1;
		delay(5);
		
	}
	GpioDataRegs.GPBDAT.bit.GPIOB6=1;
	delay(5);
}




//¼ÆËãAD9833µÄ28Î»Êı¾İ²¢³õÊ¼»¯

//±äÁ¿frequence¾ÍÊÇÆµÂÊÖµ£¬µ¥Î»Hz£¬±ÈÈçÊäÈë100Hz£¬Ôò frequenceÎª100£¬ĞèÒªÌØ±ğ×¢ÒâµÄÊÇ²»ÄÜ³¬¹ı12MHz£»
//±äÁ¿frequence_SFRÊÇÉèÖÃÆµÂÊ¼Ä´æÆ÷Ñ¡Ôñ0ÎªÆµÂÊ¼Ä´æÆ÷0,1ÎªÆµÂÊ¼Ä´æÆ÷1£»
//±äÁ¿WAVE_MODEÊÇÉèÖÃÊä³ö²¨ĞÎÑ¡Ôñ0ÎªÈı½Ç²¨£¬1Îª·½²¨,2ÎªÕıÏÒ²¨£»
//±äÁ¿PhaseÊÇÉèÖÃ²¨ĞÎÏàÎ»Öµ,µ¥Î»ÊÇ¶È;
 
void ad9833_data(double frequence1,double frequence2,double phase1,double phase2,unsigned int frequence_SFR,unsigned int WAVE_MODE)
{
	unsigned int frequence_LSB1,frequence_MSB1,Phs_data1,frequence_LSB2,frequence_MSB2,Phs_data2,phase_hex;
	double  frequence_DATA,phase_DATA;
	long int frequence_hex;
 
	
	//¼ÆËãA9833_1ÆµÂÊµÄ16½øÖÆÖµ
	frequence_DATA=frequence1*268435456/25000000;	//Èç¹ûÊ±ÖÓÆµÂÊ²»Îª25MHZ£¬ĞŞ¸Ä¸Ã´¦µÄÆµÂÊÖµ£¬µ¥Î»MHz £¬AD9833×î´óÖ§³Ö25MHz
	frequence_hex=frequence_DATA;  //Õâ¸öfrequence_hexµÄÖµÊÇ32Î»µÄÒ»öºÜ´óµÄÊı×Ö£¬ĞèÒª²ğ·Ö³ÉÁ½¸ö14Î»½øĞĞ´¦Àí£»
	frequence_LSB1=frequence_hex; //frequence_hexµÍ16Î»ËÍ¸øfrequence_LSB
	frequence_LSB1=frequence_LSB1&0x3fff;//È¥³ı×î¸ßÁ½Î»£¬16Î»Êı»»È¥µô¸ßÎ»ºó±ä³ÉÁË14Î»
	frequence_MSB1=frequence_hex>>14; //frequence_hex¸ß16Î»ËÍ¸øfrequence_HSB
	frequence_MSB1=frequence_MSB1&0x3fff;//È¥³ı×î¸ßÁ½Î»£¬16Î»Êı»»È¥µô¸ßÎ»ºó±ä³ÉÁË14Î»
	//¼ÆËãA9833_1ÏàÎ»µÄ16½øÖÆµ
	phase_DATA=phase1*4096/360;
	phase_hex=phase_DATA;
	Phs_data1=phase_hex|0xC000;


	//¼ÆËãA9833_2ÆµÂÊµÄ16½øÖÆ
	frequence_DATA=frequence2*268435456/25000000;
	frequence_hex=frequence_DATA;  //Õâ¸öfrequence_hexµÄÖµÊÇ32Î»µÄÒ»öºÜ´óµÄÊı×Ö£¬ĞèÒª²ğ·Ö³ÉÁ½¸ö14Î»½øĞĞ´¦Àí£»
	frequence_LSB2=frequence_hex; //frequence_hexµÍ16Î»ËÍ¸øfrequence_LSB
	frequence_LSB2=frequence_LSB2&0x3fff;//È¥³ı×î¸ßÁ½Î»£¬16Î»Êı»»È¥µô¸ßÎ»ºó±ä³ÉÁË14Î»
	frequence_MSB2=frequence_hex>>14; //frequence_hexß16Î»ËÍ¸øfrequence_HSB
	frequence_MSB2=frequence_MSB2&0x3fff;//È¥³ı×î¸ßÁ½Î»£¬16Î»Êı»»È¥µô¸ßÎ»ºó±ä³ÉÁË14Î»
	//¼ÆËãA9833_2ÏàÎ»µÄ16½øÖÆÖµ	
	phase_DATA=phase2*4096/360;
	phase_hex=phase_DATA;
	Phs_data2=phase_hex|0xC000;

	



	if(frequence_SFR==0)				  //°ÑÊı¾İÉèÖÃµ½ÉèÖÃÆµÂÊ¼Ä´æÆ÷0
	{
		frequence_LSB1=frequence_LSB1|0x4000;
 		frequence_MSB1=frequence_MSB1|0x4000;
 
 		frequence_LSB2=frequence_LSB2|0x4000;
		frequence_MSB2=frequence_MSB2|0x4000;

	//Ê¹ÓÃÆµÂÊ¼Ä´æÆ÷0Êä³ö²¨ĞÎ
	write_ad9833_d16(0x0100,0x0100); //¸´Î»AD9833,¼´RESETÎ»Îª1
	write_ad9833_d16(0x2100,0x2100); //Ñ¡ÔñÊı¾İÒ»´ÎĞ´Èë£¬B28Î»ºÍRESETÎ»Îª1
	write_ad9833_d16(frequence_LSB1,frequence_LSB2); //L14£¬Ñ¡ÔñÆµÂÊ¼Ä´æÆ÷0µÄµÍ14Î»Êı¾İÊäÈë
	write_ad9833_d16(frequence_MSB1,frequence_MSB2); //H14 ÆµÂÊ¼Ä´æÆ÷µÄ¸ß14Î»Êı¾İÊäÈë
	write_ad9833_d16(Phs_data1,Phs_data2);//ÉèÖÃÏàÎ»
	//write_ad9833_d16(0x2000); //ÉèÖÃFSELECTÎ»Îª0£¬Ğ¾Æ¬½øÈë¹¤×÷×´Ì¬,ÆµÂÊ¼Ä´æÆ÷0Êä³ö²¨ĞÎ
	}


	if(frequence_SFR==1)				//°ÑÊı¾İÉèÖÃµ½ÉèÖÃÆµÂÊ¼Ä´æÆ÷1
	{
		frequence_LSB1=frequence_LSB1|0x8000;
 		frequence_MSB1=frequence_MSB1|0x8000;
 
 		frequence_LSB2=frequence_LSB2|0x8000;
		frequence_MSB2=frequence_MSB2|0x8000;

 		//Ê¹ÓÃÆµÂÊ¼Ä´æÆ÷1Êä³ö²¨ĞÎ
		write_ad9833_d16(0x0100,0x0100); //¸´Î»AD9833,¼´RESETÎ»Îª1
		write_ad9833_d16(0x2100,0x2100); //¡ÔñÊı¾İÒ»´ÎĞ´Èë£¬B28Î»ºÍRESETÎ»Îª1
		write_ad9833_d16(frequence_LSB1,frequence_LSB2); //L14£¬Ñ¡ÔñÆµÂÊ¼Ä´æÆ÷1µÄµÍ14Î»Êı¾İÊäÈë
		write_ad9833_d16(frequence_MSB1,frequence_MSB2); //H14 ÆµÂÊ¼Ä´æÆ÷µÄ¸ß14Î»Êı¾İÊäÈë
		write_ad9833_d16(Phs_data1,Phs_data2);//ÉèÖÃÏàÎ»
		//write_ad9833_d16(0x2800); ÉèÖÃFSELECTÎ»Îª1£¬¼´Ê¹ÓÃµÂÊ¼Ä´æÆ÷1µÄÖµ£¬Ğ¾Æ¬½øë¹¤×÷×´¬,ÆµÂÊ¼Ä´æÆ÷1Êä³ö²¨ĞÎ
	}



	
	if(WAVE_MODE==0)
	{
	//ÆµÂÊ¼Ä´æÆ÷Êä³öÈı½Ç²¨²¨ĞÎ
	delay(100);
	write_ad9833_d16(0x2002,0x2002); //ÉèÃMODEÎ»Îª1£¬Êä³öÈı½Ç²¨Ä£Ê½
	}



	if(WAVE_MODE==1)
	{
	//ÆµÂÊ¼Ä´æÆ÷Êä³ö·½²¨²¨ĞÎ
	delay(100);
	write_ad9833_d16(0x2028,0x2028); //ÉèÖÃOPBITENÎ»Îª1£¬·½²¨Êä³öÄ£Ê½
	}


	if(WAVE_MODE==2)
	{
	//ÆµÂÊ¼Ä´æÆ÷Êä³öÕıÏÒ²¨²¨ĞÎ
	delay(100);
	write_ad9833_d16(0x2000,0x2000); //ÉèÖÃMODEÎ»Îª0£¬Êä³öÕıÏÒ²¨Ä£Ê½
	}

}


//ÊıÄ£×ª»»Ğ¾Æ¬DAC712Êä³öÅäÖÃ
void dac712_data(long voltage)
{

    BBufL=voltage & 0x00FF;
	* DA_CHA =BBufL;
	BBufH=voltage>>8;
    * DA_CHB =BBufH;	
}



//ÊıÄ£×ª»»Ğ¾Æ¬AD5660Êä³öÅäÖÃ
/*  void ad5660_data(double voltage)
{
	unsigned int  voltage_DATA;
	int i,w;
	voltage_DATA=voltage*65536/5;
	delay(5);
	GpioDataRegs.GPBDAT.bit.GPIOB7=1;
	delay(5);
	GpioDataRegs.GPBDAT.bit.GPIOB6=1;
	delay(5);
	GpioDataRegs.GPBDAT.bit.GPIOB6=0;
	delay(5);
	w=voltage_DATA;
	for(i=23;i>=16;i--)
	{	
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB3=0;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB7=0;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB7=1;
		delay(5);
	}
	for(i=15;i>=0;i--)
	{	
		
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB3=(w>>i)&0x0001;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB7=0;
		delay(5);
		GpioDataRegs.GPBDAT.bit.GPIOB7=1;
		delay(5);
	}
	GpioDataRegs.GPBDAT.bit.GPIOB6=1;
	delay(5);
}

*/

/*  void data_acquire()
{
	long i;
	
	for(i=0;i<N;i++)
	{
		GpioDataRegs.GPBDAT.bit.GPIOB0=0;//Æô¶¯ADCÊı¾İ×ª»»
		GpioDataRegs.GPBDAT.bit.GPIOB1=0;
		GpioDataRegs.GPBDAT.bit.GPIOB2=0;
		delay(10); //while(GpioDataRegs.GPFDAT.bit.GPIOF13==0);//µÈ´ıADCÊı¾İ×ª»»µÄÍê³É
		
		GpioDataRegs.GPBDAT.bit.GPIOB0=1;//Æô¶¯ADCÊı¾İ±£³Ö
		GpioDataRegs.GPBDAT.bit.GPIOB1=1;
		GpioDataRegs.GPBDAT.bit.GPIOB2=1;
		delay(80);
		
		AD_Data1[i]=* A0CH-32768;
		if (AD_Data1[i]>4096 || AD_Data1[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£
			Error=1;
		if (AD_Data1[i]>2047) 
			AD_Data1[i]=AD_Data1[i]-4096;

		AD_Data2[i]=* A1CH-36864;
		if (AD_Data2[i]>4096 || AD_Data2[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£ 
			Error=1;
		if (AD_Data2[i]>2047) 
			AD_Data2[i]=AD_Data2[i]-4096;

		AD_Data3[i]=* B0CH-40960;
		if (AD_Data3[i]>4096 || AD_Data3[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£ 
			Error=1;
		if (AD_Data3[i]>2047) 
			AD_Data3[i]=AD_Data3[i]-4096;

		AD_Data4[i]=* B1CH-45056;
		if (AD_Data4[i]>4096 || AD_Data4[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£ 
			Error=44;
		if (AD_Data4[i]>2047) 
			AD_Data4[i]=AD_Data4[i]-4096;

	    AD_Data5[i]=* A0CH1-32768;
		if (AD_Data5[i]>4096 || AD_Data5[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£ 
			Error=44;
		if (AD_Data5[i]>2047) 
			AD_Data5[i]=AD_Data5[i]-4096;

		AD_Data6[i]=* A1CH1-36864;
		if (AD_Data6[i]>4096 || AD_Data6[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£ 
			Error=44;
		if (AD_Data6[i]>2047) 
			AD_Data6[i]=AD_Data6[i]-4096;

		AD_Data7[i]=* B0CH1-40960;
		if (AD_Data7[i]>4096 || AD_Data7[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£ 
			Error=44;
		if (AD_Data7[i]>2047) 
			AD_Data7[i]=AD_Data7[i]-4096;

		AD_Data8[i]=* B1CH1-45056;
		if (AD_Data8[i]>4096 || AD_Data8[i]<0)//ÅĞ¶Ï²É¼¯µÄĞÅºÅÊÇ·ñÕı³£ 
			Error=44;
		if (AD_Data8[i]>2047) 
			AD_Data8[i]=AD_Data8[i]-4096;
	  
	
	}
	

}

*/
/*
void correlation(long x[],long y[])//xÉÏÓÎ´«¸ĞÆ÷ĞÅºÅ£¬yÏÂÓÎ´«¸ĞÆ÷ĞÅºÅ
{
	long i,j;
	double Correlation_Max=0;//´æ·ÅÏà¹Øº¯Êı×î´óÖµ
	double Correlation_Result[400]={0};//´æ·ÅÏà¹Øº¯ÊıÖµ
	double tp1=0;
	double tp2=0;
	double rms=0;
	
	for(i=0;i<400;i++)
  	{
  		Correlation_Result[i]=0;
  		for(j=0;j<N-i;j++)
  		{ 
  			Correlation_Result[i]+=x[j]*y[j+i];
  		}
  	}

  	Correlation_Max=x[0];
	for(i=0;i<400;i++)    //Ñ°ÕÒ×î´óÖµ
	{
		if(x[i]>Correlation_Max)
		{
			Correlation_Shift = i;
			Correlation_Max = x[i];
		}
	}	
	
		
    for(i=0;i<N;i++)//¼ÆËãĞÅºÅµÄ¾ù·½¸ùÖµ	
	{
        tp1+=x[i]*x[i];
	    tp2+=y[i]*y[i];
	}
	rms=sqrt(tp1*tp2)/N;
	Correlation_Coefficient=Correlation_Max/(N-Correlation_Shift)/rms;
}



	

void capacitance_calculation(long x[])//¼ÆµçÈİÖµ
{
	long i,m;
	m=0;
	for(i=0;i<N;i++)
	{
		m+=x[i];
	}
	Capacitance=m/N;
}

*/


void getcheckcode(unsigned int x[],int num)
{
	
	int i=0,j=0;
	crc=0xFFFF;
	
	for(i=0;i<num-2;i++)
	{
		crc^=x[i];
		for(j=0;j<8;j++)
		{
			if(crc&1)
			{
				crc>>=1;
				crc^=0xA001;
			}
			else
			{
				crc>>=1;
			}

		}
		
	}

}



