#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h> // Correct path to the libical headers

    // Function signature from the project-under-test
    void icalproperty_set_requeststatus(icalproperty *prop, struct icalreqstattype reqstat);
}

extern "C" int LLVMFuzzerTestOneInput_1233(const uint8_t *data, size_t size) {
    // Ensure we have enough data to proceed
    if (size < sizeof(struct icalreqstattype)) {
        return 0;
    }

    // Initialize a dummy icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Prepare a icalreqstattype structure from the input data
    struct icalreqstattype reqstat;
    reqstat.code = static_cast<enum icalrequeststatus>(data[0] % 256); // Use first byte for code and cast to enum
    reqstat.desc = (const char *)(data + 1); // Use remaining bytes for desc
    reqstat.debug = (const char *)(data + 1); // Use remaining bytes for debug

    // Call the function-under-test
    icalproperty_set_requeststatus(prop, reqstat);

    // Clean up
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

    LLVMFuzzerTestOneInput_1233(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
