#include "pong.h"
#include <math.h>
public double ball_direction;
/*return non-zero when something had been changed*/
int think_and_move(){
    int val = ball.y - op.loc.y;
    if(val > 0){
        if(val > op.size){
            op.loc.y++;
        }else if(op.size - val){
            val = rand() % 3;
            if(val == 1){
                op.loc.y--;
            }else if(val == 2){
                op.loc.y++;
            }else{
                return 0;
            }
        }else{
            if(rand() % 2){
                op.loc.y++;
            }else{
                return 0;
            }
        }
    }else if(val < 0){
        val = abs(val);
        if(val > op.size){
            op.loc.y--;
        }else if(op.size - val){
            val = rand() % 3;
            if(val == 1){
                op.loc.y++;
            }else if(val == 2){
                op.loc.y--;
            }else{
                return 0;
            }
        }else{
            if(rand() % 2){
                op.loc.y--;
            }else{
                return 0;
            }
        }
    }else{
        val = rand() % 3;
        if(val == 1){
            op.loc.y--;
        }else if(val == 2){
            op.loc.y++;
        }else{
            return 0;
        }
    }
    return 1;
}
double get_dir(racket *r){
    double distance;
    double abs_distance;
    double radi;
    distance = ball.y - r->loc.y;
    abs_distance = fabs(distance); 
    if(((int)abs_distance) > r->size ){
        return NAN;
    }
    radi = (M_PI_2*(abs_distance/r->size)*(1.0f/4.0f));
    if(distance > 0.0f){
        radi = radi * -1;
    }
    return radi;
}
private void mv_me(int c){
    if(c == KEY_UP){
        if(me.loc.y > 0)
            me.loc.y--;
    }else{
        if(me.loc.y < w_size.y-1)
            me.loc.y--;
    }
}

void pong_main(){
    int frequency_val = frequency;
    struct timespec sleep_t;
    sleep_t.tv_sec = 0;
    sleep_t.tv_nsec = quickness;
    bool v_changed = false; /*value changed*/
    ball_direction = 0.0f;
    double dval;
    int difficulty = 1;
    int t_m_val = (20-difficulty)*10; /*think and move value*/

    int s_return;
    struct timeval timei = {0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0,&fds);
    while(1){
        if(frequency_val <= 0){
            frequency_val = frequency;
            ball.x += b_speed * cos(ball_direction);
            ball.y += b_speed * sin(ball_direction);
            v_changed = true;
            if(ball.x <= 1.0f && b_speed < 0){
                dval = get_dir(&me);
                if(isnan(dval)){
                    die(1);
                }
                ball_direction = dval;
                b_speed *= -1.0f;
            }else if(ball.x >= w_size.x - 2.0f && b_speed > 0){
                dval = get_dir(&op);
                if(isnan(dval) ){
                    /*won*/
                    die(1);
                }
                ball_direction = dval;
                b_speed *= -1.0f;
            }
            if(ball.y <= 0){
                ball_direction *= -1.0f;
            }else if(ball.y >= w_size.y){
                ball_direction *= -1.0f;
            }
        }
        timei.tv_sec = 0;
        timei.tv_usec = 0;
        if((s_return = select(1,&fds,NULL,NULL,&timei)) < 0){
            fprintf(stderr,"error at select system call\n");
            die(1);
        }else if(s_return > 0){
            int c;
            fprintf(stderr,"here");
            while(s_return > 0){
                c = getch();
                if(c==KEY_UP || c == KEY_DOWN){
                    mv_me(c);
                    v_changed = true;
                }
                s_return--;
            }
        }else
            fprintf(stderr,"no");
        if(t_m_val <= 0){
            if(think_and_move())
                v_changed = true;
            t_m_val = (20-difficulty)*10;
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


