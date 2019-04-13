#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include <stdlib.h>
#include <time.h>

#include "Background.h"
#include "Carta.h"
#include "PilhaEncadeada.h"

#include <iostream>
using namespace std;

//Variaveis globais
const int WIDTH = 1080;
const int HEIGHT = 720;

Pilha <int> pCaipira;
Pilha <int> pDiabo;

int contador = 0;
int antCont = 13;
bool desempilhaOk = true;

bool venceu = false;

int caipiraScore = 0;
int diaboScore = 0;

enum STATE{TITLE, INSTRUCTIONS, PLAYING, END};

//Funcoes globais
void ChangeState(int &state, int newState);
char* caso(int);

int main(void){
	
	FreeConsole();
	
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	int state = -1;
	int posX = WIDTH / 2;
	int posY = HEIGHT / 2;
	int curTempo = 0;
	int tempoArb = 0;
	bool chegouTimer = false;
	bool isTimerAtivo = false;
	int cont[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	int tempoDesempilha = 0;
	int tempoDiabo = 0;

	//object variables
	Background back;
	Carta cartas[52];
	int tituloWidth = 0, instruWidth = 0, infoWidth = 0, playWidth = 0, infoMouseWidth = 0, playMouseWidth = 0, backWidth = 0, backMouseWidth = 0, bateuWidth = 0, winWidth = 0, loseWidth = 0;
	int tituloHeight = 0, instruHeight = 0, infoHeight = 0, playHeight = 0, infoMouseHeight = 0, playMouseHeight = 0, backHeight = 0,backMouseHeight = 0, bateuHeight = 0, winHeight = 0, loseHeight = 0;

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_SAMPLE *devil8bit;
	ALLEGRO_FONT *fontHB = NULL;
	ALLEGRO_FONT *fontHBaralho = NULL;
	ALLEGRO_FONT *fontDBaralho = NULL;
	ALLEGRO_FONT *fontDevil = NULL;
	ALLEGRO_BITMAP *backImage = NULL;
	ALLEGRO_BITMAP *cartasImage = NULL;
	ALLEGRO_BITMAP *tituloImage = NULL;
	ALLEGRO_BITMAP *instruImage = NULL;
	ALLEGRO_BITMAP *infoButton = NULL;
	ALLEGRO_BITMAP *infoMouse = NULL;
	ALLEGRO_BITMAP *playButton = NULL;
	ALLEGRO_BITMAP *playMouse = NULL;
	ALLEGRO_BITMAP *backButton = NULL;
	ALLEGRO_BITMAP *backMouse = NULL;
	ALLEGRO_BITMAP *area = NULL;
	ALLEGRO_BITMAP *hillbillyImage = NULL;
	ALLEGRO_BITMAP *devilImage = NULL;
	ALLEGRO_BITMAP *hillbillyBalloon = NULL;
	ALLEGRO_BITMAP *devilBalloon = NULL;
	ALLEGRO_BITMAP *hillbillyBaralho = NULL;
	ALLEGRO_BITMAP *devilBaralho = NULL;
	ALLEGRO_BITMAP *bateu = NULL;
	ALLEGRO_BITMAP *winImage = NULL;
	ALLEGRO_BITMAP *loseImage = NULL;

	//Initialization Functions
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	al_reserve_samples(1);

	devil8bit = al_load_sample("audio/devil8bit.ogg");
	
	backImage = al_load_bitmap("img/background.png");
	cartasImage = al_load_bitmap("img/spriteCartas.png");
	al_convert_mask_to_alpha(cartasImage, al_map_rgb(42, 111, 55));
	tituloImage = al_load_bitmap("img/titulo.png");
	instruImage = al_load_bitmap("img/instrucoes.png");
	infoButton = al_load_bitmap("img/info128.png");
	infoMouse = al_load_bitmap("img/infoMouse.png");
	playButton = al_load_bitmap("img/play128.png");
	playMouse = al_load_bitmap("img/playMouse.png");
	backButton = al_load_bitmap("img/backButton.png");
	backMouse = al_load_bitmap("img/backMouse.png");
	area = al_load_bitmap("img/area.png");
	hillbillyImage = al_load_bitmap("img/hillbilly.png");
	hillbillyBalloon = al_load_bitmap("img/hillbillyBalloon.png");
	hillbillyBaralho = al_load_bitmap("img/hillbillyBaralho.png");
	devilImage = al_load_bitmap("img/devil.png");
	devilBalloon = al_load_bitmap("img/devilBalloon.png");
	devilBaralho = al_load_bitmap("img/devilBaralho.png");
	bateu = al_load_bitmap("img/bateu.png");
	winImage = al_load_bitmap("img/win.png");
	loseImage = al_load_bitmap("img/lose.png");
	
	fontHB = al_load_font("fontes/BOOKOS.ttf", 52, 0);
	fontHBaralho = al_load_font("fontes/BOOKOS.ttf", 44, 0);
	fontDevil = al_load_font("fontes/MTCORSVA.ttf", 52, 0);
	fontDBaralho = al_load_font("fontes/MTCORSVA.ttf", 44, 0);
	
	tituloWidth =  al_get_bitmap_width(tituloImage);
	tituloHeight = al_get_bitmap_height(tituloImage);
	instruWidth = al_get_bitmap_width(instruImage);
	instruHeight = al_get_bitmap_height(instruImage);
	infoWidth = al_get_bitmap_width(infoButton);
	infoHeight = al_get_bitmap_height(infoButton);
	infoMouseWidth = al_get_bitmap_width(infoMouse);
	infoMouseHeight = al_get_bitmap_height(infoMouse);
	playWidth = al_get_bitmap_width(playButton);
	playHeight = al_get_bitmap_height(playButton);
	playMouseWidth = al_get_bitmap_width(playMouse);
	playMouseHeight = al_get_bitmap_height(playMouse);
	backWidth = al_get_bitmap_width(backButton); 
	backHeight = al_get_bitmap_height(backButton);
	backMouseWidth = al_get_bitmap_width(backMouse);
	backMouseHeight = al_get_bitmap_height(backMouse);
	bateuWidth = al_get_bitmap_width(bateu);
	bateuHeight = al_get_bitmap_height(bateu);
	winWidth = al_get_bitmap_width(winImage);
	winHeight = al_get_bitmap_height(winImage);
	loseWidth = al_get_bitmap_width(loseImage);
	loseHeight = al_get_bitmap_height(loseImage);

	srand(time(NULL));

	ChangeState(state, TITLE);

	back.InitBackground(0, 0, 1080, 720, backImage);
	
	int valorDaCarta = 0;
	int naipeDaCarta = 0;
	int randX, randY;
	
	for(int i = 0; i < 52; i++){
		if(i >= 0 && i <= 12){
			valorDaCarta = i;
			naipeDaCarta = 0;
		}else if(i > 12 && i <= 25){
			valorDaCarta = i % 13;
			naipeDaCarta = 1;
		}else if(i > 25 && i <= 38){
			valorDaCarta = i % 26;
			naipeDaCarta = 2;
		}else if(i > 38 && i < 52){
			valorDaCarta = i % 39;
			naipeDaCarta = 3;
		}
		randX = 400 + (rand() % 30) * 10;
		randY = 100 + (rand() % 20) * 10;
		cartas[i].InitCarta(i, valorDaCarta, naipeDaCarta, true, randX, randY, cartasImage);	
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_play_sample(devil8bit, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
			
			if(state == TITLE){
			}
			else if(state == PLAYING)
			{}
			else if(state == END)
			{}
			if(isTimerAtivo == true)
				curTempo++;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1){
				if(state == TITLE){
					if((posX >= WIDTH / 2 - infoWidth / 2 + 64) && (posX <= WIDTH / 2 - infoWidth / 2 + 64 + infoWidth) &&
						(posY >= 540 - infoHeight / 2) && (posY <= 540 - infoHeight / 2 + infoHeight)){
							ChangeState(state, INSTRUCTIONS);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
					if((posX >= WIDTH / 2 - infoWidth / 2 - 64) && (posX <= WIDTH / 2 - infoWidth / 2 - 64 + infoWidth) &&
						(posY >= 540 - infoHeight / 2) && (posY <= 540 - infoHeight / 2 + infoHeight)){
							ChangeState(state, PLAYING);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
				}else if(state == INSTRUCTIONS){
					if((posX >= WIDTH / 2 - infoWidth / 2) && (posX <= WIDTH / 2 - infoWidth / 2 + infoWidth) &&
						(posY >= 590 - infoHeight / 2) && (posY <= 590 - infoHeight / 2 + infoHeight)){
							ChangeState(state, PLAYING);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
					if((posX >= 210 - backWidth / 2) && (posX <= 210 - backWidth / 2 + backWidth) &&
						(posY >= 590 - backHeight / 2) && (posY <= 590 - backHeight / 2 + backHeight)){
							ChangeState(state, TITLE);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
				}else if(state == END){
					if((posX >= WIDTH / 2 - infoWidth / 2) && (posX <= WIDTH / 2 - infoWidth / 2 + infoWidth) &&
						(posY >= 590 - infoHeight / 2) && (posY <= 590 - infoHeight / 2 + infoHeight)){
							ChangeState(state, PLAYING);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
					if((posX >= 210 - backWidth / 2) && (posX <= 210 - backWidth / 2 + backWidth) &&
						(posY >= 590 - backHeight / 2) && (posY <= 590 - backHeight / 2 + backHeight)){
							ChangeState(state, TITLE);
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					}
				}
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			posX = ev.mouse.x;
			posY = ev.mouse.y;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		int jorge;
		if(redraw && al_is_event_queue_empty(event_queue)){
			redraw = false; 
						
			back.DrawBackground();
		/*	for(int i = 0; i < 52; i++){
				cartas[i].DrawCarta();	
			} */

			if(state == TITLE){
				al_draw_bitmap(tituloImage, WIDTH / 2 - tituloWidth / 2, 200 - tituloHeight / 2, 0);
				
				if((posX >= WIDTH / 2 - infoWidth / 2 + 64) && (posX <= WIDTH / 2 - infoWidth / 2 + 64 + infoWidth) &&
					(posY >= 540 - infoHeight / 2) && (posY <= 540 - infoHeight / 2 + infoHeight)){
						al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
						al_draw_bitmap(infoMouse, WIDTH / 2 - infoMouseWidth / 2 + 64, 540 - infoMouseHeight / 2, 0);
						al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2 - 64, 540 - playHeight / 2, 0);
				}else if((posX >= WIDTH / 2 - infoWidth / 2 - 64) && (posX <= WIDTH / 2 - infoWidth / 2 - 64 + infoWidth) &&
						(posY >= 540 - infoHeight / 2) && (posY <= 540 - infoHeight / 2 + infoHeight)){
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
							al_draw_bitmap(playMouse, WIDTH / 2 - playMouseWidth / 2 - 64, 540 - playMouseHeight / 2, 0);
							al_draw_bitmap(infoButton, WIDTH / 2 - infoWidth / 2 + 64, 540 - infoHeight / 2, 0);
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					al_draw_bitmap(infoButton, WIDTH / 2 - infoWidth / 2 + 64, 540 - infoHeight / 2, 0);
					al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2 - 64, 540 - playHeight / 2, 0);
				}
			}
			else if(state == INSTRUCTIONS){
				al_draw_bitmap(instruImage, WIDTH / 2 - instruWidth / 2, HEIGHT / 2 - instruHeight / 2, 0);
				
				if((posX >= WIDTH / 2 - infoWidth / 2) && (posX <= WIDTH / 2 - infoWidth / 2 + infoWidth) &&
					(posY >= 590 - infoHeight / 2) && (posY <= 590 - infoHeight / 2 + infoHeight)){
						al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
						al_draw_bitmap(playMouse, WIDTH / 2 - playMouseWidth / 2, 590 - playMouseHeight / 2, 0);
						al_draw_bitmap(backButton, 210 - playWidth / 2, 590 - playHeight / 2, 0);
				}else if((posX >= 210 - backWidth / 2) && (posX <= 210 - backWidth / 2 + backWidth) &&
						(posY >= 590 - backHeight / 2) && (posY <= 590 - backHeight / 2 + backHeight)){
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
							al_draw_bitmap(backMouse, 210 - playMouseWidth / 2, 590 - playMouseHeight / 2, 0);
							al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2, 590 - playHeight / 2, 0);
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					al_draw_bitmap(backButton, 210 - playWidth / 2, 590 - playHeight / 2, 0);
					al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2, 590 - playHeight / 2, 0);
				}
				
			}
			else if(state == PLAYING){
				int qCaipira;
				int qDiabo;
				pCaipira.quantidadeDeElementos(qCaipira);
				pDiabo.quantidadeDeElementos(qDiabo);
				al_draw_bitmap(area, 0, 520, 0);
				al_draw_bitmap(hillbillyImage, 20, 300, 0);
				al_draw_bitmap(devilImage, 849, 300, 0);
				al_draw_bitmap(hillbillyBaralho, 20 + 211 + 10, 300 + 200 - 130, 0);
				al_draw_bitmap(devilBaralho, 849 - 10 - 99, 300 + 200 - 130, 0);
				
				
				
				
				al_draw_textf(fontHBaralho, al_map_rgb(0, 0, 0), 20 + 211 + 66, 300 + 200 - 100, ALLEGRO_ALIGN_CENTRE, "%d", qCaipira);
				al_draw_textf(fontDBaralho, al_map_rgb(0, 0, 0), 849 - 10 - 59, 300 + 200 - 100, ALLEGRO_ALIGN_CENTRE, "%d", qDiabo);
					
				
				if(desempilhaOk){
					pCaipira.desempilha(jorge);
					contador = 1;
					al_draw_bitmap(hillbillyBalloon, 50, 108, 0);
					al_draw_textf(fontHB, al_map_rgb(0, 0, 0), 156, 152, ALLEGRO_ALIGN_CENTRE, "%s", caso(contador));
					desempilhaOk = false;
				}
				
				if(posY >= 520 && posY <= 720){
					cartas[jorge].setIsCartaDrawn(true);
					if(isTimerAtivo == false){
						curTempo = 0;
					}
					isTimerAtivo = true;
				}else if(isTimerAtivo == true && (cartas[jorge].getIsCartaDrawn())){
					curTempo = 0;
					isTimerAtivo = false;
				}
				
				if(curTempo >= 60){
					chegouTimer = true;
				}
				
				if(cartas[jorge].getIsCartaDrawn()){
					if(curTempo >= 60 || chegouTimer == true){
						cartas[jorge].DrawCarta();
						if(pCaipira.getTam() != pDiabo.getTam()){
							al_draw_bitmap(hillbillyBalloon, 50, 108, 0);
							al_draw_textf(fontHB, al_map_rgb(0, 0, 0), 156, 152, ALLEGRO_ALIGN_CENTRE, "%s", caso(contador));
						}else{
							al_draw_bitmap(devilBalloon, 819, 108, 0);
							al_draw_textf(fontDevil, al_map_rgb(0, 0, 0), 922, 152, ALLEGRO_ALIGN_CENTRE, "%s", caso(contador));
						}
						tempoDesempilha++;
						if(tempoDesempilha >= 59 && antCont == cartas[jorge].getValor()){
							venceu = false;
							ChangeState(state, END);
						}
						if(tempoDesempilha >= 60){
							desempilhaOk = true;
							if(desempilhaOk){
								if(pCaipira.getTam() == pDiabo.getTam() && (!pDiabo.vazia())){
									if(contador >= 13)
										contador = 0;
									if(antCont >= 13)
										antCont = 0;
									contador++;
									antCont++;
									pCaipira.desempilha(jorge);
									
								}else{
									if(contador >= 13)
										contador = 0;
									if(antCont >= 13)
										antCont = 0;
									contador++;
									antCont++;
									pDiabo.desempilha(jorge);
									
								}
								desempilhaOk = false;
								
								}
							tempoDesempilha = 0;
						}
					}else{
						desempilhaOk = false;
						tempoDesempilha = 0;
						
					}
							
						
					
				}
				if(cartas[jorge].getIsCartaDrawn() && chegouTimer == true){
					if((posX >= cartas[jorge].getX() - cartas[jorge].getFrameWidth() / 2) && (posX <= cartas[jorge].getX() - cartas[jorge].getFrameWidth() / 2 + cartas[jorge].getFrameWidth()) &&
					(posY >= cartas[jorge].getY() - cartas[jorge].getFrameHeight() / 2) && (posY <= cartas[jorge].getY() - cartas[jorge].getFrameHeight() / 2 + cartas[jorge].getFrameHeight())){
						al_draw_bitmap(bateu, cartas[jorge].getX() - bateuWidth / 2, cartas[jorge].getY() - bateuHeight / 2, 0);
						if(antCont == cartas[jorge].getValor()){
							venceu = true;
						
						}else{
							venceu = false;
						}
						if(tempoArb == 6)
							ChangeState(state, END);
						tempoArb++;
					}else{
						tempoArb = 0;
					}
				}
			}
			else if(state == END){
				curTempo = 0;
				tempoArb = 0;
				tempoDesempilha = 0;
				contador = 1;
				antCont = 13;
				pCaipira.desempilha(jorge);
				isTimerAtivo = false;
				cartas[jorge].setIsCartaDrawn(false);
				chegouTimer = false;
				
				if((posX >= WIDTH / 2 - infoWidth / 2) && (posX <= WIDTH / 2 - infoWidth / 2 + infoWidth) &&
					(posY >= 590 - infoHeight / 2) && (posY <= 590 - infoHeight / 2 + infoHeight)){
						al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
						al_draw_bitmap(playMouse, WIDTH / 2 - playMouseWidth / 2, 590 - playMouseHeight / 2, 0);
						al_draw_bitmap(backButton, 210 - playWidth / 2, 590 - playHeight / 2, 0);
				}else if((posX >= 210 - backWidth / 2) && (posX <= 210 - backWidth / 2 + backWidth) &&
						(posY >= 590 - backHeight / 2) && (posY <= 590 - backHeight / 2 + backHeight)){
							al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
							al_draw_bitmap(backMouse, 210 - playMouseWidth / 2, 590 - playMouseHeight / 2, 0);
							al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2, 590 - playHeight / 2, 0);
				}else{
					al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
					al_draw_bitmap(backButton, 210 - playWidth / 2, 590 - playHeight / 2, 0);
					al_draw_bitmap(playButton, WIDTH / 2 - playWidth / 2, 590 - playHeight / 2, 0);
				}
				
				if(venceu){
					al_draw_bitmap(winImage, WIDTH / 2 - winWidth / 2, HEIGHT / 2 - 60 - winHeight / 2, 0);
				}else{
					al_draw_bitmap(loseImage, WIDTH / 2 - loseWidth / 2, HEIGHT / 2 - 60 - loseHeight / 2, 0);
				}
				
				
				al_draw_textf(fontHBaralho, al_map_rgb(255, 153, 0), 3 * WIDTH / 4, 3 * HEIGHT / 4, ALLEGRO_ALIGN_CENTRE, "Jogador: %d", caipiraScore);
				al_draw_textf(fontDevil, al_map_rgb(236, 34, 47), 3 * WIDTH / 4, 3 * HEIGHT / 4 + 54, ALLEGRO_ALIGN_CENTRE, "Diabo: %d", diaboScore);
			}
		
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	
	al_destroy_sample(devil8bit);
	al_destroy_bitmap(backImage);
	al_destroy_bitmap(cartasImage);
	al_destroy_bitmap(tituloImage);
	al_destroy_bitmap(instruImage);
	al_destroy_bitmap(infoButton);
	al_destroy_bitmap(infoMouse);
	al_destroy_bitmap(playButton);
	al_destroy_bitmap(playMouse);
	al_destroy_bitmap(backButton);
	al_destroy_bitmap(backMouse);
	al_destroy_bitmap(area);
	al_destroy_bitmap(hillbillyImage);
	al_destroy_bitmap(devilImage);
	al_destroy_bitmap(hillbillyBalloon);
	al_destroy_bitmap(devilBalloon);
	al_destroy_bitmap(hillbillyBaralho);
	al_destroy_bitmap(devilBaralho);
	al_destroy_bitmap(bateu);
	al_destroy_bitmap(winImage);
	al_destroy_bitmap(loseImage);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(fontHB);
	al_destroy_font(fontHBaralho);
	al_destroy_font(fontDevil);
	al_destroy_font(fontDBaralho);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

void ChangeState(int &state, int newState){
	if(state == TITLE){
	}
	else if(state == PLAYING){
		pCaipira.desempilhaTudo();
		pDiabo.desempilhaTudo();
		if(venceu)
			caipiraScore++;
		else
			diaboScore++;
	}
	else if(state == INSTRUCTIONS){
	}
	else if(state == END){
	}

	state = newState;

	if(state == TITLE){
	}
	else if(state == PLAYING){
		contador = 1;
		antCont = 13;
		Pilha <int> pAux;
		Pilha <int> pEmbaralhada;
		for(int i = 0; i < 52; i++){
			pAux.empilha(i);
		}
		pEmbaralhada = *pAux.embaralha();
		int jorge;
		for(int i = 0; i < 26; i++){
			pEmbaralhada.desempilha(jorge);
			pCaipira.empilha(jorge);
			pEmbaralhada.desempilha(jorge);
			pDiabo.empilha(jorge);
		}
		desempilhaOk = true;
	}
	else if(state == INSTRUCTIONS){
	}
	else if(state == END){
	}
}

char* caso(int x){
	switch(x){
		case 1:
			return "A";
			break;
		case 2:
			return "2";
			break;
		case 3:
			return "3";
			break;
		case 4:
			return "4";
			break;
		case 5:
			return "5";
			break;
		case 6:
			return "6";
			break;
		case 7:
			return "7";
			break;
		case 8:
			return "8";
			break;
		case 9:
			return "9";
			break;
		case 10:
			return "10";
			break;
		case 11:
			return "J";
			break;
		case 12:
			return "Q";
			break;
		case 13:
			return "K";
			break;
	}
}
