#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "map.h"
#include "list.h"
#include "pokemon.h"

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
    char *id;
    char *nombre;
    int pc;
    int ps;
    char *sexo;
};

struct Pokedex{
    char *nombre;
    int existencia;
    List *tipos;
    char *ev_prev;
    char *ev_post;
    char *num_pokedex;
    char *region;
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
    pokemon->id = id;
    printf("%s ", pokemon->id);
    pokemon->nombre = nombre;
    printf("%s ", pokemon->nombre);
    pokemon->pc = pc;
    printf("%d ", pokemon->pc);
    pokemon->ps = ps;
    printf("%d ", pokemon->ps);
    pokemon->sexo = sexo;
    printf("%s ", pokemon->sexo);
    return pokemon;
}

Pokedex *crear_pokedex(char *nombre, List *tipos, char *ev_prev, char *ev_post, char *num_pokedex, char *region){
    Pokedex *pokedex = (Pokedex *) malloc (sizeof(Pokedex));
    pokedex->nombre = nombre;
    printf("%s ", pokedex->nombre);
    int existencia;
    pokedex->existencia = 1;
    printf("%d ", pokedex->existencia);
    pokedex->tipos = tipos;
    leer_lista(pokedex->tipos);
    pokedex->ev_prev = ev_prev;
    printf("%s ", pokedex->ev_prev);
    pokedex->ev_post = ev_post;
    printf("%s ", pokedex->ev_post);
    pokedex->num_pokedex = num_pokedex;
    printf("%s ", pokedex->num_pokedex);
    pokedex->region = region;
    printf("%s ", pokedex->region);
    return pokedex;
}

void leer_archivo(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, HashMap *map_num_pokedex){

    char archivo[20];
    printf("\nPor favor ingrese el archivo que se desea leer: ");
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
    char *tipo;
    List *list_tipos;
    int pc;
    int ps;
    char *sexo;
    char *ev_prev;
    char *ev_post;
    char *num_pokedex;
    char *region;

    Pokemon *pokemon;
    Pokedex *pokedex;

    fgets(linea, 1023, archivoEntrada);
    while (fscanf(archivoEntrada, "%[^\n]s", linea) != EOF){
        fgetc(archivoEntrada);

        list_tipos = createList();

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
        num_pokedex = token;

        token = strtok(NULL, ",");
        region = token;

        token = strtok(tipo, ", ");
        pushBack(list_tipos, token);
        token = strtok(NULL, ", ");
        while (token != NULL){
            pushBack(list_tipos, token);
            token = strtok(NULL, ", ");
        }

        pokemon = crear_pokemon(id, nombre, pc, ps, sexo);
        pokedex = crear_pokedex(nombre, list_tipos, ev_prev, ev_post, num_pokedex, region);
        printf("\n");
        insert_map_pokedex(pokemon, pokedex, map_pokedex);
        //insert_map_pokemon(pokemon, map_pokemon);
        insert_map_id(pokemon, map_id);
        //insert_map_tipo(pokemon, pokedex, map_tipo);
        //insert_map_region(pokemon, pokedex, map_region);
        insert_map_num_pokedex(pokedex, map_num_pokedex);
        leer_mapa_pokemon(map_id);

    }

    //leer_mapa_pokemon(map_pokedex);

    if (fclose(archivoEntrada) == EOF){
        printf("El archivo no se pudo cerrar correctamente.");
    }

}

/*void pedir_datos(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, HashMap *map_num_pokedex){

	char *nombre = (char *) malloc (15 * sizeof(char));
	char *sexo = (char *) malloc (6 * sizeof(char));
	char *ev_prev = (char *) malloc (15 * sizeof(char));
	char *ev_post = (char *) malloc (15 * sizeof(char));
	int pc, ps, num_pokedex;
	char *region = (char *) malloc (10 * sizeof(char));
	List* list_tipos = createList();

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

    /* Falta verificar 'No tiene'
	printf("Ingrese su evolucion previa (Si no tiene simplemente escriba: No tiene): ");
	scanf("%s", ev_prev);

    /* Falta verificar 'No tiene' 
	printf("Ingrese su evolucion posterior (Si no tiene simplemente escriba: No tiene): ");
	scanf("%s", ev_post);

    /* Falta comparar num de pokedex 
	printf("Ingrese el numero en la pokedex del pokemon: ");
	scanf("%i", &num_pokedex);

	printf("Ingrese la region del pokemon: ");
	scanf("%s", region);

    pokemon = crear_pokemon(id, nombre, pc, ps, sexo);
    pokedex = crear_pokedex(nombre, list_tipos, ev_prev, ev_post, num_pokedex, region);
    printf("\n");
    insert_map_pokedex(pokemon, pokedex, map_pokedex);
    insert_map_pokemon(pokemon, map_pokemon);
    insert_map_id(pokemon, map_id);
    insert_map_tipo(pokemon, pokedex, map_tipo);
    insert_map_region(pokemon, pokedex, map_region);
    insert_map_num_pokedex(pokedex, map_num_pokedex);

    //atrapar_pokemon(almacenamiento, map_pokedex, map_pokemon, map_id, map_tipo, map_region, map_num_pokedex);

}*/

