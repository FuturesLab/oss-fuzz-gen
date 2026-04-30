#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // Include for strcmp

extern "C" int LLVMFuzzerTestOneInput_1151(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int) + 1) { // Ensure there's at least one byte for null-termination
        return 0;
    }

    // Extract an integer from the data
    int percent_complete = *(reinterpret_cast<const int*>(data));

    // Create a separate buffer for extra_data to avoid modifying const data
    size_t extra_data_size = size - sizeof(int);
    char* extra_data = new char[extra_data_size + 1]; // +1 for null-termination
    std::memcpy(extra_data, data + sizeof(int), extra_data_size);
    extra_data[extra_data_size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_percentcomplete(percent_complete, extra_data, nullptr);

    // Clean up if necessary
    if (property != NULL) {
        icalproperty_free(property);
    }

    // Free the allocated memory for extra_data
    delete[] extra_data;

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

    LLVMFuzzerTestOneInput_1151(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
