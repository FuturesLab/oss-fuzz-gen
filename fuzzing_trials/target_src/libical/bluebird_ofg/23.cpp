#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"

    // Function-under-test
    icalproperty_pollcompletion icalproperty_get_pollcompletion(const icalproperty *);
}

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty_pollcompletion value
    if (size < sizeof(enum icalproperty_pollcompletion)) {
        return 0;
    }

    // Extract a pollcompletion value from the input data
    enum icalproperty_pollcompletion pollcompletion_value = 
        static_cast<enum icalproperty_pollcompletion>(data[0]);

    // Create a dummy icalproperty object with the extracted pollcompletion value
    icalproperty *property = icalproperty_new_pollcompletion(pollcompletion_value);

    // Call the function-under-test
    icalproperty_pollcompletion result = icalproperty_get_pollcompletion(property);

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

    LLVMFuzzerTestOneInput_23(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
