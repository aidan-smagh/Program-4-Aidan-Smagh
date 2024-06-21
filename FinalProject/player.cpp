#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "player.h"
#include <iostream>

player::~player()
{
    al_destroy_bitmap(image);
}
player::player(int HEIGHT)
{
    
    image = al_load_bitmap("bird.png");
    al_convert_mask_to_alpha(image, al_map_rgb(255, 255, 255));
    
    sample = al_load_sample("hit.wav");
    
    x = 300;
    y = 0;
    speed = 15;
    lives = 5;
    
    
    maxFrame = 3;
    curFrame = 0;
    frameCount = 0;
    frameDelay = 10;
    frameWidth = 200;
    frameHeight = 160;
    animationColumns = 5;
    animationRows = 0;
    animationDirection = 1;
    

}
void player::drawPlayer()
{
    int fx = (curFrame % animationColumns) * frameWidth;
    int fy = (curFrame / animationColumns) * frameHeight;
    
    al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x, y, 0);
    
}
void player::updatePlayer(int width, int height)
{
    if (++frameCount >= frameDelay) {
        curFrame += animationDirection;
        if (curFrame >= maxFrame) {
            curFrame = 0;
        } else if (curFrame <= 0) {
            curFrame = maxFrame - 1;
        }
        frameCount = 0;
    }
}
void player::MoveUp()
{
    y -= speed;
    if (y < 0) {
        y = 0;
    }
}
void player::MoveDown()
{
    y += speed;
    if (y > 800) {
        y = 800;
    }
}
void player::removeLife()
{
    lives--;
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}
