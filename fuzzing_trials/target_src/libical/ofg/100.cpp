#include <stdint.h>
#include <stdbool.h>

// Assuming these are the correct headers for the functions and types used
extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/icalenums.h>
}

extern "C" {

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract an icalcomponent_kind
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract an icalcomponent_kind from the input data
    icalcomponent_kind kind = *(const icalcomponent_kind *)data;

    // Call the function-under-test
    bool is_valid = icalcomponent_kind_is_valid(kind);

    // Use the result to avoid any compiler optimizations removing the call
    if (is_valid) {
        // Do something trivial
        volatile bool dummy = is_valid;
        (void)dummy;
    }

    return 0;
}

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

    LLVMFuzzerTestOneInput_100(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
