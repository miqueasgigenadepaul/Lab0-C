#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h> // para UINT_MAX

#define ARRAY_SIZE 4

struct bound_data { // bound de limite (en este caso superior o inferior)
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.is_upperbound = true;
    res.is_lowerbound = true;
    res.exists = false;
    res.where = UINT_MAX; // representa el valor maximo que puede almacenar un variable de tipo unsigned int

    for (unsigned int i = 0; i < length; i++){
        if (arr[i] > value){
            res.is_upperbound = false;
        }
        if (arr[i] < value){
            res.is_lowerbound = false; 
        }
        if (arr[i] == value) {
            res.exists = true;
            res.where = i;
        }
    }
    return res;
}

int main(void) {
    int a[ARRAY_SIZE];
    int value;
    
    // pedir entrada al usuario
    printf("Ingrese %d elementos del arreglo\n", ARRAY_SIZE);

    for(int i = 0; i < ARRAY_SIZE; i++){
        scanf("%d", &a[i]);
    }

    printf("Ingrese un valor: ");
    scanf("%d", &value);

    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    if (result.is_upperbound){
        printf("%d es una cota superior\n", value);
    }
    if (result.is_lowerbound) {
        printf("%d es una cota inferior\n", value);
    }
    if (result.exists){
        printf("%d se encuentra en el arreglo en la posicion %u\n", value, result.where);
        if (result.is_upperbound) {
            printf("Es el maximo\n");
        }
        if(result.is_lowerbound){
            printf("Es el minimo\n");
        }
    }

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    printf("%d ", result.is_upperbound); // Imprime 1 (verdadero)
    printf("%d ", result.is_lowerbound); // Imprime 0 (falso)
    printf("%d ", result.exists);        // Imprime 1 (true)
    printf("%u ", result.where);         // Imprime 0-3 (posicion donde se encontro el valor en el arreglo, sino UINT MAX)

    return EXIT_SUCCESS;
}

