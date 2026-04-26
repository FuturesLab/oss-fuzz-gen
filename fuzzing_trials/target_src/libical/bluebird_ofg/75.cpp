#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for meaningful data
    if (size < 5) { // Adjust size check to ensure enough data for meaningful input
        return 0;
    }

    // Create a buffer for the attachment data
    char *attachment_data = (char *)malloc(size + 1);
    if (attachment_data == nullptr) {
        return 0;
    }

    // Copy the data into the attachment buffer and null-terminate it
    memcpy(attachment_data, data, size);
    attachment_data[size] = '\0';

    // Define a no-op free function for icalattach
    auto noop_free_fn = [](char *data, void *user_data) {
        // Do nothing, as we will handle freeing ourselves
    };

    // Create an icalattach object with the data
    icalattach *attachment = icalattach_new_from_data(attachment_data, noop_free_fn, nullptr);

    if (attachment == nullptr) {
        free(attachment_data);
        return 0;
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_new_structureddata(attachment);

    // Ensure the property is not null and has valid data
    if (property != nullptr) {
        // Optionally, perform additional operations on the property to increase coverage
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind != ICAL_NO_PROPERTY) {
            // Perform operations based on the property kind
            const char *value = icalproperty_get_value_as_string(property);
            if (value != nullptr) {
                // Process value to trigger more code paths
                size_t value_len = strlen(value);
                if (value_len > 0) {
                    // Example: Check for specific patterns or values
                }
            }
        }
        icalproperty_free(property);
    }

    // Clean up
    icalattach_unref(attachment);
    free(attachment_data);

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

    LLVMFuzzerTestOneInput_75(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
