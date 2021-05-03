#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"
#include "list.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

void menu_pokemon();

void leer_archivo(List *list_pc, List *list_numpokedex, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

void pedir_datos(List *list_pc, List *list_numpokedex, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

Pokemon *crear_pokemon(char *id, char *nombre, int pc, int ps, char *sexo);

Pokedex *crear_pokedex(char *nombre, List *tipos, char *ev_prev, char *ev_post, int num_pokedex, char *region);

void insert_map_pokedex(Pokedex *pokedex, HashMap *map_pokedex, List *list_numpokedex);

void insert_map_pokemon(Pokemon *pokemon, HashMap *map_pokemon);

void insert_map_id(Pokemon *pokemon, HashMap *map_id);

void insert_map_tipo(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_tipo);

void insert_map_region(Pokedex *pokedex, HashMap *map_region);

void leer_lista(List *lista);

void leer_mapa_id(HashMap *map);

void leer_mapa_pokedex(HashMap *map);

void leer_mapa_tipos(HashMap *map_tipo);

void leer_mapa_pokemon(HashMap *map_pokemon);

void leer_mapa_region(HashMap *map_region);

void leer_tipos(HashMap *map_region, Pokedex *pokedex);

void leer_list_pokemon(List *list_pc);

void leer_list_numpokedex(List *list_num_pokedex);

#endif /* POKEMON_H */