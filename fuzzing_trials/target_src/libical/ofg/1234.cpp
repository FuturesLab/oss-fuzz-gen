#include <stdint.h>
#include <stddef.h>
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1234(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < sizeof(struct icalreqstattype) + 2) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (!prop) {
        return 0;
    }

    // Create an icalreqstattype structure
    struct icalreqstattype req_status;
    req_status.code = (enum icalrequeststatus)(data[0] % 100); // Set a code from data
    size_t str_size = size - 1;
    char *desc = (char *)malloc(str_size);
    char *debug = (char *)malloc(str_size);

    if (desc && debug) {
        memcpy(desc, data + 1, str_size - 1);
        memcpy(debug, data + 1, str_size - 1);
        desc[str_size - 1] = '\0';
        debug[str_size - 1] = '\0';

        req_status.desc = desc;
        req_status.debug = debug;

        // Call the function-under-test
        icalproperty_set_requeststatus(prop, req_status);

        // Clean up
        free(desc);
        free(debug);
    }

    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_1234(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
