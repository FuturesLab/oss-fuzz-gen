#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// Assuming the function is defined somewhere in the linked libraries
extern const char * hts_feature_string(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Call the function-under-test with the fuzzing input
    const char *result = hts_feature_string(data, size);

    // Optionally, you can do something with the result, like printing it
    // For debugging purposes, you might want to print the result
    if (result != NULL) {
        printf("Result: %s\n", result);
    }

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

    LLVMFuzzerTestOneInput_215(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
