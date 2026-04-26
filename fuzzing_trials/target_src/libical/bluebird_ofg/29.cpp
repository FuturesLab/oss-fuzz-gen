#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstddef>
#include <cstring> // Include this for strlen
#include <cstdlib> // Include this for malloc and free

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create an icalattach
    if (size < 1) {
        return 0;
    }

    // Ensure the data is null-terminated to prevent buffer overflow in strlen
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create an icalattach from the input data
    icalattach *attachment = icalattach_new_from_data(null_terminated_data, NULL, NULL);

    // Check if attachment creation was successful
    if (attachment == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Create an icalproperty using the attachment
    icalproperty *property = icalproperty_vanew_attach(attachment, NULL);

    // Check if property creation was successful
    if (property != NULL) {
        // Manipulate the property to ensure different code paths are exercised
        icalproperty_set_attach(property, attachment);

        // Additional operations to increase code coverage
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind == ICAL_ATTACH_PROPERTY) {
            icalattach *retrieved_attachment = icalproperty_get_attach(property);
            if (retrieved_attachment != NULL) {
                const char *value = reinterpret_cast<const char *>(icalattach_get_data(retrieved_attachment));
                if (value != NULL) {
                    // Perform operations on the value
                    size_t value_length = strlen(value);
                    if (value_length > 0) {
                        // Example operation: check if the value is a valid URL
                        icalattach *new_attachment = icalattach_new_from_url(value);
                        if (new_attachment != NULL) {
                            icalattach_unref(new_attachment);
                        }
                    }
                }
                // Do not unref retrieved_attachment here as it is the same as attachment
            }
        }

        icalproperty_free(property);
    }

    // Clean up
    icalattach_unref(attachment);
    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_29(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
