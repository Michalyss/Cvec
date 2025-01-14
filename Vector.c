#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
//OMAN this is a BIG...
/**
 * @brief Converts a status code into a string representation.
 *
 * @param err A status code to print information about.
 * @return A string describing the error or success.
 */
const char* Vector_error_message(const VectorError err) {
    switch (err) {
        case VECTOR_SUCCESS: return "No error";
        case VECTOR_ALLOCATION_ERROR: return "Memory allocation failed";
        case VECTOR_INDEX_OUT_OF_BOUNDS: return "Index out of bounds";
        case VECTOR_NULL_POINTER: return "Null pointer error";
        default: return "Unknown error";
    }
}

/**
 * @brief Adds an element to the vector at the end.
 *
 * @param vector The vector to append to.
 * @param elem The element to append.
 * @return A status code indicating success (VECTOR_SUCCESS) or failure (VECTOR_ALLOCATION_ERROR, VECTOR_NULL_POINTER).
 */
int Vector_append(struct Vector* vector, const int elem) {
    if (!vector) return VECTOR_NULL_POINTER;

    // If the vector is full, double the capacity
    if (vector->sz >= vector->capacity) {
        const size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;  // Start with capacity 1 if it's the first append
        int* temp = realloc(vector->elem, sizeof(int) * new_capacity);
        if (temp == NULL) {
            return VECTOR_ALLOCATION_ERROR;
        }
        vector->elem = temp;
        vector->capacity = new_capacity;  // Update capacity to the new value
    }

    // Append the new element
    vector->elem[vector->sz] = elem;
    vector->sz++;

    return VECTOR_SUCCESS;
}

/**
 * @brief Frees the resources allocated for the vector.
 *
 * @param vector The vector to free.
 * @return A status code indicating success or failure.
 */
int Vector_free(const struct Vector* vector) {
    if (!vector) return VECTOR_NULL_POINTER; // Check if the vector is NULL
    if (!vector->elem) return VECTOR_NULL_POINTER; // Check if the elements are NULL
    free(vector->elem); // Free the memory allocated for the vector's elements
    return VECTOR_SUCCESS; // Return success if memory was freed correctly
}

/**
 * @brief Removes an element from the vector at a specified position.
 *
 * @param vector The vector from which the element will be removed.
 * @param pos The position of the element to remove.
 * @return A status code indicating success (VECTOR_SUCCESS) or failure (VECTOR_NULL_POINTER, VECTOR_INDEX_OUT_OF_BOUNDS).
 */
int Vector_pop(struct Vector* vector, const int pos) {
    if (!vector) return VECTOR_NULL_POINTER;
    if (pos < 0 || pos >= vector->sz) return VECTOR_INDEX_OUT_OF_BOUNDS;

    for (int i = pos; i < vector->sz - 1; i++) {
        vector->elem[i] = vector->elem[i + 1];
    }
    vector->sz--;
    int* temp = realloc(vector->elem, sizeof(int) * vector->sz);
    if (temp != NULL || vector->sz == 0) {
        vector->elem = temp;
    }
    return VECTOR_SUCCESS;
}

/**
 * @brief Initializes a vector with the given capacity.
 *
 * @param capacity The initial capacity of the vector.
 * @return A struct Vector initialized with the specified capacity.
 */
struct Vector Vector_init(const int capacity) {
    struct Vector vector;
    vector.elem = (int*)malloc(sizeof(int) * capacity);
    if (vector.elem == NULL) {
        vector.sz = 0;
        vector.capacity = 0;
        vector.append = NULL; // NOLINT(*-use-nullptr)
        vector.pop = NULL; // NOLINT(*-use-nullptr)
        vector.free = NULL; // NOLINT(*-use-nullptr)
        vector.print = NULL; // NOLINT(*-use-nullptr)
        vector.get = NULL; // NOLINT(*-use-nullptr)
        vector.size = NULL; // NOLINT(*-use-nullptr)
        return vector;
    }
    vector.sz = 0;
    vector.capacity = capacity;
    vector.append = Vector_append;
    vector.pop = Vector_pop;
    vector.free = Vector_free;
    vector.print = Vector_print;
    vector.get = Vector_get;
    vector.size = Vector_size;

    return vector;
}

/**
 * @brief Prints all elements of the vector.
 *
 * @param vector The vector whose elements will be printed.
 */
int Vector_print(const struct Vector* vector) {
    if (!vector) return VECTOR_NULL_POINTER;

    for (int i = 0; i < vector->sz; i++) {
        int result;
        const int err = vector->get(vector, i, &result);
        if (err != VECTOR_SUCCESS) {
            fprintf(stderr, "Error: %s\n", Vector_error_message(err));
            return err;
        }
        printf("%d ", result);
    }
    printf("\n");
    return VECTOR_SUCCESS;
}

/**
 * @brief Retrieves an element at the specified index.
 *
 * @param vector The vector to retrieve an element from.
 * @param index The index of the element to retrieve.
 * @param out_elem A pointer to store the retrieved element.
 * @return A status code indicating success (VECTOR_SUCCESS) or failure (VECTOR_NULL_POINTER, VECTOR_INDEX_OUT_OF_BOUNDS).
 */
int Vector_get(const struct Vector* vector, const int index, int* out_elem) {
    if (!vector || !out_elem) return VECTOR_NULL_POINTER;
    if (index < 0 || index >= vector->sz) return VECTOR_INDEX_OUT_OF_BOUNDS;

    *out_elem = vector->elem[index];
    return VECTOR_SUCCESS;
}

/**
 * @brief Retrieves the size of the vector.
 *
 * @param vector The vector whose size will be retrieved.
 * @param out_size A pointer to store the size of the vector.
 * @return A status code indicating success (VECTOR_SUCCESS).
 */
int Vector_size(const struct Vector* vector, int* out_size) {
    if (!vector || !out_size) return VECTOR_NULL_POINTER;
    *out_size = vector->sz;
    return VECTOR_SUCCESS;
}
