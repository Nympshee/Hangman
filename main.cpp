#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>


using namespace std;

const vector<string> HANGMAN = {
    "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
};

void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

string escolherPalavra() {
    vector<string> palavras = {"abacaxi", "bicicleta", "chocolate", "dinossauro", "elefante"};
    return palavras[rand() % palavras.size()];
}

void mostrarProgresso(const string& palavra, const vector<char>& letrasAdivinhadas) {
    for (char letra : palavra) {
        if (find(letrasAdivinhadas.begin(), letrasAdivinhadas.end(), letra) != letrasAdivinhadas.end()) {
            cout << letra << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool jogarNovamente() {
    char resposta;
    cout << "Quer jogar de novo? (s/n): ";
    cin >> resposta;
    return (resposta == 's' || resposta == 'S');
}

int main() {
    {
   
    srand(time(0));
    
    do {
        string palavraSecreta = escolherPalavra();
        vector<char> letrasAdivinhadas;
        int tentativasRestantes = 6;
        bool ganhou = false;
        string mensagem = "";

        while (tentativasRestantes > 0 && !ganhou) {
            limparTela();
            cout << HANGMAN[6 - tentativasRestantes] << endl;
            cout << "Tentativas restantes: " << tentativasRestantes << endl;
            mostrarProgresso(palavraSecreta, letrasAdivinhadas);

            if (!mensagem.empty()) {
                cout << mensagem << endl;
                mensagem = "";
            }

            char palpite;
            cout << "Digite uma letra: ";
            cin >> palpite;
            palpite = tolower(palpite);

            if (!isalpha(palpite)) {
                mensagem = "Por favor, digite apenas letras!";
                continue;
            }

            if (find(letrasAdivinhadas.begin(), letrasAdivinhadas.end(), palpite) != letrasAdivinhadas.end()) {
                mensagem = "Voce ja tentou essa letra!";
                continue;
            }

            letrasAdivinhadas.push_back(palpite);

            if (palavraSecreta.find(palpite) == string::npos) {
                tentativasRestantes--;
                mensagem = "Letra errada!";
            } else {
                mensagem = "Boa! Acertou uma letra.";
            }

            ganhou = all_of(palavraSecreta.begin(), palavraSecreta.end(), [&](char c) {
                return find(letrasAdivinhadas.begin(), letrasAdivinhadas.end(), c) != letrasAdivinhadas.end();
            });
        }

        limparTela();
        cout << HANGMAN[6 - tentativasRestantes] << endl;
        if (ganhou) {
            cout << "Parabens! Voce venceu! A palavra era: " << palavraSecreta << endl;
        } else {
            cout << "Que pena! Voce perdeu. A palavra era: " << palavraSecreta << endl;
        }

    } while (jogarNovamente());

    cout << "Obrigado por jogar! Ate a próxima!" << endl;
    return 0;
}
}