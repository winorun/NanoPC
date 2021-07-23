#include <cstdio>
#include "core.h"

unsigned char memory[256]={'h','e','l','l','o',' ','w','o','r','l','d',0,0,0,0,0,0,1};
unsigned char reg[0x20]={};

unsigned char * const getOptDefauld(unsigned char * const opt, unsigned char optParam){
const unsigned char OPT_PARAM_VALUE=0b00;
const unsigned char OPT_PARAM_REG=0b01;
const unsigned char OPT_PARAM_LINK_REG=0b10;
const unsigned char OPT_PARAM_LINK_LINK_REG=0b11;

unsigned char * out;
unsigned char r=*opt%0x10;
    switch(optParam%0b100){
        case OPT_PARAM_VALUE:out=opt;break;
        case OPT_PARAM_LINK_LINK_REG :out=&memory[memory[reg[r]]]; break;
        case OPT_PARAM_REG:out=&reg[r]; break;
        case OPT_PARAM_LINK_REG :out=&memory[reg[r]]; break;
    }
    return out;
}

TwoOpt getTwoOpt(const unsigned char &i){
    const unsigned char cmdb = memory[i]%0x10;
    unsigned char opt1_mod=cmdb%0b100;
    unsigned char opt2_mod=cmdb/0b100;

    unsigned char * const opt1 = getOptDefauld(&memory[i+1],opt1_mod);
    unsigned char * const opt2 = getOptDefauld(&memory[i+2],opt2_mod);
    
    return {opt1,opt2};
}

OneOpt getOneOpt(const unsigned char i){
    const unsigned char cmdb = memory[i]%0x10;
    unsigned char cmp = cmdb/0b100; 

    unsigned char opt_mod=cmdb%0b100;
    unsigned char * const opt = getOptDefauld(&memory[i+1],opt_mod);
    return {opt,cmp};
}

void nextCmd(){
    reg[REG_PROGRAM_COUNTER]+=3;
}

void cmd_jne(TwoOpt opt){
    unsigned char a = *opt.opt1&reg[REG_PC_STATUS];
    if(a != *opt.opt1)
        reg[REG_PROGRAM_COUNTER]=*opt.opt2;
    else
        reg[REG_PROGRAM_COUNTER]+=3;
}

void cmd_joe(TwoOpt opt){
    unsigned char a = *opt.opt1&reg[REG_PC_STATUS];
    if(a&*opt.opt1)
        reg[REG_PROGRAM_COUNTER]=*opt.opt2;
    else
        reg[REG_PROGRAM_COUNTER]+=3;
}


void cmd_je(TwoOpt opt){
    unsigned char a = *opt.opt1&reg[REG_PC_STATUS];
    if(a == *opt.opt1)
        reg[REG_PROGRAM_COUNTER]=*opt.opt2;
    else
        reg[REG_PROGRAM_COUNTER]+=3;
}

void cmd_cmp(TwoOpt opt){
    unsigned char * const status = &reg[REG_PC_STATUS];
    if(*opt.opt1 == *opt.opt2){
        *status |= PC_STATUS_ZERO_FLAG;
    }else{
        *status &= ~PC_STATUS_ZERO_FLAG;
    }

    if(*opt.opt1 < *opt.opt2){
        *status |= PC_STATUS_NEGATIVE_FLAG;
    }else{
        *status &= ~PC_STATUS_NEGATIVE_FLAG;
    }

    if(*opt.opt1 > *opt.opt2){
        *status |= PC_STATUS_POSITIVE_FLAG;
    }else{
        *status &= ~PC_STATUS_POSITIVE_FLAG;
    }
}
void cmd_sub(TwoOpt opt){
    if(*opt.opt1<*opt.opt2){
        reg[REG_PC_STATUS] |= PC_STATUS_CARRY_FLAG;
    }else{
        //!@todo reg[REG_PC_STATUS] - установить флаг в ноль 
        reg[REG_PC_STATUS] &= ~PC_STATUS_CARRY_FLAG;
    }
    *opt.opt1-=*opt.opt2;    
}

