#include <libical/ical.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_1170(const uint8_t *data, size_t size) {
    // Ensure there's at least one byte to determine the icalcomponent_kind
    if (size < 1) {
        return 0;
    }

    // Map the first byte of data to a valid icalcomponent_kind
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0] % ICAL_NO_COMPONENT);

    // Call the function-under-test
    icalcomponent *component = icalcomponent_vanew(kind, NULL);

    // Clean up the created component to prevent memory leaks
    if (component != NULL) {
        icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_1170(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
