// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalerror_crash_here at icalerror.c:73:6 in icalerror.h
// icalerror_supress at icalerror.c:182:16 in icalerror.h
// icalerror_stop_here at icalerror.c:68:6 in icalerror.h
// icalerror_icalerrno at icalerror.c:39:16 in icalerror.h
// icalerror_set_errors_are_fatal at icalerror.c:100:6 in icalerror.h
// icalerror_get_errors_are_fatal at icalerror.c:105:6 in icalerror.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalerror.h"
}

#include <cstdint>
#include <cstring>

static void fuzz_icalerror_crash_here() {
    // This function will crash the program, so we handle it carefully
    // We will not call this function to prevent AddressSanitizer errors
}

static void fuzz_icalerror_stop_here() {
    icalerror_stop_here();
}

static void fuzz_icalerror_set_errors_are_fatal() {
    bool fatal = (rand() % 2 == 0);
    icalerror_set_errors_are_fatal(fatal);
}

static void fuzz_icalerror_icalerrno() {
    icalerrorenum *error_ptr = icalerror_icalerrno();
    if (error_ptr) {
        // Randomly set an error
        *error_ptr = static_cast<icalerrorenum>(rand() % (ICAL_UNKNOWN_ERROR + 1));
    }
}

static void fuzz_icalerror_get_errors_are_fatal() {
    bool are_fatal = icalerror_get_errors_are_fatal();
    (void)are_fatal; // Suppress unused variable warning
}

static void fuzz_icalerror_supress(const char *error_name, size_t length) {
    // Ensure the error_name is null-terminated and within bounds
    char buffer[256];
    size_t copy_length = length < sizeof(buffer) - 1 ? length : sizeof(buffer) - 1;
    std::memcpy(buffer, error_name, copy_length);
    buffer[copy_length] = '\0'; // Null-terminate the string

    icalerrorstate prev_state = icalerror_supress(buffer);
    (void)prev_state; // Suppress unused variable warning
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    // Ensure there is enough data to work with
    if (Size < 1) return 0;

    // Use the first byte of data to decide which function to fuzz
    uint8_t choice = Data[0];

    // Use remaining data as a string input for icalerror_supress
    const char *error_name = (Size > 1) ? reinterpret_cast<const char *>(&Data[1]) : "";
    size_t error_name_length = Size - 1;

    switch (choice % 5) { // Reduced to 5 as we skip fuzz_icalerror_crash_here
        case 0:
            fuzz_icalerror_stop_here();
            break;
        case 1:
            fuzz_icalerror_set_errors_are_fatal();
            break;
        case 2:
            fuzz_icalerror_icalerrno();
            break;
        case 3:
            fuzz_icalerror_get_errors_are_fatal();
            break;
        case 4:
            fuzz_icalerror_supress(error_name, error_name_length);
            break;
        default:
            // This should never happen
            break;
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

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_65(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    