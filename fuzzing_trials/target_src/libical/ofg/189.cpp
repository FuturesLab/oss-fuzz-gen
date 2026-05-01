#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent and icalcompiter
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcompiter iter;

    // Ensure that the data size is sufficient to create some properties
    if (size > 0) {
        // Create a string from the input data
        char *summary = static_cast<char*>(malloc(size + 1));
        if (summary == nullptr) {
            icalcomponent_free(component);
            return 0;
        }
        memcpy(summary, data, size);
        summary[size] = '\0';

        // Add properties to the component
        icalcomponent_set_summary(component, summary);
        free(summary);
    }

    // Initialize the iterator
    iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Use the iterator to traverse components
    if (icalcompiter_deref(&iter) != nullptr) {
        do {
            // Call the function-under-test
            icalcomponent *prior_component = icalcompiter_prior(&iter);

            // Clean up
            if (prior_component != nullptr) {
                icalcomponent_free(prior_component);
            }

            // Move to the next component
            icalcompiter_next(&iter);
        } while (icalcompiter_deref(&iter) != nullptr);
    }

    icalcomponent_free(component);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_189(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
