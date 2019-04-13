#include "Carta.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

Carta::Carta(){
	this->id = 0;
	this->valor = 0;
	this->naipe = 0;
	this->visivel = false;
	this->x = 0;
	this->y = 0;
	this->isCartaDrawn = false;
	
	this->maxFrame = 0;
	this->curFrame = 0;
	this->frameWidth = 100;
	this->frameHeight = 140;
	this->image = NULL;
}

void Carta::InitCarta(int id, int valor, int naipe, bool visivel, int x, int y, ALLEGRO_BITMAP *image){
	this->id = id;
	this->valor = valor;
	this->naipe = naipe;
	this->visivel = visivel;
	this->x = x;
	this->y = y;
	this->isCartaDrawn = false;
	this->maxFrame = 13;
	this->curFrame = valor;
	this->frameWidth = 100;
	this->frameHeight = 140;
	this->image = image;
}

void Carta::DrawCarta(){
	
	int fx = valor * frameWidth;
	int fy = naipe * frameHeight;
	
	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Carta::setValor(int valor){
	this->valor = valor;
}

void Carta::setNaipe(int naipe){
	this->naipe = naipe;
}

void Carta::setVisivel(bool visivel){
	this->visivel = visivel;
}

void Carta::setX(int x){
	this->x = x;
}

void Carta::setY(int y){
	this->y = y;
}

void Carta::setIsCartaDrawn(bool isCartaDrawn){
	this->isCartaDrawn = isCartaDrawn;
}

int Carta::getValor(){
	return this->valor;
}

int Carta::getNaipe(){
	return this->naipe;
}

bool Carta::getVisivel(){
	return this->visivel;
}

int Carta::getX(){
	return this->x;
}

int Carta::getY(){
	return this->y;
}

bool Carta::getIsCartaDrawn(){
	return this->isCartaDrawn;
}

void Carta::setMaxFrame(int maxFrame){
	this->maxFrame= maxFrame;
}
void Carta::setCurFrame(int curFrame){
	this->curFrame = curFrame;
}
void Carta::setFrameWidth(int frameWidth){
	this->frameWidth = frameWidth;
}
void Carta::setFrameHeight(int frameHeight){
	this->frameHeight = frameHeight;
}
void Carta::setImage(ALLEGRO_BITMAP * image){
	this->image = image;
}
int Carta::getMaxFrame(){
	return maxFrame;
}
int Carta::getCurFrame(){
	return curFrame;
}
int Carta::getFrameWidth(){
	return frameWidth;
}
int Carta::getFrameHeight(){
	return frameHeight;
}
ALLEGRO_BITMAP * Carta::getImage(){
	return image;	
}
