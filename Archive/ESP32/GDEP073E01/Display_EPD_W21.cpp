#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

unsigned char partFlag=1;

void EPD_W21_Init(void)
{
  EPD_W21_RST_0;    // Module reset
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10);//At least 10ms delay 
  
}

void lcd_chkstatus(void)
{
  while(!isEPD_W21_BUSY);                         
}
//slow
void EPD_init(void)
{ 

  EPD_W21_Init(); //Electronic paper IC reset   
  
  EPD_W21_WriteCMD(0xAA);    // CMDH
  EPD_W21_WriteDATA(0x49);
  EPD_W21_WriteDATA(0x55);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x08);
  EPD_W21_WriteDATA(0x09);
  EPD_W21_WriteDATA(0x18);

  EPD_W21_WriteCMD(PWRR);//
  EPD_W21_WriteDATA(0x3F);
  
  EPD_W21_WriteCMD(PSR);  
  EPD_W21_WriteDATA(0x5F);
  EPD_W21_WriteDATA(0x69);
  
  EPD_W21_WriteCMD(POFS);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x44); 

  EPD_W21_WriteCMD(BTST1);
  EPD_W21_WriteDATA(0x40);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x2C);
  
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x17);
  EPD_W21_WriteDATA(0x49);

  EPD_W21_WriteCMD(BTST3);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x22);
  EPD_W21_WriteCMD(PLL);
  EPD_W21_WriteDATA(0x08);
  EPD_W21_WriteCMD(CDI);
  EPD_W21_WriteDATA(0x3F);
  
  EPD_W21_WriteCMD(TCON);
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(TRES);
  EPD_W21_WriteDATA(0x03);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x01); 
  EPD_W21_WriteDATA(0xE0);

  EPD_W21_WriteCMD(T_VDCS);
  EPD_W21_WriteDATA(0x01);
  
  EPD_W21_WriteCMD(PWS);
  EPD_W21_WriteDATA(0x2F);

  EPD_W21_WriteCMD(0x04);     //PWR on  
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}
  //fast
void EPD_init_fast(void)
{ 

  EPD_W21_Init(); //Electronic paper IC reset   
  
  EPD_W21_WriteCMD(0xAA);    // CMDH
  EPD_W21_WriteDATA(0x49);
  EPD_W21_WriteDATA(0x55);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x08);
  EPD_W21_WriteDATA(0x09);
  EPD_W21_WriteDATA(0x18);

  EPD_W21_WriteCMD(PWRR);
  EPD_W21_WriteDATA(0x3F);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x32);
  EPD_W21_WriteDATA(0x2A);
  EPD_W21_WriteDATA(0x0E);
  EPD_W21_WriteDATA(0x2A);
  
  EPD_W21_WriteCMD(PSR);  
  EPD_W21_WriteDATA(0x5F);
  EPD_W21_WriteDATA(0x69);
  
  EPD_W21_WriteCMD(POFS);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x44); 

  EPD_W21_WriteCMD(BTST1);
  EPD_W21_WriteDATA(0x40);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x2C);
  
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x16);
  EPD_W21_WriteDATA(0x25);

  EPD_W21_WriteCMD(BTST3);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x22);
 
  EPD_W21_WriteCMD(0x13);    // IPC
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x04);
  
  EPD_W21_WriteCMD(PLL);
  EPD_W21_WriteDATA(0x02);
  
  EPD_W21_WriteCMD(0x41);     // TSE
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(CDI);
  EPD_W21_WriteDATA(0x3F);
  
  EPD_W21_WriteCMD(TCON);
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(TRES);
  EPD_W21_WriteDATA(0x03);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x01); 
  EPD_W21_WriteDATA(0xE0);
  
  EPD_W21_WriteCMD(VDCS);
  EPD_W21_WriteDATA(0x1E); 

  EPD_W21_WriteCMD(T_VDCS);
  EPD_W21_WriteDATA(0x01);

  EPD_W21_WriteCMD(0x86);    // AGID
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(PWS);
  EPD_W21_WriteDATA(0x2F);
 
  EPD_W21_WriteCMD(0xE0);   // CCSET
  EPD_W21_WriteDATA(0x00); 
  
  EPD_W21_WriteCMD(0xE6);   // TSSET
  EPD_W21_WriteDATA(0x00);  

  EPD_W21_WriteCMD(0x04);     //PWR on  
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}