void insert_map_pokedex(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_pokedex){
    
    Pokemon *dato_pokemon = searchMap(map_pokedex, pokedex->nombre);
    if (dato_pokemon == NULL){
        insertMap(map_pokedex, pokedex->nombre, pokemon);
    }
    else{
        pokedex->existencia ++;
    }
    
}

void insert_map_pokemon(Pokemon *pokemon, HashMap *map_pokemon){

    List *list = searchMap(map_pokemon, pokemon->nombre);
    Pokemon *primer_dato = firstList(list);
    if (primer_dato == NULL){
        List *list_nombres = createList();
        pushBack(list_nombres, pokemon);
        insertMap(map_pokemon, pokemon->nombre, list_nombres);
    }
    else{
        pushBack(list, pokemon);
    }

}

/* Hay que utilizar la ultima key id ingresada para agregar un pokemon con la key id siguiente */
void insert_map_id(Pokemon *pokemon, HashMap *map_id){

    insertMap(map_id, pokemon->id, pokemon);
    printf("%s %s %d %d %s \n", pokemon->id, pokemon->nombre, pokemon->pc, pokemon->ps, pokemon->sexo);

}

void insert_map_tipo(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_tipo){

    char * tipo = firstList(pokedex->tipos);
    while(tipo != NULL)
    {
        List *list = searchMap(map_tipo, tipo);
        Pokemon *primer_dato = firstList(list);
        if (primer_dato == NULL){
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

void insert_map_region(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_region){

    List *list = searchMap(map_region, pokedex->region);
    Pokemon *primer_dato = firstList(list);
    if (primer_dato == NULL){
        List *list_region = createList();
        pushBack(list_region, pokedex->region);
        insertMap(map_region, pokedex->region, list_region);
    }else{
        pushBack(list, pokemon);
    }

}

void insert_map_num_pokedex(Pokedex *pokedex, HashMap *map_num_pokedex){

    Pokedex *dato_pokedex = searchMap(map_num_pokedex, pokedex->num_pokedex);
    if (dato_pokedex == NULL){
        insertMap(map_num_pokedex, pokedex->num_pokedex, pokedex);
    }
    /*else{
        printf("El numero pokedex del pokemon ingresado ya existe.\n");
    }*/

}

void leer_lista(List *lista){

    char *iterador = firstList(lista);
    while (iterador != NULL){
        printf("%s ", iterador);
        iterador = nextList(lista);
    }

}

void leer_mapa_pokemon(HashMap *map){

    Pokemon *pokemon = firstMap(map);
    printf("%s %s %d %d %s \n", pokemon->id, pokemon->nombre, pokemon->pc, pokemon->ps, pokemon->sexo);
    /*while (pokemon){
        printf("%s %s %d %d %s \n", pokemon->id, pokemon->nombre, pokemon->pc, pokemon->ps, pokemon->sexo);
        pokemon = nextMap(map);
    }*/

}

/*void leer_mapa_pokedex(HashMap *map){

    Pokedex *pokedex = firstMap(map);
    while (pokedex){
        printf("%s %d", pokedex->nombre, pokedex->existencia);
        pokedex = nextMap(map);
    }

}*/

// Leer mapas para comprobar que los datos se guardan correspontamente

/*void atrapar_pokemon(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, HashMap *map_num_pokedex){

    char aux_id[3];
    sprintf(aux_id, "%d", id);
    printf("atrapar_pokemon\n");

}*/