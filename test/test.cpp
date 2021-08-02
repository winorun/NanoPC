#define BOOST_TEST_MODULE main
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "core.h"

void cmd_mov(TwoOpt opt);
void cmd_add(TwoOpt opt);
void cmd_sub(TwoOpt opt);
void cmd_or(TwoOpt opt);
bool timer_tik();


// bool timer_tik(){
//     unsigned char timer_status = reg[REG_PC_CONTROL] & 0xC0;
//     if(timer_status == PC_CONTROL_TIMER_TAKT){
//         reg[REG_TIMER_DATA]++;
//         if(reg[REG_TIMER_DATA] == 0){
//             reg[REG_PC_STATUS] |= PC_STATUS_CARRY_TIMER_FLAG;
//             return true;
//         }else{
//             reg[REG_PC_STATUS] &= ~PC_STATUS_CARRY_TIMER_FLAG;
//             return false;
//         }
//     }
//     return false;
// }

BOOST_AUTO_TEST_CASE(timer_tik_test){
    reg[REG_TIMER_DATA] = 0;
    reg[REG_PC_CONTROL] = PC_CONTROL_TIMER_TAKT;
    bool interrupt = timer_tik();
    BOOST_TEST(!interrupt);
    BOOST_TEST(reg[REG_TIMER_DATA]==1);
} 

BOOST_AUTO_TEST_CASE(cmd_or_test) 
{
  unsigned char a=0,b=1;
  TwoOpt opt={&a,&b};
  cmd_or(opt);
  BOOST_TEST(a==b);
}


BOOST_AUTO_TEST_CASE(cmd_mov_test) 
{
  unsigned char a=1,b=3;
  TwoOpt opt={&a,&b};
  cmd_mov(opt);
  BOOST_TEST(a==b);
}

BOOST_AUTO_TEST_CASE(cmd_add_test) 
{
  unsigned char a=1,b=3;
  bool is_flag;
  TwoOpt opt={&a,&b};

  a=1;b=3;
  cmd_add(opt);
  BOOST_TEST(a==4);
  is_flag = reg[REG_PC_STATUS]&PC_STATUS_CARRY_FLAG;
  BOOST_TEST(!is_flag);

  a=240; b=100;
  cmd_add(opt);
  BOOST_TEST(a==0x54);
  is_flag = reg[REG_PC_STATUS]&PC_STATUS_CARRY_FLAG;
  BOOST_TEST(is_flag);

  a=1;b=3;
  cmd_add(opt);
  BOOST_TEST(a==4);
  is_flag = reg[REG_PC_STATUS]&PC_STATUS_CARRY_FLAG;
  BOOST_TEST(!is_flag);
}

BOOST_AUTO_TEST_CASE(cmd_sub_test) 
{
  unsigned char a=1,b=3;
  bool is_flag;
  TwoOpt opt={&a,&b};

  a=3;b=1;
  cmd_sub(opt);
  BOOST_TEST(a==2);
  is_flag = reg[REG_PC_STATUS]&PC_STATUS_CARRY_FLAG;
  BOOST_TEST(!is_flag);

  a=40; b=100;
  cmd_sub(opt);
  BOOST_TEST(a==0xC4);
  is_flag = reg[REG_PC_STATUS]&PC_STATUS_CARRY_FLAG;
  BOOST_TEST(is_flag);

  a=3;b=1;
  cmd_sub(opt);
  BOOST_TEST(a==2);
  is_flag = reg[REG_PC_STATUS]&PC_STATUS_CARRY_FLAG;
  BOOST_TEST(!is_flag);
}