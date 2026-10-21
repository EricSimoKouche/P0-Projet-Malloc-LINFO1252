#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

uint8_t MY_HEAP[64000];

int least_power_of_two(int value) {
    uint32_t power_of_two = 1;
    while (power_of_two < value) 
        power_of_two *= 2;   
    return power_of_two;
}

void init() {
    Meta_t *first = (Meta_t *) MY_HEAP;
    first->block_size = sizeof(MY_HEAP);
    first->next = NULL;
}

void *my_malloc(size_t size) {
    // 0. Mauvaise taille entrée par l'utilisateur
    if (size == 0) return NULL;

    Meta_t *first = (Meta_t *) MY_HEAP;
    // 1. Calcul de la veritable a alloué
    uint32_t new_size = least_power_of_two(size + sizeof(Meta_t));

    // 2. Parcourir la mémoire à la recherche d'un bloc disponible
    Meta_t *current = first;
    while (current != NULL &&                       // Si l'on n'est pas arrivé a la fin
            ((current->block_size & 0x1) != 0 ||    // Le bloc est déjà alloué
            current->block_size < new_size)) {      // Le bloc n'a pas l'espace nécéssaire
        current = current->next;
    }
    // 3. La fin de la mémoire a été atteint
    if (current == NULL) return NULL;

    // 4. Sinon, on met à jour la taille du bloc courant et on le marque comme occupé en forcant le bit de poids faible à 1.
    uint32_t old_size = current->block_size & ~0x1;

    // 5. Créer la prochaine metadonée qui suivra le bloc alloué
    // Check si la mémoire restante permettra de pouvoir stockée une metadonnée
    if (old_size - new_size > sizeof(Meta_t)){
        uint8_t *p = (uint8_t*) current;
        Meta_t* next = (Meta_t*) (p + new_size);
        next->block_size = old_size - new_size;
        next->next = current->next;
        current->next = next;
        current->block_size = new_size | 0x1;
    }
    // Sinon, on alloue l'entiereté de la memoire restante
    else {
        current->block_size = old_size | 0x1;
    }

    // 6. Retourner un pointeur vers la mémoire demandée
    return (void *) (current + 1);
}

void my_free(void *pointer) {
    
}

int main(void) {
    printf("la taille de la structure est de %zu.\n", sizeof(struct Meta));
    printf("La taille de ma mémoire est de %zu.\n", sizeof(MY_HEAP));
    init();
    void *ptr1 = my_malloc(1000);
    int iteration = 1;
    while (ptr1 != NULL) {
        printf("Itération n° %2.d ; ptr1 pointe vers %p.\n", iteration, ptr1);
        ptr1 = my_malloc(1000);
        iteration++;
    }
    return 0;
}
