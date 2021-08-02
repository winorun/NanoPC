#include "spi.h"

unsigned char highByte=0xff;

bool interchangeBit(unsigned char &lowByte){
	static char i = 8; 
	int bufer=highByte*0x100+lowByte;
	bool lastBit = ( lowByte & 1);
	bufer = bufer >> 1;
	if(lastBit)bufer+=0x8000;// 0b1000_0000_0000_0000 = 0x8000
	lowByte = (unsigned char)(bufer & 0xff);
	highByte = (unsigned char)((bufer & 0xff00)>>8);
	i--;
	if(i == 0){
		i = 8;
		return true;
	}
	return false;
}