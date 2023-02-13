#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

#include "Globals.h"
#include "Car.hpp"
#include "Road.hpp"
#include "Barrier.hpp"

sf::Texture textureCar;
sf::Texture textureRoad;
sf::Texture textureBarrier;

void controllPlayer(Car* player) {
    player->setDirection(STOP);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player->setDirection(UP);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player->setDirection(DOWN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->setDirection(LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->setDirection(RIGHT);
    }
}

void checkCollision(GameObject* obj1, GameObject* obj2) {
 
}

int main() {
    Barrier* b = new Barrier;
    b->setBarrier(60, 0);
    Barrier b2;
    b2.setBarrier(200, 800);

    textureRoad.loadFromFile("Assets/road.jpg");
    textureCar.loadFromFile("Assets/car.png");
    textureBarrier.loadFromFile("Assets/barrier.png");

    sf::Sprite spriteCar(textureCar), spriteRoad(textureRoad), spriteBarrier(textureBarrier);

    Car* player = new Car(spriteCar);
    Road road(spriteRoad, spriteBarrier, player);

    sf::View view(sf::Vector2f(player->getX(), player->getY()), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Race it");

    b->setSprite(spriteBarrier);
    b2.setSprite(spriteBarrier);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        controllPlayer(player);

        window.clear(sf::Color::White);

        player->Update();
        road.Update(player);
        b->Update();
        b2.Update();
        checkCollision(player, b);

        view.setCenter(SCREEN_WIDTH / 2, player->getY());

        window.setView(view);

        window.draw(road.getSprite().first);
        window.draw(road.getSprite().second);
        window.draw(player->getSprite());
        window.draw(b->getSprite());
        window.draw(b2.getSprite());

        //std::cout << player->getX() << " " << player->getY()
            //<< " " << player->getSpeed() << " " << road.getSprite().first.getPosition().y << road.getSprite().second.getPosition().y << "\n";

        window.display();
    }

    delete player;

    return 0;
}