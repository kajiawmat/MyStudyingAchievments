#ifndef MYREADKEY_H
#define MYREADKEY_H

#include<termios.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

static int KeyFlag;

enum keys
{
	key_load,
	key_save,
	key_run,
	key_step,
	key_reset,
	key_F5,
	key_F6,
	key_up,
	key_down,
	key_left,
	key_right,
	key_other,
	key_enter,
	key_exit
};

static struct termios mysettings;

int rk_mytermsave();

int rk_mytermrestore();

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

int rk_readkey(enum keys *key, int flag);

#endif
