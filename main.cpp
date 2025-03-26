#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace sf;
using namespace std;

class Bullet 
{
public:
    CircleShape shape;
    Vector2f currentVelocity;
    float maxSpeed;

    Bullet(float radius = 5.f)
        : currentVelocity(0.f, 0.f), maxSpeed(10.f)
    {
        this->shape.setRadius(radius);
        this->shape.setFillColor(Color::Red);
    }
};

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
    window.setFramerateLimit(60);

    //Player
    CircleShape player(25.f);
    player.setFillColor(Color::White);

    //Enemy
    RectangleShape enemy;
    enemy.setFillColor(Color::Magenta);
    enemy.setSize(Vector2(50.f, 50.f));
    vector<RectangleShape> enemies;
    int enemySpawnCounter = 0;

    //Bullet
    Bullet b1;
    vector<Bullet> bullets;

    //Vector
    Vector2f playerCentre;
    Vector2f mousePosWindow;
    float arctangent;
    Vector2f aimDirNorm;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            //Update

            //Create Vector from player location to mouse location
            //Full equation for a normalized vector is: (cos(arctan((x1 - x2) / (y1 - y2))), sin(arctan((x1 - x2) / (y1 - y2)))))
            playerCentre = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
            mousePosWindow = Vector2f(Mouse::getPosition(window));
            arctangent = atan2f(mousePosWindow.x - playerCentre.x, mousePosWindow.y - playerCentre.y);
            aimDirNorm = Vector2f(cos(arctangent), sin(arctangent));
            
            //cout << aimDirNorm.x << " " << aimDirNorm.y << endl;

            //Player Movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                player.move({ -3.f, 0.f });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                player.move({ 3.f, 0.f });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                player.move({ 0.f, -3.f });
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                player.move({ 0.f, 3.f });
            }

            //Enemies
            if (enemySpawnCounter < 20)
            {
                enemySpawnCounter++;
            }
            if (enemySpawnCounter >= 20 && enemies.size() <20) 
            {
                enemy.setPosition(Vector2f(rand()% window.getSize().x, rand()% window.getSize().y));
                enemies.push_back(RectangleShape(enemy));
                enemySpawnCounter = 0;
            }

            //Shooting
            if (Mouse::isButtonPressed(Mouse::Button::Left))
            {
                b1.shape.setPosition(playerCentre);
                b1.currentVelocity = aimDirNorm * b1.maxSpeed;

                bullets.push_back(Bullet(b1));
            }

            for (size_t i = 0; i < bullets.size(); i++)
            {
                bullets[i].shape.move(bullets[i].currentVelocity);
                if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x)
                { //seperated into two loops for readability, checks to see if bullet is out of bounds
                    if (bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
                    {
                        bullets.erase(bullets.begin() + i);
                        cout << "should delete bullet" << endl;
                        
                    }
                }
                else
                {
                    for (size_t k = 0; k < enemies.size(); k++)
                    {
                        //collision check here
                    }
                }
            }



            //Draw
            window.clear();

            for (size_t i = 0; i < enemies.size(); i++)
            {
                window.draw(enemies[i]);
            }

            window.draw(player);

            for (size_t i = 0; i < bullets.size(); i++)
            {
                window.draw(bullets[i].shape);
            }
            window.display();
        }
    }
}