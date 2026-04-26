extern "C" {
#include <libical/ical.h>
}

#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1149(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a kind and a string
    if (size < sizeof(icalvalue_kind) + 1) {
        return 0;
    }

    // Extract an icalvalue_kind from the data
    icalvalue_kind kind = static_cast<icalvalue_kind>(data[0]);

    // Extract a string from the data
    const char *str = reinterpret_cast<const char *>(data + 1);

    // Ensure the string is null-terminated
    size_t str_len = size - 1;
    char *null_terminated_str = new char[str_len + 1];
    std::memcpy(null_terminated_str, str, str_len);
    null_terminated_str[str_len] = '\0';

    // Call the function-under-test
    icalvalue *value = icalvalue_new_from_string(kind, null_terminated_str);

    // Clean up
    if (value != nullptr) {
        icalvalue_free(value);
    }
    delete[] null_terminated_str;

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

    LLVMFuzzerTestOneInput_1149(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
