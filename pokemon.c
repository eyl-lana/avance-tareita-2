#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "pokemon.h"

int int_id = 0;

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
    char id[3];
    char nombre[20];
    int pc;
    int ps;
    char sexo[10];
};

struct Pokedex{
    char nombre[20];
    int existencia;
    List *tipos;
    char ev_prev[20];
    char ev_post[20];
    int num_pokedex;
    char region[20];
};

void menu_pokemon(){
  printf("\nMenu de opciones\n");
  printf("1.- Leer archivo.\n");
  printf("2.- Atrapar un pokemon\n");
  printf("3.- Evolucionar un pokemon\n");
  printf("4.- Mostrar pokemones de acuerdo a su tipo\n");
  printf("5.- Pokemon y su informacion de combate\n");
  printf("6.- Pokemon y su informacion personal\n");
  printf("7.- Mostrar todos los pokemones\n");
  printf("8.- Pokemones ordenados por puntos de combate\n");
  printf("9.- Liberar un pokemon\n");
  printf("10.- Mostrar pokemones de acuerdo a su region\n");
  printf("11.- Salir del juego\n");
  printf("Ingrese opcion: ");
}

Pokemon *crear_pokemon(char *id, char *nombre, int pc, int ps, char *sexo){
    Pokemon *pokemon = (Pokemon *) malloc (sizeof(Pokemon));
    strcpy(pokemon->id, id);
    int_id = atoi(id);
    printf("%d ", int_id);
    printf("%s ", pokemon->id);
    strcpy(pokemon->nombre, nombre);
    printf("%s ", pokemon->nombre);
    pokemon->pc = pc;
    printf("%d ", pokemon->pc);
    pokemon->ps = ps;
    printf("%d ", pokemon->ps);
    strcpy(pokemon->sexo, sexo);
    printf("%s ", pokemon->sexo);
    return pokemon;
}

Pokedex *crear_pokedex(char *nombre, List *tipos, char *ev_prev, char *ev_post, int num_pokedex, char *region){
    Pokedex *pokedex = (Pokedex *) malloc (sizeof(Pokedex));
    strcpy(pokedex->nombre, nombre);
    printf("%s ", pokedex->nombre);
    pokedex->existencia = 1;
    printf("%d ", pokedex->existencia);

    pokedex->tipos = tipos;
    char *aux = firstList(pokedex->tipos);
    while(aux){
        printf("%s ", aux);
        aux = nextList(pokedex->tipos);
    }

    strcpy(pokedex->ev_prev, ev_prev);
    printf("%s ", pokedex->ev_prev);
    strcpy(pokedex->ev_post, ev_post);
    printf("%s ", pokedex->ev_post);
    pokedex->num_pokedex = num_pokedex;
    printf("%d ", pokedex->num_pokedex);
    strcpy(pokedex->region, region);
    printf("%s ", pokedex->region);
    return pokedex;
}

void leer_archivo(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    char archivo[20];
    printf("\nPor favor ingrese el archivo que se desea leer: ");
    /* leer archivo con fgets */
    scanf("%s", archivo);
    FILE *archivoEntrada = fopen(archivo, "r");
    if (archivoEntrada == NULL){
        printf("El archivo no se pudo abrir en modo lectura");
        exit(1);
    }

    char linea[1024];
    char *token;
    char *id;
    char *nombre;
    //char tipo[20];
    //char *tipo;
    int pc;
    int ps;
    char *sexo;
    char *ev_prev;
    char *ev_post;
    int num_pokedex;
    char *region;

    Pokemon *pokemon;
    Pokedex *pokedex;

    fgets(linea, 1023, archivoEntrada);
    while (fscanf(archivoEntrada, "%[^\n]s", linea) != EOF){
        fgetc(archivoEntrada);

        List *list_tipos = createList();
        char *tipo;
        tipo = (char *) malloc (20 * sizeof(char));

        token = strtok(linea, ",");
        id = token;

        token = strtok(NULL, ",");
        nombre = token;

        token = strtok(NULL, "\"");
        tipo = token;

        token = strtok(NULL, ",");
        if (token == NULL){
            token = strtok(tipo, ",");
            tipo = token;
            token = strtok(NULL, ",");
            pc = atoi(token);
        }
        else{
            pc = atoi(token);
        }

        token = strtok(NULL, ",");
        ps = atoi(token);

        token = strtok(NULL, ",");
        sexo = token;

        token = strtok(NULL, ",");
        ev_prev = token;

        token = strtok(NULL, ",");
        ev_post = token;

        token = strtok(NULL, ",");
        num_pokedex = atoi(token);

        token = strtok(NULL, ",");
        region = token;

        token = strtok(tipo, ", ");
        pushBack(list_tipos, token);
        token = strtok(NULL, ", ");
        while (token){
            pushBack(list_tipos, token);
            token = strtok(NULL, ", ");
        }

        pokemon = crear_pokemon(id, nombre, pc, ps, sexo);
        pokedex = crear_pokedex(nombre, list_tipos, ev_prev, ev_post, num_pokedex, region);
        printf("\n");
        insert_map_pokemon(pokemon, map_pokemon); /* funciona */
        insert_map_id(pokemon, map_id); /* funciona */
        insert_map_tipo(pokemon, pokedex, map_tipo); /* funciona */
        insert_map_pokedex(pokedex, map_pokedex); /* Corre pero lee mal los tipos */
        insert_map_region(pokedex, map_region); /* Corre pero lee mal los tipos */
        //pushBack(almacenamiento, pokedex); /* Corre pero lee mal los tipos */
        //leer_tipos(map_region, pokedex);

    }

    /* Lee todo bien */
    //leer_mapa_id(map_id);
    //leer_mapa_tipos(map_tipo);
    //leer_mapa_pokemon(map_pokemon);

    /* Lee mal los tipos */
    //leer_lista(almacenamiento);
    //leer_mapa_pokedex(map_pokedex);
    //leer_mapa_region(map_region);

    if (fclose(archivoEntrada) == EOF){
        printf("El archivo no se pudo cerrar correctamente.");
    }

}

