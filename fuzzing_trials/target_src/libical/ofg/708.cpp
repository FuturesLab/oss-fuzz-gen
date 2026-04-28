#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>  // For std::rand and std::srand
#include <ctime>    // For std::time

extern "C" int LLVMFuzzerTestOneInput_708(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated and non-empty
    if (size == 0) {
        return 0; // Early return if the input size is zero
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Randomly decide to modify the input to increase code coverage
    bool modify_input = (std::rand() % 2 == 0);
    char *null_terminated_data = new char[size + 1];
    std::memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    if (modify_input) {
        // Modify the input slightly to explore more code paths
        null_terminated_data[size / 2] = 'X'; // Arbitrary modification
    }

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_relcalid(null_terminated_data);

    // Clean up
    if (prop != nullptr) {
        // Utilize the property to ensure the function is effectively invoked
        const char *relcalid = icalproperty_get_relcalid(prop);
        if (relcalid != nullptr) {
            // Perform some operation with relcalid, like checking its length
            size_t relcalid_length = std::strlen(relcalid);
            (void)relcalid_length; // Suppress unused variable warning
        }
        icalproperty_free(prop);
    }
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

    LLVMFuzzerTestOneInput_708(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
