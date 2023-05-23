#include "shell.h"

/**
 * free_arraybid - frees a bidimensional array
 * @arr: double pointer that points to the address of memory of an array
 */
void free_arraybid(char **arr)
{
    int i;

    for (i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}
