#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

const int ALTURA = 4;
const int LARGURA = 10;
const int FPS = 30;
const int RENDER_DISTANCE = 20;
const char PLAYER = 'A';
const char OBSTACULO = 'I';

string mapa[] = {
    "................................................................................",
    "..................................I.............................................",
    ".................I........I.......I.............III........II...................",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

bool board(int x, int y) {
    bool colidiu = false;

    for (int i = 0; i < 4; i++) {
        for (int j = x; j < min((int)mapa[0].size(), x + RENDER_DISTANCE); j++) {
            if (j == x + RENDER_DISTANCE/2 && i == y) {
                cout << PLAYER;

                if (mapa[i][j] == OBSTACULO)
                    colidiu = true;

            } else
                cout << mapa[i][j];
        }
        cout << endl;
    }
    cout << endl;

    return colidiu;
}

int main() {
    int x = 0, y = 2, contador = 0, velocidade = 20;
    bool isjumping = false;
    int contador_pulo = 0;
    srand(time(NULL));

    bool iniciar = false;
    while (!iniciar) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

        cout << "PRESSIONE A TECLA W PARA INICIAR" << endl;

        if (kbhit()) {
            switch (getch()) {
                case 'w':
                    iniciar = true;
                    break;
            }
        }
    }

    // loop infinito
    while (true) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

        if (board(x, y)) {
            cout << "VOCE PERDEU!" << endl;
            break;
        }
        

        if (kbhit()) {
            switch (getch()) {
                case 'w':
                    if (!isjumping)
                        isjumping = true;

                    break;
            }
        }

        // pulo (criar função)
        if (isjumping) {
            contador_pulo++;

            switch (contador_pulo) {
                case FPS:
                    y--;
                    break;
                case FPS*2:
                    y--;
                    break;
                case 3*FPS:
                    y++;
                    break;
                case 4*FPS:
                    y++;
                    contador_pulo = 0;
                    isjumping = false;
                    break;
            }
        }

        // fim do mapa
        contador++;
        if (contador >= velocidade) {
            contador = 0;

            if (x < (int)mapa[0].size() - RENDER_DISTANCE)
                x++;
        }
    }

    while (true) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
        cout << "VOCE PERDEU" << endl;
    }

    return 0;
}