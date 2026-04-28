#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_650(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer and a string
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract an integer from the input data
    int pollwinner_value = *(reinterpret_cast<const int*>(data));

    // Extract a string from the input data
    const char *dummy_ptr = reinterpret_cast<const char*>(data + sizeof(int));

    // Ensure the string is null-terminated
    size_t remaining_size = size - sizeof(int);
    char *safe_dummy_ptr = new char[remaining_size + 1];
    memcpy(safe_dummy_ptr, dummy_ptr, remaining_size);
    safe_dummy_ptr[remaining_size] = '\0';

    // Check if the string is empty and handle it
    if (remaining_size == 0 || safe_dummy_ptr[0] == '\0') {
        delete[] safe_dummy_ptr;
        return 0;
    }

    // Call the function-under-test with the extracted integer and string
    icalproperty *property = icalproperty_vanew_pollwinner(pollwinner_value, safe_dummy_ptr, nullptr);

    // Clean up if necessary
    if (property != NULL) {
        icalproperty_free(property);
    }

    // Free the allocated memory for the safe string
    delete[] safe_dummy_ptr;

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

    LLVMFuzzerTestOneInput_650(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
