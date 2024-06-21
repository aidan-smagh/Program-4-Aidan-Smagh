#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "pipes.h"

pipes::pipes()
{
    image = al_load_bitmap("fireball.png");
    al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
    
    sample = al_load_sample("levelup.wav");
    
    live = false;
    speed = 6;
    boundX = al_get_bitmap_width(image);
    boundY = al_get_bitmap_height(image);
    x = 50;
    y = 50;
    angle = 0;
    
    
}
pipes::~pipes()
{
    al_destroy_bitmap(image);
}
void pipes::drawPipe()
{
    if (live)
    {
        //al_draw_rotated_bitmap(image, x, y, x, y, angle, 0);
        al_draw_bitmap(image, x, y, 0);
        //angle += 0.001;
    }
}
void pipes::startPipe(int WIDTH, int HEIGHT)
{
    if (!live)
    {
        if (rand() % 100 == 0)
        {
            live = true;
            x = WIDTH;
            y = rand() % (1000 - boundY);
        }
    }
}
void pipes::updatePipe(player &Player)
{
    if (live)
    {
        x -= 6;
        level = 1;
        if (Player.getScore() > 15) {
            if (Player.getScore() == 16) {
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            x -= 12;
            level = 2;
        }
        if (Player.getScore() > 40) {
            if (Player.getScore() == 41) {
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            x -= 16;
            level = 3;
        }
    }
}
void pipes::collidePipe(player &Player)
{
    if (live)
    {
        if( x + 20 < Player.getX() + Player.getWidth() &&
            x  - 20 > Player.getX() - Player.getWidth() &&
            y  + 20 < Player.getY() + Player.getHeight() &&
            y  - 20 > Player.getY() - Player.getHeight())
        {
            Player.removeLife();
            live = false;
        }
        else if (x < 0)
        {
            live = false;
            Player.addScore();
        }
    }
}
