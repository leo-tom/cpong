#ifndef __PONG_H__
#define __PONG_H__

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <float.h>
/*public and private do not have actuall means. just a memo*/
#define private
#define public

typedef struct{
	double x;
	double y;
}location;
typedef struct{
    int size;
    location loc;
}racket;
public extern int flag;
public extern int b_speed; /*speed of ball*/
public extern int quickness;
public extern int frequency;
public extern double ball_direction;

extern location w_size;
extern racket me;
extern racket op;
extern location ball;
extern FILE *logfile;

public extern void show_all();
public extern void die();
public extern void pong_main();

#define FLAG_DEBUG 1 << 0

#endif
