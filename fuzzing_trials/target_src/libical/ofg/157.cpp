extern "C" {
    #include <libical/ical.h>
}

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *x_name = new char[size + 1];
    if (!x_name) {
        return 0;
    }

    // Copy the input data to the string and null-terminate it
    std::memcpy(x_name, data, size);
    x_name[size] = '\0';

    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_x(x_name);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    delete[] x_name;

    return 0;
}