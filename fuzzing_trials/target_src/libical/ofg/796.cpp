#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the libical header
}

extern "C" int LLVMFuzzerTestOneInput_796(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the URL string and copy the data
    char *url = new char[size + 1];
    memcpy(url, data, size);
    url[size] = '\0';  // Null-terminate the string

    // Call the function under test
    icalproperty *prop = icalproperty_new_url(url);

    // Clean up
    if (prop != NULL) {
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

    LLVMFuzzerTestOneInput_796(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
