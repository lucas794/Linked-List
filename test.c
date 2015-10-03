#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "testing.h"
#include "lista.h"

bool imprimir_elementos_enteros(void *dato, void* extra)
{
	int *contador = extra;
	printf("%d.- %d\n", ++(*contador), *(int*) dato);
	return true;
}

void imprimir_lista_iter_externo(lista_t *lista)
{
	lista_iter_t* iterador_externo_lista3 = lista_iter_crear(lista);
	printf("Mostrando elementos CON iterador externo...\n");
	while(!lista_iter_al_final(iterador_externo_lista3))
	{
		printf("%d-", *(int *) lista_iter_ver_actual(iterador_externo_lista3));
		lista_iter_avanzar(iterador_externo_lista3);
	}
	printf("\n");
	lista_iter_destruir(iterador_externo_lista3);
}

bool imprimir_profesores(void *dato, void* extra)
{
	printf("%s, ", (char *) dato);
	return true;
}

void pruebas_lista_alumno()	{
	lista_t* lista1 = lista_crear();
	print_test("[PRUEBA 1] Inicio de las pruebas para la primera lista", true);
	print_test("[PRUEBA 1] Lista está vacia ?", lista_esta_vacia(lista1));
	
	int iEnterosAInsertar[ ] = { 32, 63, 44, 54, 99 };
	int iContador = 0;
	
	print_test("[PRUEBA 1] Prueba de insertar al inicio", true);
	print_test("\n\n[PRUEBA 1] Insertando al principio el primer elemento de un arreglo", lista_insertar_primero(lista1, &iEnterosAInsertar[iContador]));
	print_test("[PRUEBA 1] Insertando al principio el segundo elemento de un arreglo", lista_insertar_primero(lista1, &iEnterosAInsertar[++iContador]));
	print_test("[PRUEBA 1] Insertando al principio el tercer elemento de un arreglo", lista_insertar_primero(lista1, &iEnterosAInsertar[++iContador]));
	print_test("[PRUEBA 1] Insertando al principio el cuarto elemento de un arreglo", lista_insertar_primero(lista1, &iEnterosAInsertar[++iContador]));
	print_test("[PRUEBA 1] Insertando al principio el quinto elemento de un arreglo", lista_insertar_primero(lista1, &iEnterosAInsertar[++iContador]));
	
	//La lista queda aquí del estilo [99, 54, 44, 63, 32] de forma momentanea..
	print_test("[PRUEBA 1] El primero coincide con el &arreglo[4]?", lista_ver_primero(lista1) == &iEnterosAInsertar[iContador]);
	print_test("[PRUEBA 1] La lista tiene elementos", !lista_esta_vacia(lista1));
	print_test("[PRUEBA 1] La cantidad de elementos de la lista es 5?", (++iContador == lista_largo(lista1)));
	print_test("\n[PRUEBA 1] Prueba de insertar al final", 1);
	
	print_test("[PRUEBA 1] Insertando al final el último elemento de un arreglo", lista_insertar_ultimo(lista1, &iEnterosAInsertar[--iContador]));
	print_test("[PRUEBA 1] Insertando al final el último elemento de un arreglo", lista_insertar_ultimo(lista1, &iEnterosAInsertar[--iContador]));
	print_test("[PRUEBA 1] Insertando al final el último elemento de un arreglo", lista_insertar_ultimo(lista1, &iEnterosAInsertar[--iContador]));
	print_test("[PRUEBA 1] Insertando al final el último elemento de un arreglo", lista_insertar_ultimo(lista1, &iEnterosAInsertar[--iContador]));
	print_test("[PRUEBA 1] Insertando al final el último elemento de un arreglo", lista_insertar_ultimo(lista1, &iEnterosAInsertar[--iContador]));
	
	//Aquí la lista es [99, 54, 44, 63, 32, 99, 54, 44, 63, 32]
	/* Recordemos , que tenemos la lista con el doble de los elementos ... */
	print_test("[PRUEBA 1] La cantidad de elementos de la lista es 10?", (lista_largo(lista1) == ((sizeof(iEnterosAInsertar) / sizeof(int)) * 2)));
	lista_destruir(lista1, NULL);
	
	lista_t* lista2 = lista_crear();
	print_test("\n[PRUEBA 2] Prueba (Sencilla) de elementos de tipo char con MALLOC", true);
	
	char* nombreProfesora = malloc(sizeof(char) * 22 );
	if( !nombreProfesora )
	{
		print_test( "ERROR AL PEDIR MEMORIA", false );
		return;
	}
		
	strcpy(nombreProfesora, "Rosita Wachenchauzer");
	
	print_test("\n\n[PRUEBA 2] Lista está vacia", lista_esta_vacia(lista2));
	
	// recordemos , que la lista está vacia en este punto y si insertamos al final un nodo éste será el último y el primero.
	print_test("[PRUEBA 2] Insertando nombre profesora tutora de Algoritmos y Programacion II (Con lista_insertar_ultimo)", lista_insertar_ultimo(lista2, nombreProfesora));
	print_test("[PRUEBA 2] Lista NO está vacia ?", !lista_esta_vacia(lista2));
	
	// Confirmamos que el último ingresado a la vez se convierte en el primero.
	print_test("[PRUEBA 2] Verificar que el primer elemento coincida con el string insertado", lista_ver_primero(lista2) == nombreProfesora);
	
	lista_destruir(lista2, free);
	
	lista_t* lista3 = lista_crear();
	print_test("\n[PRUEBA 3] Prueba de un array de enteros, pero con ITERADOR", true);
	for( int *puntero = iEnterosAInsertar; puntero != iEnterosAInsertar + 5 ; puntero++ )
	{
		print_test("[PRUEBA 3] [LOOP] Ingresando datos del array de enteros", lista_insertar_primero(lista3, puntero));
	}
	lista_iter_t* iterador_lista_3 = lista_iter_crear(lista3);
	
	print_test("[PRUEBA 3] Visualizamos la lista para confirmar el ingreso", true);
	
	// La lista aquí es de [99, 54, 44, 63, 32] pero con las referencias de memoria!!
	// El iterador está parado en '99'
	int elementosTotales = 0;
	lista_iterar(lista3, imprimir_elementos_enteros, &elementosTotales); //Mostremos sencillamente la lista
	
	print_test("[PRUEBA 3] El largo de la lista enlazada coincide con el extra pasado por parámetro de lista_iterar", lista_largo(lista3) == elementosTotales);
	
	// Probemos avanzar el iterador 2 veces y veamos donde está parado
	print_test("[PRUEBA 3] Avanzo con el iterador", lista_iter_avanzar(iterador_lista_3));
	print_test("[PRUEBA 3] Avanzo con el iterador", lista_iter_avanzar(iterador_lista_3));
	
	// En teoria, estamos parados en la posicion del 44, es cierto?
	print_test("[PRUEBA 3] El iterador está parado sobre la referencia de 44 (index 2)?", lista_iter_ver_actual(iterador_lista_3) == &iEnterosAInsertar[2]);
	print_test("[PRUEBA 3] El iterador NO ESTÁ parado en el final?", !lista_iter_al_final(iterador_lista_3));
	
	// Probemos insertando AQUÍ un nuevo valor, 88 ejemplo.
	// La listá quedara del estilo [99, 54, 49, 44, 63, 32]
	int dato = 88;
	print_test("[PRUEBA 3] Insertando en la posicion del 44 la referencia del numero 88", lista_insertar(lista3, iterador_lista_3, &dato));
	print_test("[PRUEBA 3] Mostramos la lista para verificar las actualizaciones", true);
	elementosTotales = 0;
	lista_iterar(lista3, imprimir_elementos_enteros, &elementosTotales); // mostramos la lista para confirmar la actualización
	
	/* Llegados aquí , la lista es [99, 54, 49, 88, 44, 63, 32] , avanzemos hasta el último y borremos el último dato */
	print_test("[PRUEBA 3] Estamos parados en el 88?", lista_iter_ver_actual(iterador_lista_3) == &dato);
	print_test("[PRUEBA 3] Avanzo con el iterador", lista_iter_avanzar(iterador_lista_3));
	print_test("[PRUEBA 3] Avanzo con el iterador", lista_iter_avanzar(iterador_lista_3));
	print_test("[PRUEBA 3] Avanzo con el iterador", lista_iter_avanzar(iterador_lista_3));
	
	/* borramos el último y preguntamos si estamos parado en el FINAL */
	print_test("[PRUEBA 3] Una vez borrado el último elemento, estamos parados en el final?", lista_borrar(lista3, iterador_lista_3) && lista_iter_al_final(iterador_lista_3));
	
	elementosTotales = 0;
	print_test("[PRUEBA 3] Mostramos la actualizacion de la lista", true); // mostramos la lista para confirmar la última actualizacion
	lista_iterar(lista3, imprimir_elementos_enteros, &elementosTotales);
	
	//Imprimimos de forma externa
	imprimir_lista_iter_externo(lista3);
	
	lista_iter_destruir(iterador_lista_3);
	lista_destruir(lista3, NULL);
	
	char *szDocentesParaApilar[] = { "dato", "fede b", "martin b", "sebas", "daniela",
									"rosita", "ana", "jenny", "fede e", "emiliano", "nacho", NULL};
	int iLargoDocentes = 11;
				 
	lista_t* lista_4 = lista_crear();
	lista_iter_t* iter_l4 = lista_iter_crear(lista_4);
	print_test("\n\n[PRUEBA 4] Lista vacia, probar funcionalidad del iterador con listas vacias", true);
	print_test("[PRUEBA 4] Efectivamente, la lista está vacia?", lista_esta_vacia(lista_4));
	
	/* intentamos borrar el elemento primero, esto devolvera NULL ya que no se puede realizar esto */
	print_test("[PRUEBA 4] El borrar el primer elemento es NULL? En este caso significa que no se puede borrar el primero", lista_borrar(lista_4, iter_l4) == NULL);
	print_test("[PRUEBA 4] Ahora, insertamos un array de profesores", true);
	
	for( char **p = szDocentesParaApilar; *p ; p++ )
	{
		print_test("[PRUEBA 4] Insertando docentes del array", lista_insertar(lista_4, iter_l4, *p));
		
		if( !(p + 1) ) // Quiero parar en el último (nacho)
			lista_iter_avanzar(iter_l4);
	}
	print_test("[PRUEBA 4] El último es NACHO?", !strcmp(lista_iter_ver_actual(iter_l4), szDocentesParaApilar[iLargoDocentes - 1]));
	
	print_test("[PRUEBA 4] Abajo mostraré los profesores para ver si se insertaron todos OK", true);
	lista_iterar(lista_4, imprimir_profesores, NULL);
	printf("\n");
	
	lista_iter_t* iterador2_4 = lista_iter_crear(lista_4);
	lista_iter_avanzar(iterador2_4);
	print_test("[PRUEBA 4] Excepto dato, intento borrar a todos", true);
	
	// Borro todos los elementos que terminen en la posicion 2.
	while( !lista_iter_al_final(iterador2_4) )
		 print_test("[PRUEBA 4] Borrando...", lista_borrar(lista_4, iterador2_4));

	print_test("[PRUEBA 4] El largo de la lista es 1?", lista_largo(lista_4) == 1);
	print_test("[PRUEBA 4] Efectivamente, el primero coincide con dato?", strcmp(lista_ver_primero(lista_4), szDocentesParaApilar[0]));
	lista_destruir(lista_4, NULL);
	lista_iter_destruir(iter_l4);
	lista_iter_destruir(iterador2_4);
}
