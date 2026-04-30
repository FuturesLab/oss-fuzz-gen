#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1073(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use as a C-string
    if (size == 0) {
        return 0; // No need to proceed if there's no data
    }

    char *description = new char[size + 1];
    memcpy(description, data, size);
    description[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_description(description);

    // Additional processing to increase code coverage
    if (prop != nullptr) {
        // Access some properties or methods to ensure the object is fully utilized
        const char *desc = icalproperty_get_description(prop);
        if (desc != nullptr) {
            // Do something with desc to ensure it is accessed
            volatile size_t len = strlen(desc); // Use volatile to prevent optimization
            (void)len; // Suppress unused variable warning

            // Modify the description to test setter functionality
            icalproperty_set_description(prop, "Modified description");

            // Retrieve the modified description
            const char *new_desc = icalproperty_get_description(prop);
            if (new_desc != nullptr) {
                volatile size_t new_len = strlen(new_desc); // Use volatile to prevent optimization
                (void)new_len; // Suppress unused variable warning
            }
        }

        // Test other functionalities to maximize code coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind != ICAL_NO_PROPERTY) {
            volatile int kind_value = static_cast<int>(kind); // Use volatile to prevent optimization
            (void)kind_value; // Suppress unused variable warning
        }

        // Clean up
        icalproperty_free(prop);
    }

    delete[] description;

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

    LLVMFuzzerTestOneInput_1073(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