void pedir_datos(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    char id[3];
	char nombre[20];
	char sexo[10];
	char ev_prev[20];
	char ev_post[20];
	int pc, ps, num_pokedex;
	char region[20];
	List *list_tipos = createList();

    int_id ++;
    sprintf(id, "%d", int_id);
    printf("%s\n", id);

	printf("Ingrese el nombre del pokemon: ");
	scanf("%s", nombre);
	
	int cant_pokemon;
	printf("¿Cuantos tipos tiene su pokemon? (ingrese un numero entero): ");
	scanf("%d", &cant_pokemon);
	
	for (int i = 0; i < cant_pokemon; i++)
	{
		char* tipo = (char *) malloc (10 * sizeof(char));
		printf("Ingrese el tipo de su pokemon: ");
		scanf("%s", tipo);
		pushBack(list_tipos, tipo);
	}

	printf("Ingrese los puntos de combate del pokemon: ");
	scanf("%d", &pc);

	printf("Ingrese los puntos de salud del pokemon: ");
	scanf("%d", &ps);

	printf("Ingrese el sexo del pokemon (Macho o Hembra): ");
	scanf("%s", sexo);

    /* Falta verificar 'No tiene' */
	printf("Ingrese su evolucion previa (Si no tiene simplemente escriba: No tiene): ");
	scanf("%s", ev_prev);

    /* Falta verificar 'No tiene' */
	printf("Ingrese su evolucion posterior (Si no tiene simplemente escriba: No tiene): ");
	scanf("%s", ev_post);

    /* Falta comparar num de pokedex */
	printf("Ingrese el numero en la pokedex del pokemon: ");
	scanf("%d", &num_pokedex);

	printf("Ingrese la region del pokemon: ");
	scanf("%s", region);

    Pokemon *pokemon = crear_pokemon(id, nombre, pc, ps, sexo);
    Pokedex *pokedex = crear_pokedex(nombre, list_tipos, ev_prev, ev_post, num_pokedex, region);
    printf("\n");
    insert_map_pokedex(pokedex, map_pokedex);
    insert_map_pokemon(pokemon, map_pokemon);
    insert_map_id(pokemon, map_id);
    insert_map_tipo(pokemon, pokedex, map_tipo);
    insert_map_region(pokedex, map_region);

    /* Lee todo bien */
    //leer_mapa_id(map_id);
    //leer_mapa_tipos(map_tipo);
    //leer_mapa_pokemon(map_pokemon);

    /* Lee mal los tipos */
    //leer_lista(almacenamiento);
    //leer_mapa_pokedex(map_pokedex);
    //leer_mapa_region(map_region);

}

void insert_map_pokedex(Pokedex *pokedex, HashMap *map_pokedex){
    
    Pokedex *dato_pokemon = searchMap(map_pokedex, pokedex->nombre);
    if (dato_pokemon == NULL){
        insertMap(map_pokedex, pokedex->nombre, pokedex);
    }
    else{
        dato_pokemon->existencia ++;
    }
    
}

void insert_map_pokemon(Pokemon *pokemon, HashMap *map_pokemon){

    List *list = searchMap(map_pokemon, pokemon->nombre);
    //Pokemon *primer_dato = firstList(list);
    if (list == NULL){
        List *list_nombres = createList();
        pushBack(list_nombres, pokemon);
        insertMap(map_pokemon, pokemon->nombre, list_nombres);
    }
    else{
        pushBack(list, pokemon);
    }

}

