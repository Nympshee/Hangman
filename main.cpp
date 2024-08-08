#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype> // Para verificar caracteres
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printWord(const std::vector<char>& guessed, const std::string& word) {
    for (char c : word) {
        if (std::find(guessed.begin(), guessed.end(), c) != guessed.end()) {
            std::cout << c << ' ';
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

void printHangman(int chances) {
    const char* hangman[] = {
        "  +---+\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========\n",
        
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========\n",

        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "=========\n",

        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|   |\n"
        "      |\n"
        "      |\n"
        "=========\n",

        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        "      |\n"
        "      |\n"
        "=========\n",

        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " /    |\n"
        "      |\n"
        "=========\n",

        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " / \\  |\n"
        "      |\n"
        "=========\n"
    };

    std::cout << hangman[6 - chances];
}

int main() {
    std::vector<std::string> words = {"programacao", "computador", "terminal", "jogo"};
    std::srand(std::time(nullptr));
    std::string word = words[std::rand() % words.size()];

    std::vector<char> guessed;
    int chances = 6;
    char guess;

    while (chances > 0) {
        clearScreen();
        printHangman(chances);
        printWord(guessed, word);
        std::cout << "Chances restantes: " << chances << std::endl;
        std::cout << "Digite uma letra: ";
        std::cin >> guess;

        guess = std::tolower(guess); // Converter para minúscula

        if (!std::isalpha(guess)) {
            std::cout << "Entrada inválida. Por favor, digite uma letra." << std::endl;
#ifdef _WIN32
            Sleep(2000); // Pausar para que o usuário veja a mensagem (2 segundos)
#else
            sleep(2); // Pausar para que o usuário veja a mensagem (2 segundos)
#endif
            continue;
        }

        if (std::find(guessed.begin(), guessed.end(), guess) == guessed.end()) {
            guessed.push_back(guess);
            if (word.find(guess) == std::string::npos) {
                --chances;
            }
        }

        bool won = true;
        for (char c : word) {
            if (std::find(guessed.begin(), guessed.end(), c) == guessed.end()) {
                won = false;
                break;
            }
        }

        if (won) {
            clearScreen();
            printHangman(chances);
            std::cout << "Você ganhou! A palavra era: " << word << std::endl;
            break;
        }
    }

    if (chances == 0) {
        clearScreen();
        printHangman(chances);
        std::cout << "Você perdeu! A palavra era: " << word << std::endl;
    }
    system("pause");
    return 0;
}
