#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Define a non-NULL string
    const char *input_string = (const char *)data;
    
    // Define a non-zero size
    size_t input_size = size > 0 ? size : 1;
    
    // Define a valid enumeration value for ucl_string_flags
    enum ucl_string_flags flags = UCL_STRING_RAW;
    
    // Call the function under test
    ucl_object_t *obj = ucl_object_fromstring_common(input_string, input_size, flags);
    
    // Clean up any allocated resources
    if (obj != NULL) {
        ucl_object_unref(obj);
    }
    
    return 0;
}