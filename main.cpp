#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <random>
#include <iostream>

#define dg(x) cout << #x << " : " << (x) << "\n";

using namespace std;
using namespace sf;
int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 800), "Basket Game");

    Font f, f2;
    sf::Texture apple, basket, bg, GameOverPhoto;
    if (!apple.loadFromFile("apple.png")){
        cout << "Failed Loading File" << endl;
        system("Pause");
    }
    if (!basket.loadFromFile("basket.png")){
        cout << "Failed Loading Image" << endl;
        system("Pause");
    }
    if (!bg.loadFromFile("background.jpeg")){
        cout << "Failed Loading Image" << endl;
        system("Pause");
    }
    if (!GameOverPhoto.loadFromFile("GameOver.png")){
        cout << "Failed Loading Image" << endl;
        system("Pause");
    }
    if (!f.loadFromFile("KolkerBrush-Regular.ttf")){
        cout << "Error Loading Font" << endl;
        system("Pause");
    }
    if (!f2.loadFromFile("CormorantUpright-Bold.ttf")){
        cout << "Error Loading Font" << endl;
    }

    int CurrScore = 0, maxScore = 0, BasketY, BasketX, AppleY, AppleX;
    Text text_score, text_maxScore, toRestart;
    text_score.setFont(f), text_maxScore.setFont(f), toRestart.setFont(f2);
    text_score.setPosition(40,15), text_maxScore.setPosition(550, 15), toRestart.setPosition(150, 400);
//    toRestart.setColor(Color::Green);
    toRestart.setOutlineColor(Color(0, 0, 0));
    toRestart.setOutlineThickness(5);
    text_score.setString("Score: " + to_string(CurrScore));
    text_maxScore.setString("Max Score: " + to_string(maxScore));
    toRestart.setString("Press Space to restart the game");
    text_score.setCharacterSize(60), text_maxScore.setCharacterSize(60), toRestart.setCharacterSize(40);

    uniform_int_distribution<int> TheRange(5, 750);
    random_device rd;
    mt19937 randomNumbers(rd());
    Music m;
    m.openFromFile("audio_Game.ogg");
    m.play();

    Sprite SpApple(apple), SpBasket(basket), SpBg(bg), SpGameOver(GameOverPhoto);
    SpGameOver.scale(.18, .18);
    SpGameOver.setPosition(200, 100);
    SpApple.scale(0.1, 0.1);
    SpApple.setPosition(TheRange(randomNumbers), 0);
    SpBasket.scale(0.2f,0.2f);
    SpBasket.setPosition(0,600);
    SpBg.scale(1.15,.65);
    Vector2f currPos = SpApple.getPosition();
    sf::Event ev;
    bool gameOver = false;
    while (app.isOpen())
    {
        SpApple.move(0, 0.1);
        if (SpApple.getPosition().y >= 680 && !gameOver){
            maxScore = max(maxScore, CurrScore);
            gameOver = true;
        }

        while (app.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                app.close();
            else if (ev.type == Event::KeyPressed){
                if (ev.key.code == Keyboard::Right && !gameOver && SpBasket.getPosition().x <= 660)
                    SpBasket.move(20,0);
                else if (ev.key.code == Keyboard::Left && !gameOver && SpBasket.getPosition().x >= 1)
                    SpBasket.move(-20,0);
                else if (ev.key.code == Keyboard::Space){
                    CurrScore = 0;
                    SpApple.setPosition(TheRange(randomNumbers), 0);
                    gameOver = false;
                }

            }
        }
        BasketX = SpBasket.getPosition().x, BasketY = SpBasket.getPosition().y;
        AppleX = SpApple.getPosition().x, AppleY = SpApple.getPosition().y;
            if (AppleY >= 650 && AppleY <= 660 && AppleX >= BasketX - 10 && AppleX <= BasketX + 95)
                CurrScore++, SpApple.setPosition(TheRange(randomNumbers), 0);
        app.clear();

        app.draw(SpBg);
        app.draw(SpApple);
        app.draw(SpBasket);
        text_score.setString("Score: " + to_string(CurrScore));
        text_maxScore.setString("Max Score: " + to_string(maxScore));
        app.draw(text_score);
        app.draw(text_maxScore);
        if (gameOver)
            app.draw(SpGameOver), app.draw(toRestart);

        app.display();


    }
}
