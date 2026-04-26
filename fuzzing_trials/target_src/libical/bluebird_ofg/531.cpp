#include <string.h>
#include <sys/stat.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Since the header file "icalproperty.h" does not exist, we need to declare the function prototype manually.
// Wrap it with extern "C" to ensure C linkage.
extern "C" {
    // Declare the function prototype for icalproperty_kind_and_string_to_enum
    void icalproperty_kind_and_string_to_enum(int kind, const char *str);
}

// Fuzzing harness for icalproperty_kind_and_string_to_enum
extern "C" int LLVMFuzzerTestOneInput_531(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract an integer and a string
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract an integer from the data
    int kind;
    memcpy(&kind, data, sizeof(int));

    // Extract a string from the remaining data
    const char *str = reinterpret_cast<const char *>(data + sizeof(int));

    // Ensure the string is null-terminated
    char *null_terminated_str = (char *)malloc(size - sizeof(int) + 1);
    if (null_terminated_str == NULL) {
        return 0;
    }
    memcpy(null_terminated_str, str, size - sizeof(int));
    null_terminated_str[size - sizeof(int)] = '\0';

    // Call the function-under-test
    icalproperty_kind_and_string_to_enum(kind, null_terminated_str);

    // Clean up
    free(null_terminated_str);

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

    LLVMFuzzerTestOneInput_531(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
