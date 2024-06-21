
#ifndef player_h
#define player_h
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
class player
{
public:
    player(int HEIGHT);
    ~player();
    void updatePlayer(int width, int height);
    void drawPlayer();
    void MoveUp();
    void MoveDown();
    void rotate();
    int getWidth() {return frameWidth;}
    int getHeight() {return frameHeight;}
    int getX() {return x;}
    int getY() {return y;}
    void removeLife();
    int getLives() {return lives;}
    int getScore() {return score;}
    void addScore() {score++;}
private:
    int x;
    int y;
    int speed;
    int score;
    int lives;
    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationRows;
    int animationDirection;
    
    ALLEGRO_BITMAP *image;
    ALLEGRO_SAMPLE *sample;
};
#endif
