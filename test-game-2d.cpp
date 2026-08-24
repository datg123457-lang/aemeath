#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

class Player {
public:
    float x, y, speed;

    Player(float startX, float startY)
        : x(startX), y(startY), speed(5.0f) {}

    void moveLeft() {
        x -= speed;
    }

    void moveRight() {
        x += speed;
    }
};

class Food {
public:
    float x, y, speed;

    Food() : speed(3.0f) {
        reset();
    }

    void reset() {
        x = static_cast<float>(rand() % 760);
        y = 0.0f;
    }

    void update() {
        y += speed;

        if (y > 600.0f)
            reset();
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Tạo cửa sổ 800x600
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "OOP C++ 2D Game Demo"
    );

    window.setFramerateLimit(60);

    // Đối tượng game
    Player player(375.0f, 520.0f);
    Food food;

    int score = 0;

    // Font
    sf::Font font;
    bool hasFont = font.openFromFile("arial.ttf");

    // SFML 3 yêu cầu font khi tạo Text
    sf::Text scoreText(font);

    if (hasFont) {
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition({10.0f, 10.0f});
    }

    // Player
    sf::RectangleShape playerSprite(
        sf::Vector2f(50.0f, 20.0f)
    );

    playerSprite.setFillColor(sf::Color::Green);

    // Food
    sf::CircleShape foodSprite(10.0f);
    foodSprite.setFillColor(sf::Color::Red);

    // =========================
    // GAME LOOP
    // =========================
    while (window.isOpen()) {

        // Xử lý sự kiện
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Điều khiển Player
        if (
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
            && player.x > 0.0f
        ) {
            player.moveLeft();
        }

        if (
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
            && player.x < 750.0f
        ) {
            player.moveRight();
        }

        // Cập nhật Food
        food.update();

        // Kiểm tra va chạm
        sf::FloatRect playerBounds(
            {player.x, player.y},
            {50.0f, 20.0f}
        );

        sf::FloatRect foodBounds(
            {food.x, food.y},
            {20.0f, 20.0f}
        );

        if (playerBounds.findIntersection(foodBounds)) {
            score += 10;
            food.reset();
        }

        // Cập nhật Score
        if (hasFont) {
            scoreText.setString(
                "Score: " + std::to_string(score)
            );
        }

        // Cập nhật vị trí
        playerSprite.setPosition({
            player.x,
            player.y
        });

        foodSprite.setPosition({
            food.x,
            food.y
        });

        // Vẽ
        window.clear(sf::Color(30, 30, 30));

        window.draw(playerSprite);
        window.draw(foodSprite);

        if (hasFont) {
            window.draw(scoreText);
        }

        window.display();
    }

    return 0;
}