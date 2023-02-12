#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <deque>

#include "Globals.h"
#include "Car.hpp"
#include "Road.hpp"
#include "Barrier.hpp"

sf::Texture textureCar;
sf::Texture textureRoad;
sf::Texture textureBarrier;

b2Vec2 gravity(0.0, 0.0);

b2World world(gravity);

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

int main() {
    Barrier b;
    b.setBarrier(60, 0, world, 1);
    Barrier b2;
    b2.setBarrier(200, 800, world, 1);

    textureRoad.loadFromFile("Assets/road.jpg");
    textureCar.loadFromFile("Assets/car.png");
    textureBarrier.loadFromFile("Assets/barrier.png");

    sf::Sprite spriteCar(textureCar), spriteRoad(textureRoad), spriteBarrier(textureBarrier);

    Car* player = new Car(spriteCar, world);
    Road road(spriteRoad, spriteBarrier, player, world);

    sf::View view(sf::Vector2f(player->getX(), player->getY()), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Race it");

    b.setSprite(spriteBarrier);
    b2.setSprite(spriteBarrier);

    //b.getBody()->SetGravityScale(0.3);
    b2.getBody()->SetGravityScale(0.0);
    player->_body->SetGravityScale(0.0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1 / 60.0, 8, 3);

        controllPlayer(player);

        window.clear(sf::Color::White);

        player->Update();
        road.Update(player);
        b.Update();
        b2.Update();

        std::cout << player->_body->GetPosition().x * SCALE << " " << player->_body->GetPosition().x * SCALE << "\n";

        view.setCenter(SCREEN_WIDTH / 2, player->getY());

        window.setView(view);

        window.draw(road.getSprite().first);
        window.draw(road.getSprite().second);
        window.draw(player->getSprite());
        window.draw(b.getSprite());
        window.draw(b2.getSprite());
        //window.draw(road.getBarrier().getSprite());

        //std::cout << player->getX() << " " << player->getY()
            //<< " " << player->getSpeed() << " " << road.getSprite().first.getPosition().y << road.getSprite().second.getPosition().y << "\n";

        window.display();
    }

    delete player;

    return 0;
}