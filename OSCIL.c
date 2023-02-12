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
#include <stdio.h>

int PrintSelection(int selected, int compareto){
    if(selected==compareto){
        return MINI_REV;
    }else{
        return MINI_OVER;
    }
}

void PrintMainMenu(int selected){
    PrintMini(0,1,(unsigned char*)" General                     ",MINI_REV);
    PrintMini(2,9,(unsigned char*)" 1 frequency ",PrintSelection(selected,1));

    PrintMini(0,18,(unsigned char*)" Oscillation                  ",MINI_REV);
    PrintMini(2,26,(unsigned char*)" 2 string pendulum ",PrintSelection(selected,2));
    PrintMini(2,33,(unsigned char*)" 3 springs ",PrintSelection(selected,3));

    PrintMini(0,42,(unsigned char*)" Waves                       ",MINI_REV);
    PrintMini(2,50,(unsigned char*)" 4 wavelength ",PrintSelection(selected,4));
    PrintMini(2,57,(unsigned char*)" 5 speed of propagation ",PrintSelection(selected,5));

}

void RenderFrequency(int inputfield){
    unsigned char f[3]={0xE6,0x01,0};
    //display title
    PrintMini(1,1,(unsigned char*)" frequency                      ",MINI_REV);
    //display formula
    PrintXY(85,15,(unsigned char*)"f =",0);
    PrintXY(110,10,(unsigned char*)"n",0);
    PrintXY(110,20,(unsigned char*)"t",0);
    Bdisp_DrawLineVRAM(108,18,118,18);
    //dispaly symbols of formula
    PrintXY(5,15,(unsigned char*)"n=",0);
    PrintXY(5,26,(unsigned char*)"t=",0);
    PrintXY(5,37,(unsigned char*)"f=",0);

    if(inputfield==1){
        PrintXY(5,15,(unsigned char*)"n=",1);
    }else if(inputfield==2){
        PrintXY(5,26,(unsigned char*)"t=",1);
    }else if(inputfield==3){
        PrintXY(5,37,(unsigned char*)"f=",1);
    }
}

void RenderWavelength(){
    unsigned char lambda[3]={0xE6,0x4A,0};
    //display title
    PrintMini(1,1,(unsigned char*)" wave length                    ",MINI_REV);
    //display formula
    PrintXY(85,15,(unsigned char*)"  =",0);
    PrintXY(85,15, lambda,0);
    PrintXY(110,10,(unsigned char*)"v",0);
    PrintXY(110,20,(unsigned char*)"f",0);
    Bdisp_DrawLineVRAM(108,18,118,18);
    //dispaly symbols of formula
    PrintXY(5,15,(unsigned char*)"v=",0);
    PrintXY(5,26,(unsigned char*)"f=",0);
    PrintXY(5,37,(unsigned char*)" =",0);
    PrintXY(5,37,lambda,0);

}

int Inputfield(int key,int inputfield, int max){
    if(key==KEY_CTRL_UP){
        inputfield = inputfield - 1;
    }else if(key==KEY_CTRL_DOWN){
        inputfield = inputfield + 1;
    }

    if(inputfield<1){
        inputfield = max;
    }else if(inputfield>max){
        inputfield = 1;
    }

    return inputfield;
}

void RenderField(int x, int y,char characters[]){
    int iteration = 0;
    unsigned char buffer[12];

    while(iteration<9){
        sprintf(buffer, "%c", characters[iteration]);
        PrintXY(x+(iteration*6),y,buffer,0);
        iteration = iteration + 1;
    }
}

void Input(int x, int y,char characters[]){
    unsigned int key;
    int pointer = 0;
    while(1){
        GetKey(&key);
        if(key==KEY_CTRL_EXE){
            break;
        }else if(key==KEY_CTRL_DEL){
            characters[pointer-1] = ' ';
            pointer = pointer - 1;
        }else if(key==KEY_CHAR_0||key==KEY_CHAR_1||key==KEY_CHAR_2||key==KEY_CHAR_3||key==KEY_CHAR_4||key==KEY_CHAR_5||key==KEY_CHAR_6||key==KEY_CHAR_7||key==KEY_CHAR_8||key==KEY_CHAR_9||key==KEY_CHAR_DP){
            characters[pointer] = key;
            pointer = pointer + 1;
        }

        RenderField(x, y, characters);
    }
}


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
    int selected;
    int pointer = 0;
    int inputfield = 1;
    char n[9] = "";
    char t[9] = "";
    char f[9] = "";
    char v[9] = "";

    Bdisp_AllClr_DDVRAM();

    PrintXY(5,5,(unsigned char*)"Oscillation",0);
    PrintMini(7,14,(unsigned char*)"by Felix Wittwer",MINI_OVER);
    PrintMini(50,57,(unsigned char*)"(c)2023",MINI_OVER);
    selected = 1;

    while(1){
        GetKey(&key);
        Bdisp_AllClr_DDVRAM();

        if(key==KEY_CHAR_1){
            selected = 1;
        }else if(key==KEY_CHAR_2){
            selected = 2;
        }else if(key==KEY_CHAR_3){
            selected = 3;
        }else if(key==KEY_CHAR_4){
            selected = 4;
        }else if(key==KEY_CHAR_5){
            selected = 5;
        }else if(key==KEY_CTRL_UP){
            selected = selected - 1;
        }else if(key==KEY_CTRL_DOWN){
            selected = selected + 1;
        }else{
            selected = selected;
        }

        if(selected>5){
            selected = 1;
        }else if(selected<1){
            selected = 5;
        }

        PrintMainMenu(selected);

        if(key==KEY_CTRL_EXE){
            //frequency menu
            if(selected==1){
                Bdisp_AllClr_DDVRAM();
                RenderFrequency(inputfield);
                while(1){
                    GetKey(&key);

                    inputfield = Inputfield(key,inputfield,3);

                    RenderFrequency(inputfield);

                    if(key==KEY_CTRL_EXE){
                        if(inputfield==1){
                            Input(18,15,n);
                        }else if(inputfield==2){
                            Input(18,26,t);
                        }else if(inputfield==3){
                            Input(18,37,f);
                        }
                    }

                    if(key==KEY_CTRL_EXIT){
                        Bdisp_AllClr_DDVRAM();
                        PrintMainMenu(selected);
                        break;
                    }
                }  
            }
            //wave length menu
            if(selected==4){
                Bdisp_AllClr_DDVRAM();
                RenderWavelength();
                while(1){
                    GetKey(&key);

                    RenderWavelength();

                    if(key==KEY_CTRL_EXIT){
                        Bdisp_AllClr_DDVRAM();
                        PrintMainMenu(selected);
                        break;
                    }
                }                  
            }
        }
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

