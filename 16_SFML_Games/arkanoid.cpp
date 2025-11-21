#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int const SCREEN_WIDTH = 520;
int const SCREEN_HEIGHT = 450;
int const FPS = 60;

int const BLOCK_WIDTH = 43;
int const BLOCK_HEIGHT = 20;
int const LENGTH = 10;

int const PAD_SPEED = 6;

sf::Vector2f paddlePos = sf::Vector2f(300.0f, 440.0f);

int arkanoid()
{
    srand(time(0));

    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid!");
    app.setFramerateLimit(FPS);

    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/arkanoid/block01.png");
    t2.loadFromFile("images/arkanoid/background.jpg");
    t3.loadFromFile("images/arkanoid/ball.png");
    t4.loadFromFile("images/arkanoid/paddle.png");

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(paddlePos);

    Sprite block[1000];

    int blockIndex = 0;

    for (int column = 1; column <= LENGTH; column++)
    {
        for (int row = 1; row <= LENGTH; row++)
        {
            block[blockIndex].setTexture(t1);
            block[blockIndex].setPosition(column * BLOCK_WIDTH, row * BLOCK_HEIGHT);
            blockIndex++;
        }
    }

    float dx=6, dy=5;
    float x=300, y=300;

    sf::Vector2f ballSpeed = sf::Vector2f(6.0f, 5.0f);
    sf::Vector2f ballPos = sf::Vector2f(300.0f, 300.0f);

    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
       }

        x+=dx;
        for (int i = 0; i < blockIndex; i++)
        {
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0);
                dx = -dx;
            }
        }

        y+=dy;
        for (int i = 0; i < blockIndex; i++)
        {
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0);
                dy = -dy;
            }
        }

        if (x < 0 || x > SCREEN_WIDTH)
        {
            dx = -dx;
        }

        if (y < 0 || y > SCREEN_HEIGHT)
        {
            dy = -dy;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            sPaddle.move(PAD_SPEED, 0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            sPaddle.move(-PAD_SPEED, 0);
        }

        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()))
        {
            dy = -(rand() % 5 + 2);
        }

        sBall.setPosition(x,y);

        app.clear();
        app.draw(sBackground);
        app.draw(sBall);
        app.draw(sPaddle);

        for (int i = 0; i < blockIndex; i++)
        {
            app.draw(block[i]);
        }

        app.display();
    }

  return 0;
}
