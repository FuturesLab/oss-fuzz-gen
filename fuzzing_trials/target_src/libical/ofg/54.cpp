#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Convert input data to a null-terminated string
    char *input_str = (char *)malloc(size + 1);
    if (!input_str) {
        return 0; // Early exit if memory allocation fails
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Initialize a default icalcomponent
    icalcomponent *original_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    
    // Add properties to the component using the input data
    icalcomponent_add_property(original_component, icalproperty_new_summary(input_str));
    icalcomponent_add_property(original_component, icalproperty_new_description(input_str));
    
    // Clone the component
    icalcomponent *cloned_component = icalcomponent_clone(original_component);
    
    // Perform cleanup
    if (cloned_component != NULL) {
        icalcomponent_free(cloned_component);
    }
    icalcomponent_free(original_component);
    free(input_str);

    return 0;
}