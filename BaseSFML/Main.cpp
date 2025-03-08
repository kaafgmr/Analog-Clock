#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Clock", sf::Style::Titlebar);

    float middleX = window.getSize().x * 0.5f;
    float middleY = window.getSize().y * 0.5f;
    float radius = window.getSize().y * 0.45f;
    float DEG_TO_RAD = 0.0174533f;

    sf::Font font;
    font.loadFromFile("Fonts/digital-7.ttf");
    std::vector<sf::Text> HoursText;

    //hours Dots and text
    std::vector<sf::CircleShape> HourDots;
    int hours = 1;
    for (int i = 0; i < 360; i += 30)
    {
        sf::CircleShape Dot(10);
        Dot.setFillColor(sf::Color::White);
        Dot.setOrigin(Dot.getLocalBounds().width * 0.5f, Dot.getLocalBounds().height * 0.5f);
        float Dotangle = i * DEG_TO_RAD;
        Dot.setPosition(middleX + (sin(Dotangle) * (radius - 10)), middleY + (cos(Dotangle) * (radius - 10)));
        HourDots.push_back(Dot);

        float textAngle = (i-150) * DEG_TO_RAD * -1;
        sf::Text text(std::to_string(hours), font, 64);
        text.setOrigin(text.getGlobalBounds().width * 0.5f, text.getGlobalBounds().height * 0.5f);
        text.setPosition(middleX + (sin(textAngle) * (radius - 50)), middleY + (cos(textAngle) * (radius - 50) - 20));
        HoursText.push_back(text);
        hours++;
    }

    //seconds Circle
    sf::CircleShape SecondsCircle(8);
    SecondsCircle.setOrigin(SecondsCircle.getLocalBounds().width * 0.5f, SecondsCircle.getLocalBounds().height * 0.5f);
    SecondsCircle.setPosition(middleX, middleY);
    SecondsCircle.setFillColor(sf::Color(255,48,80));
    SecondsCircle.setOutlineThickness(4);

    //second Hand
    sf::RectangleShape secH(sf::Vector2f(radius, 2));
    secH.setFillColor(sf::Color(255, 48, 80));
    secH.setOrigin(50, secH.getLocalBounds().height * 0.5f);
    secH.setPosition(sf::Vector2f(middleX, middleY));

    //minute Hand
    sf::RectangleShape minH(sf::Vector2f(radius * 0.7f, 10));
    minH.setOrigin(0, minH.getLocalBounds().height * 0.5f);
    minH.setPosition(sf::Vector2f(middleX, middleY));


    //hour Hand
    sf::RectangleShape HH(sf::Vector2f(radius * 0.5f, 10));
    HH.setFillColor(sf::Color::Transparent);
    HH.setOrigin(0, HH.getLocalBounds().height * 0.5f);
    HH.setOutlineThickness(4);
    HH.setPosition(sf::Vector2f(middleX, middleY));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        //Getting local time
        time_t Rawtime;
        time(&Rawtime);
        struct tm* realTime;
        realTime = localtime(&Rawtime);

        int seconds = realTime->tm_sec;
        int minutes = realTime->tm_min;
        int hours = realTime->tm_hour;

        int angle = (6 * seconds) - 90;  // 360 / 60 = 6   6 degres for every second and -90 to rotate it 90 degres counterclockwise
        secH.setRotation((float)angle);

        angle = (6 * minutes) - 90;
        minH.setRotation((float)angle);

        angle = (30 * (hours - 12)) - 90;
        HH.setRotation((float)angle);

        window.clear();

        window.draw(minH);
        window.draw(HH);
        window.draw(SecondsCircle);
        for (int i = 0; i < HourDots.size(); i++)
        {
            window.draw(HourDots[i]);
            window.draw(HoursText[i]);
        }
        window.draw(secH);

        window.display();
    }

    return 0;
}