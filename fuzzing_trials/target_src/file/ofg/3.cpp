extern "C" {
    #include <magic.h>
    #include <stddef.h>
    #include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    struct magic_set *magic = magic_open(MAGIC_NONE);
    if (magic == NULL) {
        return 0;
    }

    // Ensure data is not null and has enough size to be used as a parameter
    if (size < sizeof(int)) {
        magic_close(magic);
        return 0;
    }

    // Use the first part of data as an integer parameter
    int param = *(const int *)data;
    const void *value = data + sizeof(int);

    // Call the function under test
    magic_setparam(magic, param, value);

    // Clean up
    magic_close(magic);
    return 0;
}