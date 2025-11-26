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

void initSprites(Texture &t1)
{
    sPaddle.setPosition(paddlePos);
    sBall.setPosition(ballPos);

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
    if (ballPos.x < 0 || ballPos.x > SCREEN_WIDTH)
    {
        ballSpeed.x = -ballSpeed.x;
    }

    if (ballPos.y < 0 || ballPos.y > SCREEN_HEIGHT)
    {
        ballSpeed.y = -ballSpeed.y;
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

void doesBallIntersectBlock(float &t_pos, float &t_speed)
{
    for (int i = 0; i < blockIndex; i++)
    {
        if (FloatRect(ballPos.x + 3, ballPos.y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
        {
            block[i].setPosition(-100, 0);
            t_speed = -t_speed;
        }
    }
}

int arkanoid()
{
    Texture t1, t2, t3, t4;

    srand(time(0));

    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid!");
    app.setFramerateLimit(FPS);

    initTextures(t1, t2, t3, t4);
    initSprites(t1);

    while (app.isOpen())
    {
       Event event;
       while (app.pollEvent(event))
       {
         if (event.type == Event::Closed)
             app.close();
       }

        ballPos.x += ballSpeed.x;
        doesBallIntersectBlock(ballPos.x, ballSpeed.x);

        ballPos.y += ballSpeed.y;
        doesBallIntersectBlock(ballPos.y, ballSpeed.y);

        checkBounds();
        movePaddle();

        if (FloatRect(ballPos.x, ballPos.y, 12, 12).intersects(sPaddle.getGlobalBounds()))
        {
            ballSpeed.y = -(rand() % 5 + 2);
        }

        sBall.setPosition(ballPos);

        drawSprites(app);

    }

  return 0;
}