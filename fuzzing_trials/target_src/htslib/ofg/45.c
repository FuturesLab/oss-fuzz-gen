#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Assume the function is declared in some header file that we include
// int hfile_list_schemes(const char *, const char **, int *);

extern int hfile_list_schemes(const char *, const char **, int *);

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there is enough data for the inputs
    }

    // Split the input data into three parts for the three parameters
    size_t str1_len = size / 3;
    size_t str2_len = size / 3;
    size_t int_len = size - str1_len - str2_len;

    // Allocate memory for the strings and the integer
    char *str1 = (char *)malloc(str1_len + 1);
    char **str2 = (char **)malloc(sizeof(char *));
    int *int_ptr = (int *)malloc(sizeof(int));

    if (!str1 || !str2 || !int_ptr) {
        free(str1);
        free(str2);
        free(int_ptr);
        return 0;
    }

    // Copy data into the allocated memory
    memcpy(str1, data, str1_len);
    str1[str1_len] = '\0'; // Null-terminate the string

    *str2 = (char *)malloc(str2_len + 1);
    if (!*str2) {
        free(str1);
        free(str2);
        free(int_ptr);
        return 0;
    }

    memcpy(*str2, data + str1_len, str2_len);
    (*str2)[str2_len] = '\0'; // Null-terminate the string

    memcpy(int_ptr, data + str1_len + str2_len, int_len);

    // Call the function-under-test
    hfile_list_schemes(str1, (const char **)str2, int_ptr);

    // Free allocated memory
    free(str1);
    free(*str2);
    free(str2);
    free(int_ptr);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_45(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
