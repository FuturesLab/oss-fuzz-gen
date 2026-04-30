#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_838(const uint8_t *data, size_t size) {
    // Ensure that the data is null-terminated to be safely used as a C-string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *tzname = (char *)malloc(size + 1);
    if (tzname == NULL) {
        return 0;
    }

    // Copy the data into the tzname buffer and null-terminate it
    memcpy(tzname, data, size);
    tzname[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_tzname(tzname);

    // Check if the property is created successfully
    if (property != NULL) {
        // Perform operations on the property to increase code coverage
        const char *retrieved_tzname = icalproperty_get_tzname(property);
        if (retrieved_tzname != NULL) {
            // Compare the original and retrieved timezone names
            if (strcmp(tzname, retrieved_tzname) == 0) {
                // Further operations can be added here if necessary
                // Print the retrieved timezone name for debugging purposes
                std::cout << "Timezone name: " << retrieved_tzname << std::endl;
            }
        }
        icalproperty_free(property);
    }

    // Clean up
    free(tzname);

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

    LLVMFuzzerTestOneInput_838(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
