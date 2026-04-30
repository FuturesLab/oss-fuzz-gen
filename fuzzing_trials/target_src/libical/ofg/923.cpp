extern "C" {
#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cctype>  // Include cctype for isprint
}

extern "C" int LLVMFuzzerTestOneInput_923(const uint8_t *data, size_t size) {
    // Ensure data is not empty and has a reasonable length for a UID
    if (size == 0 || size > 1000) return 0;

    // Copy the data into a null-terminated string
    char *uid = new char[size + 1];
    memcpy(uid, data, size);
    uid[size] = '\0';

    // Basic validation to ensure the UID is a printable string
    for (size_t i = 0; i < size; ++i) {
        if (!isprint(uid[i])) {
            delete[] uid;
            return 0;
        }
    }

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_uid(uid);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Utilize the property to potentially explore more code paths
        const char *retrieved_uid = icalproperty_get_uid(prop);
        if (retrieved_uid) {
            // Compare the set and retrieved UID to ensure correctness
            if (strcmp(uid, retrieved_uid) != 0) {
                // Log an error or handle the mismatch case
                fprintf(stderr, "Mismatch: set UID '%s', retrieved UID '%s'\n", uid, retrieved_uid);
            }
        }

        // Further utilize the property to explore more code paths
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind != ICAL_NO_PROPERTY) {
            // Do something with the kind to explore more paths
        }

        // Clean up the property
        icalproperty_free(prop);
    }

    // Free allocated memory
    delete[] uid;

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

    LLVMFuzzerTestOneInput_923(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
