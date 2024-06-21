//Aidan Smagh
//Final Project

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "player.h"
#include "pipes.h"

int main(int argc, char **argv)
{
    const int WIDTH = 1600;
    const int HEIGHT = 1100;
    enum KEYS{UP, DOWN, SPACE};
    bool keys[3] = {false, false, false};
    
    bool beginning = false;
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    
    
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_SAMPLE *sample1 = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_BITMAP *fullHealth = NULL;
    ALLEGRO_BITMAP *fourHealth = NULL;
    ALLEGRO_BITMAP *threeHealth = NULL;
    ALLEGRO_BITMAP *twoHealth = NULL;

    
    //initialize the works
    if (!al_init()) {
        return -1;
    }
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(3);
    al_init_ttf_addon();
    al_init_font_addon();
    al_install_keyboard();
    al_init_image_addon();
    
    //background music and image
    sample1 = al_load_sample("background.wav");
    background = al_load_bitmap("background.png");
    fullHealth = al_load_bitmap("fullhealth.png");
    fourHealth = al_load_bitmap("4health.png");
    threeHealth = al_load_bitmap("3health.png");
    twoHealth = al_load_bitmap("2health.png");
    display = al_create_display(WIDTH, HEIGHT);
    font = al_load_font("Minecraft.ttf", 24, 0);
    
    //object variables
    player myPlayer(HEIGHT);
    pipes thePipes[5];
    

    
    
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    
    //init randomness
    srand(time(0));
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_play_sample(sample1, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    al_start_timer(timer);
    
    while(!done)
    {
        
        if (myPlayer.getLives() == 0) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_textf(font, al_map_rgb(0, 0, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Your final score is %i", myPlayer.getScore());
            al_flip_display();
            al_rest(10.0);
            return 0;
        }
        
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            if(keys[UP])
                myPlayer.MoveUp();
            if(keys[DOWN])
                myPlayer.MoveDown();
            
            for (int i = 0; i < 5; i++) {
                thePipes[i].startPipe(WIDTH, HEIGHT);
            }
            for (int i = 0; i < 5; i++) {
                thePipes[i].updatePipe(myPlayer);
            }
            for (int i = 0; i < 5; i++) {
                thePipes[i].collidePipe(myPlayer);
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }
        if (redraw && al_is_event_queue_empty(event_queue))
        {
            
            while (!beginning)
            {
                //al_draw_bitmap(background, 0, 0, 0);
                al_draw_text(font, al_map_rgb(0, 0, 255), WIDTH / 2, 300, ALLEGRO_ALIGN_CENTER, "Welcome to the game.");
                al_draw_text(font, al_map_rgb(0, 0, 255), WIDTH / 2, 400, ALLEGRO_ALIGN_CENTER, "Your goal is to dodge as many fireballs as you can without getting hit.");
                al_draw_text(font, al_map_rgb(0, 0, 255), WIDTH / 2, 500, ALLEGRO_ALIGN_CENTER, "You will have five lives to make it through all three levels, each level gets progressively harder.");
                al_draw_text(font, al_map_rgb(0, 0, 255), WIDTH / 2, 600, ALLEGRO_ALIGN_CENTER, "You can use the up and down arrow keys to maneuver, you can also hit the space bar to do a trick.");
                al_flip_display();
                al_rest(5.0);
                beginning = true;
                
            }
            
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 1075, ALLEGRO_ALIGN_LEFT, "Score = %i", myPlayer.getScore());
            al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH / 2, 1075, ALLEGRO_ALIGN_CENTER, "Lives remaining = %i", myPlayer.getLives());
            for (int i = 0; i < 5; i++) {
                al_draw_textf(font, al_map_rgb(255, 255, 255), WIDTH - 200, 1075, ALLEGRO_ALIGN_LEFT, "Level = %i", thePipes[i].getLevel());
            }
            al_draw_bitmap(background, 0, 0, 0);
            myPlayer.drawPlayer();
            myPlayer.updatePlayer(WIDTH, HEIGHT);
            for (int i = 0; i < 5; i++) {
                thePipes[i].drawPipe();
            }
            if (myPlayer.getLives() == 5) {
                al_draw_bitmap(fullHealth, WIDTH / 2 + 100, 1000, 0);
                al_convert_mask_to_alpha(fullHealth, al_map_rgb(255, 255, 255));
            }

            al_flip_display();
            
        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(background);
    al_destroy_timer(timer);
    al_destroy_display(display);
    return 0;
}
