#include "myBigChars.h"

int bc_printA(char * str) {
    if (str == NULL) return -1;
    printf("\E(0");
    for (int i = 0; i < strlen(str); i++) printf("%c", str[i]);
    printf("\E(B");
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    if (x2 <= 0 || y2 <= 0) return -1;
    int div_x = x2 - x1;
    int div_y = y2 - y1;
    if (div_x <= 0 || div_y <= 0) return -1;
    char * str1 = (char * ) malloc(sizeof(char) * (div_x + 1));
    char * str2 = (char * ) malloc(sizeof(char) * (div_x + 1));
    str1[0] = 'l';
    str2[0] = 'x';
    str1[div_x] = 'k';
    str2[div_x] = 'x';
    for (int i = 1; i < div_x; i++) {
        str1[i] = 'q';
        str2[i] = ' ';
    }
    mt_gotoXY(x1, y1);
    bc_printA(str1);
    for (int y = y1 + 1; y < y2; y++) {
        mt_gotoXY(x1, y);
        bc_printA(str2);
    }
    str1[0] = 'm';
    str1[div_x] = 'j';
    mt_gotoXY(x1, y2);
    bc_printA(str1);
    return 0;
}

int bc_printbigchar(long int * nums, int x, int y, enum colors col_bg, enum colors col_fg) {
    int rows, cols;
    mt_getscreensize( & rows, & cols);
    if (x < 0 || x > cols - 7 || y < 0 || y > rows - 7) return -1;
    long int num_0 = nums[0], num_1 = nums[1];
    printf("\E(0");
    mt_setfgcolor(col_fg);
    mt_setbgcolor(col_bg);
    for (int i = 0; i < 8; i++) {
        mt_gotoXY(x, y + i);
        for (int j = 0; j < 8; j++) {
            if (i < 4) {
                if (num_0 & 0x1) printf("a");
                else printf(" ");
                num_0 = num_0 >> 1;
            } else {
                if (num_1 & 0x1) printf("a");
                else printf(" ");
                num_1 = num_1 >> 1;
            }
        }
    }
    printf("\E(B");
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(DEFAULT);
    return 0;
}

int bc_setbigcharpos(long int * big, int x, int y, int value) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return -1;
    int ind = 1;
    if (y < 4) ind = 0;
    else y -= 4;
    if (value > 2 || value < 0) return -1;
    if (value) big[ind] = big[ind] | (1 << (x + y * 8));
    else big[ind] = big[ind] & (~(1 << (x + y * 8)));
    return 0;
}

int bc_getbigcharpos(long int * big, int x, int y, int * value) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return -1;
    int ind = 1;
    if (y < 4) ind = 0;
    else y -= 4;
    * value = (big[ind] >> (x + y * 8)) & 0x1;
    return 0;
}

int bc_bigcharwrite(char * filename, long int * big, int N, int count) {
    FILE * fp = fopen(filename, "w+");
    int i = 0;
    if (count <= 0) return -1;
    if (N / 2 < count) return -1;
    while (count) {
        fwrite((char * ) & big[i], sizeof(big[i]), 1, fp);
        i++;
        fwrite((char * ) & big[i], sizeof(big[i]), 1, fp);
        i++;
        count--;
    }
    fclose(fp);
    return 0;
}

int bc_bigcharread(char * filename, long int * big, int N, int need_count, int * count) {
    FILE * fp = fopen(filename, "r");
    if (fp == NULL) return -1;
    * count = 0;
    int i = 0;
    while (need_count > 0 && ( * count) + 1 <= N / 2) {
        fread((char * ) & big[i], sizeof(big[i]), 1, fp);
        i++;
        fread((char * ) & big[i], sizeof(big[i]), 1, fp);
        i++;
        need_count--;
        ( * count) ++;
    }
    fclose(fp);
    return 0;
}
