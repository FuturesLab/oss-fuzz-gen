#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
    // Since the header file 'icaltimezone.h' does not exist, we assume the function
    // icaltimezone_set_zone_directory is declared elsewhere in the C project.
    // We declare it here to avoid compilation errors.
    void icaltimezone_set_zone_directory(const char *zone_directory);
}

extern "C" int LLVMFuzzerTestOneInput_1010(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to be used as a string
    char *zone_directory = (char *)malloc(size + 1);
    if (zone_directory == NULL) {
        return 0;
    }
    memcpy(zone_directory, data, size);
    zone_directory[size] = '\0';

    // Call the function-under-test
    icaltimezone_set_zone_directory(zone_directory);

    // Clean up
    free(zone_directory);

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

    LLVMFuzzerTestOneInput_1010(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
