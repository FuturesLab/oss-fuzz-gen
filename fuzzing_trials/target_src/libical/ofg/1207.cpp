#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h> // Include for string manipulation functions

extern "C" int LLVMFuzzerTestOneInput_1207(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for an int and some additional data
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract an integer from the data
    int max_component_size = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        max_component_size |= (data[i] << (i * 8));
    }

    // Ensure additional data is null-terminated to prevent undefined behavior in string functions
    char *additional_data = (char *)(data + sizeof(int));
    size_t additional_data_size = size - sizeof(int);

    // Create a null-terminated string from the additional data
    char *null_terminated_data = new char[additional_data_size + 1];
    memcpy(null_terminated_data, additional_data, additional_data_size);
    null_terminated_data[additional_data_size] = '\0';

    // Check if the null-terminated string is not empty to prevent strcmp crash
    if (strlen(null_terminated_data) == 0) {
        delete[] null_terminated_data;
        return 0;
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_maxcomponentsize(max_component_size, null_terminated_data, NULL);

    // Clean up if necessary
    if (property != NULL) {
        icalproperty_free(property);
    }

    // Free the allocated memory for null-terminated data
    delete[] null_terminated_data;

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

    LLVMFuzzerTestOneInput_1207(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
