#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"

extern "C" {
    // Function-under-test
    void icalvalue_reset_kind(icalvalue *);
}

extern "C" int LLVMFuzzerTestOneInput_375(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create an icalvalue
    if (size < 1) {
        return 0;
    }

    // Create a new icalvalue of a random kind
    icalvalue_kind kind = static_cast<icalvalue_kind>(data[0] % ICAL_NO_VALUE);
    icalvalue *value = icalvalue_new(kind);

    // Fuzz the function-under-test
    if (value != NULL) {
        icalvalue_reset_kind(value);
        icalvalue_free(value);
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

    LLVMFuzzerTestOneInput_375(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
