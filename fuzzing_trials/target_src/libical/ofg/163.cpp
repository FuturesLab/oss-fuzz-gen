#include <libical/ical.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an icalcomponent_kind
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract the icalcomponent_kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(*reinterpret_cast<const int*>(data));

    // Call the function-under-test
    icalcomponent *component = icalcomponent_vanew(kind, nullptr);

    // Clean up
    if (component != nullptr) {
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_163(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
