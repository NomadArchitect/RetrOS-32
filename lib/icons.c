#include <lib/icons.h>

unsigned char screen_32[32*32] = {
    0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xff,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xff,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x1f,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x1f,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x1f,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x00,0x00,0xfa,0xfa
    ,0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0x92,0x92,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0xdb,0xdb,0xdb,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0x92,0xff,0xff,0xff,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0x92,0xff,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0xdb,0x92,0x92,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa

};

unsigned char computer_icon[32*32] = {
    0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xff,0xff,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0xdb,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x92,0x92,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xdb,0xdb,0xdb,0xdb,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x02,0x02,0x92,0x92,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x02,0x02,0x92,0x92,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0xdb,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x03,0x02,0x02,0x92,0x92,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x1f,0x03,0x03,0x02,0x02,0x92,0x92,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x03,0x1f,0x03,0x1f,0x03,0x03,0x1f,0x03,0x02,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x1f,0xff,0x03,0x1f,0x03,0x03,0x03,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x03,0x1f,0x03,0xfc,0x1f,0x03,0x03,0x03,0x03,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x03,0x03,0x03,0x1f,0x03,0x03,0x03,0x03,0x03,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xff,0xdb,0x00,0x02,0x03,0x03,0x1f,0x03,0x1f,0x03,0x03,0x03,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xdb,0x92,0x92,0x92,0x02,0x02,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0x00,0xdb,0xdb,0xdb,0x92,0x92,0x02,0x02,0x03,0x03,0x03,0x03,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xdb,0xdb,0x00,0x00,0xdb,0xdb,0xdb,0x92,0x92,0x02,0x02,0x03,0x03,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xff,0xdb,0xdb,0x00,0x00,0xdb,0xdb,0xdb,0x92,0x92,0x02,0x02,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xdb,0xff,0xff,0xdb,0xdb,0x00,0x00,0xdb,0xdb,0xdb,0x92,0x92,0x02,0xdb,0x92,0x92,0x92,0x92,0x00,0x00,0x92,0x92,0x00,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xdb,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0x00,0x00,0xdb,0xdb,0xdb,0x92,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xdb,0x1c,0x1c,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0x00,0x00,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x00,0x92,0x92,0x92,0xdb,0xdb,0x00,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xdb,0x10,0x10,0xdb,0xdb,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0x00,0x00,0xdb,0x92,0x92,0x00,0x00,0x92,0x92,0xdb,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xff,0xff,0xdb,0xdb,0x00,0x00,0x00,0x92,0x92,0xdb,0xdb,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xff,0xff,0xdb,0x92,0x92,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xff,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0xdb,0x92,0x92,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
};

unsigned char terminal_16[16*16] = {
    0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb
    ,0xdb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x92,0x92,0x03,0x03,0x03,0xdb,0x03,0xdb,0x03,0xdb,0x03,0x03,0x03,0x92,0x92
    ,0xdb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0xff,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xdb,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92
    ,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
            
};

