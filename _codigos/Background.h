#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

class Background{
	
	public:
		Background();
		void InitBackground(float, float ,int , int, ALLEGRO_BITMAP *);
		void DrawBackground();
	
	private:
		float x;
		float y;
		int width;
		int height;
		ALLEGRO_BITMAP *image;
};
