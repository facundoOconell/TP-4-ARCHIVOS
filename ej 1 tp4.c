#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona{
	
	int dni[20];
	char nombre[50];
	char apellido[50];
	
};

void ingresarDatos(FILE *archivo);

void buscarPorDni(FILE *archivo);



int main() {
    FILE *archivo;
    int opcion;

    // Abre el archivo en modo de escritura (crea uno nuevo o sobrescribe uno existente)
    archivo = fopen("datos.txt", "w+");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Salir\n");
        printf("Ingrese su opciOn: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarDatos(archivo);
                break;
            case 2:
                buscarPorDNI(archivo);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 3);


    fclose(archivo);

    return 0;
}




void ingresarDatos(FILE *archivo) {
    struct Persona persona;

    printf("Ingrese el nombre: ");
    scanf("%s", persona.nombre);
    printf("Ingrese el apellido: ");
    scanf("%s", persona.apellido);
    printf("Ingrese el DNI: ");
    scanf("%s", persona.dni);

    // Escribe los datos en el archivo
    fprintf(archivo, "%s %s %s\n", persona.nombre, persona.apellido, persona.dni);
    printf("Datos guardados correctamente.\n");
}



void buscarPorDNI(FILE *archivo) {
    char dniBuscar[20];
    char nombre[50], apellido[50], dni[20];
    int encontrado = 0;

    printf("Ingrese el DNI a buscar: ");
    scanf("%s", dniBuscar);

    // Reinicia el puntero de archivo al principio
    rewind(archivo);

    // Busca el DNI en el archivo
    while (fscanf(archivo, "%s %s %s", nombre, apellido, dni) != EOF) {
        if (strcmp(dni, dniBuscar) == 0) {
            printf("Nombre: %s\n", nombre);
            printf("Apellido: %s\n", apellido);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontraron datos para el DNI ingresado.\n");
    }
}
