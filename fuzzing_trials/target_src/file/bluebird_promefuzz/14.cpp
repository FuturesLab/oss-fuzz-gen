#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "magic.h"
#include <cstdint>
#include <cstddef>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

static void fuzz_magic_descriptor(magic_t magic, const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_RDWR | O_CREAT, 0666);
    if (fd != -1) {
        write(fd, Data, Size);
        lseek(fd, 0, SEEK_SET);
        const char *result = magic_descriptor(magic, fd);
        if (!result) {
            const char *error = magic_error(magic);
            if (error) {
                // Handle error if needed
            }
        }
        close(fd);
    }
}

static void fuzz_magic_file(magic_t magic, const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
        const char *result = magic_file(magic, "./dummy_file");
        if (!result) {
            const char *error = magic_error(magic);
            if (error) {
                // Handle error if needed
            }
        }
    }
}

static void fuzz_magic_load(magic_t magic, const uint8_t *Data, size_t Size) {
    char filename[256];
    snprintf(filename, sizeof(filename), "./dummy_file_%zu", Size);
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function magic_load with magic_compile
        int result = magic_compile(magic, filename);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (result == -1) {
            const char *error = magic_error(magic);
            if (error) {
                // Handle error if needed
            }
        }
    }
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    int flags = MAGIC_NONE;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of magic_open
    magic_t magic = magic_open(MAGIC_PARAM_ENCODING_MAX);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!magic) {
        return 0;
    }

    fuzz_magic_descriptor(magic, Data, Size);
    fuzz_magic_file(magic, Data, Size);
    fuzz_magic_load(magic, Data, Size);

    magic_close(magic);
    return 0;
}