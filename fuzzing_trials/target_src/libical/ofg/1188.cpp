#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    // Function-under-test
    // Correcting the function signature to match the header file
    icalproperty *icalproperty_vanew_url(const char *, ...);
}

extern "C" int LLVMFuzzerTestOneInput_1188(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and has a minimum length for a valid URL
    if (size < 5) {  // Assuming a minimum length for a valid URL
        return 0;
    }

    // Create a null-terminated string from the input data
    char *url = new char[size + 1];
    memcpy(url, data, size);
    url[size] = '\0';

    // Call the function-under-test
    // Provide a valid second argument to match the variadic function signature
    icalproperty *prop = icalproperty_vanew_url(url, nullptr);

    // Clean up
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    delete[] url;

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

    LLVMFuzzerTestOneInput_1188(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
