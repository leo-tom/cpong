#include "pong.h"
#include <math.h>
#include <errno.h>
public double ball_direction;
/*return non-zero when something had been changed*/
private void mv_closer(){
    int val = ball.y - op.loc.y;
    if(val > 0){
        op.loc.y++;
    }else if(val < 0){
        op.loc.y--;
    }
}
private int think_and_move(int lose){
    int val = abs(ball.y - op.loc.y);
    if(lose <= 0){
        /*try to lose*/
        if((val - op.size) > 0){
            if((val - op.size) == 1){
                return 0;
            }else{
                mv_closer();
            }
        }
    }else{
        if(val - op.size > 0){
            mv_closer();
        }else{
            if(rand() % 40 > 38){
                if(val == 0){
                    if(rand()%2)
                        op.loc.y--;
                    else
                        op.loc.y++;
                }else{
                    mv_closer();
                }
            }else{
                return 0;
            }
        }
    }
    return 1;
}
/*Returns NAN when ball did not hit racket*/
private double get_dir(racket *r){
    double distance;
    double abs_distance;
    double radi;
    int i_abs;
    distance = ball.y - r->loc.y;
    abs_distance = fabs(distance);
    i_abs = (int)abs_distance;
    if(i_abs > r->size ){
        return NAN;
    }
    /*
    if(i_abs == 0){
        return 0;
    }*/
    radi = (M_PI_2*(abs_distance/r->size)*(1.0f/4.0f));
    if(distance > 0.0f){
        radi = 0.0f - radi;
    }
    return radi;
}
private void mv_me(int c){
    if(c == 'A'){
        if(me.loc.y > 0)
            me.loc.y--;
    }else{
        if(me.loc.y < w_size.y-1)
            me.loc.y++;
    }
}

void pong_main(){
    int frequency_val = frequency;
    struct timespec sleep_t;
    sleep_t.tv_sec = 0;
    sleep_t.tv_nsec = QUICKNESS;
    bool v_changed = false; /*value changed*/
    ball_direction = 0.0f;
    double dval;
    int t_m_val = (15-difficulty)*5; /*think and move value*/
    timeout(0);
    int c;
    int speed_up = (20 - difficulty)*10;
    int lose_in = (difficulty + 1) * 2;
    while(1){
        if(frequency_val <= 0){
            frequency_val = frequency;
            ball.x += b_speed * cos(ball_direction);
            ball.y += b_speed * sin(ball_direction);
            v_changed = true;
            if(rand()%2)
                if(think_and_move(lose_in))
                    v_changed = true;
            if(ball.x <= 0.0f && b_speed < 0){
                dval = get_dir(&me);
                if(isnan(dval)){
                    show_all();
                    show_string("You lost..",w_size.y/2);
                    show_string("hit enter to exit",w_size.y/2 + 2);
                    getchar();
                    die(1);
                }
                ball_direction = dval * -1.0f;
                b_speed *= -1.0f;
            }else if(ball.x >= w_size.x - 1.0f && b_speed > 0){
                /*oppornet is hitting back*/
                dval = get_dir(&op);
                if(isnan(dval) ){
                    /*won*/
                    show_all();
                    show_string("You won!",w_size.y/2);
                    show_string("hit enter to exit",w_size.y/2+2);
                    getchar();
                    die(1);
                }
                ball_direction = dval;
                b_speed *= -1.0f;
                lose_in--;
            }
            if(ball.y <= 0){
                ball_direction *= -1.0f;
            }else if(ball.y >= w_size.y){
                ball_direction *= -1.0f;
            }
            speed_up--;
            if(speed_up <= 0){
                b_speed += (b_speed < 0.0f) ? -0.1f : 0.1f;
                speed_up = (20 - difficulty)*50;
            }
        }
        c = getch();
        if(c == '\033')
            if(getch() == '[')
                if((c = getch()) == 'A' || c == 'B'){
                    mv_me(c);
                    v_changed = true;
                }
        if(t_m_val <= 0){
            if(think_and_move(lose_in))
                v_changed = true;
            t_m_val = (15-difficulty)*5;
        }
        t_m_val-= difficulty;
        if(v_changed){
            show_all();
            v_changed = false;
        }
        nanosleep(&sleep_t,NULL);
        frequency_val--;
    }
}
