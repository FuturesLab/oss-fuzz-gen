#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_664(const uint8_t *data, size_t size) {
    // Ensure enough data for an integer and a string
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract an integer from the data
    int sequence = *(reinterpret_cast<const int*>(data));
    
    // Extract a string from the data for extra_data
    const char* extra_data = reinterpret_cast<const char*>(data + sizeof(int));

    // Ensure the string is null-terminated
    size_t extra_data_size = size - sizeof(int);
    char* null_terminated_extra_data = new char[extra_data_size + 1];
    std::memcpy(null_terminated_extra_data, extra_data, extra_data_size);
    null_terminated_extra_data[extra_data_size] = '\0';

    // Call the function under test
    icalproperty* prop = icalproperty_vanew_sequence(sequence, null_terminated_extra_data, nullptr);

    // Clean up if necessary
    if (prop != nullptr) {
        icalproperty_free(prop);
    }

    delete[] null_terminated_extra_data;

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

    LLVMFuzzerTestOneInput_664(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
