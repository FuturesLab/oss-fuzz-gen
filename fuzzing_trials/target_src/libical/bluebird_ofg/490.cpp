#include <string.h>
#include <sys/stat.h>
#include <cstdint>  // Include for uint8_t
#include <cstdlib>  // Include for size_t

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_490(const uint8_t *data, size_t size) {
    // Since icalcomponent_new_xdaylight does not take any parameters,
    // we can directly call it without needing to use the input data.
    
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xdaylight();
    
    // Perform some operations on the returned component if needed
    // For example, we can convert it to a string and then free it
    if (component != NULL) {
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, we would do something with the string here
            // For fuzzing purposes, we can just print it or ignore it
            // printf("%s\n", component_str);
        }
        
        // Free the component after use
        icalcomponent_free(component);
    }
    
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

    LLVMFuzzerTestOneInput_490(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
