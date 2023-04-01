// 2dGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Entity {
public:
    float x;
    float y;
    int width;
    int height;
    Entity(float x, float y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;

    }
};

class Platform :Entity {
public:
    RectangleShape rectangle;
    Platform(float x, float y, int width, int height) :Entity(x, y, width, height) {
        rectangle.setFillColor(sf::Color(66, 245, 179));
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setPosition(sf::Vector2f(x, y));
    }

    bool collide(float x, float y, float width, float height) {
        if (this->x < x + width && this->x + this->width > x && this->y < y + height && this->y + this->height > y) {
            return true;
        }
        else {
            return false;
        }
    }
        // right/left of platform 
    bool collideRight(float x, float y, float width, float height) {
        if (this->x + this->width > x && this->x + this->width/2 < x + width && this->y + 1 < y + height && this->y + this->height - 1 > y) {
            return true;
        }
        else {
            return false;
        }
    }
    bool collideLeft(float x, float y, float width, float height) {
        if (this->x < x + width && this->x + this->width/2 > x && this->y + 1 < y + height && this->y + this->height - 1 > y) {
            return true;
        }
        else {
            return false;
        }
    }


private:

};


class Player:Entity {
public:
    bool grounded = false;
    int score;
    float speed;
    float gravity = 0;
    RectangleShape rectangle;
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    Player(float x, float y, int width, int height, float speed) :Entity(x, y, width, height) {
        score = 0;
        this->speed = speed;
        rectangle.setFillColor(sf::Color(245, 117, 66));
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setPosition(sf::Vector2f(x, y));
        movingLeft = false;
        movingRight = false;
        movingUp = false;
    }
    void update(Time dt, Platform platforms[], int platformLength) {
        
        for (int i = 0; i < platformLength; i++) {
            if (platforms[i].collide(this->x, this->y, this->width, this->height) && gravity > 0) {
                gravity = 0;
                this->grounded = true;
            }
            if (platforms[i].collideRight(this->x, this->y, this->width, this->height) && movingLeft) {
                movingRight = true;
                cout << "collideRight" << endl;
                break;
            }
            else if (platforms[i].collideLeft(this->x, this->y, this->width, this->height) && movingRight) {
                movingLeft = true;
                cout << "collideLeft" << endl;
                break;
            }
        }
        if (movingLeft) {
            this->x -= speed * dt.asSeconds()*2;
        }
        if (movingRight) {
            this->x += speed * dt.asSeconds()*2;
        }
        if (movingUp) {
            this->gravity = -100;
            this->grounded = false;
        }

        /*if (this->y > 1000) {
            this->y = 500;
            this->x = 50;
        }
        */

        this->y += gravity * dt.asSeconds();
        this->gravity += 0.009;
        
        int b = 10;

        
        



      
        rectangle.setPosition(sf::Vector2f(this->x, this->y));

    }

};



void gameLoop(RenderWindow& window) {
    Text hud;
    Player player(50, 500, 20, 20, 150);
    int platformLength = 5;
    Platform platforms[] = {
        Platform(0, 650, 300, 30),
        Platform(500, 650, 200, 30),
        Platform(900, 650, 400, 30),
        Platform(1500, 650, 300, 30),
        Platform(1800, 650, 100, 30),
        /*Platform(0, 350, 300, 30),
        Platform(500, 350, 200, 30),
        Platform(900, 350, 400, 30),
        Platform(1500, 350, 300, 30),
        Platform(1800, 350, 100, 30)
        */
    };

    
    
    Clock clock;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.movingLeft = true;
            player.movingRight = false;
        }
        else {
            player.movingLeft = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.movingRight = true;
            player.movingLeft = false;
        }
        else {
            player.movingRight = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::W) && player.grounded) {
            player.movingUp = true;
        }
        else {
            player.movingUp = false;
        }
        Time dt = clock.restart();
        player.update(dt, platforms, platformLength);
        window.clear();
        window.draw(player.rectangle);
        for (int i = 0; i < platformLength; i++) {
            window.draw(platforms[i].rectangle);
        }
        window.display();
    }
}

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "2dGame", Style::Fullscreen);
    gameLoop(window);
}

