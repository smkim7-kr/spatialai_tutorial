// C++ supports object-oriented programming (OOP)
// A class is a way to group data and functionality together
#include <iostream>
#define Log(x) std::cout << x << std::endl;

class Player {
public: // By default, class members are private; public allows access from outside the class
    int x, y;
    int speed;

    // Method to move the player by modifying the x and y coordinates
    void M_Move(int dx, int dy) { 
        x += dx * speed;
        y += dy * speed;
    }
}; // A semicolon is required at the end of the class declaration

// Struct vs. Class:
// - The default visibility in a struct is public, while in a class it's private.
// - Inheritance is usually done with classes, not structs.
// - Structs in C++ are similar to classes but mainly exist for compatibility with the C language.
// - Use struct when you just need to group variables (without much functionality that a class would provide).
struct s_Player { 
    int x, y;
    int speed;

    void M_Move(int dx, int dy) {
        x += dx * speed;
        y += dy * speed;
    }
};

// Function to move a Player object using pass-by-reference (to avoid copying the object)
void Move(Player& player, int dx, int dy) { 
    player.x += dx * player.speed;
    player.y += dy * player.speed;
}

int main() {
    // Declaring variables for player's position and speed
    int positionX, positionY; 
    double playerSpeed = 2; 

    // Grouping variables into a Player class
    Player player; // Instantiate a Player object
    player.x = 5; 
    player.y = 10; 
    player.speed = 1; // If speed is private, accessing it directly would result in an error

    // Move the player using both the external function and the class method
    Move(player, 5, -7);   // External function manipulating player's data
    player.M_Move(5, -7);  // Better approach: Using the class method for cleaner and more efficient code

    // Struct instantiation
    s_Player s_player; // Instantiate a struct
    s_player.x = 10;   // Default visibility in struct is public

    return 0;
}
