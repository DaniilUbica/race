#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Car.h"
#include "Road.h"
#include "Barrier.h"

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
    float x1, y1, x2, y2;

    x1 = sin(obj1->getAngle()) * MAX_SPEED;
    y1 = cos(obj1->getAngle()) * MAX_SPEED;

    x2 = sin(obj2->getAngle()) * MAX_SPEED;
    y2 = cos(obj2->getAngle()) * MAX_SPEED;

    sf::Sprite sprite1 = obj1->getSprite();
    sf::Sprite sprite2 = obj2->getSprite();

    float dx = (sprite2.getPosition().x - sprite1.getPosition().x) / 10;
    float angle = obj1->getSpeed() * dx / (MAX_SPEED * 10);

    if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds())) {
        if (obj1->getMass() >= obj2->getMass()) {
            if (obj1->getY() > obj2->getY()) {
                obj2->setSpeed(obj1->getSpeed());
            }
            if (obj1->getY() < obj2->getY() && obj1->getSpeed() >= 0) {
                obj2->setSpeed(-obj1->getSpeed());
            }
            if (obj1->getY() < obj2->getY() && obj1->getSpeed() < 0) {
                obj2->setSpeed(obj1->getSpeed());
            }

            if (dx < 0 || (dx < 0 && obj1->getY() > obj2->getY())) {
                obj2->setAngle(obj2->getAngle() - (TURN_SPEED / 100));
            }
            if (dx > 0 || (dx > 0 && obj1->getY() > obj2->getY())) {
                obj2->setAngle(obj2->getAngle() + (TURN_SPEED / 100));
            }
        }

        if (obj1->getMass() < obj2->getMass()) {
            obj2->setSpeed(obj1->getSpeed() / 10 * obj2->getMass());
            obj1->setSpeed(-obj1->getSpeed() / obj1->getMass());

            if (dx < 0 || (dx < 0 && obj1->getY() > obj2->getY())) {
                obj2->setAngle(obj2->getAngle() - (TURN_SPEED / 100));
            }
            if (dx > 0 || (dx > 0 && obj1->getY() > obj2->getY())) {
                obj2->setAngle(obj2->getAngle() + (TURN_SPEED / 100));
            }
        }
    }
}

int main() {
    Barrier* b = new Barrier;
    b->setBarrier(300, 400);
    Barrier* b2 = new Barrier;
    b2->setBarrier(300, 300);

    textureRoad.loadFromFile("Assets/road.jpg");
    textureCar.loadFromFile("Assets/car.png");
    textureBarrier.loadFromFile("Assets/barrier.png");

    sf::Sprite spriteCar(textureCar), spriteRoad(textureRoad), spriteBarrier(textureBarrier);

    Car* player = new Car(spriteCar);
    Road road(spriteRoad, spriteBarrier, player);

    sf::View view(sf::Vector2f(player->getX(), player->getY()), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Race it");

    b->setSprite(spriteBarrier);
    b2->setSprite(spriteBarrier);

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
        b2->Update();
        checkCollision(player, b);
        checkCollision(player, b2);
        checkCollision(b, b2);
        checkCollision(b2, b);

        view.setCenter(SCREEN_WIDTH / 2, player->getY());

        window.setView(view);

        window.draw(road.getSprite().first);
        window.draw(road.getSprite().second);
        window.draw(player->getSprite());
        window.draw(b->getSprite());
        window.draw(b2->getSprite());

        window.display();
    }

    delete player;
    delete b;
    delete b2;

    return 0;
}