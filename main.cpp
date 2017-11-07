#include "SFML/Graphics.hpp"
using namespace sf;

int main() {

	//Colocar fondo
	Texture fondo;
	fondo.loadFromFile("sprites/piso.png");
	Sprite piso(fondo);
	Vector2u size2 = fondo.getSize();

	//Crear ventana
	RenderWindow window(VideoMode(800, 600), "Dragon VS Viking");
	Event boton;

	//Sprite calabera
	Texture calabera;
	calabera.loadFromFile("sprites/sprite1.png");
	IntRect rectSpriteCalabera(0, 0, 31, 48);
	//Rectangulo de sprite (0,0... -> posicion  ...31, 48) -> tamaño
	Sprite skull(calabera, rectSpriteCalabera);
	Vector2u size(31, 48);
	skull.setPosition(400, 300);
	Vector2f increment(0.4, 0.4);

	//Sprite dragon
	Texture dragonFrames;
	dragonFrames.loadFromFile("sprites/dragonFrames.png");
	IntRect rectSpriteDragon(0, 0, 190, 200); //Rectangulo de sprite (0,0... -> posicion  ...190, 200) -> tamaño
	Sprite dragon(dragonFrames, rectSpriteDragon);

	Clock clock;

	while (window.isOpen()) {
		while (window.pollEvent(boton)) {
			if (boton.type == Event::EventType::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() > 1.0f) {
			if (rectSpriteCalabera.left == 93)
				rectSpriteCalabera.left = 0;
			else
				rectSpriteCalabera.left += 31;
		}

		//movimiento de la calabera
		if ((skull.getPosition().x + (size.x / 2) > 800 && increment.x > 0)
			|| (skull.getPosition().x - (size.x / 2) < 0 && increment.x < 0)) {
			increment.x = -increment.x;
			skull.setScale(skull.getScale().x * -1, 1); //voltea horizontal
		}

		if ((skull.getPosition().y + (size.y / 2) > 600 && increment.y > 0)
			|| (skull.getPosition().y - (size.y / 2) < 0 && increment.y < 0)) {
			increment.y = -increment.y;
		}


		//Movimiento del dragon
		if (clock.getElapsedTime().asSeconds() > 0.4f) {
			if (rectSpriteDragon.left == 380)
				rectSpriteDragon.left = 0;
			else
				rectSpriteDragon.left += 190;

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				rectSpriteDragon.top = 600;
				dragon.setPosition(dragon.getPosition().x, dragon.getPosition().y - 40);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				rectSpriteDragon.top = 0;
				dragon.setPosition(dragon.getPosition().x, dragon.getPosition().y + 40);
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				rectSpriteDragon.top = 200;
				dragon.setPosition(dragon.getPosition().x - 40, dragon.getPosition().y);
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				rectSpriteDragon.top = 400;
				dragon.setPosition(dragon.getPosition().x + 40, dragon.getPosition().y);
			}

			dragon.setTextureRect(rectSpriteDragon);
			clock.restart();
		}

		skull.setPosition(skull.getPosition() + increment);

		window.clear();
		window.draw(piso);
		window.draw(skull);
		window.draw(dragon);
		window.display();

	}
}
