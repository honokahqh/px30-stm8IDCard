#include "bsp_Manchester.h"
#include "stm8s.h"
#include "bsp.h"
#include "appValue.h"
#include "bsp_clock.h"
#include "app.h"

u8  rd_data[12];
u8  mdata=0;
__IO u8  btime=0;//ע���ж�����Ҫ��ȡ����Ҫ��__io

_DEF_RFID SysRfid={0};

_DEF_MANCHESTER Manchester=
{
	&btime,
	rd_data_55bit,
	rd_data_conver,
};

static void BtimeAdd() {
    int tim = 1;    /* 8us */
	  volatile int i = 0;
    while (1) {
        for (i = 0; i < 10; i++);
        tim--;
        if (tim <= 0)
            break;
    }
    //btime++;
	//++(*Manchester.PulseCnt);
}



//PD3��RFID�������ţ���ʼ������
void Rfid_Init(void)
{	
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);
}   
/**********************************************/
/* rd_data_55bit()����--��ȡ55λ��������
**********************************************/
u8 rd_data_55bit(void)
{
	u8 i = 55,j = 0,k = 0;
	rd_data_clr();
	if ( rd_start_bit() )   	//��Ϊ0ʱ���棩��Ϊ1ʱִ�У�
	{
		if ( rd_head_9bit() )
		{
			while ( i-- )
			{
				mdata=rd_next_bit();
				if (mdata==2)
				{
					return(0);
				}
				rd_data[j]|=mdata;
				++k;
				if (k==5)
				{
					++j;
					k=0;
				}
				rd_data[j]<<=1;
			}
			//if ( rd_data_pair() )
				return(1);
			//else
			//	return(0);
		}
		return(0);
	}
	return(0);
}

/**********************************************/
/* rd_start_bit()����--�Ƿ�������
*********************************************/
u8 rd_start_bit(void)
{
	#define OVER_CNT	3000
	static u16 cnt=0;
	btime=0;
	if (ManChesterIn)
	{
		while (ManChesterIn)
		{
			//BtimeAdd();
			if (btime>250 || ++cnt>OVER_CNT)
			{
				cnt=0;
				return(0);
			}
		}
		btime=0;
		while (!ManChesterIn)
		{
			//BtimeAdd();
			if (btime>250 || ++cnt>OVER_CNT)
			{
				cnt=0;
				return(0);
			}
		}
		btime=0;cnt=0;
		return(1);
	}
	else
	{
		cnt=0;
	}
	return(0);
}

/**********************************************/
/* rd_next_bit()����--��ȡһλ����
**********************************************/
u8 rd_next_bit(void)
{
	volatile u8 x,y=2;
	//while(btime>=47 || btime <=44){
		//BtimeAdd();
	//}
        //while(btime>=48 || btime <=45);
        while(btime>=47 || btime <=44);
	x=ManChesterIn;
	while (ManChesterIn==x)
	{
		//BtimeAdd();
		if (btime>79)	return(y);
	}
	btime=0;
        if(x)
          return 1;
        else
          return 0;
}
/**********************************************/
/* rd_head_9bit()����--��ȡ���뿪ʼ9��һ

**********************************************/
u8 rd_head_9bit(void)
{
	u8 x = 0,z = 0;
	while ( x != 0x09 )
	{
		z=rd_next_bit();
		if ( z == 1 )
			x++;
		else
			x = 0;

		if ( z==2)
		{
			return(0);
		}
	}
	return(1);
}
/**********************************************/
/* rd_data_clr()����--���55λ���ݻ�����
**********************************************/
void rd_data_clr(void)
{
	u8 c;
	for (c=0;c<11;++c)
		rd_data[c]=0;
}
/**********************************************/
/* rd_data_pair()����--
**********************************************/
u8 rd_data_pair(void)
{
	u8 i;
	for (i=0;i<10;++i)
	{
		if ( chenk_pair(rd_data[i]) ) return(0);
	}
	return(1);
}
/**********************************************/
/* chenk_pair()����--
**********************************************/
u8 chenk_pair(u8 c)
{
	switch (c)
	{
		case  0:return FALSE;
		case  3:return FALSE;
		case  5:return FALSE;
		case  6:return FALSE;
		case  9:return FALSE;
		case 10:return FALSE;
		case 12:return FALSE;
		case 15:return FALSE;
		case 17:return FALSE;
		case 18:return FALSE;
		case 20:return FALSE;
		case 23:return FALSE;
		case 24:return FALSE;
		case 27:return FALSE;
		case 29:return FALSE;
		case 30:return FALSE;
		default:return TRUE;
	}
}

/**********************************************/
/* rd_data_conver()����--����ת��4���ֽ�16����
**********************************************/
void rd_data_conver(u8 OutBuf[4])
{
	u8 i=0;

	u8 buf[10];
	for (i=0;i<10;++i)
	{
		rd_data[i]>>=1;
		buf[i]=rd_data[i];
	}
	OutBuf[0]=(buf[2]<<4)|buf[3];
	OutBuf[1]=(buf[4]<<4)|buf[5];
	OutBuf[2]=(buf[6]<<4)|buf[7];
	OutBuf[3]=(buf[8]<<4)|buf[9];	
}


/*---------------------------------------------------------------
** ��������: RFID_Read(void)
** ��������: ����������
----------------------------------------------------------------*/
void RFID_Read(void)
{
	u8 Ret=0;
	static u32 LastId=0;
	static u8  Find_NewCard=FALSE,OverCnt=0;

	Ret=Manchester.Decode();
	if(Ret==1)
	{
		u8 Tmp[4];
		Manchester.Result(Tmp);
		holdRegValue[HREG_RFID_ID1] = SysRfid.Buf[0]=Tmp[0];
		holdRegValue[HREG_RFID_ID2] = SysRfid.Buf[1]=Tmp[1];
		holdRegValue[HREG_RFID_ID3] = SysRfid.Buf[2]=Tmp[2];
		holdRegValue[HREG_RFID_ID4] = SysRfid.Buf[3]=Tmp[3];
		Find_NewCard=TRUE;
		OverCnt		=0;
                
		if(LastId!=SysRfid.Val)
		{
			LastId=SysRfid.Val;			
			//�����º��룬ִ���¿��ŵ��¼�     
			coilState[COIL_CARD] = 1;
			flag = 1;
		}	
	}
	///////////////////////////////////////////////////////////////
	if(Find_NewCard==TRUE)
	{
		if(++OverCnt > 40)/////////////��ʱ��������ʵ�����������
		{
			OverCnt				=0;
			LastId				=0;
			Find_NewCard		=FALSE;
			SysRfid.Val			=0;
		}
	}
	/////////////////////////////////////////////////////////////
	
}

