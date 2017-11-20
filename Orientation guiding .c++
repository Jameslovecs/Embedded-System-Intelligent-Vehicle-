//Intelligent Vehicles project
//Orientation guiding part
//By Ranran Cao

#include "UltraSonic.h"
char RX_buf[17];
unsigned char TX_buf1[5] = {0x76, 0x00, 0xF0, 0x00, 0xF0};
unsigned char TX_buf2[5] = {0x76, 0x00, 0x0F, 0x00, 0x0F};
void setup()
{
	int i=0;
	Serial.begin(115200);
	Serial1.begin(115200);
}
void loop()
{
}
void serialEvent1()
{
	unsigned char z,tmp=0;
	Serial1.readBytes(RX_buf,17);
	if((RX_buf[0] == 0x76) && (RX_buf[1] == 0))
	{
		for(z=2;z<16;z++)
		tmp += (unsigned char)RX_buf[z];
		tmp = tmp & 0xFF;
		if((unsigned char)RX_buf[16] == tmp)
		{
			Serial.println("\n\r FRONT");
			for(z=4;z<11;z++)
			{
				Serial.print(" ");
				Serial.print(z-4);
				Serial.print(": ");
				Serial.print((unsigned char)RX_buf[z]);
			}
			Serial.println("\n\r BACK");
			for(z=11;z<16;z++)
			{
				Serial.print(" ");
				Serial.print(z-11);
				Serial.print(": ");
				Serial.print((unsigned char)RX_buf[z]);
			}
		}
	}
}
void serialEvent()
{
	int i;
	unsigned char da=Serial.read();
	if(da == 't')
	{
		Serial1.write(TX_buf1,5);
		Serial.print("\n\r START : ");
		for(i=0;i<5;i++)
		{
			Serial.print(" ");
			Serial.print(TX_buf1[i],HEX);
		}
	}
	else if(da == 's')
	{
		Serial1.write(TX_buf2,5);
		Serial.print("\n\r STOP : ");
		for(i=0;i<5;i++)
		{
			Serial.print(" ");
			Serial.print(TX_buf2[i],HEX);
		}
	}
}
