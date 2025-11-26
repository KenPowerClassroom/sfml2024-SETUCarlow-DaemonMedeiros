#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int blockIndex = 0;
int const MAXBLOCKS = 100;

int const SCREEN_WIDTH = 520;
int const SCREEN_HEIGHT = 450;
int const FPS = 60;
int const BLOCK_WIDTH = 43;
int const BLOCK_HEIGHT = 20;
int const LENGTH = 10;
int const PAD_SPEED = 6;

Sprite sBackground, sBall, sPaddle;
Sprite block[MAXBLOCKS];

float dx = 6, dy = 5;
float x = 300, y = 300;

Vector2f paddlePos = Vector2f(300.0f, 440.0f);
Vector2f ballPos = Vector2f(300.0f, 300.0f);
Vector2f ballSpeed = Vector2f(6.0f, 5.0f);

void initTextures(Texture &t1, Texture &t2, Texture &t3,Texture &t4)
{
    t1.loadFromFile("images/arkanoid/block01.png");
    t2.loadFromFile("images/arkanoid/background.jpg");
    t3.loadFromFile("images/arkanoid/ball.png");
    t4.loadFromFile("images/arkanoid/paddle.png");

    sBackground.setTexture(t2);
    sBall.setTexture(t3);
    sPaddle.setTexture(t4);
}

void initBlockSprites(Texture &t1)
{
    sPaddle.setPosition(paddlePos);

    for (int column = 1; column <= LENGTH; column++)
    {
        for (int row = 1; row <= LENGTH; row++)
        {
            block[blockIndex].setTexture(t1);
            block[blockIndex].setPosition(column * BLOCK_WIDTH, row * BLOCK_HEIGHT);
            blockIndex++;
        }
    }
}

void checkBounds()
{
    if (x < 0 || x > SCREEN_WIDTH)
    {
        dx = -dx;
    }

    if (y < 0 || y > SCREEN_HEIGHT)
    {
        dy = -dy;
    }
}

void movePaddle()
{
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        sPaddle.move(PAD_SPEED, 0);
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        sPaddle.move(-PAD_SPEED, 0);
    }
}

void drawSprites(RenderWindow & t_app)
{
    t_app.clear();

    t_app.draw(sBackground);
    t_app.draw(sBall);
    t_app.draw(sPaddle);

    for (int i = 0; i < blockIndex; i++)
    {
        t_app.draw(block[i]);
    }

    t_app.display();
}

int arkanoid()
{
    Texture t1, t2, t3, t4;

    srand(time(0));

    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid!");
    app.setFramerateLimit(FPS);

    initTextures(t1, t2, t3, t4);
    initBlockSprites(t1);

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

        y += dy;
        for (int i = 0; i < blockIndex; i++)
        {
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0);
                dy = -dy;
            }
        }

        checkBounds();
        movePaddle();

        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()))
        {
            dy = -(rand() % 5 + 2);
        }

        sBall.setPosition(x,y);

        drawSprites(app);

    }

  return 0;
}