void insert_map_id(Pokemon *pokemon, HashMap *map_id){

    insertMap(map_id, pokemon->id, pokemon);

}

void insert_map_tipo(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_tipo){

    char *tipo = firstList(pokedex->tipos);
    while(tipo)
    {
        List *list = searchMap(map_tipo, tipo);
        //Pokemon *primer_dato = firstList(list);
        if (list == NULL){
            List *list_tipos = createList();
            pushBack(list_tipos, pokemon);
            insertMap(map_tipo, tipo, list_tipos);
        }
        else{
            pushBack(list, pokemon);
        }
        tipo = nextList(pokedex->tipos);
    }

}

void insert_map_region(Pokedex *pokedex, HashMap *map_region){

    List *list = searchMap(map_region, pokedex->region);
    //Pokemon *primer_dato = firstList(list);
    if (list == NULL){
        List *list_region = createList();
        pushBack(list_region, pokedex);
        insertMap(map_region, pokedex->region, list_region);
    }else{
        pushBack(list, pokedex);
    }

}

void leer_lista(List *list){

    Pokedex *pokedex = firstList(list);
    List *list_tipos;
    char *tipo;
    while (pokedex){
        printf("%s %d %s %s %d %s ", pokedex->nombre, pokedex->existencia, pokedex->ev_prev, pokedex->ev_post, pokedex->num_pokedex, pokedex->region);
        list_tipos = pokedex->tipos;
        tipo = firstList(list_tipos);
        while(tipo){
            printf("%s ", tipo);
            tipo = nextList(list_tipos);
        }
        printf("\n");
        pokedex = nextList(list);
    }

}

void leer_mapa_id(HashMap *map){

    Pokemon *pokemon = firstMap(map);
    while (pokemon){
        printf("- %s -\n", pokemon->id );
        printf("%s %d %d %s \n", pokemon->nombre, pokemon->pc, pokemon->ps, pokemon->sexo);
        pokemon = nextMap(map);
    }

}

void leer_mapa_pokedex(HashMap *map){

    Pokedex *pokedex = firstMap(map);
    List *list_tipos = createList();
    char *tipo;
    while (pokedex){
        printf("%s %d %s %s %d %s ", pokedex->nombre, pokedex->existencia, pokedex->ev_prev, pokedex->ev_post, pokedex->num_pokedex, pokedex->region);
        List *list_tipos = createList();
        list_tipos = pokedex->tipos;
        tipo = firstList(list_tipos);
        while(tipo){
            printf("%s ", tipo);
            tipo = nextList(list_tipos);
        }
        printf("\n");
        pokedex = nextMap(map);
    }

}

void leer_mapa_tipos(HashMap *map_tipo){

    List *list_tipos = firstMap(map_tipo);
    Pokemon *tipo;
    while(list_tipos){
        //printf("- %s -\n", list_tipos);
        tipo = firstList(list_tipos);
        while(tipo){
            printf("%s %s %d %d %s \n", tipo->id, tipo->nombre, tipo->pc, tipo->ps, tipo->sexo);
            tipo = nextList(list_tipos);
        }
        list_tipos = nextMap(map_tipo);
    }

}

void leer_mapa_pokemon(HashMap *map_pokemon){

    List *list_nombres = firstMap(map_pokemon);
    Pokemon *pokemon;
    while(list_nombres){
        pokemon = firstList(list_nombres);
        printf("- %s -\n", pokemon->nombre);
        while(pokemon){
            printf("%s %d %d %s \n", pokemon->id, pokemon->pc, pokemon->ps, pokemon->sexo);
            pokemon = nextList(list_nombres);
        }
        list_nombres = nextMap(map_pokemon);
    }

}

void leer_mapa_region(HashMap *map_region){

    List *list_region = firstMap(map_region);
    Pokedex *pokedex;
    while(list_region){
        pokedex = firstList(list_region);
        printf("- %s -\n", pokedex->region);
        while(pokedex){
            printf("%s %d %s %s ", pokedex->nombre, pokedex->existencia, pokedex->ev_prev, pokedex->ev_post);

            List *list_tipos = pokedex->tipos;
            char *tipo = firstList(list_tipos);
            while(tipo){
                printf("%s ", tipo);
                tipo = nextList(list_tipos);
            }
            printf("\n");
            pokedex = nextList(list_region);
        }
        list_region = nextMap(map_region);
    }

}

void leer_tipos(HashMap *map_region, Pokedex *pokedex){

    List *list = searchMap(map_region, pokedex->region);
    Pokedex *dato = firstList(list);
    while(dato){
        List *list_tipos = dato->tipos;
        char *tipo = firstList(list_tipos);
        while(tipo){
            printf("%s ", tipo);
            tipo = nextList(list_tipos);
        }
        printf("\n");
        dato = nextList(list);
    }

}