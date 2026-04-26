#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

// Wrap the libical includes in extern "C" since the project is written in C
extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an enumeration value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an enumeration value from the input data
    icalproperty_xlicclass xlicclass =
        static_cast<icalproperty_xlicclass>(data[0] % 3); // Assuming there are 3 classes

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_xlicclass(xlicclass, NULL);

    // Clean up if necessary
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_230(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
