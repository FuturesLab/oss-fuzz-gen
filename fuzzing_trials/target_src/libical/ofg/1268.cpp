#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1268(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use it as a C-string.
    char *organizer = (char *)malloc(size + 1);
    if (!organizer) {
        return 0;
    }

    // Copy the input data into the organizer string and null-terminate it.
    memcpy(organizer, data, size);
    organizer[size] = '\0';

    // Call the function-under-test with the organizer string.
    icalproperty *prop = icalproperty_new_organizer(organizer);

    // Clean up allocated resources.
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

    LLVMFuzzerTestOneInput_1268(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
