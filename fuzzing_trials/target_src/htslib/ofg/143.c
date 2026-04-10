#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assume the function is declared in some header file
int hfile_list_schemes(const char *, const char **, int *);

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 3) {
        return 0;
    }

    // Allocate memory for the first parameter
    char *param1 = (char *)malloc(size + 1);
    if (param1 == NULL) {
        return 0;
    }
    memcpy(param1, data, size);
    param1[size] = '\0'; // Null-terminate the string

    // Prepare a set of strings for the second parameter
    const char *schemes[] = {"http", "https", "ftp", "file"};
    const char **param2 = schemes;

    // Prepare an integer for the third parameter
    int param3 = 0;

    // Call the function-under-test
    hfile_list_schemes(param1, param2, &param3);

    // Clean up
    free(param1);

    return 0;
}