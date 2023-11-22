#include "constvalue.h"


bool GlobalKeyValue::keyPressed =false;

  bool GlobalKeyValue::key_a=false;
  bool GlobalKeyValue::key_b=false;
  bool GlobalKeyValue::key_c=false;
  bool GlobalKeyValue::key_d=false;
  bool GlobalKeyValue::key_e=false;
  bool GlobalKeyValue::key_f=false;
  bool GlobalKeyValue::key_g=false;
  bool GlobalKeyValue::key_h=false;
  bool GlobalKeyValue::key_i=false;
  bool GlobalKeyValue::key_j=false;
  bool GlobalKeyValue::key_k=false;
  bool GlobalKeyValue::key_l=false;
  bool GlobalKeyValue::key_m=false;
  bool GlobalKeyValue::key_n=false;
  bool GlobalKeyValue::key_o=false;
  bool GlobalKeyValue::key_p=false;
  bool GlobalKeyValue::key_q=false;
  bool GlobalKeyValue::key_r=false;
  bool GlobalKeyValue::key_s=false;
  bool GlobalKeyValue::key_t=false;
  bool GlobalKeyValue::key_u=false;
  bool GlobalKeyValue::key_v=false;
  bool GlobalKeyValue::key_w=false;
  bool GlobalKeyValue::key_x=false;
  bool GlobalKeyValue::key_y=false;
  bool GlobalKeyValue::key_z=false;
  bool GlobalKeyValue::key_1=false;
  bool GlobalKeyValue::key_2=false;
  bool GlobalKeyValue::key_3=false;
  bool GlobalKeyValue::key_4=false;
  bool GlobalKeyValue::key_5=false;
  bool GlobalKeyValue::key_6=false;
  bool GlobalKeyValue::key_7=false;
  bool GlobalKeyValue::key_8=false;
  bool GlobalKeyValue::key_9=false;
  bool GlobalKeyValue::key_0=false;

bool GlobalKeyValue::key_up     =false;
bool GlobalKeyValue::key_down   =false;
bool GlobalKeyValue::key_left   =false;
bool GlobalKeyValue::key_right  =false;


QMap<QString,bool*> GlobalKeyValue::keyPressedDictionary{
    {"a",&key_a},
    {"b",&key_b},
    {"c",&key_c},
    {"d",&key_d},
    {"e",&key_e},
    {"f",&key_f},
    {"g",&key_g},
    {"h",&key_h},
    {"i",&key_i},
    {"j",&key_j},
    {"k",&key_k},
    {"l",&key_l},
    {"m",&key_m},
    {"n",&key_n},
    {"o",&key_o},
    {"p",&key_p},
    {"q",&key_q},
    {"r",&key_r},
    {"s",&key_s},
    {"t",&key_t},
    {"u",&key_u},
    {"v",&key_v},
    {"w",&key_w},
    {"x",&key_x},
    {"y",&key_y},
    {"z",&key_z},
    {"1",&key_1},
    {"2",&key_2},
    {"3",&key_3},
    {"4",&key_4},
    {"5",&key_5},
    {"6",&key_6},
    {"7",&key_7},
    {"8",&key_8},
    {"9",&key_9},
    {"0",&key_0},
    {"up",&key_up},{"down",&key_down},{"left",&key_left},{"right",&key_right}
};
QMap<int,bool*>GlobalKeyValue::keyDictionaryByChar{
    {0 ,&key_a},
    {1 ,&key_b},
    {2 ,&key_c},
    {3 ,&key_d},
    {4 ,&key_e},
    {5 ,&key_f},
    {6 ,&key_g},
    {7 ,&key_h},
    {8 ,&key_i},
    {9 ,&key_j},
    {10,&key_k},
    {11,&key_l},
    {12,&key_m},
    {13,&key_n},
    {14,&key_o},
    {15,&key_p},
    {16,&key_q},
    {17,&key_r},
    {18,&key_s},
    {19,&key_t},
    {20,&key_u},
    {21,&key_v},
    {22,&key_w},
    {23,&key_x},
    {24,&key_y},
    {25 ,&key_z}
};
 QMap<int,bool*>GlobalKeyValue::keyDictionaryByNum
{
    {1,&key_1},
    {2,&key_2},
    {3,&key_3},
    {4,&key_4},
    {5,&key_5},
    {6,&key_6},
    {7,&key_7},
    {8,&key_8},
    {9,&key_9},
    {0,&key_0}
};
