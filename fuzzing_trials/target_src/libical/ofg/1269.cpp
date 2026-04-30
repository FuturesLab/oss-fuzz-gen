#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1269(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely convert to a C string
    char *organizer = new char[size + 1];
    memcpy(organizer, data, size);
    organizer[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_organizer(organizer);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    delete[] organizer;

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

    LLVMFuzzerTestOneInput_1269(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
