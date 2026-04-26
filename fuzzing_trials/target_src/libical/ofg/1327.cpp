#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1327(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *organizer = (char *)malloc(size + 1);
    if (organizer == NULL) {
        return 0;
    }
    memcpy(organizer, data, size);
    organizer[size] = '\0';

    // Call the function under test
    icalproperty *prop = icalproperty_vanew_organizer(organizer, NULL);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    free(organizer);

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

    LLVMFuzzerTestOneInput_1327(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
