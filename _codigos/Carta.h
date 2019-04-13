#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class Carta{
	public:
		Carta();
		void InitCarta(int, int, int, bool, int, int, ALLEGRO_BITMAP *);
		void DrawCarta();
		void setValor(int);
		void setNaipe(int);
		void setVisivel(bool);
		void setX(int);
		void setY(int);
		void setIsCartaDrawn(bool);
		void setMaxFrame(int);
		void setCurFrame(int);
		void setFrameWidth(int);
		void setFrameHeight(int);
		void setImage(ALLEGRO_BITMAP *);
		int getValor();
		int getNaipe();
		bool getVisivel();
		int getX();
		int getY();
		bool getIsCartaDrawn();
		int getMaxFrame();
		int getCurFrame();
		int getFrameWidth();
		int getFrameHeight();
		ALLEGRO_BITMAP * getImage();
		
	private:
		int id;
		int valor;
		int naipe;
		bool visivel;
		int x;
		int y;
		bool isCartaDrawn;
		
		int maxFrame;
		int curFrame;
		int frameWidth;
		int frameHeight;
		ALLEGRO_BITMAP *image;
};
