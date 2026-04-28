#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the necessary library for memcpy

extern "C" {
    #include <libical/ical.h> // Ensure libical is installed and linked correctly

    void icalproperty_set_maxdate(icalproperty *, struct icaltimetype);
}

extern "C" int LLVMFuzzerTestOneInput_949(const uint8_t *data, size_t size) {
    // Check if the input size is large enough to create an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_NO_PROPERTY);
    if (property == NULL) {
        return 0; // If property creation fails, exit
    }

    // Create an icaltimetype object from the input data
    struct icaltimetype maxdate;
    memcpy(&maxdate, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    icalproperty_set_maxdate(property, maxdate);

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

    LLVMFuzzerTestOneInput_949(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
