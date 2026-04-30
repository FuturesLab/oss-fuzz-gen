#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h" // Adjust the include path as necessary
    // The header for icalpvl_elem and icalpvl_new_element might be different or the functions might be declared elsewhere
    // Since libical/icalpvl.h is not found, we need to find the correct header or assume the declarations here if not found
    typedef struct icalpvl_elem_t* icalpvl_elem; // Assuming a typedef based on typical C conventions
    icalpvl_elem icalpvl_new_element(void* ptr, icalpvl_elem elem1, icalpvl_elem elem2); // Assuming function prototype
}

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract elements
    if (size < 2 * sizeof(icalpvl_elem)) {
        return 0;
    }

    // Extract two icalpvl_elem values from the data
    icalpvl_elem elem1 = *(icalpvl_elem*)(data);
    icalpvl_elem elem2 = *(icalpvl_elem*)(data + sizeof(icalpvl_elem));

    // Use a non-null pointer for the first parameter
    void* non_null_ptr = (void*)data;

    // Call the function-under-test
    icalpvl_elem new_elem = icalpvl_new_element(non_null_ptr, elem1, elem2);

    // Optionally, perform some operations with new_elem if needed
    // For now, just suppress unused variable warning
    (void)new_elem;

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

    LLVMFuzzerTestOneInput_104(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
