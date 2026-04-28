#include <stdint.h>
#include <stddef.h>
#include <cstring>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_598(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *patchversion = new char[size + 1];
    std::memcpy(patchversion, data, size);
    patchversion[size] = '\0';

    // Create an icalproperty object with a specific property type
    icalproperty *prop = icalproperty_new(ICAL_PATCHVERSION_PROPERTY);

    // Check if the property was created successfully
    if (prop == nullptr) {
        delete[] patchversion;
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_patchversion(prop, patchversion);

    // Add additional operations to ensure the fuzz target is effective
    const char *retrieved_version = icalproperty_get_patchversion(prop);
    if (retrieved_version != nullptr) {
        // Compare the set and retrieved versions to ensure correctness
        if (std::strcmp(patchversion, retrieved_version) != 0) {
            // Handle unexpected case
            // This block can be used to log or debug unexpected behavior
        }
    }

    // Clean up
    icalproperty_free(prop);
    delete[] patchversion;

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

    LLVMFuzzerTestOneInput_598(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
