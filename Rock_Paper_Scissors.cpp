#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0)); //to ensure random sequence for rand()

    char computer, player;
    int randomNum;

    std::cout << "Enter 0, 1, or 2:\n0 for (Rock)\n1 for (Paper)\n2 for (Scissors)\nYou chose: ";
    std::cin >> player;
    
    randomNum = rand() % 3; // Random number between 0 and 2
    computer = '0' + randomNum; // Convert int to char ('0', '1', '2')
    std::cout << "Computer chose: " << computer << std::endl;
    
    if (player == computer) {
        std::cout << "It's a tie!" << std::endl;
    } else if ((player == '0' && computer == '2') || 
               (player == '1' && computer == '0') || 
               (player == '2' && computer == '1')) {
        std::cout << "You win!" << std::endl;
    } else if ((player == '0' && computer == '1') || 
               (player == '1' && computer == '2') || 
               (player == '2' && computer == '0')) {
        std::cout << "Computer wins!" << std::endl;
    } else {
        std::cout << "Invalid input!" << std::endl;
    }

}