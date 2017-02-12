#include <stdio.h>
#include "pong.h"

/*window size*/
public location w_size;
public FILE *logfile;

private extern void del_log();
private extern void open_log();

public int flag;
public int b_speed = 1;
public int quickness = 900000;
public int frequency = 50;

void init_field(){
    int center_y;
    int r_size = 2;
	getmaxyx(stdscr,w_size.y,w_size.x);
    center_y = w_size.y / 2;

    ball.x = w_size.x/2;
    ball.y = center_y;
    me.size = op.size = r_size;
    me.loc.x = 0;
    me.loc.y = center_y;
    op.loc.x = w_size.x -1;
    op.loc.y = center_y - 1;
    show_all();
}
/*Die if non zero is given*/
void die(int val){
	if(val){
		endwin();
		exit(1);
        del_log();
	}
}
void open_log(){
    char buff[128];
    sprintf(buff,"/tmp/pong_%d",getpid());
    logfile = fopen(buff,"w");
}
int main(int argc,char *argv[]){
    flag = 0;
    //flag |= FLAG_DEBUG;
	initscr();cbreak();noecho();
    if(flag & FLAG_DEBUG)
        open_log();
    init_field();
	cbreak();
    pong_main();
	endwin();
}
