#ifndef CORE_H
#define CORE_H

const unsigned char START_DISPLAY_MEMORY=0;
const unsigned char START_PROGRAMM_MEMORY=0x10;

const unsigned char SPI_DATA_REGISTER=0x10;//SPDR
const unsigned char SPI_CONTROL_AND_STATUS_REGISTER=0x11;//SPCR

const unsigned char REG_PROGRAM_COUNTER=0xF;//PC
const unsigned char REG_PC_STATUS=0xE;//PS


/*
SPIE (SPI Interrupt Enable) – бит, который разрешает прерывания.

SPE (SPI Enable) – бит, включающий шину SPI.

SPIF (SPI Interrupt Flag) – Флаг прерывания.Установку данного бита в единицу мы ждём. когда принимаем байт. Как только байт от другого устройства появится полностью у нас в буфере, то данный флаг установится. Данный флаг работает только в случае установки бита, разрешающего прерывания

WCOL (Write COLlision Flag) – флаг конфликта, или коллизий, установится в том случае, если во время передачи данных будет конфликт битов, если во время передачи данных выполнится попытка записи в регистр данных.
*/


/*
const int REG_PC_ERROR_PARAM=0x9;
const int REG_PC_STATUS=0xA;//PS
const int REG_NEXT_COMMAND=0xB;//PC - Program Counter
const int REG_KEYBOARD_CHAR=0xC;
const int REG_KEYBOARD_VECTOR=0xD;
const int REG_HDD_CHAR=0xE;
const int REG_STACK_HEAD_MEMORY=0xF;//SP
*/

//PC_STATUS
const unsigned char PC_STATUS_ZERO_FLAG=0x01;// a == b
const unsigned char PC_STATUS_NEGATIVE_FLAG=0x02;// a < b
const unsigned char PC_STATUS_POSITIVE_FLAG=0x04;// a > b
//const unsigned char PC_STATUS_NOT_ZERO_FLAG=0x08;
const unsigned char PC_STATUS_CARRY_FLAG=0x10;
const unsigned char PC_STATUS_KEYBOARD_ENABLE=0x20;
const unsigned char PC_STATUS_NODEFINE_COMMAND=0x40;
const unsigned char PC_STATUS_CRITICAL_ERROR=0x80;

//PC_PARAM
const unsigned char PC_STATUS_2_ERROR_READ_FILE=0x01;
const unsigned char PC_STATUS_2_NODEFINE_COMMAND=0x02;
//const unsigned char PC_STATUS_ERROR_MAX_VALUE=0x01;

extern unsigned char memory[256];
extern unsigned char reg[0x20];

struct TwoOpt{
    unsigned char * opt1;
    unsigned char * opt2;
}; 

struct OneOpt{
    unsigned char * opt;
    unsigned char cmd;
}; 

void loadProgramm(unsigned char *programm,unsigned char start=START_PROGRAMM_MEMORY,unsigned char size=240);
bool runOneStep();
bool loadFile(char *);
#endif
