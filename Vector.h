#ifndef VECTOR_H
#define VECTOR_H
#pragma once

/**
 * @brief Forward declaration of the Vector structure.
 */
struct Vector;

/**
 * @brief Typedef for the Vector structure for easier usage.
 */
typedef struct Vector Vector;

/**
 * @brief The Vector structure represents a dynamic array.
 *
 * This structure contains the vector's elements, the current size of the
 * vector, the current capacity, and function pointers for common operations such as appending,
 * popping, and retrieving elements.
 */
struct Vector {
    int* elem;  ///< Pointer to the array of elements in the vector.
    int sz;     ///< The current size (number of elements) in the vector.
    size_t capacity;  ///< The current capacity of the vector (change this from int to size_t).


    // Function pointers for vector operations.
    int (*free)(const struct Vector* vector);    ///< Function to free the vector's memory.
    int (*append)(struct Vector* vector, int elem); ///< Function to append an element to the vector.
    int (*pop)(struct Vector* vector, int pos);    ///< Function to remove an element from the vector at the given position.
    int (*print)(const struct Vector* vector);    ///< Function to print all elements of the vector.
    int (*get)(const struct Vector* vector, const int index, int* out_elem); ///< Function to retrieve an element at the specified index.
    int (*size)(const struct Vector* vector, int* out_size); ///< Function to retrieve the size of the vector.
};

/**
 * @brief Enumeration of error codes returned by vector functions.
 */
typedef enum {
    VECTOR_SUCCESS,             ///< Operation succeeded without errors.
    VECTOR_ALLOCATION_ERROR,    ///< Memory allocation failed.
    VECTOR_INDEX_OUT_OF_BOUNDS, ///< The provided index is out of bounds.
    VECTOR_NULL_POINTER         ///< The provided pointer is NULL.
} VectorError;

/**
 * @brief Initializes a new vector with the given initial capacity.
 *
 * @param capacity The initial capacity of the vector.
 * @return A new vector initialized with the specified capacity.
 */
struct Vector Vector_init(int capacity);

/**
 * @brief Frees the resources allocated for the vector.
 *
 * @param vector The vector to free.
 * @return A status code indicating success or failure.
 */
int Vector_free(const struct Vector* vector);

/**
 * @brief Appends an element to the vector.
 *
 * @param vector The vector to append the element to.
 * @param elem The element to append.
 * @return A status code indicating success or failure (VECTOR_SUCCESS or VECTOR_ALLOCATION_ERROR).
 */
int Vector_append(struct Vector* vector, int elem);

/**
 * @brief Removes an element from the vector at a specified position.
 *
 * @param vector The vector to remove an element from.
 * @param pos The position of the element to remove.
 * @return A status code indicating success or failure (VECTOR_SUCCESS, VECTOR_INDEX_OUT_OF_BOUNDS).
 */
int Vector_pop(struct Vector* vector, int pos);

/**
 * @brief Prints all elements of the vector.
 *
 * @param vector The vector whose elements will be printed.
 */
int Vector_print(const struct Vector* vector);

/**
 * @brief Converts a status code into a string representation.
 *
 * @param err A status code to print information about.
 * @return A string describing the error or success.
 */
const char* Vector_error_message(VectorError err);

/**
 * @brief Retrieves an element at the specified index.
 *
 * @param vector The vector to retrieve an element from.
 * @param index The index of the element to retrieve.
 * @param out_elem A pointer to store the retrieved element.
 * @return A status code indicating success or failure (VECTOR_SUCCESS or VECTOR_INDEX_OUT_OF_BOUNDS).
 */
int Vector_get(const struct Vector* vector, const int index, int* out_elem);

/**
 * @brief Retrieves the size of the vector.
 *
 * @param vector The vector whose size will be retrieved.
 * @param out_size A pointer to store the size of the vector.
 * @return A status code indicating success or failure (VECTOR_SUCCESS).
 */
int Vector_size(const struct Vector* vector, int* out_size);

#endif // VECTOR_H
