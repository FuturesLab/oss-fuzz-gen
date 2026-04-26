#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "libical/ical.h"

extern "C" {
    #include "libical/icalproperty.h"
}

extern "C" {
    void icalproperty_set_pollcompletion(icalproperty *, enum icalproperty_pollcompletion);
}

extern "C" int LLVMFuzzerTestOneInput_975(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract an enumeration value
    if (size < sizeof(enum icalproperty_pollcompletion)) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_NO_PROPERTY);

    // Extract an enumeration value from the input data
    enum icalproperty_pollcompletion pollcompletion = 
        static_cast<enum icalproperty_pollcompletion>(data[0] % 3); // Assuming there are 3 enum values

    // Call the function-under-test
    icalproperty_set_pollcompletion(property, pollcompletion);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_975(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