unsigned char menu_16[16*16] = {
    0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0x92,0xdb,0xfc,0xdb,0xdb,0x92,0x92,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0x92,0xdb,0xe0,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00
    ,0x92,0x92,0xdb,0xdb,0xdb,0x92,0x02,0x02,0x02,0x02,0x02,0xff,0x02,0xff,0x02,0x00
    ,0x92,0x92,0xdb,0x1f,0xdb,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00
    ,0x92,0x92,0xdb,0xdb,0xdb,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00
    ,0x92,0x92,0xdb,0x1c,0xdb,0x92,0xdb,0xff,0xff,0xe0,0xff,0xff,0xff,0xff,0xdb,0x00
    ,0x92,0x92,0xdb,0xdb,0xdb,0x92,0xdb,0xff,0xe0,0xe0,0xff,0x02,0x02,0xff,0xdb,0x00
    ,0x92,0x92,0xdb,0xdb,0xdb,0x92,0xdb,0xff,0xff,0x80,0xff,0xff,0x00,0xff,0xdb,0x00
    ,0x92,0x92,0xdb,0xdb,0xdb,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00
    ,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xff,0x92,0x92,0xff,0x92,0x92,0xff,0xdb,0x00
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char finder_16[16*16] = {
    0xfa,0xfa,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0x92,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x90,0x00,0xfa
    ,0x92,0xff,0xfc,0xdb,0x92,0x92,0xfa,0x92,0xfc,0xdb,0xfc,0xdb,0xfc,0x90,0x00,0xfa
    ,0x92,0xff,0xdb,0x92,0xff,0x1f,0xff,0xfa,0x92,0xfc,0xdb,0xfc,0xdb,0x90,0x00,0xfa
    ,0x92,0xff,0x92,0xff,0x1f,0xff,0x1f,0xdb,0xfa,0x92,0xfc,0xdb,0xfc,0x90,0x00,0xfa
    ,0x92,0xff,0x92,0x1f,0xff,0x1f,0xdb,0x1f,0xfa,0x90,0xdb,0xfc,0xdb,0x90,0x00,0xfa
    ,0x92,0xff,0x92,0xff,0x1f,0xdb,0x1f,0xdb,0xfa,0x90,0xfc,0xdb,0xfc,0x90,0x00,0xfa
    ,0x92,0xff,0xdb,0x92,0xdb,0x1f,0xdb,0xfa,0x92,0x90,0x90,0xfc,0xdb,0x90,0x00,0xfa
    ,0x92,0xff,0xfc,0xdb,0x92,0xfa,0xfa,0x92,0xdb,0x03,0x03,0x90,0xfc,0x90,0x00,0xfa
    ,0x92,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x02,0x1f,0x03,0x03,0x90,0x90,0x00,0xfa
    ,0xfa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x1f,0x03,0x03,0x00,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x02,0x1f,0x03,0x03,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x02,0x1f,0x03,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
};

unsigned char editor_16[16*16] = {
    0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0x00,0xff,0x92,0xff,0x92,0xff,0x92,0xff,0x92,0xff,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,0xfa,0xfa,0xfa,0x02
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00,0xfa,0x02,0x03
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00,0x02,0x03,0xff
    ,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0x02,0xff,0x03
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00,0x00,0x03,0x02
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xb4,0x00,0x00,0xfa,0x02
    ,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xb4,0xfc,0xb4,0x00,0xfa,0xfa
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xb4,0xfc,0xff,0xb4,0x92,0xfa,0xfa
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xb4,0xfc,0xff,0xb4,0x00,0xfa,0xfa,0xfa
    ,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xb4,0x00,0x00,0x00,0x00,0x00,0xfa,0xfa,0xfa
    ,0x92,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0xdb,0x00,0xfa,0xfa,0xfa
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00,0xfa,0xfa,0xfa
    ,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xfa,0xfa,0xfa
    ,0xfa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa,0xfa,0xfa,0xfa
};

unsigned char bin_16[16*16] = {
    0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92
    ,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0xfa
    ,0x92,0xdb,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x92,0xfa
    ,0x92,0xdb,0x02,0x02,0x02,0x02,0x02,0x02,0xff,0x00,0xff,0x00,0xff,0x00,0x92,0xfa
    ,0x92,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa
    ,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xfa
    ,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xfa
    ,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xfa
    ,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xfa
    ,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xfa
    ,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xfa
    ,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xfa
    ,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
};

unsigned char wlanerr_16[16*16] = {
0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x00,0x00,0x00,0x00,0x02,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x00,0x1f,0x03,0x03,0x02,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x00,0x03,0x03,0x03,0x02,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x02,0x02,0x02,0x02,0x02,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa
,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xfa
,0x92,0x00,0x00,0x00,0x00,0x00,0x92,0xff,0x00,0x00,0x00,0x00,0x00,0xdb,0x00,0xfa
,0x92,0xff,0xff,0xff,0xff,0xff,0x92,0xff,0x00,0x1f,0xe0,0xe0,0xe0,0xe0,0x00,0xfa
,0x92,0xdb,0x1c,0x92,0x92,0x92,0x92,0xff,0x00,0xe0,0xe0,0xff,0xff,0xe0,0xe0,0xfa
,0xfa,0xfa,0x00,0xfa,0xfa,0xfa,0x92,0xff,0xe0,0xe0,0xe0,0xff,0xff,0xe0,0xe0,0xe0
,0xfa,0xfa,0x92,0x00,0xfa,0xfa,0x92,0xdb,0xe0,0xe0,0xe0,0xff,0xff,0xe0,0xe0,0xe0
,0xfa,0xfa,0x92,0x00,0xfa,0xfa,0x92,0x00,0xe0,0xe0,0xe0,0xff,0xff,0xe0,0xe0,0xe0
,0x92,0x92,0xfc,0x90,0x00,0x92,0x92,0xff,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0
,0xfa,0xfa,0xfc,0x90,0x00,0xfa,0x92,0xdb,0x1c,0xe0,0xe0,0xff,0xff,0xe0,0xe0,0x00
,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xe0,0xe0,0xe0,0xe0,0x00,0xfa
};

unsigned char wlan_16[16*16] = {
0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x00,0x00,0x00,0x00,0x02,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x00,0x1f,0x03,0x03,0x02,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x00,0x03,0x03,0x03,0x02,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
,0x92,0xff,0x02,0x02,0x02,0x02,0x02,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa
,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xfa
,0x92,0x00,0x00,0x00,0x00,0x00,0x92,0xff,0x00,0x00,0x00,0x00,0x00,0xdb,0x00,0xfa
,0x92,0xff,0xff,0xff,0xff,0xff,0x92,0xff,0x00,0x1f,0x12,0x12,0x92,0xdb,0x00,0xfa
,0x92,0xdb,0x1c,0x92,0x92,0x92,0x92,0xff,0x00,0x12,0x12,0x12,0x92,0xdb,0x00,0xfa
,0xfa,0xfa,0x00,0xfa,0xfa,0xfa,0x92,0xff,0x00,0x92,0x92,0x92,0x92,0xdb,0x00,0xfa
,0xfa,0xfa,0x92,0x00,0xfa,0xfa,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xfa
,0xfa,0xfa,0x92,0x00,0xfa,0xfa,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xfa
,0x92,0x92,0xfc,0x90,0x00,0x92,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x00
,0xfa,0xfa,0xfc,0x90,0xfa,0xfa,0x92,0xdb,0x1c,0x92,0x92,0x92,0x92,0x92,0x92,0x00
,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
};

unsigned char clock_16[16*16] = {
    0xfa,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xfa
    ,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0x00,0xdb,0x00,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0x00,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0x00,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0x00,0xdb,0xdb,0xdb,0x00,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0x00,0x00,0x00,0x00,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0x00,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xe0,0x00
    ,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0x00
    ,0xfa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfa
};

unsigned char calc_16[16*16] = {
    0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0xfa
    ,0x12,0xff,0x1f,0xff,0x1f,0xff,0x1f,0xff,0x1f,0xff,0x1f,0xff,0x1f,0xff,0x12,0xfa
    ,0x12,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x12,0x12,0x12,0x02,0xfa
    ,0x12,0xff,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x12,0x12,0x12,0x12,0x02,0xfa
    ,0x12,0x1f,0x00,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x12,0x12,0x12,0x12,0x02,0xfa
    ,0x12,0xff,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x02,0xfa
    ,0x12,0x1f,0x12,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0x02,0xfa
    ,0x12,0xff,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x02,0xfa
    ,0x12,0x1f,0x12,0x00,0xff,0x00,0xff,0x00,0xff,0x00,0xff,0xff,0xdb,0x00,0x02,0xfa
    ,0x12,0xff,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x02,0xfa
    ,0x12,0x12,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
};

unsigned char desktop_16[16*16] = {
    0xfa,0xfa,0xfa,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0x92,0x92,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0x92,0xdb,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xdb,0x92,0x92,0xfa,0xfa,0xfa
    ,0x92,0xdb,0x92,0x92,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xdb,0x92,0x92,0x00
    ,0x92,0xdb,0x00,0x02,0x92,0x92,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0x92,0xdb,0x92,0x00
    ,0x92,0xdb,0x00,0x03,0x02,0x02,0x92,0x92,0xff,0xff,0xdb,0x92,0x00,0x92,0x92,0x00
    ,0x92,0xdb,0x00,0x03,0x1f,0x03,0x03,0x02,0xdb,0xdb,0x92,0x92,0x00,0x92,0x92,0x00
    ,0x92,0xdb,0x00,0x03,0x1f,0x03,0x03,0x02,0xdb,0xdb,0x92,0x92,0x00,0x92,0x92,0x00
    ,0x92,0xdb,0x00,0x1f,0x03,0x1f,0x1f,0x02,0xdb,0xdb,0x92,0x92,0x00,0x92,0x92,0x00
    ,0x92,0xdb,0x00,0x03,0x1f,0x03,0x03,0x02,0xdb,0xdb,0x92,0x92,0x00,0x92,0x92,0x00
    ,0x92,0xdb,0xdb,0x02,0x02,0x03,0x03,0x02,0xdb,0xdb,0x92,0x92,0x00,0x92,0xfa,0xfa
    ,0x00,0x92,0x92,0xdb,0xdb,0x02,0x02,0x02,0xdb,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa
    ,0xfa,0x00,0x00,0x92,0x92,0xdb,0xdb,0x02,0xdb,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x00,0x00,0x92,0x92,0xdb,0xdb,0xdb,0x92,0x92,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0x00,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
};

unsigned char wlan_32[32*32] = {
    0xfa,0xfa,0xfa,0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x00,0x03,0x1f,0x03,0x03,0x03,0x03,0x03,0x02,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x00,0x03,0x1f,0x03,0x03,0x03,0x03,0x03,0x02,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0x92,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xff,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xff,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xff,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0xff,0x92,0x00,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0x92,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0xff,0x92,0x00,0x12,0x1f,0x12,0x12,0x12,0x12,0x12,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0x92,0xff,0xdb,0x1c,0x1c,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0x00,0x92,0xff,0x92,0x00,0x12,0x1f,0x12,0x12,0x12,0x12,0x12,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0x92,0xff,0xdb,0x10,0x10,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0xff,0x92,0x00,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xff,0x92,0x00,0x12,0x12,0x12,0x12,0x12,0x12,0x12,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xff,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92,0x92,0x00,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x00,0x92,0x92,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0x92,0xdb,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0xdb,0x00,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xdb,0x92,0xfa
    ,0x92,0xfa,0x92,0x92,0x90,0x90,0x90,0x90,0x00,0x92,0x92,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0xfa
    ,0xdb,0xfa,0xdb,0xdb,0x90,0xff,0xfc,0x90,0x00,0xdb,0xdb,0x92,0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0xdb,0x92,0x92,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0x90,0xff,0xfc,0x90,0x00,0xfa,0xfa,0x92,0xff,0xdb,0x1c,0x1c,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0x00,0x00,0x00,0x00,0x00,0xdb,0x92,0x92,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x00,0xfa,0xfa,0x92,0xff,0xdb,0x10,0x10,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
    ,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa,0xfa
};