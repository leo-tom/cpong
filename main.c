#include <stdio.h>
#include "pong.h"

/*window size*/
public location w_size;
public FILE *logfile;

private extern void del_log();
private extern void open_log();

public int flag = 0;
public double b_speed = 1;
public int frequency = 50;
public int difficulty = 3;

private const char AVALIABLE_ARGS[] = "l:";
private const char USAGE_STR[] =
"pong [-l level]\nvalue of level only can be 1 to 10\n";


void init_field(){
    int center_y;
	getmaxyx(stdscr,w_size.y,w_size.x);
    center_y = w_size.y / 2;

    ball.x = w_size.x/2;
    ball.y = center_y;
    me.size = op.size = w_size.y / 12;
    me.loc.x = 0;
    me.loc.y = center_y;
    op.loc.x = w_size.x -1;
    op.loc.y = center_y - 2;
    show_all();
    srand(time(NULL));
}
/*Die if non zero is given*/
void die(int val){
	if(val){
		endwin();
		exit(0);
	}
}
void open_log(){
    char buff[128];
    sprintf(buff,"/tmp/pong_%d",getpid());
    logfile = fopen(buff,"w");
}
private void usage(){
    fprintf(stderr,USAGE_STR);
}
private void show_title(){
    show_string("C PONG",w_size.y / 2);
    show_string("Hit enter to start game",w_size.y / 2 + 1);
    show_string("Copyright (c) 2017, Reo Tomura",w_size.y/2+5);
}
private void show_version(){
    fprintf(stderr, "1.1\n");
}
int main(int argc,char *argv[]){
    int c;
    int i = 1;
    while((c = getopt(argc,argv,AVALIABLE_ARGS))!= -1){
        switch(c){
            case 'l':
                /*level*/
                difficulty = atoi(argv[i+1]);
                break;
            case 'v'
                show_version();
                return 0;
            case '?':
            default:
                usage();
                exit(1);
        }
        i++;
    }
    if(difficulty <= 0 || difficulty > 10){
        fprintf(stderr,"You can only set level 1 to 10\n");
        exit(1);
    }
	initscr();cbreak();noecho();
    init_field();
    show_title();
    getchar();
    pong_main();
	endwin();
}
