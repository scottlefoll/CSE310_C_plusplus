#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

// Game window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NUM_ENEMIES = 5;
const int NUM_TOKENS = 5;
const float PLAYER_SPEED = 0.5f;
const float ENEMY_SPEED = 0.1f;
const float TOKEN_SPEED = 0.1f;

// Forward declaration of classes
class Player;
class Token;
class TokenController;
class Enemy;
class EnemyController;
class Score;


// Player class
class Player {
    public:
        Player(sf::Texture& texture) : m_sprite(texture)
        {
            m_sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            m_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        }

        void move(float x, float y)
        {
            m_sprite.move(x, y);
        }

        sf::Sprite& getSprite()
        {
            return m_sprite;
        }

    private:
        sf::Sprite m_sprite;
};

// Token class
class Token {
    public:
        Token(sf::Texture& texture) : m_sprite(texture)
        {
            m_sprite.setPosition(rand() % (WINDOW_WIDTH - 100) + 50, rand() % (WINDOW_HEIGHT - 100) + 50);
        }

        void respawn()
        {
            m_sprite.setPosition(rand() % (WINDOW_WIDTH - 100) + 50, rand() % (WINDOW_HEIGHT - 100) + 50);
        }

        sf::Sprite& getSprite()
        {
            return m_sprite;
        }

    private:
        sf::Sprite m_sprite;
};

// TokenController class
class TokenController {
    public:
        TokenController(sf::Texture& texture) : m_texture(texture) {
            std::srand(std::time(nullptr)); // Seed the random number generator
            for (int i = 0; i < NUM_TOKENS; i++) {
                m_tokens.push_back(Token(m_texture));
            }
        }

        void update() {
            // Update each token's position
            for (auto& token : m_tokens) {
                token.getSprite().move(-TOKEN_SPEED, 0.0f);
                // If a token goes off the left side of the screen, respawn it on the right side
                if (token.getSprite().getPosition().x < -100) {
                    token.respawn();
                }
            }
        }

        void draw(sf::RenderWindow& window) {
            for (auto& token : m_tokens) {
                window.draw(token.getSprite());
            }
        }

        bool checkCollision(const sf::FloatRect& bounds) {
            for (auto& token : m_tokens) {
                // Check for collision between player and token
                if (token.getSprite().getGlobalBounds().intersects(bounds)) {
                    token.respawn();
                    return true;
                }
            }
            return false;
        }

    private:
        std::vector<Token> m_tokens;
        sf::Texture& m_texture;
};

// Enemy class
class Enemy {
    public:
        Enemy(sf::Texture& texture) : m_sprite(texture) {
            m_sprite.setPosition(rand() % (WINDOW_WIDTH - 100) + 50, rand() % (WINDOW_HEIGHT - 100) + 50);
        }
        sf::Sprite& getSprite() {
            return m_sprite;
        }
    private:
        sf::Sprite m_sprite;
};

// Enemy Controller class
class EnemyController {
    public:
        EnemyController(sf::Texture& texture) : m_texture(texture) {
            std::srand(std::time(nullptr)); // Seed the random number generator
            for (int i = 0; i < NUM_ENEMIES; i++) {
                m_enemies.push_back(Enemy(m_texture));
            }
        }
        void update() {
            // Update each enemy's position
            for (auto& enemy : m_enemies) {
                enemy.getSprite().move(-ENEMY_SPEED, 0.0f);
                // If an enemy goes off the left side of the screen, respawn it on the right side
                if (enemy.getSprite().getPosition().x < -100) {
                    enemy.getSprite().setPosition(WINDOW_WIDTH + 100, rand() % (WINDOW_HEIGHT - 100) + 50);
                }
            }
        }
        void draw(sf::RenderWindow& window) {
            // Draw each enemy to the window
            for (auto& enemy : m_enemies) {
                window.draw(enemy.getSprite());
            }
        }
        bool checkCollision(const sf::FloatRect& bounds) {
            // Check for collision between the given bounds and each enemy
            for (auto& enemy : m_enemies) {
                if (enemy.getSprite().getGlobalBounds().intersects(bounds)) {
                    return true;
                }
            }
            return false;
        }
    private:
        std::vector<Enemy> m_enemies;
        sf::Texture& m_texture;
};

// Score class
class Score {
    public:
        Score(sf::Font& font) : m_text("", font, 20)
        {
            m_text.setFillColor(sf::Color::White);
            m_text.setPosition(10, 10);
        }

        void setScore(int score)
        {
            m_text.setString("Score: " + std::to_string(score));
        }

        sf::Text& getText()
        {
            return m_text;
        }

    private:
        sf::Text m_text;
};

// main function
int main()
{
    // Create the game window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Minion's Adventure");

    // Load the images
    sf::Texture playerTexture, tokenTexture, enemyTexture;
    playerTexture.loadFromFile("character_x.png");
    tokenTexture.loadFromFile("coin_x.png");
    enemyTexture.loadFromFile("enemy_1_x.png");

    // Load the font
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // Create game objects
    Player player(playerTexture);
    TokenController tokenController(tokenTexture);// create an EnemyController instance
    Score score(font);
    EnemyController enemyController(enemyTexture); // create an EnemyController instance


    // Set the starting score
    int currentScore = 0;

    // Start game loop
    while (window.isOpen())
    {
        // Events handler
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Move player sprite based on arrow keys
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(-PLAYER_SPEED, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(PLAYER_SPEED, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.move(0, -PLAYER_SPEED);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player.move(0, PLAYER_SPEED);
        }

        // Update game objects
        enemyController.update();
        tokenController.update();

        // Check for collision between player and enemy
        if (enemyController.checkCollision(player.getSprite().getGlobalBounds()))
        {
            currentScore = 0;
            score.setScore(currentScore);
            player.getSprite().setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        }

        // Check for collision between player and token
        if (tokenController.checkCollision(player.getSprite().getGlobalBounds()))
        {
            currentScore += 1;
            score.setScore(currentScore);
        }

        // Window Clear
        window.clear();

        // Update and draw the game objects
        enemyController.update(); // update the EnemyController instance
        window.draw(player.getSprite());
        enemyController.draw(window); // draw the EnemyController instance
        tokenController.draw(window); // draw the TokenController instance
        window.draw(score.getText());

        // Window Display
        window.display();
    }

    return 0;
}