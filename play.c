#include "pong.h"
#include <math.h>
public double ball_direction;
/*return non-zero when something had been changed*/
int think_and_move(){

}
double get_dir(racket *r){
    double distance;
    double abs_distance;
    double radi;
    distance = ball.y - r->loc.y;
    abs_distance = fabs(distance); 
    if(abs_distance >= r->size ){
        return NAN;
    }
    radi = (M_PI_2*(abs_distance/r->size)*(1.0f/4.0f));
    if(distance > 0.0f){
        radi = radi * -1;
    }
    return radi;
}
void pong_main(){
    int frequency_val = frequency;
    struct timespec sleep_t;
    sleep_t.tv_sec = 0;
    sleep_t.tv_nsec = quickness;
    bool v_changed = false; /*value changed*/
    ball_direction = 0.0f;
    double dval;
    while(1){
        if(frequency_val <= 0){
            frequency_val = frequency;
            ball.x += b_speed * cos(ball_direction);
            ball.y += b_speed * sin(ball_direction);
            v_changed = true;
            if(ball.x <= 1 && b_speed < 0){
                if((dval = get_dir(&me))== NAN){
                    die(1);
                }
                ball_direction = dval;
                b_speed *= -1.0f;
            }else if(ball.x >= w_size.x - 2 && b_speed > 0){
                if((dval = get_dir(&op)) == NAN){
                    /*won*/
                    die(1);
                }
                ball_direction = dval;
                b_speed *= -1.0f;
            }
        }
        if(think_and_move())
            v_changed = true;
        if(v_changed){
            show_all();
            v_changed = false;
        }
        nanosleep(&sleep_t,NULL);
        frequency_val--;
    }
}


