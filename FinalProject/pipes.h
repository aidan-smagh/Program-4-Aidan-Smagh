#include "player.h"
#ifndef PIPESH
#define PIPESH
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
class pipes
{
public:
    pipes();
    ~pipes();
    void drawPipe();
    void updatePipe(player &Player);
    void startPipe(int WIDTH, int HEIGHT);
    void collidePipe(player &Player);
    int getBoundX() {return boundX;}
    int getBoundY() {return boundY;}
    int getX() {return x;}
    int getY() {return y;}
    bool getLive() {return live;}
    bool setLive(bool l) {return live = l;}
    int getLevel() {return level;}
private:
    int x;
    int y;
    int boundX;
    int boundY;
    int speed;
    bool live;
    int level;
    float angle;
    ALLEGRO_BITMAP *image;
    ALLEGRO_SAMPLE *sample;
};
#endif

