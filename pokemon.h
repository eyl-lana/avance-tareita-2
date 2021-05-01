#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"
#include "list.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

void menu_pokemon();

void leer_archivo(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, HashMap *map_num_pokedex);

void pedir_datos(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, HashMap *map_num_pokedex);

Pokemon *crear_pokemon(char *id, char *nombre, int pc, int ps, char *sexo);

Pokedex *crear_pokedex(char *nombre, List *tipos, char *ev_prev, char *ev_post, char *num_pokedex, char *region);

//void ingresar_mapas(Pokemon *pokemon, Pokedex *pokedex, List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, HashMap *map_num_pokedex);

void insert_map_pokedex(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_pokedex);

void insert_map_pokemon(Pokemon *pokemon, HashMap *map_pokemon);

void insert_map_id(Pokemon *pokemon, HashMap *map_id);

void insert_map_tipo(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_tipo);

void insert_map_region(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_region);

void insert_map_num_pokedex(Pokedex *pokedex, HashMap *map_num_pokedex);

void leer_lista(List *);

void leer_mapa_pokemon(HashMap *map);

//void atrapar_pokemon(List *almacenamiento, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, HashMap *map_num_pokedex);

#endif /* POKEMON_H */