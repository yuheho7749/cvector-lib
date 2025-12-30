#include <stdio.h>
#include <stdlib.h>
#include <vector.h>

int main(void) {
    vector_t* vec;
    int status;

    printf("=== c vector test ===\n");

    // Initialize vector for int64_t
    status = vector_create(&vec, sizeof(int64_t), 1);
    printf("vec %p\n", vec);
    if (status != 0) {
        printf("vector_init failed: %d\n", status);
        return status;
    }

    // Append some integers
    for (int64_t i = 0; i < 8; i++) {
        status = vector_append(vec, &i);
        if (status != 0) {
            fprintf(stderr, "vector_append failed at %ld: %d\n", i, status);
            vector_destroy(vec);
            return status;
        }
        printf("Appended %ld\n", i);
    }

    // Retrieve and print values
    printf("Vector contents:\n");
    for (size_t i = 0; i < vec->size; i++) {
        int64_t* value = (int64_t*)vector_get(vec, i);
        printf("[%zu] = %ld\n", i, *value);
        printf("elem %p\n", value);
    }

    for (int64_t i = 8; i < 13; i++) {
        status = vector_append(vec, &i);
        if (status != 0) {
            fprintf(stderr, "vector_append failed at %ld: %d\n", i, status);
            vector_destroy(vec);
            return status;
        }
        printf("Appended %ld\n", i);
    }

    printf("Vector contents:\n");
    for (size_t i = 0; i < vec->size; i++) {
        int64_t* value;
        status = vector_get_safe(vec, i, (void**)&value);
        if (status != 0) {
            fprintf(stderr, "vector_get failed at index %zu: %d\n", i, status);
            vector_destroy(vec);
            return status;
        }
        printf("[%zu] = %ld\n", i, *value);
        printf("elem %p\n", value);
    }

    // Free vector memory
    vector_destroy(vec);
    printf("Vector memory freed.\n");

    return 0;
}
