#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Declare the function prototype since the header is not available
    const char* icaltimezone_get_system_zone_directory();
}

// Fuzzing harness for the function-under-test
extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *zone_directory = icaltimezone_get_system_zone_directory();

    // Optionally, you can print the result for debugging purposes
    if (zone_directory != NULL) {
        printf("System Zone Directory: %s\n", zone_directory);
    } else {
        printf("System Zone Directory is NULL\n");
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

    LLVMFuzzerTestOneInput_161(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
