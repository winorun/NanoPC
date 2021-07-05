#include <stdio.h>
#include <unistd.h>
#include <string>

#include "core.h"
#include "ui.h"

void printReg(){
    puts(
"╔════╤═════════════════════════╤═════════════════════════╗\n║    │ 00 01 02 03 04 05 06 07 │ 08 EP PS PC KC KV HD SP ║\n╠════╪═════════════════════════╪═════════════════════════╣" );
        printf("║REG │ ");
        for(int i=0;i<=0xf;i++){
            if(i==8)printf("│ ");
            printf("%02X ",reg[i]);
        }
        puts("║\n╚════╧═════════════════════════╧═════════════════════════╝" ); 
}

void printMemory(){
    puts(
"╔════╤═════════════════════════╤═════════════════════════╗\n║    │ 00 01 02 03 04 05 06 07 │ 08 09 0A 0B 0C 0D 0E 0F ║\n╠════╪═════════════════════════╪═════════════════════════╣" );
    for(int i=0;i<=0xf;i++){
        printf("║ %X0 │ ",i);
        for (int y = 0; y <= 0xf; y++){
            int b = i*0x10+y;
            if(y==8)printf("│ ");
            if(b==reg[REG_PROGRAM_COUNTER]){
                printf("%02X<",memory[b]);
            }else
                printf("%02X ",memory[b]);
            //printf("%02X ",i*0x10+y);
        }
        puts("║");
    }
    puts("╚════╧═════════════════════════╧═════════════════════════╝" ); 
}

void printDisplay(){
    //char *display = &memory[0xf6];
    puts("Display:\n  0123456789ABCDF\n╔═════════════════╗" );
    printf(       "║ ");
    for (int i = 0; i < 16; ++i) {
        if((memory[i]>32)&&(memory[i]<127)){
            char a=memory[i];
            putchar(a);
        }else
            putchar(' ');
    }
    puts("║\n╚═════════════════╝"); 
}

void printGraphicDisplay(){
    //char *display = &memory[0xf6];
    std::string str;
    str="╔════════╗\n";
    for (int i = 0; i < 10; ++i) {
        str+="║";
        std::string spaceChar="□";
        std::string trueChar="■";
        str+=(memory[i]&0b00000001)?trueChar:spaceChar;
        str+=(memory[i]&0b00000010)?trueChar:spaceChar;
        str+=(memory[i]&0b00000100)?trueChar:spaceChar;
        str+=(memory[i]&0b00001000)?trueChar:spaceChar;
        str+=(memory[i]&0b00010000)?trueChar:spaceChar;
        str+=(memory[i]&0b00100000)?trueChar:spaceChar;
        str+=(memory[i]&0b01000000)?trueChar:spaceChar;
        str+=(memory[i]&0b10000000)?trueChar:spaceChar;
        str+=("║\n");
    }
    str+="╚════════╝";
   printf("%s\n",str.c_str()); 
}

void gotoHomeConsole(){
    printf("\033[1;1H");
}

void clearConsole(){
    printf("\033[2J\033[1;1H");
}

void debug(){
    getchar();
}

void drawConWindow(int flag){
    gotoHomeConsole();
    printReg();
    printMemory();
    printDisplay();
    printGraphicDisplay(); 
};
