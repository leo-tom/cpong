#include "pong.h"
racket me;
racket op; /*oppornent*/
dlocation ball;
void set_char(int x,int y,char ch){
	move(y,x);
	delch();
	insch(ch);
}
void move_racket(racket *ptr,int ny){
    if(ny - ptr->size / 2 < 0 || ny + ptr->size / 2 > w_size.y){
        return;
    }
    ptr->loc.y = ny;
}
void show_rackets(){
    register int size;
    int x = me.loc.x;
    register int y = me.loc.y;
    int n;
    for(n = -1; n <= 1 ;n+=2){
        /*do twice -1 and +1*/
        for(size = me.size; size>0 ;size--){
           set_char(me.loc.x,me.loc.y + size * n,'|'); 
        }
        for(size = op.size; size>0 ;size--){
           set_char(op.loc.x,op.loc.y + size * n,'|');
        }
    }
    set_char(me.loc.x,me.loc.y,'|');
    set_char(op.loc.x,op.loc.y,'|');
}
void show_all(){
    clear();
    show_rackets();
    set_char(ball.x,ball.y,'O');
    move(0,0);
    refresh();
}






