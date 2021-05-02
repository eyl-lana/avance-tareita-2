#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "pokemon.h"


int main()
{

	List *almacenamiento = createList();
	HashMap *map_pokedex = createMap(300);
	HashMap *map_pokemon = createMap(300);
	HashMap *map_id = createMap(300);
	HashMap *map_tipo = createMap(300);
	HashMap *map_region = createMap(300);
	HashMap *map_num_pokedex = createMap(300);

	leer_archivo(almacenamiento, map_pokedex, map_pokemon, map_id, map_tipo, map_region, map_num_pokedex);
	printf("Se leyo el archivo correctamente.\n");

	int opcion;
	do{

		menu_pokemon();
		scanf("%d", &opcion);
		printf("\n");

		switch(opcion){

			case 1: /* Leer archivo */
				break;
			case 2: /* Atrapar pokemon */
				//pedir_datos(almacenamiento, map_pokedex, map_pokemon, map_id, map_tipo, map_region, map_num_pokedex);
				break;
			case 3: /* Evolucionar pokemon */
				break;
			case 4: /* Buscar pokemones por tipo */
				break;
			case 5: /* Buscar pokemones por nombre */
				break;
			case 6: /* Buscar pokemon por nombre en pokedex */
				break;
			case 7: /* Mostrar todos los pokemones de la pokedex (en orden por num pokedex) */
				break;
			case 8: /* Mostrar pokemones ordenar por pc */
				break;
			case 9: /* Liberar pokemon */
				break;
			case 10: /* Mostrar pokemones por region */
				break;
			case 11: /* Salir */
				break;
			default:
				opcion = 12;
				printf("Intentelo nuevamente.\n");
				getchar();
				break;
		
		}
		
		
	}while(opcion != 11);

	return 0;
}