void EPD_sleep(void)
{
    EPD_W21_WriteCMD(0X02);   //power off
    EPD_W21_WriteDATA(0x00);
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
    /*EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);*/
}

void EPD_SetRAMValue_BaseMap(const unsigned char* datasBW,const unsigned char* datasRW)
{
  unsigned int i;	
	EPD_W21_WriteCMD(0x10);	       //Transfer old data
	for(i=0;i<EPD_ARRAY;i++)	  
	{	
		EPD_W21_WriteDATA(~datasBW[i]);  //Transfer the actual displayed data
	}	
	EPD_W21_WriteCMD(0x13);		     //Transfer new data
	for(i=0;i<EPD_ARRAY;i++)	     
	{
		EPD_W21_WriteDATA(datasRW[i]);  //Transfer the actual displayed data
	} 
  EPD_Update();		 
	 
}

void EPD_Init_Part(void)
{	
	EPD_W21_RST_0;  // Module reset   
	delay(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay(10); //At least 10ms delay 
	
	EPD_W21_WriteCMD(0X00);			//PANNEL SETTING
	EPD_W21_WriteDATA(0x1F);   //KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f
	
	EPD_W21_WriteCMD(0x04); //POWER ON
	delay(100);  
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
	
	EPD_W21_WriteCMD(0xE0);
	EPD_W21_WriteDATA(0x02);
	EPD_W21_WriteCMD(0xE5);
	EPD_W21_WriteDATA(0x6E);
	
	EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING
	EPD_W21_WriteDATA(0xA9); 	
	EPD_W21_WriteDATA(0x07);	
}

void EPD_Dis_Part_Time(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
												const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	EPD_Dis_Part_RAM(x_start,y_start,datas_A,datas_B,datas_C,datas_D,datas_E,num,PART_COLUMN,PART_LINE);
	EPD_Update();
	EPD_W21_WriteCMD(0X92);  	//This command makes the display exit partial mode and enter normal mode. 
 
}	

void EPD_Dis_Part_RAM(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
												const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i,j;  
	unsigned int x_end,y_end;

	x_end=x_start+PART_LINE*num-1; 
	y_end=y_start+PART_COLUMN-1;

	EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
	EPD_W21_WriteCMD(0x90);		//resolution setting
	EPD_W21_WriteDATA (x_start/256);
	EPD_W21_WriteDATA (x_start%256);   //x-start    

	EPD_W21_WriteDATA (x_end/256);		
	EPD_W21_WriteDATA (x_end%256-1);  //x-end	

	EPD_W21_WriteDATA (y_start/256);  //
	EPD_W21_WriteDATA (y_start%256);   //y-start    

	EPD_W21_WriteDATA (y_end/256);		
	EPD_W21_WriteDATA (y_end%256-1);  //y-end
	EPD_W21_WriteDATA (0x01);	

  if(partFlag==1)
	{
		partFlag=0;
		EPD_W21_WriteCMD(0x10);				 //writes New data to SRAM.
		for(i=0;i<PART_COLUMN;i++)	     
		 {
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(0xFF);  	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(0xFF);   
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(0xFF);   	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(0xFF);  
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(0xFF);   			 
		 }		
		EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
		for(i=0;i<PART_COLUMN;i++)	     
		 {
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_A[i*PART_LINE/8+j]);  	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_B[i*PART_LINE/8+j]);  
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_C[i*PART_LINE/8+j]);  	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_D[i*PART_LINE/8+j]); 	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_E[i*PART_LINE/8+j]); 			 
		 }		
	}
	else
	{
		EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
		for(i=0;i<PART_COLUMN;i++)	     
		 {
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_A[i*PART_LINE/8+j]);  	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_B[i*PART_LINE/8+j]);  
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_C[i*PART_LINE/8+j]);  	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_D[i*PART_LINE/8+j]); 	
				for(j=0;j<PART_LINE/8;j++)	     
					EPD_W21_WriteDATA(datas_E[i*PART_LINE/8+j]); 			 
		 }
  }	 
	 
	  
}

