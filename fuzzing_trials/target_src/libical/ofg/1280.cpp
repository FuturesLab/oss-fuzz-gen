#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1280(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Create a buffer to hold a null-terminated string
    char *filename = new char[size + 1];
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_xlicmimefilename(filename);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    delete[] filename;

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

    LLVMFuzzerTestOneInput_1280(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
