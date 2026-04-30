#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for size_t and free
#include <cstring> // Include for memcpy
#include <string>  // Include for std::string

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_363(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to populate icalreqstattype
    if (size < sizeof(struct icalreqstattype)) {
        return 0;
    }

    // Initialize icalreqstattype structure with data from the fuzzer
    struct icalreqstattype reqstattype;
    memcpy(&reqstattype, data, sizeof(struct icalreqstattype));

    // Validate the icalreqstattype fields before using them
    if (reqstattype.code < ICAL_UNKNOWN_STATUS || reqstattype.code > ICAL_STATUS_X) {
        return 0;
    }

    // Call the function-under-test
    char *result = icalreqstattype_as_string_r(reqstattype);

    // Check if result is valid
    if (result != NULL) {
        // Ensure the result is a valid string
        if (std::strlen(result) > 0) {
            // Do something with the result if needed
        }
        free(result);
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

    LLVMFuzzerTestOneInput_363(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
