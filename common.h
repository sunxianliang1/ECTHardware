#ifndef COMMON_H
#define COMMON_H
// fft.c

#define N   28

//extern double Correlation_Result[400];
 extern unsigned int Sci_Bufdec[9];
 extern unsigned int Send_Flag;
 extern unsigned int z;
 extern unsigned int Sci_VarRx[28],Sci_VarRx2[56],E_full[56],E_empty[56],BufH,BufL,BBufH,BBufL,BBuf,BBu,Gain,Error; 
 extern unsigned int crc,crcH,crcL;//存放CRC校验数据




//extern double Correlation_Result[400];


//ADS8505
extern long AD_Data1;
extern long AC_Case[N];
extern long fL,fH,pcon;
extern long fcon1,pcon1,fcon2,pcon2,w,y;
extern long i;


extern long Correlation_Shift;//存放相关函数最大值对应的点数位移
extern double Correlation_Coefficient;//存放相关系数
extern double Capacitance;//存放电容值
//extern unsigned int Sci_Data[6],BufH,BufL,Buf;
//extern unsigned int BBufH,BBufL,BBuf,BBu;
//extern int Error;
//extern Uint16 ReceivedChar;//存取上位机发来的开始信号

/*
extern void delay(unsigned int t);
extern void write_ad9833_d16(unsigned int x1,unsigned int x2);//向AD9833写16位数据操作
extern void ad9833_data(double frequence1,double frequence2,double Phase1,double Phase2,unsigned int frequence_SFR,unsigned int WAVE_MODE);//向AD9833写命令和数据（串行），//频率单位为MHz
extern void ad5660_data(double voltage);//向AD5660写命令和数据（串行），单位V
extern void data_acquire();//数据采集
extern void rms_calculation(long x[],long y[]);//计算信号的均方根值
extern void correlation(long x[],long y[]);//相关函数
extern void correlation_max(long x[]);//寻找相关函数最大值及点数位移
extern void correlation_coefficient_calculation();//计算相关系数
extern void capacitance_calculation(long x[]);
*/


#endif
