#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>

// Lớp Logic Player
class Player {
public:
    float x, y, speed;
    Player(float startX, float startY) : x(startX), y(startY), speed(5.0f) {}

    void moveLeft() { x -= speed; }
    void moveRight() { x += speed; }
};

// Lớp Logic Food
class Food {
public:
    float x, y, speed;
    Food() {
        reset();
        speed = 3.0f;
    }

    void reset() {
        x = static_cast<float>(rand() % 760); // Tọa độ X ngẫu nhiên
        y = 0.0f;                             // Rơi từ mép trên màn hình
    }

    void update() {
        y += speed;
        if (y > 600) reset(); // Rơi quá đáy thì reset lại
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // 1. Khởi tạo cửa sổ game 2D (800x600 px) - Cú pháp SFML 3.x
    sf::RenderWindow window(sf::VideoMode({800, 600}), "OOP C++ 2D Game Demo");
    window.setFramerateLimit(60); // Giới hạn 60 FPS

    // 2. Khởi tạo đối tượng
    Player player(375.0f, 520.0f);
    Food food;
    int score = 0;

    // 3. Khởi tạo Font và Text để hiển thị điểm
    sf::Font font;
    bool hasFont = font.openFromFile("arial.ttf"); 
    
    // Khởi tạo Text truyền trực tiếp Font vào constructor (Chuẩn SFML 3.x)
    sf::Text scoreText(font);
    if (hasFont) {
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition({10.0f, 10.0f});
    }

    // 4. Tạo hình ảnh đồ họa (Shapes)
    sf::RectangleShape playerSprite(sf::Vector2f({50.0f, 20.0f})); // Thanh người chơi
    playerSprite.setFillColor(sf::Color::Green);

    sf::CircleShape foodSprite(10.0f); // Viên thực phẩm
    foodSprite.setFillColor(sf::Color::Red);

    // VÒNG LẶP GAME (GAME LOOP)
    while (window.isOpen()) {
        // --- A. Xử lý sự kiện (Input) ---
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && player.x > 0)
            player.moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && player.x < 750)
            player.moveRight();

        // --- B. Cập nhật logic game ---
        food.update();

        // Kiểm tra va chạm (Player ăn Food)
        sf::FloatRect playerBounds({player.x, player.y}, {50.0f, 20.0f});
        sf::FloatRect foodBounds({food.x, food.y}, {20.0f, 20.0f});

        if (playerBounds.findIntersection(foodBounds)) {
            score += 10;
            food.reset();
        }

        // Cập nhật text hiển thị
        if (hasFont) {
            scoreText.setString("Score: " + std::to_string(score));
        }

        // Cập nhật vị trí các hình vẽ theo Logic (Cú pháp SFML 3.x)
        playerSprite.setPosition({player.x, player.y});
        foodSprite.setPosition({food.x, food.y});

        // --- C. Vẽ mọi thứ lên màn hình (Render) ---
        window.clear(sf::Color(30, 30, 30)); // Màn hình nền xám đen

        window.draw(playerSprite);
        window.draw(foodSprite);
        if (hasFont) window.draw(scoreText);

        window.display(); // Đẩy khung hình ra màn hình
    }

    return 0;
}