#include <cstdint>  // Include standard library for uint8_t
#include <cstddef>  // Include standard library for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_191(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *participant = icalcomponent_new_participant();

    // Perform any additional operations on the participant if needed
    // For instance, you might want to add properties or manipulate the component

    // Clean up
    if (participant != NULL) {
        icalcomponent_free(participant);
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

    LLVMFuzzerTestOneInput_191(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
