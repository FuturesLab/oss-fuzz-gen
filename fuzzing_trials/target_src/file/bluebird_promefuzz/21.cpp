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
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    std::ofstream file("./dummy_file", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();
    }
}

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0; // Ensure there is enough data to read an int

    // Initialize magic_t structure
    magic_t magic_cookie = magic_open(MAGIC_NONE);
    if (magic_cookie == nullptr) {
        return 0;
    }

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    // Use magic_compile with the dummy file
    magic_compile(magic_cookie, "./dummy_file");

    // Check for errors using magic_errno
    int err = magic_errno(magic_cookie);
    if (err != 0) {
        std::cerr << "Error: " << err << std::endl;
    }

    // Set flags using magic_setflags
    int flags = *reinterpret_cast<const int*>(Data) % 0xFFFF; // Use some part of Data as flags
    magic_setflags(magic_cookie, flags);

    // Get parameters using magic_getparam
    if (Size >= sizeof(int) * 2) { // Ensure there is enough data to read another int
        int param_type = *reinterpret_cast<const int*>(Data + sizeof(int)) % 0xFFFF; // Use some part of Data as param type
        size_t param_value;
        magic_getparam(magic_cookie, param_type, &param_value);
    }

    // Load buffers using magic_load_buffers
    void *buffers[1] = { (void*)Data };
    size_t buffer_sizes[1] = { Size };
    magic_load_buffers(magic_cookie, buffers, buffer_sizes, 1);

    // Set parameters using magic_setparam
    if (Size >= sizeof(size_t)) { // Ensure there is enough data to read a size_t
        size_t new_param_value = Size; // Use Size as the new parameter value
        magic_setparam(magic_cookie, 0, &new_param_value); // Use 0 as default param type
    }

    // Cleanup
    magic_close(magic_cookie);
    return 0;
}