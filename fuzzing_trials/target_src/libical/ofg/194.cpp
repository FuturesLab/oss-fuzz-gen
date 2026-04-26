#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *icalStr = (char *)malloc(size + 1);
    if (icalStr == nullptr) {
        return 0;
    }

    // Copy the data into the string and null-terminate it
    memcpy(icalStr, data, size);
    icalStr[size] = '\0';

    // Parse the string into an icalproperty
    icalproperty *prop = icalproperty_new_from_string(icalStr);
    free(icalStr);

    // Ensure the property was created successfully
    if (prop == nullptr) {
        return 0;
    }

    // Call the function-under-test
    const char *replyUrl = icalproperty_get_replyurl(prop);

    // Optionally, do something with replyUrl
    // (e.g., check if it's a valid URL, print it, etc.)

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

    LLVMFuzzerTestOneInput_194(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
