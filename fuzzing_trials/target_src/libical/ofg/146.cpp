#include <cstdint>
#include <cstdio>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vtodo();

    // We should check if the component is not NULL to avoid dereferencing a NULL pointer
    if (component != NULL) {
        // Perform operations on the component if needed
        // For example, convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // In a real fuzzing scenario, you might want to do something with this string
            // For this example, we will just print it
            printf("%s\n", component_str);
        }

        // Free the component to avoid memory leaks
        icalcomponent_free(component);
    }

    return 0;
}