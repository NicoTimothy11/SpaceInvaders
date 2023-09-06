#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle");

    // Circle shape
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(375, 275);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    
        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;

}