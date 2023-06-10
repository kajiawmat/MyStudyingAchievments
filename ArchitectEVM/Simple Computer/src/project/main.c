#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include "libproject/mySimpleComputer.h"
#include "libproject/myTerm.h"
#include "libproject/myUI.h"
#include "libproject/myReadkey.h"

void signalHandler(int signal) {
    switch (signal) {
    case SIGALRM:
        signalRun( & Memory_Position);
        break;
    case SIGUSR1:
        ui_restart();
        //ui_initial() ;
        break;
    case SIGUSR2:
        signalRun( & Memory_Position);
        break;
    default:
        break;
    }

}

int main() {
    ui_terminal_init();
    signal(SIGALRM, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);
    Memory_Position = 0;
    enum keys key;
    struct itimerval nval, oval;
    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
    KeyFlag = 1;
    do {
        ui_terminal_update();
        rk_readkey( & key, KeyFlag);
        switch (key) {
        case key_up:
            ui_Change_Memory_Position(key_up, KeyFlag);
            break;
        case key_right:
            ui_Change_Memory_Position(key_right, KeyFlag);
            break;
        case key_down:
            ui_Change_Memory_Position(key_down, KeyFlag);
            break;
        case key_left:
            ui_Change_Memory_Position(key_left, KeyFlag);
            break;

        case key_load:
            ui_loadMemory();
            break;
        case key_save:
            ui_saveMemory();
            break;

        case key_run:
            while (signalRun( & Memory_Position) == 0) usleep(25000);
            break;
        case key_step:
            raise(SIGUSR2);
            break;
        case key_reset:
            raise(SIGUSR1);
            break;

        case key_F5:
            ui_set_accumulator();
            break;
        case key_F6:
            ui_set_instructionCounter( & Memory_Position);
            break;

        case key_enter:
            ui_set_memory_value();
            break;

        default:
            break;

        }
    } while (key != key_exit);

    return 0;
}
