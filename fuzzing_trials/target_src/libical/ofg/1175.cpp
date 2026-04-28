#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Assuming the function is part of a library that needs to be included
extern "C" {
    const char *icaltimezone_get_zone_directory();
}

extern "C" int LLVMFuzzerTestOneInput_1175(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *zone_directory = icaltimezone_get_zone_directory();
    
    // Check the result and print it for debugging purposes
    if (zone_directory != NULL) {
        printf("Zone Directory: %s\n", zone_directory);
    } else {
        printf("Zone Directory is NULL\n");
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

    LLVMFuzzerTestOneInput_1175(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
