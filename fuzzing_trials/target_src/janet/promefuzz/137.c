// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_cstring at string.c:88:16 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_cstring at string.c:88:16 in janet.h
// janet_symeq at janet.c:4626:5 in janet.h
// janet_getcstring at janet.c:4553:13 in janet.h
// janet_cstrcmp at janet.c:34043:5 in janet.h
// janet_keyeq at janet.c:4618:5 in janet.h
// janet_streq at janet.c:4622:5 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static Janet create_random_janet_symbol(const uint8_t *data, size_t size) {
    Janet symbol;
    if (size > 0) {
        char *buffer = (char *)malloc(size + 1);
        if (buffer) {
            memcpy(buffer, data, size);
            buffer[size] = '\0'; // Ensure null-termination
            symbol.pointer = janet_cstring(buffer);
            free(buffer);
        } else {
            symbol.pointer = janet_cstring("");
        }
    } else {
        symbol.pointer = janet_cstring("");
    }
    return symbol;
}

static JanetString create_random_janet_string(const uint8_t *data, size_t size) {
    char *buffer = (char *)malloc(size + 1);
    if (buffer) {
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Ensure null-termination
        JanetString janetStr = janet_cstring(buffer);
        free(buffer);
        return janetStr;
    }
    return janet_cstring("");
}

static void fuzz_janet_symeq(const uint8_t *data, size_t size) {
    Janet symbol = create_random_janet_symbol(data, size);
    janet_symeq(symbol, (const char *)data);
}

static void fuzz_janet_getcstring(const uint8_t *data, size_t size) {
    if (size < sizeof(Janet)) return;
    Janet argv[1];
    argv[0].pointer = create_random_janet_string(data, size);
    janet_getcstring(argv, 0);
}

static void fuzz_janet_cstrcmp(const uint8_t *data, size_t size) {
    if (size == 0) return; // Ensure there is data to compare
    JanetString janetStr = create_random_janet_string(data, size);
    char *cstr = (char *)malloc(size + 1);
    if (cstr) {
        memcpy(cstr, data, size);
        cstr[size] = '\0'; // Ensure null-termination
        janet_cstrcmp(janetStr, cstr);
        free(cstr);
    }
}

static void fuzz_janet_keyeq(const uint8_t *data, size_t size) {
    Janet keyword = create_random_janet_symbol(data, size);
    janet_keyeq(keyword, (const char *)data);
}

static void fuzz_janet_streq(const uint8_t *data, size_t size) {
    Janet janetStr;
    janetStr.pointer = create_random_janet_string(data, size);
    janet_streq(janetStr, (const char *)data);
}

int LLVMFuzzerTestOneInput_137(const uint8_t *Data, size_t Size) {
    // Initialize the Janet VM
    if (!janet_init()) {
        return 0; // Exit if initialization fails
    }

    fuzz_janet_symeq(Data, Size);
    fuzz_janet_getcstring(Data, Size);
    fuzz_janet_cstrcmp(Data, Size);
    fuzz_janet_keyeq(Data, Size);
    fuzz_janet_streq(Data, Size);

    // Deinitialize the Janet VM
    janet_deinit();

    return 0;
}