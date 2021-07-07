#ifndef CORE_H
#define CORE_H

const unsigned char START_DISPLAY_MEMORY=0;
const unsigned char START_PROGRAMM_MEMORY=0x10;

const unsigned char SPI_DATA_REGISTER=0x10;//SPDR
const unsigned char SPI_CONTROL_AND_STATUS_REGISTER=0x11;//SPCR

const unsigned char REG_PROGRAM_COUNTER = 0xF;//PC
const unsigned char REG_PC_STATUS       = 0xE;//PS
const unsigned char REG_PC_CONTROL      = 0xD;//RC
const unsigned char REG_KEYBORD_CHAR    = 0xC;//KC
const unsigned char REG_KEYBORD_VECTOR  = 0xB;//KV
const unsigned char REG_TIMER_DATA      = 0xA;//TD
const unsigned char REG_TIMER_VECTOR    = 0x9;//TV
const unsigned char REG_SPI_DATA        = 0x8;//SD
const unsigned char REG_SPI_VECTOR      = 0x7;//SV


/*
SPIE (SPI Interrupt Enable) – бит, который разрешает прерывания.

SPE (SPI Enable) – бит, включающий шину SPI.

SPIF (SPI Interrupt Flag) – Флаг прерывания.Установку данного бита в единицу мы ждём. когда принимаем байт. Как только байт от другого устройства появится полностью у нас в буфере, то данный флаг установится. Данный флаг работает только в случае установки бита, разрешающего прерывания

WCOL (Write COLlision Flag) – флаг конфликта, или коллизий, установится в том случае, если во время передачи данных будет конфликт битов, если во время передачи данных выполнится попытка записи в регистр данных.
*/

//PC_STATUS
const unsigned char PC_STATUS_ZERO_FLAG=0x01;// a == b
const unsigned char PC_STATUS_NEGATIVE_FLAG=0x02;// a < b
const unsigned char PC_STATUS_POSITIVE_FLAG=0x04;// a > b
const unsigned char PC_STATUS_CARRY_FLAG=0x08;
const unsigned char PC_STATUS_CARRY_TIMER_FLAG=0x10;
const unsigned char PC_STATUS_SPI_FLAG=0x20;
const unsigned char PC_STATUS_NODEFINE_COMMAND=0x40;
const unsigned char PC_STATUS_CRITICAL_ERROR=0x80;

//PC_CONTROL
const unsigned char PC_CONTROL_INTERRUPT_ENABLE         = 0x01;
const unsigned char PC_CONTROL_KEYBORD_INTERRUPT_ENABLE = 0x02;
const unsigned char PC_CONTROL_TIMER_INTERRUPT_ENABLE   = 0x04;
const unsigned char PC_CONTROL_SPI_INTERRUPT_ENABLE     = 0x08;
const unsigned char PC_CONTROL_SPI_ENABLE               = 0x10;
                                                        //0x20
const unsigned char PC_CONTROL_TIMER_TAKT               = 0x40;
const unsigned char PC_CONTROL_TIMER_MSEC               = 0x80;
const unsigned char PC_CONTROL_TIMER_SEC                = 0xC0;

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
bool runOneStep(unsigned char);
bool loadFile(char *);
#endif