void cmd_add(TwoOpt opt){
    *opt.opt1+=*opt.opt2;
    if(*opt.opt1<*opt.opt2){
        reg[REG_PC_STATUS] |= PC_STATUS_CARRY_FLAG;
    }else{
        //!@todo reg[REG_PC_STATUS] - установить флаг в ноль 
        reg[REG_PC_STATUS] &= ~PC_STATUS_CARRY_FLAG;
    }
}

void cmd_rol(TwoOpt opt){
    *opt.opt1 = *opt.opt1 << *opt.opt2;
}

void cmd_ror(TwoOpt opt){
    *opt.opt1 = *opt.opt1 >> *opt.opt2;
}

void cmd_xor(TwoOpt opt){
    *opt.opt1^=*opt.opt2;
}

void cmd_and(TwoOpt opt){
    *opt.opt1&=*opt.opt2;
}

void cmd_or(TwoOpt opt){
    *opt.opt1|=*opt.opt2;
}

void cmd_pull(TwoOpt opt){
    *opt.opt2=memory[*opt.opt1];
    *opt.opt1-=1;
}

void cmd_push(TwoOpt opt){
    *opt.opt1+=1;
    memory[*opt.opt1]=*opt.opt2;
}

void cmd_jsr(TwoOpt opt){
    *opt.opt1+=1;
    memory[*opt.opt1]=reg[REG_PROGRAM_COUNTER]+3;
    reg[REG_PROGRAM_COUNTER]=*opt.opt2;
}

void cmd_mov(TwoOpt opt){
    *opt.opt1=*opt.opt2;
}

void other_cmd(unsigned char cmd){
    unsigned char a = cmd & 0b00001100;  
    unsigned char b = cmd & 0b00000011;
    if(cmd == 0){
        reg[REG_PROGRAM_COUNTER]++;
        return;
    }
    if(a == 0b00001000){//jmp
        unsigned char * const opt = getOptDefauld(&memory[reg[REG_PROGRAM_COUNTER]+1],b);
        reg[REG_PROGRAM_COUNTER]=*opt;
        return;
    }   
    reg[REG_PC_STATUS] |= PC_STATUS_NODEFINE_COMMAND | PC_STATUS_CRITICAL_ERROR;
}

void interruptRun(unsigned char vector){
    if(reg[REG_PC_STATUS] & PC_CONTROL_INTERRUPT_ENABLE ){
    }
}

bool delay(){
    return true;
}

bool runOneStep(unsigned char ch){
    if(!ch)return false;

    if(ch > 32 ){
        reg[REG_KEYBORD_CHAR] = ch;
        if(reg[REG_PC_STATUS] & PC_CONTROL_KEYBORD_INTERRUPT_ENABLE )
            interruptRun(reg[REG_KEYBORD_VECTOR]);
    }


    unsigned char &ncmd = reg[REG_PROGRAM_COUNTER];
    if(memory[ncmd]==0x01)return false;
    if(memory[ncmd]==0x02)return true;
    unsigned char cmdl=memory[ncmd]/0x10;

    switch(cmdl){
        case 0x0: other_cmd(memory[ncmd]); break;
        case 0x1: cmd_mov(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        case 0x2: cmd_add(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        case 0x3: cmd_sub(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        case 0x4: cmd_cmp(getTwoOpt(ncmd)); 
                  nextCmd(); break;

        case 0x5: cmd_je(getTwoOpt(ncmd));break;
        case 0x6: cmd_jne(getTwoOpt(ncmd));break;
        case 0x7: cmd_joe(getTwoOpt(ncmd));break;

        case 0x8: cmd_and(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        case 0x9: cmd_xor(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        case 0xA: cmd_or(getTwoOpt(ncmd)); 
                  nextCmd(); break;

        case 0xB: cmd_rol(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        case 0xC: cmd_ror(getTwoOpt(ncmd)); 
                  nextCmd(); break;

        case 0xD: cmd_jsr(getTwoOpt(ncmd));break;
        case 0xE: cmd_pull(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        case 0xF: cmd_push(getTwoOpt(ncmd)); 
                  nextCmd(); break;
        default: reg[REG_PC_STATUS] |= PC_STATUS_NODEFINE_COMMAND | PC_STATUS_CRITICAL_ERROR;
    }
    if(reg[REG_PC_STATUS] & PC_STATUS_CRITICAL_ERROR) return false;
    return delay();
}

