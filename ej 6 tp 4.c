#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 10
#define MAX_NAME_LENGTH 50

struct Player {
    char name[MAX_NAME_LENGTH];
    int score;
};

// Función para guardar un registro de jugador en el archivo
void savePlayer(struct Player player) {
    FILE *file = fopen("players.dat", "ab");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    fwrite(&player, sizeof(struct Player), 1, file);
    fclose(file);
}

// Función para cargar los registros de jugadores desde el archivo
void loadPlayers(struct Player players[]) {
    FILE *file = fopen("players.dat", "rb");
    if (file == NULL) {
        printf("No hay registros de jugadores.\n");
        return;
    }
    int i = 0;
    while (fread(&players[i], sizeof(struct Player), 1, file)) {
        i++;
    }
    fclose(file);
}

// Función para mostrar los 10 mejores jugadores ordenados por mayor puntaje
void showTopPlayers(struct Player players[]) {
    int i, j;
    struct Player temp;
    for (i = 0; i < MAX_PLAYERS - 1; i++) {
        for (j = 0; j < MAX_PLAYERS - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
    printf("Top 10 Jugadores:\n");
    for (i = 0; i < 10; i++) {
        printf("%d. Nombre: %s - Puntaje: %d\n", i + 1, players[i].name, players[i].score);
    }
}

// Función para realizar una búsqueda de un jugador por nombre
void searchPlayer(struct Player players[], char *searchName) {
    int i;
    printf("Resultados de la busqueda para '%s':\n", searchName);
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (strcmp(players[i].name, searchName) == 0) {
            printf("Nombre: %s - Puntaje: %d\n", players[i].name, players[i].score);
        }
    }
}

int main() {
    struct Player players[MAX_PLAYERS];
    int choice;
    do {
        printf("\n1. Ingresar nuevo jugador\n");
        printf("2. Mostrar top 10 jugadores\n");
        printf("3. Buscar jugador por nombre\n");
        printf("4. Salir\n");
        printf("Ingrese su eleccion: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ingrese el nombre del jugador: ");
                scanf("%s", players[MAX_PLAYERS - 1].name);
                printf("Ingrese el puntaje del jugador: ");
                scanf("%d", &players[MAX_PLAYERS - 1].score);
                savePlayer(players[MAX_PLAYERS - 1]);
                break;
            case 2:
                loadPlayers(players);
                showTopPlayers(players);
                break;
            case 3:
                loadPlayers(players);
                char searchName[MAX_NAME_LENGTH];
                printf("Ingrese el nombre a buscar: ");
                scanf("%s", searchName);
                searchPlayer(players, searchName);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Inténtelo de nuevo.\n");
        }
    } while (choice != 4);

    return 0;
}


