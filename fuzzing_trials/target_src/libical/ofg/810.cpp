#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_810(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated to be used as a string
    char *version_string = (char *)malloc(size + 1);
    if (version_string == NULL) {
        return 0;
    }
    memcpy(version_string, data, size);
    version_string[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_version(version_string, NULL);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(version_string);

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

    LLVMFuzzerTestOneInput_810(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
