#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

int leggi(string);
void muro(char *, int);
void genera_labirinto(char *, int, int, int);
int genera_Punti(char *, int, int, int, char);
int indice_casuale(int);
bool percorsi(char *, int, int &, int &, char);
void stampa(char *, int);
void scambio(int *, int, int);

int main()
{
    cout << "Gioco del labirinto" << endl;
    // regole del gioco
    cout << "W-sopra\tS-sotto" << endl;
    cout << "A-sinistra\tD-destra" << endl;

    srand(time(0));
    int dim = leggi("\nInserisci la diemnsione del labrinto:\t");
    system("cls");

    char matrice[dim][dim];

    muro(*(matrice), dim);
    genera_labirinto(*(matrice), 1, 1, dim); // i numeri sono il posto iniziale
    int i = genera_Punti(*(matrice), indice_casuale(dim), indice_casuale(dim),
                         dim, 'A');
    i = genera_Punti(*(matrice), indice_casuale(dim), indice_casuale(dim), dim,
                     'S');
    int x = i / dim;
    int y = i % dim;

    stampa(*(matrice), dim);

    char direzione;
    // cin >> direzione;
    direzione = getch();

    bool flag = percorsi(*(matrice), dim, x, y, direzione);
    while (flag == 0)
    {
        system("cls");
        stampa(*(matrice), dim);
        // cin >> direzione;
        direzione = getch();
        flag = percorsi(*(matrice), dim, x, y, direzione);
    }
    cout << "Hai vinto!" << endl;

    return 0;
}

void muro(char *matrice, int dim)
{
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            matrice[i * dim + j] = '#';
}

// generazione labirinto
void genera_labirinto(char *matrice, int x, int y, int dim)
{
    matrice[x * dim + y] = ' ';

    int direzione[4] = {1, 2, 3, 4}; // 1-sopra, 2-soto, 3-destra, 4-sinistra

    // mescola le direzioni
    for (int i = 0; i < 4; i++)
    {
        int r = rand() % 4;
        scambio(direzione, i, r);
    }

    for (int i = 0; i < 4; i++)
    {
        switch (direzione[i])
        {
        case 1:
            if (matrice[(x - 2) * dim + y] != ' ' && x - 2 > 0)
            {
                matrice[(x - 1) * dim + y] = ' ';
                genera_labirinto(matrice, x - 2, y, dim);
            }
            break;
        case 2:
            if (matrice[(x + 2) * dim + y] != ' ' && x + 2 < dim - 1)
            {
                matrice[(x + 1) * dim + y] = ' ';
                genera_labirinto(matrice, x + 2, y, dim);
            }
            break;
        case 3:
            if (matrice[x * dim + (y + 2)] != ' ' && y + 2 < dim - 1)
            {
                matrice[x * dim + (y + 1)] = ' ';
                genera_labirinto(matrice, x, y + 2, dim);
            }
            break;
        case 4:
            if (matrice[x * dim + (y - 2)] != ' ' && y - 2 > 0)
            {
                matrice[x * dim + (y - 1)] = ' ';
                genera_labirinto(matrice, x, y - 2, dim);
            }
            break;
        default:
            break;
        }
    }
}

// genera il percorso percorribile
void scambio(int direzione[], int a, int b)
{
    int temp = direzione[b];
    direzione[b] = direzione[a];
    direzione[a] = temp;
}

int leggi(string msg)
{
    int n;

    cout << msg;
    cin >> n;

    if (n <= 5)
    {
        cout << "Errore il nuemro deve essere maggiore di 5" << endl;
        n = leggi(msg);
    }

    return n;
}

// stampa la matrice
void stampa(char *matrice, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            cout << matrice[i * dim + j] << " ";
        cout << endl;
    }
}

// genera il punto di partenza e il punto di arrivo
int indice_casuale(int d)
{
    int r = rand() % d;

    return r;
}

// gebnera le coordinate di generazione dei punti
int genera_Punti(char *matrice, int x, int y, int dim, char segno)
{
    int i = x * dim + y;

    // quando il punto di arrivo e di partenza viene generato sul muro si rigenera
    if ((x == 1 || y == 1) && matrice[i] != '#')
        matrice[i] = segno;
    else
        i = genera_Punti(matrice, indice_casuale(dim), indice_casuale(dim), dim,
                         segno);

    return i;
}

// genera il percorso che l'utente ha fatto
bool percorsi(char *matrice, int dim, int &x, int &y, char direzione)
{
    int dy = 0, dx = 0;
    switch (direzione)
    {
    case 'w':
        dx = -1;
        break;
    case 'a':
        dy = -1;
        break;
    case 's':
        dx = +1;
        break;
    case 'd':
        dy = +1;
        break;
    default:
        break;
    }

    x += dx;
    y += dy;

    if (matrice[x * dim + y] == ' ')
    {
        matrice[x * dim + y] = '*';
        matrice[(x - dx) * dim + (y - dy)] = ' ';
        return 0;
    }
    else if (matrice[x * dim + y] == '#')
    {
        x -= dx;
        y -= dy;
        return 0;
    }
    else if (matrice[x * dim + y] == 'A')
        return 1;
    else
        return 0;
}