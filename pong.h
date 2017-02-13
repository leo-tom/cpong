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
	int x;
	int y;
}location;
typedef struct{
    double x;
    double y;
}dlocation;
typedef struct{
    int size;
    location loc;
}racket;
extern int flag;
extern double b_speed; /*speed of ball*/
extern int quickness;
extern int frequency;
extern double ball_direction;

extern location w_size;
extern racket me;
extern racket op;
extern dlocation ball;
extern FILE *logfile;

extern void show_all();
extern void die();
extern void pong_main();

#define FLAG_DEBUG 1 << 0

#endif
