#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h> // Assuming the header is located here

    // Function-under-test declaration
    icalpvl_elem_t* icalpvl_prior(icalpvl_elem_t*);
}

extern "C" int LLVMFuzzerTestOneInput_1015(const uint8_t *data, size_t size) {
    // Initialize a icalpvl_elem_t pointer
    icalpvl_elem_t* elem = nullptr;

    // Since icalpvl_elem_t is an incomplete type, we cannot use sizeof directly.
    // Instead, we should allocate memory for it dynamically if needed.
    if (size > 0) { // Ensure there's at least some data to process
        // Allocate memory for icalpvl_elem_t
        elem = static_cast<icalpvl_elem_t*>(malloc(size));
        
        if (elem != nullptr) {
            // Initialize elem with data
            memcpy(elem, data, size);

            // Call the function-under-test
            icalpvl_elem_t* result = icalpvl_prior(elem);

            // Use the result in some way to prevent any compiler optimizations
            if (result != nullptr) {
                // Do something with result if needed
            }

            // Free the allocated memory
            free(elem);
        }
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

    LLVMFuzzerTestOneInput_1015(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
