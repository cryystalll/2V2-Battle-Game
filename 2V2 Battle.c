//
//  main.c
//  pastes
//
//  Created by 黃鈺舒 on 2021/7/5.
//  Copyright © 2021 黃鈺舒. All rights reserved.
//
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define GAME_TERMINATE -1

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *img = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *image3 = NULL;
ALLEGRO_BITMAP *image4 = NULL;
ALLEGRO_BITMAP *image5 = NULL;

ALLEGRO_BITMAP *background = NULL;
ALLEGRO_KEYBOARD_STATE keyState ;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer2 = NULL;
ALLEGRO_TIMER *timer3 = NULL;
ALLEGRO_TIMER *timer4 = NULL;
ALLEGRO_TIMER *timer5 = NULL;
ALLEGRO_TIMER *timer6 = NULL;



ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_FONT *font = NULL;

//Custom Definition
const char *title = "Final Project 106062304";
const float FPS = 60;
const int WIDTH = 600;
const int HEIGHT = 600;
typedef struct character
{
    int x;
    int y;
    ALLEGRO_BITMAP *image_path;

}Character;

Character character1;
Character character2;
Character character3;
Character character4;
Character character5;
Character character6;
Character character7;
Character character8;
Character character9;
Character character10;
Character character11;
Character character12;
Character character13;






int imageWidth = 0;
int imageHeight = 0;
int draw = 0;
int done = 0;
int window = 1;
int cover =1;
bool judge_next_window = false;
bool judge_about=false;

bool anattack=false;
bool muattack=false;
bool ture_1 , ture_2, ture_3;
bool anwin=false;
bool muwin=false;
bool anbig=false;
bool mubig=false;

int attack;
int defense;
int mumucphurt;
int anancphurt;
int vs;
int bigattack;
int bigdefense;
int muinix,muiniy;
int aninix,aniniy;
int munowx,munowy;
int annowx,annowy;
int k,j;




void show_err_msg(int msg);
void game_init();
int process_event();
void game_begin();
void game();
int game_run();
void game_destroy();

int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();

    game_begin();

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }

    game_destroy();
    return 0;
}

void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d\n", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if (!al_init()) {
        show_err_msg(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        show_err_msg(-1);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        show_err_msg(-1);
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        show_err_msg(-1);
    }
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    event_queue = al_create_event_queue();
    if (display == NULL || event_queue == NULL) {
        show_err_msg(-1);
    }
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

}
int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    // Our setting for controlling animation

    if(event.timer.source == timer3){
        ture_3 = !ture_3 ;
    }
    if(event.timer.source==timer6){
        vs++;
    }
    if(anattack){
    if(event.timer.source == timer4){
        attack++;
    }
    if(attack==17){
        anattack=!anattack;
        attack-=17;
    }
    if(character1.y==character2.y&&character1.x+50<character2.x-35){
        if(event.timer.source==timer5){
            mumucphurt++;
        }
    }
    if(mumucphurt>=14){
        anwin=true;
    }

    }
    if(muattack){
    if(event.timer.source == timer4){
        defense++;
    }
    if(defense==17){
        muattack=!muattack;
        defense-=17;
    }
    if(character2.y==character1.y&&character1.x+50<character2.x-35){
        if(event.timer.source==timer5){
            anancphurt++;
        }
    }
    if(anancphurt>=14){
        muwin=true;
    }

    }
     if(anbig){
         if(k==0){
            if(bigattack==0){
            muinix=character2.x;
            muiniy=character2.y;
            }
    if(event.timer.source == timer4){
        bigattack++;
    }


    if(bigattack==81){
            munowx=character2.x;
            munowy=character2.y;

    }

    if(munowy==muiniy&&munowx==muinix){
               if(event.timer.source==timer5){
                mumucphurt+=3;
                anbig=!anbig;
                k++;
                }
    }

      }


    if(mumucphurt>=14){
        anwin=true;
    }
  }

  if(mubig){
         if(j==0){
            if(bigdefense==0){
            aninix=character1.x;
            aniniy=character1.y;
            }
    if(event.timer.source == timer4){
        bigdefense++;
    }


    if(bigdefense==81){
            annowx=character1.x;
            annowy=character1.y;

    }

    if(annowy==aniniy&&annowx==aninix){
               if(event.timer.source==timer5){
                anancphurt+=3;
                mubig=!mubig;
                j++;
                }
    }

      }


    if(anancphurt>=14){
        muwin=true;
    }
  }









    // Keyboard
    if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(event.keyboard.keycode)
        {
            // P1 control
            case ALLEGRO_KEY_S:
                character1.y -= 30;
                break;
            case ALLEGRO_KEY_X:
                character1.y += 30;
                break;
            case ALLEGRO_KEY_Z:
                character1.x -= 30;
                break;
            case ALLEGRO_KEY_C:
                character1.x += 30;
                break;

            // P2 control
            case ALLEGRO_KEY_UP:
                character2.y -= 30;
                break;
            case ALLEGRO_KEY_DOWN:
                character2.y += 30;
                break;
            case ALLEGRO_KEY_RIGHT:
                character2.x += 30;
                break;
            case ALLEGRO_KEY_LEFT:
                character2.x -= 30;
                break;
                 case ALLEGRO_KEY_W:
                     anattack=true;
                    break;
                 case ALLEGRO_KEY_ENTER:
                    muattack=true;
                    break;
                 case ALLEGRO_KEY_LSHIFT:
                    anbig=true;
                    break;
                 case ALLEGRO_KEY_RSHIFT:
                    mubig=true;
                    break;

            // For Start Menu
            case ALLEGRO_KEY_SPACE:
                judge_next_window = true;
                break;
            case ALLEGRO_KEY_A:
                judge_about = true;
                break;

        }
    }



    // Shutdown our program
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;

    return 0;
}


void game_begin(){



  song = al_load_sample( "/Users/User/Desktop/music2.wav" );


         if (!song){
        printf( "Audio clip sample not loaded!\n" );
        show_err_msg(-1);
    }


    // Loop the song until the display closes
    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

   al_clear_to_color(al_map_rgb(255,255,255));
    font = al_load_ttf_font("/Users/User/Desktop/pirulen.ttf",12,0); // load font
   al_draw_text(font, al_map_rgb(255,69,0), 300, 420
            , ALLEGRO_ALIGN_CENTRE, "Tap blank key to Start :)");
    al_draw_text(font, al_map_rgb(0,0,0), 300, 460
            , ALLEGRO_ALIGN_CENTRE, "Tap A to About ");
    al_draw_text(font, al_map_rgb(95,158,160), 300, 500
            , ALLEGRO_ALIGN_CENTRE, "Click x to Exit ");
 img = al_load_bitmap("/Users/User/Desktop/Mickey.png");


    if (img == NULL)
        show_err_msg(-1);
    al_draw_bitmap(img, 170, 150, 0);

    al_flip_display();


}


