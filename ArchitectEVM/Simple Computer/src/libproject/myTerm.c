#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<sys/ioctl.h>
#include"myTerm.h"

int mt_clrscr()
{
    printf("\E[H\E[J");
    mt_gotoXY(1,1);
    return 0;
}

int mt_gotoXY(int x, int y)
{
    int rows, cols;
    mt_getscreensize(&rows, &cols);
    if(x<0||x>cols||y<0||y>rows) return -1;
    printf("\E[%i;%iH",y,x);
    return 0;
}

int mt_getscreensize(int *rows, int *cols)
{
    struct winsize ws;
    if(!ioctl(1,TIOCGWINSZ,&ws))
    {
        *rows=ws.ws_row;
        *cols=ws.ws_col;
        return 0;
    }
    return -1;
}

int mt_setfgcolor(enum colors col)
{
    printf("\E[3%im",col);
    return 0;
}

int mt_setbgcolor(enum colors col)
{
    printf("\E[4%im",col);
    return 0;
}
