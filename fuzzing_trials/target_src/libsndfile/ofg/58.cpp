#include <stdint.h>
#include <stddef.h>
#include <cstring>
#include <iostream>

// Assuming the function is defined somewhere in the project
extern "C" {
    const char * sf_version_string();
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = sf_version_string();

    // Use the version string in some way to ensure it is accessed
    if (version != nullptr) {
        // Access the first character to ensure the string is read
        volatile char first_char = version[0];
        (void)first_char; // Prevent unused variable warning

        // Use the input data to simulate some interaction
        if (size > 0 && data[0] == first_char) {
            // If the first byte of data matches the first character of the version string
            // Perform some operation (e.g., logging, further processing)
            // This is just a placeholder for additional logic
            std::cout << "Match found: " << first_char << std::endl;
        } else {
            // Log or process when there is no match
            std::cout << "No match: " << first_char << std::endl;
        }
    } else {
        // Handle the case where version is null
        std::cout << "Version string is null." << std::endl;
    }

    return 0;
}