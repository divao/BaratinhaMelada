#include "Background.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

const int WIDTH = 1080;
const int HEIGHT = 720;

Background::Background(){
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->image = NULL;
}


void Background::InitBackground(float x, float y,int width, int height, ALLEGRO_BITMAP *image){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->image = image;
}

void Background::DrawBackground(){
	al_draw_bitmap(image, x, y, 0);

	if(x + width < WIDTH)
		al_draw_bitmap(image, x + width, y, 0);
}
