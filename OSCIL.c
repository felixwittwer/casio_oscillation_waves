/*****************************************************************/
/*                                                               */
/*   oscillation, pendulum, springs                              */
/*                                                               */
/*   File name : OSCIL.c                                         */
/*                                                               */
/*   Copyright (c) 2023 Felix Wittwer                            */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
    float graviatation = 9.81;

    Bdisp_AllClr_DDVRAM();

    PrintXY(5,5,(unsigned char*)"Oscillation",0);
    PrintMini(7,14,(unsigned char*)"by Felix Wittwer",MINI_OVER);
    PrintMini(50,57,(unsigned char*)"(c)2023",MINI_OVER);

    while(1){
        GetKey(&key);
        Bdisp_AllClr_DDVRAM();
        PrintMini(0,1,(unsigned char*)" General                     ",MINI_REV);
        PrintMini(2,9,(unsigned char*)" 1 frequency ",MINI_OVER);

        PrintMini(0,18,(unsigned char*)" Oscillation                  ",MINI_REV);
        PrintMini(2,26,(unsigned char*)" 2 string pendulum ",MINI_OVER);
        PrintMini(2,33,(unsigned char*)" 3 springs ",MINI_OVER);

        PrintMini(0,42,(unsigned char*)" Waves                       ",MINI_REV);
        PrintMini(2,50,(unsigned char*)" 4 wavelength ",MINI_OVER);
        PrintMini(2,57,(unsigned char*)" 5 speed of propagation ",MINI_OVER);
    }

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