void EPD_DeepSleep(void)
{  	
		EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0xf7); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7	

		EPD_W21_WriteCMD(0X02);  	//power off
	  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
		delay(100);	  //!!!The delay here is necessary, 200uS at least!!!     	
	  EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}

unsigned char Color_get(unsigned char color)
{
  unsigned datas;
  switch(color)
  {
      case 0x00: // Black
            datas = 0x00; // 对应原始图像数据 0000
            break;
        case 0xff: // White
            datas = 0x01; // 对应原始图像数据 0001
            break;
        case 0xfc: // Yellow
            datas = 0x02; // 对应原始图像数据 0010
            break;
        case 0xE0: // Red
            datas = 0x03; // 对应原始图像数据 0011
            break;
        case 0x03: // Blue
            datas = 0x05; // 对应原始图像数据 0101
            break;
        case 0x1c: // Green
            datas = 0x06; // 对应原始图像数据 0110
            break;
        default:
            datas = 0x00; // 默认为黑色
            break;
    }
    return datas;
}

void PIC_display(const unsigned char* picData)
{
  unsigned int i,j,k;
  unsigned char temp1,temp2;
  unsigned char data_H,data_L,data;
  

   //Acep_color(White); //Each refresh must be cleaned first   
  EPD_W21_WriteCMD(0x10);        
  for(i=0;i<480;i++)
  { 
    k=0;
    for(j=0;j<800/2;j++)
    {
      
      temp1=picData[i*800+k++]; 
      temp2=picData[i*800+k++];
      data_H=Color_get(temp1)<<4;
      data_L=Color_get(temp2);
      data=data_H|data_L;
      EPD_W21_WriteDATA(data);
    }
  } 
  
   //Refresh
    EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
    EPD_W21_WriteDATA(0x00);
    delay(1);   //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

void EPD_Update(void)
{   
	//Refresh
	EPD_W21_WriteCMD(0x12);		//DISPLAY REFRESH 	
  EPD_W21_WriteDATA(0x00);
	delay(1);	             //!!!The delay here is necessary, 200uS at least!!!     
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}

void EPD_Dis_Part_temp(unsigned int x_start,unsigned int y_start,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	unsigned int i;  
	unsigned int x_end,y_end;

	x_end=x_start+PART_LINE-1; 
	y_end=y_start+PART_COLUMN-1;

	EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
	EPD_W21_WriteCMD(0x90);		//resolution setting
	EPD_W21_WriteDATA (x_start/256);
	EPD_W21_WriteDATA (x_start%256);   //x-start    

	EPD_W21_WriteDATA (x_end/256);		
	EPD_W21_WriteDATA (x_end%256-1);  //x-end	

	EPD_W21_WriteDATA (y_start/256);  //
	EPD_W21_WriteDATA (y_start%256);   //y-start    

	EPD_W21_WriteDATA (y_end/256);		
	EPD_W21_WriteDATA (y_end%256-1);  //y-end
	EPD_W21_WriteDATA (0x01);	

	EPD_W21_WriteCMD(0x10);				 //writes New data to SRAM.
	for(i=0;i<PART_COLUMN*PART_LINE/2;i++)	     
	 {
		 EPD_W21_WriteDATA(0x33);  
	 }	
  EPD_Update();	
	EPD_W21_WriteCMD(0X92);  	//This command makes the display exit partial mode and enter normal mode. 

}

void PIC_display_Clear(void)
{
   unsigned int i,j;
  //Acep_color(Clean); //Each refresh must be cleaned first 
  EPD_W21_WriteCMD(0x10);        
  for(i=0;i<480;i++)
  {
    for(j=0;j<800/2;j++)
    {
      EPD_W21_WriteDATA(White);
    }
  }
    //Refresh
  EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
  EPD_W21_WriteDATA(0x00);
  delay(1);              //!!!The delay here is necessary, 200uS at least!!!     
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

void EPD_Display_White(void)
{
  unsigned long i;
 

  
  EPD_W21_WriteCMD(DTM);
  {
    for(i=0;i<192000;i++)
    {
      EPD_W21_WriteDATA(0x11);
    }
  }
  EPD_W21_WriteCMD(PON);
  lcd_chkstatus();
  
  //20211212
  //Second setting
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x17);
  EPD_W21_WriteDATA(0x49);
    
  
  EPD_W21_WriteCMD(DRF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();
  
 
  EPD_W21_WriteCMD(POF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();

}


void EPD_Display_Black(void)
{
  unsigned long i;
 

  
  EPD_W21_WriteCMD(DTM);
  {
    for(i=0;i<192000;i++)
    {
      EPD_W21_WriteDATA(0x00);
    }
  }
  EPD_W21_WriteCMD(PON);
  lcd_chkstatus();
  
  //20211212
  //Second setting
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x17);
  EPD_W21_WriteDATA(0x49);
    
  
  EPD_W21_WriteCMD(DRF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();
  
 
  EPD_W21_WriteCMD(POF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();

}

void EPD_Display_red(void)
{
  unsigned long i;
 

  
  EPD_W21_WriteCMD(DTM);
  {
    for(i=0;i<192000;i++)
    {
      EPD_W21_WriteDATA(0x33);
    }
  }
  EPD_W21_WriteCMD(PON);
  lcd_chkstatus();
  
  //20211212
  //Second setting
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x17);
  EPD_W21_WriteDATA(0x49);
    
  
  EPD_W21_WriteCMD(DRF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();
  
 
  EPD_W21_WriteCMD(POF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();

}
void EPD_Display_Yellow(void)
{
  unsigned long i;
 

  
  EPD_W21_WriteCMD(DTM);
  {
    for(i=0;i<192000;i++)
    {
      EPD_W21_WriteDATA(0x22);
    }
  }
  EPD_W21_WriteCMD(PON);
  lcd_chkstatus();
  
  //20211212
  //Second setting
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x17);
  EPD_W21_WriteDATA(0x49);
    
  
  EPD_W21_WriteCMD(DRF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();
  
 
  EPD_W21_WriteCMD(POF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();

}

void EPD_Display_blue(void)
{
  unsigned long i;
 

  
  EPD_W21_WriteCMD(DTM);
  {
    for(i=0;i<192000;i++)
    {
      EPD_W21_WriteDATA(0x55);
    }
  }
  EPD_W21_WriteCMD(PON);
  lcd_chkstatus();
  
  //20211212
  //Second setting
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x17);
  EPD_W21_WriteDATA(0x49);
    
  
  EPD_W21_WriteCMD(DRF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();
  
 
  EPD_W21_WriteCMD(POF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();

}

void EPD_Display_Green(void)
{
  unsigned long i;
 

  
  EPD_W21_WriteCMD(DTM);
  {
    for(i=0;i<192000;i++)
    {
      EPD_W21_WriteDATA(0x66);
    }
  }
  EPD_W21_WriteCMD(PON);
  lcd_chkstatus();
  
  //20211212
  //Second setting
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x17);
  EPD_W21_WriteDATA(0x49);
    
  
  EPD_W21_WriteCMD(DRF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();
  
 
  EPD_W21_WriteCMD(POF);
  EPD_W21_WriteDATA(0x00);
  lcd_chkstatus();

}