int game_run() {
    int error = 0;
    // First window(Menu)


    if(window == 1){


        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();

        if(judge_next_window) {
                window = 2;
                // Setting Character
                character1.x = WIDTH / 2 - 300;
                character1.y = HEIGHT / 2 + 100;
                character2.x = WIDTH / 2 + 250;
                character2.y = HEIGHT / 2 + 100;
                character4.x = character1.x;
                character4.y = character1.y;
                character6.x = WIDTH / 2 - 380;
                character6.y = HEIGHT / 2 -300;
                character7.x = WIDTH / 2 + 50;
                character7.y = HEIGHT / 2 -307;
                character8.x = character2.x;
                character8.y = character2.y;
                character9.x = WIDTH / 2 -320;
                character9.y = HEIGHT / 2 -100;
                character10.x = WIDTH / 2 +60;
                character10.y = HEIGHT / 2-350 ;
                character11.x = WIDTH / 2-120;
                character11.y = HEIGHT / 2-100;





                character1.image_path = al_load_bitmap("/Users/User/Desktop/anan.jpg");
                character2.image_path = al_load_bitmap("/Users/User/Desktop/mumu.jpg");
                character3.image_path = al_load_bitmap("/Users/User/Desktop/anan2.jpg");
                character4.image_path = al_load_bitmap("/Users/User/Desktop/mikey.jpg");
                character5.image_path = al_load_bitmap("/Users/User/Desktop/mumu2.jpg");
                character6.image_path = al_load_bitmap("/Users/User/Desktop/ancp.jpg");
                character7.image_path = al_load_bitmap("/Users/User/Desktop/mucp.jpg");
                character8.image_path = al_load_bitmap("/Users/User/Desktop/miney.png");
                character9.image_path = al_load_bitmap("/Users/User/Desktop/ananbig.jpg");
                character10.image_path = al_load_bitmap("/Users/User/Desktop/mumubig.jpg");
                character11.image_path = al_load_bitmap("/Users/User/Desktop/vsvs.jpg");
                character12.image_path = al_load_bitmap("/Users/User/Desktop/wini.png");
                character13.image_path = al_load_bitmap("/Users/User/Desktop/elsa.png");
                image2=al_load_bitmap("/Users/User/Desktop/egg.gif");
                image3=al_load_bitmap("/Users/User/Desktop/finddie.jpg");
                image4=al_load_bitmap("/Users/User/Desktop/back.png");
                image5=al_load_bitmap("/Users/User/Desktop/back2.png");


                background = al_load_bitmap("/Users/User/Desktop/mario.gif");

                //Initialize Timer
                timer3  = al_create_timer(1.0/6.0);
                timer4  = al_create_timer(1.0/100.0);
                timer5  = al_create_timer(1.0/6.0);
                timer6  = al_create_timer(1.0/30.0);
                al_register_event_source(event_queue, al_get_timer_event_source(timer3)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer4)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer5)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer6)) ;


                al_start_timer(timer3);
                al_start_timer(timer4);
                al_start_timer(timer5);
                al_start_timer(timer6);


            }
            if(judge_about)
            {
                window=3;
                 // load font

            }
        }
    }
    // Second window(Main Game)
    else if(window == 2){
        // Change Image for animation

        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_bitmap(background, -240,-130, 0);

        if(vs==0)al_draw_bitmap(character9.image_path, character9.x, character9.y, 0);
        if(vs==1)al_draw_bitmap(character9.image_path, character9.x, character9.y-10, 0);
        if(vs==2)al_draw_bitmap(character9.image_path, character9.x, character9.y-20, 0);
        if(vs==3)al_draw_bitmap(character9.image_path, character9.x, character9.y-30, 0);
        if(vs==4)al_draw_bitmap(character9.image_path, character9.x, character9.y-40, 0);
        if(vs==5)al_draw_bitmap(character9.image_path, character9.x, character9.y-50, 0);
        if(vs==6)al_draw_bitmap(character9.image_path, character9.x, character9.y-60, 0);
        if(vs==7)al_draw_bitmap(character9.image_path, character9.x, character9.y-70, 0);
        if(vs==8)al_draw_bitmap(character9.image_path, character9.x, character9.y-80, 0);
        if(vs==9)al_draw_bitmap(character9.image_path, character9.x, character9.y-90, 0);
        if(vs==10)al_draw_bitmap(character9.image_path, character9.x, character9.y-100, 0);
        if(vs==11)al_draw_bitmap(character9.image_path, character9.x, character9.y-110, 0);
        if(vs==12)al_draw_bitmap(character9.image_path, character9.x, character9.y-120, 0);
        if(vs==13)al_draw_bitmap(character9.image_path, character9.x, character9.y-130, 0);
        if(vs==14)al_draw_bitmap(character9.image_path, character9.x, character9.y-140, 0);
        if(vs==15)al_draw_bitmap(character9.image_path, character9.x, character9.y-150, 0);
        if(vs==16)al_draw_bitmap(character9.image_path, character9.x, character9.y-160, 0);
        if(vs==17)al_draw_bitmap(character9.image_path, character9.x, character9.y-170, 0);
        if(vs==18)al_draw_bitmap(character9.image_path, character9.x, character9.y-180, 0);
        if(vs==19)al_draw_bitmap(character9.image_path, character9.x, character9.y-190, 0);
        if(vs==20)al_draw_bitmap(character9.image_path, character9.x, character9.y-200, 0);
        if(vs==21)al_draw_bitmap(character9.image_path, character9.x, character9.y-210, 0);
        if(vs==22)al_draw_bitmap(character9.image_path, character9.x, character9.y-220, 0);
        if(vs==23)al_draw_bitmap(character9.image_path, character9.x, character9.y-230, 0);
        if(vs==24)al_draw_bitmap(character9.image_path, character9.x, character9.y-240, 0);
        if(vs==25)al_draw_bitmap(character9.image_path, character9.x, character9.y-250, 0);
        if(vs==26)al_draw_bitmap(character9.image_path, character9.x, character9.y-260, 0);
        if(vs==27)al_draw_bitmap(character9.image_path, character9.x, character9.y-270, 0);
        if(vs==28)al_draw_bitmap(character9.image_path, character9.x, character9.y-280, 0);
        if(vs==29)al_draw_bitmap(character9.image_path, character9.x, character9.y-290, 0);
        if(vs==30)al_draw_bitmap(character9.image_path, character9.x, character9.y-300, 0);
        if(vs==31)al_draw_bitmap(character9.image_path, character9.x, character9.y-310, 0);
        if(vs==32)al_draw_bitmap(character9.image_path, character9.x, character9.y-320, 0);
        if(vs==33)al_draw_bitmap(character9.image_path, character9.x, character9.y-330, 0);
        if(vs==34)al_draw_bitmap(character9.image_path, character9.x, character9.y-340, 0);
        if(vs==35)al_draw_bitmap(character9.image_path, character9.x, character9.y-350, 0);
        if(vs==36)al_draw_bitmap(character9.image_path, character9.x, character9.y-360, 0);
        if(vs==37)al_draw_bitmap(character9.image_path, character9.x, character9.y-370, 0);
        if(vs==38)al_draw_bitmap(character9.image_path, character9.x, character9.y-380, 0);
        if(vs==39)al_draw_bitmap(character9.image_path, character9.x, character9.y-390, 0);
        if(vs==40)al_draw_bitmap(character9.image_path, character9.x, character9.y-400, 0);
        if(vs==41)al_draw_bitmap(character9.image_path, character9.x, character9.y-410, 0);
        if(vs==42)al_draw_bitmap(character9.image_path, character9.x, character9.y-420, 0);
        if(vs==43)al_draw_bitmap(character9.image_path, character9.x, character9.y-430, 0);
        if(vs==44)al_draw_bitmap(character9.image_path, character9.x, character9.y-440, 0);
        if(vs==45)al_draw_bitmap(character9.image_path, character9.x, character9.y-450, 0);
        if(vs==46)al_draw_bitmap(character9.image_path, character9.x, character9.y-460, 0);
        if(vs==47)al_draw_bitmap(character9.image_path, character9.x, character9.y-470, 0);
        if(vs==48)al_draw_bitmap(character9.image_path, character9.x, character9.y-480, 0);
        if(vs==49)al_draw_bitmap(character9.image_path, character9.x, character9.y-490, 0);
        if(vs==50)al_draw_bitmap(character9.image_path, character9.x, character9.y-500, 0);
        if(vs==51)al_draw_bitmap(character9.image_path, character9.x, character9.y-510, 0);
        if(vs==52)al_draw_bitmap(character9.image_path, character9.x, character9.y-520, 0);
        if(vs==53)al_draw_bitmap(character9.image_path, character9.x, character9.y-530, 0);
        if(vs==54)al_draw_bitmap(character9.image_path, character9.x, character9.y-540, 0);
        if(vs==55)al_draw_bitmap(character9.image_path, character9.x, character9.y-550, 0);
        if(vs==56)al_draw_bitmap(character9.image_path, character9.x, character9.y-560, 0);
        if(vs==57)al_draw_bitmap(character9.image_path, character9.x, character9.y-570, 0);
        if(vs==58)al_draw_bitmap(character9.image_path, character9.x, character9.y-580, 0);
        if(vs==59)al_draw_bitmap(character9.image_path, character9.x, character9.y-590, 0);
        if(vs==60)al_draw_bitmap(character9.image_path, character9.x, character9.y-600, 0);


        if(vs==0)al_draw_bitmap(character10.image_path, character10.x, character10.y, 0);
        if(vs==1)al_draw_bitmap(character10.image_path, character10.x, character10.y+10, 0);
        if(vs==2)al_draw_bitmap(character10.image_path, character10.x, character10.y+20, 0);
        if(vs==3)al_draw_bitmap(character10.image_path, character10.x, character10.y+30, 0);
        if(vs==4)al_draw_bitmap(character10.image_path, character10.x, character10.y+40, 0);
        if(vs==5)al_draw_bitmap(character10.image_path, character10.x, character10.y+50, 0);
        if(vs==6)al_draw_bitmap(character10.image_path, character10.x, character10.y+60, 0);
        if(vs==7)al_draw_bitmap(character10.image_path, character10.x, character10.y+70, 0);
        if(vs==8)al_draw_bitmap(character10.image_path, character10.x, character10.y+80, 0);
        if(vs==9)al_draw_bitmap(character10.image_path, character10.x, character10.y+90, 0);
        if(vs==10)al_draw_bitmap(character10.image_path, character10.x, character10.y+100, 0);
        if(vs==11)al_draw_bitmap(character10.image_path, character10.x, character10.y+110, 0);
        if(vs==12)al_draw_bitmap(character10.image_path, character10.x, character10.y+120, 0);
        if(vs==13)al_draw_bitmap(character10.image_path, character10.x, character10.y+130, 0);
        if(vs==14)al_draw_bitmap(character10.image_path, character10.x, character10.y+140, 0);
        if(vs==15)al_draw_bitmap(character10.image_path, character10.x, character10.y+150, 0);
        if(vs==16)al_draw_bitmap(character10.image_path, character10.x, character10.y+160, 0);
        if(vs==17)al_draw_bitmap(character10.image_path, character10.x, character10.y+170, 0);
        if(vs==18)al_draw_bitmap(character10.image_path, character10.x, character10.y+180, 0);
        if(vs==19)al_draw_bitmap(character10.image_path, character10.x, character10.y+190, 0);
        if(vs==20)al_draw_bitmap(character10.image_path, character10.x, character10.y+200, 0);
        if(vs==21)al_draw_bitmap(character10.image_path, character10.x, character10.y+210, 0);
        if(vs==22)al_draw_bitmap(character10.image_path, character10.x, character10.y+220, 0);
        if(vs==23)al_draw_bitmap(character10.image_path, character10.x, character10.y+230, 0);
        if(vs==24)al_draw_bitmap(character10.image_path, character10.x, character10.y+240, 0);
        if(vs==25)al_draw_bitmap(character10.image_path, character10.x, character10.y+250, 0);
        if(vs==26)al_draw_bitmap(character10.image_path, character10.x, character10.y+260, 0);
        if(vs==27)al_draw_bitmap(character10.image_path, character10.x, character10.y+270, 0);
        if(vs==28)al_draw_bitmap(character10.image_path, character10.x, character10.y+280, 0);
        if(vs==29)al_draw_bitmap(character10.image_path, character10.x, character10.y+290, 0);
        if(vs==30)al_draw_bitmap(character10.image_path, character10.x, character10.y+300, 0);
        if(vs==31)al_draw_bitmap(character10.image_path, character10.x, character10.y+310, 0);
        if(vs==32)al_draw_bitmap(character10.image_path, character10.x, character10.y+320, 0);
        if(vs==33)al_draw_bitmap(character10.image_path, character10.x, character10.y+330, 0);
        if(vs==34)al_draw_bitmap(character10.image_path, character10.x, character10.y+340, 0);
        if(vs==35)al_draw_bitmap(character10.image_path, character10.x, character10.y+350, 0);
        if(vs==36)al_draw_bitmap(character10.image_path, character10.x, character10.y+360, 0);
        if(vs==37)al_draw_bitmap(character10.image_path, character10.x, character10.y+370, 0);
        if(vs==38)al_draw_bitmap(character10.image_path, character10.x, character10.y+380, 0);
        if(vs==39)al_draw_bitmap(character10.image_path, character10.x, character10.y+390, 0);
        if(vs==40)al_draw_bitmap(character10.image_path, character10.x, character10.y+400, 0);
        if(vs==41)al_draw_bitmap(character10.image_path, character10.x, character10.y+410, 0);
        if(vs==42)al_draw_bitmap(character10.image_path, character10.x, character10.y+420, 0);
        if(vs==43)al_draw_bitmap(character10.image_path, character10.x, character10.y+430, 0);
        if(vs==44)al_draw_bitmap(character10.image_path, character10.x, character10.y+440, 0);
        if(vs==45)al_draw_bitmap(character10.image_path, character10.x, character10.y+450, 0);
        if(vs==46)al_draw_bitmap(character10.image_path, character10.x, character10.y+460, 0);
        if(vs==47)al_draw_bitmap(character10.image_path, character10.x, character10.y+470, 0);
        if(vs==48)al_draw_bitmap(character10.image_path, character10.x, character10.y+480, 0);
        if(vs==49)al_draw_bitmap(character10.image_path, character10.x, character10.y+490, 0);
        if(vs==50)al_draw_bitmap(character10.image_path, character10.x, character10.y+500, 0);
        if(vs==51)al_draw_bitmap(character10.image_path, character10.x, character10.y+510, 0);
        if(vs==52)al_draw_bitmap(character10.image_path, character10.x, character10.y+520, 0);
        if(vs==53)al_draw_bitmap(character10.image_path, character10.x, character10.y+530, 0);
        if(vs==54)al_draw_bitmap(character10.image_path, character10.x, character10.y+540, 0);
        if(vs==55)al_draw_bitmap(character10.image_path, character10.x, character10.y+550, 0);
        if(vs==56)al_draw_bitmap(character10.image_path, character10.x, character10.y+560, 0);
        if(vs==57)al_draw_bitmap(character10.image_path, character10.x, character10.y+570, 0);
        if(vs==58)al_draw_bitmap(character10.image_path, character10.x, character10.y+580, 0);
        if(vs==59)al_draw_bitmap(character10.image_path, character10.x, character10.y+590, 0);
        if(vs==60)al_draw_bitmap(character10.image_path, character10.x, character10.y+600, 0);


        if(vs==0||vs==2||vs==3||vs==4||vs==5||vs==11||vs==12||vs==13||vs==14||vs==15||vs==21||vs==22||vs==23||vs==24||vs==25||vs==31||vs==32||vs==33||vs==34||vs==35||vs==41||vs==42||vs==43||vs==44||vs==45||vs==51||vs==52||vs==53||vs==54||vs==55)al_draw_bitmap(character11.image_path, character11.x, character11.y, 0);

        if(ture_3)al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
        else al_draw_bitmap(character3.image_path, character1.x, character1.y, 0);
        if(ture_3)al_draw_bitmap(character2.image_path, character2.x, character2.y, 0);
        else al_draw_bitmap(character5.image_path, character2.x, character2.y, 0);

        if(mumucphurt==0)al_draw_bitmap(character7.image_path, character7.x, character7.y, 0);
        if(mumucphurt==1)al_draw_bitmap(character7.image_path, character7.x+20, character7.y, 0);
        if(mumucphurt==2)al_draw_bitmap(character7.image_path, character7.x+40, character7.y, 0);
        if(mumucphurt==3)al_draw_bitmap(character7.image_path, character7.x+60, character7.y, 0);
        if(mumucphurt==4)al_draw_bitmap(character7.image_path, character7.x+80, character7.y, 0);
        if(mumucphurt==5)al_draw_bitmap(character7.image_path, character7.x+100, character7.y, 0);
        if(mumucphurt==6)al_draw_bitmap(character7.image_path, character7.x+120, character7.y, 0);
        if(mumucphurt==7)al_draw_bitmap(character7.image_path, character7.x+140, character7.y, 0);
        if(mumucphurt==8)al_draw_bitmap(character7.image_path, character7.x+160, character7.y, 0);
        if(mumucphurt==9)al_draw_bitmap(character7.image_path, character7.x+180, character7.y, 0);
        if(mumucphurt==10)al_draw_bitmap(character7.image_path, character7.x+200, character7.y, 0);
        if(mumucphurt==11)al_draw_bitmap(character7.image_path, character7.x+220, character7.y, 0);
        if(mumucphurt==12)al_draw_bitmap(character7.image_path, character7.x+240, character7.y, 0);
        if(mumucphurt==13)al_draw_bitmap(character7.image_path, character7.x+260, character7.y, 0);

        if(anancphurt==0)al_draw_bitmap(character6.image_path, character6.x, character6.y, 0);
        if(anancphurt==1)al_draw_bitmap(character6.image_path, character6.x-20, character6.y, 0);
        if(anancphurt==2)al_draw_bitmap(character6.image_path, character6.x-40, character6.y, 0);
        if(anancphurt==3)al_draw_bitmap(character6.image_path, character6.x-60, character6.y, 0);
        if(anancphurt==4)al_draw_bitmap(character6.image_path, character6.x-80, character6.y, 0);
        if(anancphurt==5)al_draw_bitmap(character6.image_path, character6.x-100, character6.y, 0);
        if(anancphurt==6)al_draw_bitmap(character6.image_path, character6.x-120, character6.y, 0);
        if(anancphurt==7)al_draw_bitmap(character6.image_path, character6.x-140, character6.y, 0);
        if(anancphurt==8)al_draw_bitmap(character6.image_path, character6.x-160, character6.y, 0);
        if(anancphurt==9)al_draw_bitmap(character6.image_path, character6.x-180, character6.y, 0);
        if(anancphurt==10)al_draw_bitmap(character6.image_path, character6.x-200, character6.y, 0);
        if(anancphurt==11)al_draw_bitmap(character6.image_path, character6.x-220, character6.y, 0);
        if(anancphurt==12)al_draw_bitmap(character6.image_path, character6.x-240, character6.y, 0);
        if(anancphurt==13)al_draw_bitmap(character6.image_path, character6.x-260, character6.y, 0);

        if(attack==0)al_draw_bitmap(character4.image_path,character1.x+50 , character1.y, 0);
        if(attack==1)al_draw_bitmap(character4.image_path, character1.x+30, character1.y, 0);
        if(attack==2)al_draw_bitmap(character4.image_path, character1.x+60, character1.y, 0);
        if(attack==3)al_draw_bitmap(character4.image_path, character1.x+90, character1.y, 0);
        if(attack==4)al_draw_bitmap(character4.image_path, character1.x+120, character1.y, 0);
        if(attack==5)al_draw_bitmap(character4.image_path, character1.x+150, character1.y, 0);
        if(attack==6)al_draw_bitmap(character4.image_path, character1.x+180, character1.y, 0);
        if(attack==7)al_draw_bitmap(character4.image_path, character1.x+210, character1.y, 0);
        if(attack==8)al_draw_bitmap(character4.image_path, character1.x+240, character1.y, 0);
        if(attack==9)al_draw_bitmap(character4.image_path, character1.x+270, character1.y, 0);
        if(attack==10)al_draw_bitmap(character4.image_path, character1.x+300, character1.y, 0);
        if(attack==11)al_draw_bitmap(character4.image_path, character1.x+330, character1.y, 0);
        if(attack==12)al_draw_bitmap(character4.image_path, character1.x+360, character1.y, 0);
        if(attack==13)al_draw_bitmap(character4.image_path, character1.x+390, character1.y, 0);
        if(attack==14)al_draw_bitmap(character4.image_path, character1.x+420, character1.y, 0);
        if(attack==15)al_draw_bitmap(character4.image_path, character1.x+450, character1.y, 0);
        if(attack==16)al_draw_bitmap(character4.image_path, character1.x+480, character1.y, 0);

        if(defense==0)al_draw_bitmap(character8.image_path,character2.x-35 , character2.y, 0);
        if(defense==1)al_draw_bitmap(character8.image_path,character2.x-30 , character2.y, 0);
        if(defense==2)al_draw_bitmap(character8.image_path,character2.x-60 , character2.y, 0);
        if(defense==3)al_draw_bitmap(character8.image_path,character2.x-90 , character2.y, 0);
        if(defense==4)al_draw_bitmap(character8.image_path,character2.x-120 , character2.y, 0);
        if(defense==5)al_draw_bitmap(character8.image_path,character2.x-150 , character2.y, 0);
        if(defense==6)al_draw_bitmap(character8.image_path,character2.x-180 , character2.y, 0);
        if(defense==7)al_draw_bitmap(character8.image_path,character2.x-210 , character2.y, 0);
        if(defense==8)al_draw_bitmap(character8.image_path,character2.x-240 , character2.y, 0);
        if(defense==9)al_draw_bitmap(character8.image_path,character2.x-270 , character2.y, 0);
        if(defense==10)al_draw_bitmap(character8.image_path,character2.x-300 , character2.y, 0);
        if(defense==11)al_draw_bitmap(character8.image_path,character2.x-330 , character2.y, 0);
        if(defense==12)al_draw_bitmap(character8.image_path,character2.x-360 , character2.y, 0);
        if(defense==13)al_draw_bitmap(character8.image_path,character2.x-390 , character2.y, 0);
        if(defense==14)al_draw_bitmap(character8.image_path,character2.x-420 , character2.y, 0);
        if(defense==15)al_draw_bitmap(character8.image_path,character2.x-450 , character2.y, 0);
        if(defense==16)al_draw_bitmap(character8.image_path,character2.x-480 , character2.y, 0);

        if(bigattack==0)al_draw_bitmap(character12.image_path,WIDTH/2-300 , 100, 0);

        if(bigattack==51)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30+character1.x , character1.y-30, 0);
        if(bigattack==52)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*2+character1.x , character1.y-60, 0);
        if(bigattack==53)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*3+character1.x , character1.y-90, 0);
        if(bigattack==54)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*4+character1.x , character1.y-110, 0);
        if(bigattack==55)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*5+character1.x , character1.y-130, 0);
        if(bigattack==56)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*6+character1.x , character1.y-150, 0);
        if(bigattack==57)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*7+character1.x , character1.y-160, 0);
        if(bigattack==58)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*8+character1.x , character1.y-170, 0);
        if(bigattack==59)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*9+character1.x , character1.y-180, 0);
        if(bigattack==60)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*10+character1.x , character1.y-185, 0);
        if(bigattack==61)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*11+character1.x , character1.y-190, 0);
        if(bigattack==62)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*12+character1.x , character1.y-200, 0);
        if(bigattack==63)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*13+character1.x, character1.y-205, 0);
        if(bigattack==64)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*14+character1.x , character1.y-210, 0);
        if(bigattack==65)al_draw_bitmap(character12.image_path,(muinix-character1.x)/2, character1.y-210, 0);
        if(bigattack==66)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*16+character1.x , character1.y-210, 0);
        if(bigattack==67)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*17 +character1.x , character1.y-205, 0);
        if(bigattack==68)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*18+character1.x , character1.y-200, 0);
        if(bigattack==69)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*19+character1.x  , character1.y-195, 0);
        if(bigattack==70)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*20 +character1.x , character1.y-185, 0);
        if(bigattack==71)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*21+character1.x  , character1.y-180, 0);
        if(bigattack==72)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*22+character1.x  , character1.y-170, 0);
        if(bigattack==73)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*23 +character1.x , character1.y-160, 0);
        if(bigattack==74)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*24+character1.x , character1.y-150, 0);
        if(bigattack==75)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*25+character1.x , character1.y-130, 0);
        if(bigattack==76)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*26+character1.x , character1.y-110, 0);
        if(bigattack==77)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*27+character1.x  , character1.y-90, 0);
        if(bigattack==78)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*28+character1.x , character1.y-60, 0);
        if(bigattack==79)al_draw_bitmap(character12.image_path,(muinix-character1.x)/30*29+character1.x  ,character1.y-30, 0);
        if(bigattack==80)al_draw_bitmap(character12.image_path,muinix, muiniy, 0);
        if(bigattack==81)al_draw_bitmap(character12.image_path,1000, 1000, 0);




        if(bigdefense==0)al_draw_bitmap(character13.image_path,WIDTH/2+220 , 100, 0);
        if(bigdefense==51)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30+character2.x , character2.y-30, 0);
        if(bigdefense==52)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*2+character2.x , character2.y-60, 0);
        if(bigdefense==53)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*3+character2.x , character2.y-90, 0);
        if(bigdefense==54)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*4+character2.x , character2.y-110, 0);
        if(bigdefense==55)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*5+character2.x , character2.y-130, 0);
        if(bigdefense==56)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*6+character2.x , character2.y-150, 0);
        if(bigdefense==57)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*7+character2.x , character2.y-160, 0);
        if(bigdefense==58)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*8+character2.x , character2.y-170, 0);
        if(bigdefense==59)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*9+character2.x , character2.y-180, 0);
        if(bigdefense==60)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*10+character2.x , character2.y-185, 0);
        if(bigdefense==61)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*11+character2.x , character2.y-190, 0);
        if(bigdefense==62)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*12+character2.x , character2.y-200, 0);
        if(bigdefense==63)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*13+character2.x, character2.y-205, 0);
        if(bigdefense==64)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*14+character2.x , character2.y-210, 0);
        if(bigdefense==65)al_draw_bitmap(character13.image_path,(aninix-character2.x)/2, character2.y-210, 0);
        if(bigdefense==66)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*16+character2.x , character2.y-210, 0);
        if(bigdefense==67)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*17 +character2.x , character2.y-205, 0);
        if(bigdefense==68)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*18+character2.x , character2.y-200, 0);
        if(bigdefense==69)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*19+character2.x  , character2.y-195, 0);
        if(bigdefense==70)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*20 +character2.x , character2.y-185, 0);
        if(bigdefense==71)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*21+character2.x  , character2.y-180, 0);
        if(bigdefense==72)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*22+character2.x  , character2.y-170, 0);
        if(bigdefense==73)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*23 +character2.x , character2.y-160, 0);
        if(bigdefense==74)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*24+character2.x , character2.y-150, 0);
        if(bigdefense==75)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*25+character2.x , character2.y-130, 0);
        if(bigdefense==76)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*26+character2.x , character2.y-110, 0);
        if(bigdefense==77)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*27+character2.x  , character2.y-90, 0);
        if(bigdefense==78)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*28+character2.x , character2.y-60, 0);
        if(bigdefense==79)al_draw_bitmap(character13.image_path,(aninix-character2.x)/30*29+character2.x  ,character2.y-30, 0);
        if(bigdefense==80)al_draw_bitmap(character13.image_path,aninix, aniniy, 0);
        if(bigdefense==81)al_draw_bitmap(character13.image_path,1000, 1000, 0);

         if(bigattack==1||bigattack==2||bigattack==3||bigattack==4||bigattack==5||bigattack==6||bigattack==7||bigattack==8||bigattack==9||bigattack==10||bigattack==11||bigattack==12||bigattack==13||bigattack==14||bigattack==15||bigattack==16||bigattack==17||bigattack==18||bigattack==19||bigattack==20||bigattack==21||bigattack==22||bigattack==23||bigattack==24||bigattack==25||bigattack==26||bigattack==27||bigattack==28||bigattack==29||bigattack==30||bigattack==31||bigattack==32||bigattack==33||bigattack==34||bigattack==35||bigattack==36||bigattack==37||bigattack==38||bigattack==39||bigattack==40||bigattack==41||bigattack==42||bigattack==43||bigattack==44||bigattack==45||bigattack==46||bigattack==47||bigattack==48||bigattack==49||bigattack==50)al_draw_bitmap(image4,WIDTH/2-300 , HEIGHT / 2-500, 0);
        if(bigattack==1||bigattack==2||bigattack==3||bigattack==4||bigattack==5||bigattack==6||bigattack==7||bigattack==8||bigattack==9||bigattack==10||bigattack==11||bigattack==12||bigattack==13||bigattack==14||bigattack==15||bigattack==16||bigattack==17||bigattack==18||bigattack==19||bigattack==20||bigattack==21||bigattack==22||bigattack==23||bigattack==24||bigattack==25||bigattack==26||bigattack==27||bigattack==28||bigattack==29||bigattack==30||bigattack==31||bigattack==32||bigattack==33||bigattack==34||bigattack==35||bigattack==36||bigattack==37||bigattack==38||bigattack==39||bigattack==40||bigattack==41||bigattack==42||bigattack==43||bigattack==44||bigattack==45||bigattack==46||bigattack==47||bigattack==48||bigattack==49||bigattack==50)al_draw_bitmap(character12.image_path,WIDTH/2 -38, HEIGHT / 2-100, 0);
        if(bigattack==1||bigattack==2||bigattack==3||bigattack==4||bigattack==5||bigattack==6||bigattack==7||bigattack==8||bigattack==9||bigattack==10||bigattack==11||bigattack==12||bigattack==13||bigattack==14||bigattack==15||bigattack==16||bigattack==17||bigattack==18||bigattack==19||bigattack==20||bigattack==21||bigattack==22||bigattack==23||bigattack==24||bigattack==25||bigattack==26||bigattack==27||bigattack==28||bigattack==29||bigattack==30||bigattack==31||bigattack==32||bigattack==33||bigattack==34||bigattack==35||bigattack==36||bigattack==37||bigattack==38||bigattack==39||bigattack==40||bigattack==41||bigattack==42||bigattack==43||bigattack==44||bigattack==45||bigattack==46||bigattack==47||bigattack==48||bigattack==49||bigattack==50)al_draw_bitmap(image2,WIDTH/2 -300, HEIGHT / 2, 0);

        if(bigdefense==1||bigdefense==2||bigdefense==3||bigdefense==3||bigdefense==4||bigdefense==5||bigdefense==6||bigdefense==7||bigdefense==8||bigdefense==9||bigdefense==10||bigdefense==11||bigdefense==12||bigdefense==13||bigdefense==14||bigdefense==15||bigdefense==16||bigdefense==17||bigdefense==18||bigdefense==19||bigdefense==20||bigdefense==21||bigdefense==22||bigdefense==23||bigdefense==24||bigdefense==25||bigdefense==26||bigdefense==27||bigdefense==28||bigdefense==29||bigdefense==30||bigdefense==31||bigdefense==32||bigdefense==33||bigdefense==34||bigdefense==35||bigdefense==36||bigdefense==37||bigdefense==38||bigdefense==39||bigdefense==40||bigdefense==41||bigdefense==42||bigdefense==43||bigdefense==44||bigdefense==45||bigdefense==46||bigdefense==47||bigdefense==48||bigdefense==49||bigdefense==50)al_draw_bitmap(image5,WIDTH/2 -320, HEIGHT / 2-430, 0);
        if(bigdefense==1||bigdefense==2||bigdefense==3||bigdefense==3||bigdefense==4||bigdefense==5||bigdefense==6||bigdefense==7||bigdefense==8||bigdefense==9||bigdefense==10||bigdefense==11||bigdefense==12||bigdefense==13||bigdefense==14||bigdefense==15||bigdefense==16||bigdefense==17||bigdefense==18||bigdefense==19||bigdefense==20||bigdefense==21||bigdefense==22||bigdefense==23||bigdefense==24||bigdefense==25||bigdefense==26||bigdefense==27||bigdefense==28||bigdefense==29||bigdefense==30||bigdefense==31||bigdefense==32||bigdefense==33||bigdefense==34||bigdefense==35||bigdefense==36||bigdefense==37||bigdefense==38||bigdefense==39||bigdefense==40||bigdefense==41||bigdefense==42||bigdefense==43||bigdefense==44||bigdefense==45||bigdefense==46||bigdefense==47||bigdefense==48||bigdefense==49||bigdefense==50)al_draw_bitmap(character13.image_path,WIDTH/2 -38, HEIGHT / 2-100, 0);
        if(bigdefense==1||bigdefense==2||bigdefense==3||bigdefense==3||bigdefense==4||bigdefense==5||bigdefense==6||bigdefense==7||bigdefense==8||bigdefense==9||bigdefense==10||bigdefense==11||bigdefense==12||bigdefense==13||bigdefense==14||bigdefense==15||bigdefense==16||bigdefense==17||bigdefense==18||bigdefense==19||bigdefense==20||bigdefense==21||bigdefense==22||bigdefense==23||bigdefense==24||bigdefense==25||bigdefense==26||bigdefense==27||bigdefense==28||bigdefense==29||bigdefense==30||bigdefense==31||bigdefense==32||bigdefense==33||bigdefense==34||bigdefense==35||bigdefense==36||bigdefense==37||bigdefense==38||bigdefense==39||bigdefense==40||bigdefense==41||bigdefense==42||bigdefense==43||bigdefense==44||bigdefense==45||bigdefense==46||bigdefense==47||bigdefense==48||bigdefense==49||bigdefense==50)al_draw_bitmap(image3,WIDTH/2 +40, HEIGHT / 2+70, 0);

        if(anwin){
           window=4;
           judge_next_window=false;

        }
        if(muwin){
            window=5;
            judge_next_window=false;
        }

        al_flip_display();


        // Listening for new event
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }
    }
    else if(window==3){



   al_draw_text(font, al_map_rgb(105,105,105), 300, 50
            , ALLEGRO_ALIGN_CENTRE, "Click X to exit");
    al_draw_text(font, al_map_rgb(0,0,0), 300, 100
            , ALLEGRO_ALIGN_CENTRE, "A CUTE GAME ");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 150
            , ALLEGRO_ALIGN_CENTRE, "left one is ANAN, right one is MUMU ");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 200
            , ALLEGRO_ALIGN_CENTRE, "use up down left right to control MUMU to move");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 250
            , ALLEGRO_ALIGN_CENTRE, "and S X Z C to ANAN ");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 300
            , ALLEGRO_ALIGN_CENTRE, "tap enter for MUMU to attack");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 320
            , ALLEGRO_ALIGN_CENTRE, "RSHIFT to throw big ball Elsa!!(only once and triple kill)");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 350
            , ALLEGRO_ALIGN_CENTRE, "tap W for ANAN to attack");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 370
            , ALLEGRO_ALIGN_CENTRE, "LSHIFT to throw big ball Winnie!!(only once and triple kill)");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 400
            , ALLEGRO_ALIGN_CENTRE, "If one's HP die,another win");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 450
            , ALLEGRO_ALIGN_CENTRE, "Have fun:)");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 500
            , ALLEGRO_ALIGN_CENTRE, "P.S. you have to hit their TSUMTSUM to successfully attack!");
    al_draw_text(font, al_map_rgb(255,69,0), 300, 550
            , ALLEGRO_ALIGN_CENTRE, "Tap blank key to start!! ");
            al_flip_display();
            al_clear_to_color(al_map_rgb(135,206,235));
             if(judge_next_window){

               window = 2;
 // Setting Character
                character1.x = WIDTH / 2 - 300;
                character1.y = HEIGHT / 2 + 100;
                character2.x = WIDTH / 2 + 250;
                character2.y = HEIGHT / 2 + 100;
                character4.x = character1.x;
                character4.y = character1.y;
                character6.x = WIDTH / 2 - 380;
                character6.y = HEIGHT / 2 -300;
                character7.x = WIDTH / 2 + 50;
                character7.y = HEIGHT / 2 -307;
                character8.x = character2.x;
                character8.y = character2.y;
                character9.x = WIDTH / 2 -320;
                character9.y = HEIGHT / 2 -100;
                character10.x = WIDTH / 2 +60;
                character10.y = HEIGHT / 2-350 ;
                character11.x = WIDTH / 2-120;
                character11.y = HEIGHT / 2-100;
                character1.image_path = al_load_bitmap("/Users/User/Desktop/anan.jpg");
                character2.image_path = al_load_bitmap("/Users/User/Desktop/mumu.jpg");
                character3.image_path = al_load_bitmap("/Users/User/Desktop/anan2.jpg");
                character4.image_path = al_load_bitmap("/Users/User/Desktop/mikey.jpg");
                character5.image_path = al_load_bitmap("/Users/User/Desktop/mumu2.jpg");
                character6.image_path = al_load_bitmap("/Users/User/Desktop/ancp.jpg");
                character7.image_path = al_load_bitmap("/Users/User/Desktop/mucp.jpg");
                character8.image_path = al_load_bitmap("/Users/User/Desktop/miney.png");
                character9.image_path = al_load_bitmap("/Users/User/Desktop/ananbig.jpg");
                character10.image_path = al_load_bitmap("/Users/User/Desktop/mumubig.jpg");
                character11.image_path = al_load_bitmap("/Users/User/Desktop/vsvs.jpg");
                character12.image_path = al_load_bitmap("/Users/User/Desktop/wini.png");
                character13.image_path = al_load_bitmap("/Users/User/Desktop/elsa.png");
                 image2=al_load_bitmap("/Users/User/Desktop/egg.gif");
                image3=al_load_bitmap("/Users/User/Desktop/finddie.jpg");
                image4=al_load_bitmap("/Users/User/Desktop/back.png");
                image5=al_load_bitmap("/Users/User/Desktop/back2.png");


background = al_load_bitmap("/Users/User/Desktop/mario.gif");

                //Initialize Timer
                timer3  = al_create_timer(1.0/6.0);
                timer4  = al_create_timer(1.0/100.0);
                timer5  = al_create_timer(1.0/6.0);
                timer6  = al_create_timer(1.0/30.0);
                al_register_event_source(event_queue, al_get_timer_event_source(timer3)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer4)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer5)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer6)) ;


                al_start_timer(timer3);
                al_start_timer(timer4);
                al_start_timer(timer5);
                al_start_timer(timer6);



        }
    if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }
    }
    else if(window==4){

            al_flip_display();
            al_clear_to_color(al_map_rgb(255,218,185));
            al_draw_text(font, al_map_rgb(255,69,0), 300, 420
            , ALLEGRO_ALIGN_CENTRE, "Tap blank key to Restart!!");
            al_draw_text(font, al_map_rgb(32,178,170), 300, 100
            , ALLEGRO_ALIGN_CENTRE, "GAME OVER ");
    al_draw_text(font, al_map_rgb(0,0,0), 300, 200
            , ALLEGRO_ALIGN_CENTRE, "ANAN WIN ");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 250
            , ALLEGRO_ALIGN_CENTRE, "SO MEAN ");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 280
            , ALLEGRO_ALIGN_CENTRE, "LOOK AT UR UGLY HEART ");
    al_draw_text(font, al_map_rgb(95,158,160), 300, 500
            , ALLEGRO_ALIGN_CENTRE, "Click x to End ");
            if(judge_next_window){
        judge_next_window=false;
        anattack=false;
        muattack=false;
        anwin=false;
        muwin=false;
        anbig=false;
        mubig=false;

        bigattack=0;
    bigdefense=0;
     muinix=0;
    muiniy=0;
    aninix=0;
    aniniy=0;
    munowx=0;
    munowy=0;
    annowx=0;
    annowy=0;
    k=0;
    j=0;
        attack=0;
        defense=0;
        mumucphurt=0;
        anancphurt=0;
        vs=0;

                character1.x = WIDTH / 2 - 300;
                character1.y = HEIGHT / 2 + 100;
                character2.x = WIDTH / 2 + 250;
                character2.y = HEIGHT / 2 + 100;
                character4.x = character1.x;
                character4.y = character1.y;
                character6.x = WIDTH / 2 - 380;
                character6.y = HEIGHT / 2 -300;
                character7.x = WIDTH / 2 + 50;
                character7.y = HEIGHT / 2 -307;
                character8.x = character2.x;
                character8.y = character2.y;
                character9.x = WIDTH / 2 -320;
                character9.y = HEIGHT / 2 -100;
                character10.x = WIDTH / 2 +60;
                character10.y = HEIGHT / 2-350 ;
                character11.x = WIDTH / 2-120;
                character11.y = HEIGHT / 2-100;


             window=2;

            }



        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }

    }
    else if(window==5){
            al_flip_display();
            al_clear_to_color(al_map_rgb(255,228,225));
             al_draw_text(font, al_map_rgb(255,69,0), 300, 420
            , ALLEGRO_ALIGN_CENTRE, "Tap blank key to Restart!!");
            al_draw_text(font, al_map_rgb(32,178,170), 300, 100
            , ALLEGRO_ALIGN_CENTRE, "GAME OVER ");
    al_draw_text(font, al_map_rgb(0,0,0), 300, 200
            , ALLEGRO_ALIGN_CENTRE, "MUMU WIN ");
            al_draw_text(font, al_map_rgb(0,0,0), 300, 250
            , ALLEGRO_ALIGN_CENTRE, "FULL OF KINDNESS ");
    al_draw_text(font, al_map_rgb(0,0,0), 300, 280
            , ALLEGRO_ALIGN_CENTRE, "LUCKY YOU ");
    al_draw_text(font, al_map_rgb(95,158,160), 300, 500
            , ALLEGRO_ALIGN_CENTRE, "Click x to End ");
           if(judge_next_window){
        judge_next_window=false;
        anattack=false;
        muattack=false;
        anwin=false;
        muwin=false;
        anbig=false;
        mubig=false;

        bigattack=0;
    bigdefense=0;
    muinix=0;
    muiniy=0;
    aninix=0;
    aniniy=0;
    munowx=0;
    munowy=0;
    annowx=0;
    annowy=0;
    k=0;
    j=0;
        attack=0;
        defense=0;
        mumucphurt=0;
        anancphurt=0;
        vs=0;

                character1.x = WIDTH / 2 - 300;
                character1.y = HEIGHT / 2 + 100;
                character2.x = WIDTH / 2 + 250;
                character2.y = HEIGHT / 2 + 100;
                character4.x = character1.x;
                character4.y = character1.y;
                character6.x = WIDTH / 2 - 380;
                character6.y = HEIGHT / 2 -300;
                character7.x = WIDTH / 2 + 50;
                character7.y = HEIGHT / 2 -307;
                character8.x = character2.x;
                character8.y = character2.y;
                character9.x = WIDTH / 2 -320;
                character9.y = HEIGHT / 2 -100;
                character10.x = WIDTH / 2 +60;
                character10.y = HEIGHT / 2-350 ;
                character11.x = WIDTH / 2-120;
                character11.y = HEIGHT / 2-100;
window=2;


            }
            if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }

    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_timer(timer2);
    al_destroy_bitmap(img);
    al_destroy_sample(song);
}
