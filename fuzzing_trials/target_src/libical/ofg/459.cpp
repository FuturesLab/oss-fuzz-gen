#include <stdint.h>

// Ensure the function is callable from C++
extern "C" {
    #include <libical/icalproperty.h> // Assuming the correct path to the header file

    const char *icalproperty_kind_to_string(icalproperty_kind kind);
}

extern "C" int LLVMFuzzerTestOneInput_459(const uint8_t *data, size_t size) {
    // Check if the input size is sufficient to extract an icalproperty_kind
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Extract an icalproperty_kind from the input data
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0]);

    // Call the function-under-test
    const char *result = icalproperty_kind_to_string(kind);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != nullptr) {
        // Do something trivial with the result, like checking its length
        size_t length = 0;
        while (result[length] != '\0') {
            length++;
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

    LLVMFuzzerTestOneInput_459(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
