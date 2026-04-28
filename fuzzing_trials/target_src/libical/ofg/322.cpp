#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_322(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to fill the icaldurationtype structure
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Cast the input data to an icaldurationtype structure
    struct icaldurationtype duration;
    memcpy(&duration, data, sizeof(struct icaldurationtype));

    // Call the function-under-test
    char *ical_string = icaldurationtype_as_ical_string(duration);

    // Free the returned string if it's not NULL
    if (ical_string != NULL) {
        free(ical_string);
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

    LLVMFuzzerTestOneInput_322(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
