//// Joseph O'Keeffe
//// C00258019
//
//#ifdef _DEBUG 
//#pragma comment(lib,"sfml-graphics-d.lib") 
//#pragma comment(lib,"sfml-audio-d.lib") 
//#pragma comment(lib,"sfml-system-d.lib") 
//#pragma comment(lib,"sfml-window-d.lib") 
//#pragma comment(lib,"sfml-network-d.lib") 
//#else 
//#pragma comment(lib,"sfml-graphics.lib") 
//#pragma comment(lib,"sfml-audio.lib") 
//#pragma comment(lib,"sfml-system.lib") 
//#pragma comment(lib,"sfml-window.lib") 
//#pragma comment(lib,"sfml-network.lib") 
//#endif 
//
//#include "Game.h"
//GameState Game::currentState = MENU;
//int main()
//{
//    
//    Game game;
//   
//
//    game.run();
//
//    return 1;
//}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

struct HuffmanNode {
    char data;
    unsigned frequency;
    sf::CircleShape circle;  // Added for visualization
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {
        circle.setRadius(20.f);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2.f);
    }
};

struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

HuffmanNode* buildHuffmanTree(const std::unordered_map<char, unsigned>& frequencyMap, sf::RenderWindow& window);
void generateHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes);
void drawHuffmanTree(sf::RenderWindow& window, HuffmanNode* root, float x, float y, float xOffset, float levelSpacing);
std::string encodeString(const std::string& input, const std::unordered_map<char, std::string>& huffmanCodes);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Huffman Encoding Visualization");
    window.setFramerateLimit(60);

    std::string inputString = "hello_world";
    std::unordered_map<char, unsigned> frequencyMap;
    for (char c : inputString) {
        frequencyMap[c]++;
    }

    HuffmanNode* huffmanTreeRoot = buildHuffmanTree(frequencyMap, window);

    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(huffmanTreeRoot, "", huffmanCodes);

    std::string encodedString = encodeString(inputString, huffmanCodes);

    std::cout << "Original String: " << inputString << std::endl;
    std::cout << "Encoded String: " << encodedString << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        drawHuffmanTree(window, huffmanTreeRoot, 400.f, 50.f, 200.f, 50.f);
        window.display();
    }

    // Cleanup - free memory
    // You might want to implement a proper cleanup function for the Huffman Tree

    return 0;
}

HuffmanNode* buildHuffmanTree(const std::unordered_map<char, unsigned>& frequencyMap, sf::RenderWindow& window) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;

    for (const auto& entry : frequencyMap) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);

        // Visualize the process by drawing the Huffman Tree at each step
        window.clear(sf::Color::White);
        drawHuffmanTree(window, minHeap.top(), 400.f, 50.f, 200.f, 50.f);
        window.display();
        sf::sleep(sf::milliseconds(1000));  // Delay for visualization
    }

    return minHeap.top();
}

void drawHuffmanTree(sf::RenderWindow& window, HuffmanNode* root, float x, float y, float xOffset, float levelSpacing) {
    if (root == nullptr) {
        return;
    }

    root->circle.setPosition(x, y);
    window.draw(root->circle);

    if (root->left != nullptr) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 10.f, y + 20.f)),
            sf::Vertex(sf::Vector2f(x - xOffset + 10.f, y + levelSpacing + 20.f))
        };
       // window.draw(line, 2);
        drawHuffmanTree(window, root->left, x - xOffset, y + levelSpacing, xOffset / 2.f, levelSpacing);
    }

    if (root->right != nullptr) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 10.f, y + 20.f)),
            sf::Vertex(sf::Vector2f(x + xOffset + 10.f, y + levelSpacing + 20.f))
        };
        //window.draw(line, 2);
        drawHuffmanTree(window, root->right, x + xOffset, y + levelSpacing, xOffset / 2.f, levelSpacing);
    }

    // Display character for leaf nodes
    if (root->left == nullptr && root->right == nullptr) {
        sf::Font font;
        font.loadFromFile("arial.ttf");  // Change the font path accordingly

        sf::Text text(root->data, font, 20);
        text.setPosition(x + 5.f, y + 15.f);
        window.draw(text);
    }
}

void generateHuffmanCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

std::string encodeString(const std::string& input, const std::unordered_map<char, std::string>& huffmanCodes) {
    std::string encodedString;
    for (char c : input) {
        encodedString += huffmanCodes.at(c);
    }
    return encodedString;
}
