#include "myReadkey.h"


int rk_mytermsave() {
    return tcgetattr(fileno(stdin), & mysettings);
}

int rk_mytermrestore() {
    return tcsetattr(fileno(stdin), TCSAFLUSH, & mysettings);
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) {
    struct termios new_settings;
    tcgetattr(fileno(stdin), & new_settings);
    if (regime == 0) {
        new_settings.c_lflag &= (~ICANON);
        if (sigint == 0) new_settings.c_lflag &= (~ISIG);
        else new_settings.c_lflag |= ISIG;
        if (echo == 0) new_settings.c_lflag &= (~ECHO);
        else new_settings.c_lflag |= ECHO;
        new_settings.c_cc[VMIN] = vmin;
        new_settings.c_cc[VTIME] = vtime;
    } else {
        new_settings.c_lflag |= ICANON;
    }
    tcsetattr(0, TCSAFLUSH, & new_settings);
    return 0;
}

int rk_readkey(enum keys * key, int flag) {
    fflush(stdout);
    char buf[5] = "\0";
    rk_mytermregime(0, 1, 0, 0, 0);
    read(fileno(stdin), buf, 5);
    rk_mytermrestore();
    if (flag == 1) {
        if (!strcmp(buf, "\E[A")) * key = key_up;
        else if (!strcmp(buf, "\E[B")) * key = key_down;
        else if (!strcmp(buf, "\E[C")) * key = key_right;
        else if (!strcmp(buf, "\E[D")) * key = key_left;
        else if (!strcmp(buf, "\E[15~")) * key = key_F5;
        else if (!strcmp(buf, "\E[17~")) * key = key_F6;
        else if (buf[0] == 'l') * key = key_load;
        else if (buf[0] == 's') * key = key_save;
        else if (buf[0] == 'r') * key = key_run;
        else if (buf[0] == 't') * key = key_step;
        else if (buf[0] == 'i') * key = key_reset;
        else if (buf[0] == '\n') * key = key_enter;
        else if (buf[0] == 27) * key = key_exit;
        else *key = key_other;
    } else {
        if (buf[0] == 'i') * key = key_reset;
        else *key = key_other;
    }
    fflush(stdin);
    return 0;

}
