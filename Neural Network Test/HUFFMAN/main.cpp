#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>

const float NEURON_RADIUS = 20.f;
const float CONNECTION_WIDTH = 4.f;

enum class NeuronType {
    GoodGuy,
    BadGuy
};


class Neuron {
public:
    sf::Vector2f position;
    sf::Sprite sprite;
    NeuronType type;  // Added NeuronType member

    Neuron(float x, float y, const sf::Texture& texture, NeuronType type) : position(x, y), type(type) {
        sprite.setTexture(texture);
        sprite.setOrigin(NEURON_RADIUS, NEURON_RADIUS);
        sprite.setPosition(position);
        sprite.setScale(0.3, 0.3);
    }

    bool contains(const sf::Vector2f& point) const {
        return sprite.getGlobalBounds().contains(point);
    }

    void move(const sf::Vector2f& displacement) {
        position += displacement;
        sprite.setPosition(position);
    }
};

class NeuralNetwork {
private:
    std::vector<std::vector<Neuron>> layers;
    std::vector<sf::VertexArray> connections;
    std::vector<sf::Color> connectionColors;
    Neuron* selectedNeuron = nullptr;
    bool mouseReleased = true;  // Added variable to track mouse release

    void handleMouseInput(sf::RenderWindow& window) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            if (selectedNeuron) {
                selectedNeuron->move(mousePos - selectedNeuron->position);
                updateConnections();
                mouseReleased = false;  // Mouse is being pressed
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
        {
            // Create a new neuron on right-click
            if (mouseReleased)
            {
                createNewNeuronBad(mousePos);
                mouseReleased = false;
            }
        }
        else
        {
            if (!mouseReleased) 
            {  // Check if the mouse was just released
                updateConnections();
                mouseReleased = true;  // Mouse is now released
            }

            selectedNeuron = nullptr;

            for (auto& layer : layers) {
                for (auto& neuron : layer) {
                    if (neuron.contains(mousePos)) {
                        selectedNeuron = &neuron;
                        break;
                    }
                }
                if (selectedNeuron) {
                    break;
                }
            }
        }
    }

    void createNewNeuronBad(const sf::Vector2f& position)
    {
        // Assuming a new neuron is added to the first layer
        layers[0].emplace_back(Neuron(position.x, position.y, *layers[0][0].sprite.getTexture(), NeuronType::BadGuy));
        updateConnections();
    }

    void createNewNeuronGood(const sf::Vector2f& position)
    {
        // Assuming a new neuron is added to the first layer
        layers[0].emplace_back(Neuron(position.x, position.y, *layers[0][0].sprite.getTexture(), NeuronType::GoodGuy));
        updateConnections();
    }

    void updateConnections() {
        connections.clear();
        initializeColors();

        for (size_t i = 0; i < layers.size() - 1; ++i) {
            sf::VertexArray connection(sf::Quads);

            for (size_t j = 0; j < layers[i].size(); ++j) {
                for (size_t k = 0; k < layers[i + 1].size(); ++k) {
                    sf::Vector2f start(layers[i][j].position.x + NEURON_RADIUS, layers[i][j].position.y + NEURON_RADIUS);
                    sf::Vector2f end(layers[i + 1][k].position.x - NEURON_RADIUS, layers[i + 1][k].position.y + NEURON_RADIUS);

                    // Calculate perpendicular vector to get the points for filling
                    sf::Vector2f perpVec = sf::Vector2f(end.y - start.y, start.x - end.x);
                    perpVec = perpVec / std::sqrt(perpVec.x * perpVec.x + perpVec.y * perpVec.y);

                    // Define points to form a quad for filling
                    sf::Vector2f quad[4] = {
                        start - perpVec * CONNECTION_WIDTH,
                        start + perpVec * CONNECTION_WIDTH,
                        end + perpVec * CONNECTION_WIDTH,
                        end - perpVec * CONNECTION_WIDTH
                    };

                    // Append the points to the connection
                    for (size_t q = 0; q < 4; ++q) {
                        connection.append(sf::Vertex(quad[q], connectionColors[i]));
                    }
                }
            }
            connections.push_back(connection);
        }
    }

    void initializeColors() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        connectionColors.clear();

        for (size_t i = 0; i < layers.size() - 1; ++i) {
            sf::Color goodGuyColor(dis(gen), dis(gen), dis(gen));
            sf::Color badGuyColor(dis(gen), dis(gen), dis(gen));

            for (const auto& neuron : layers[i]) {
                if (neuron.type == NeuronType::GoodGuy) {
                    connectionColors.push_back(goodGuyColor);
                }
                else if (neuron.type == NeuronType::BadGuy) {
                    connectionColors.push_back(badGuyColor);
                }
                // Add additional conditions for other neuron types if needed
            }
        }
    }


    void drawColoredConnection(sf::RenderWindow& window, const sf::VertexArray& connection) {
        window.draw(connection);
    }

public:

    NeuralNetwork(std::vector<unsigned> topology, const sf::Texture& neuronTexture) {
        for (size_t i = 0; i < topology.size(); ++i) {
            std::vector<Neuron> layer;
            for (unsigned j = 0; j < topology[i]; ++j) {
                float x = 100.f + i * 200.f;
                float y = 100.f + j * 100.f;
                layer.push_back(Neuron(x, y, neuronTexture, NeuronType::GoodGuy));
            }
            layers.push_back(layer);
        }

        updateConnections();
    }

    void update(sf::RenderWindow& window)
    {
        handleMouseInput(window);

        window.clear(sf::Color::White);

        for (size_t i = 0; i < connections.size(); ++i) {
            drawColoredConnection(window, connections[i]);
        }

        for (const auto& layer : layers) {
            for (const auto& neuron : layer) {
                window.draw(neuron.sprite);
            }
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Neural Network");
    window.setFramerateLimit(60);

    // Load neuron texture (replace "neuron_texture.png" with your texture file)
    sf::Texture neuronTexture;
    if (!neuronTexture.loadFromFile("./ASSETS/IMAGES/SFML-LOGO.png")) {
        //return -1; // Error loading texture
    }

    std::vector<unsigned> topology = { 3, 4, 2 };
    NeuralNetwork neuralNetwork(topology, neuronTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        neuralNetwork.update(window);

        window.display();
    }

    return 0;
}
