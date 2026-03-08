extern "C" {
    #include <stddef.h>
    #include <stdint.h>
    #include <string.h>
    #include <stdio.h> // Include the necessary header for printf

    // Declaration of the function-under-test
    const char * magic_getpath(const char *, int);
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure the data is non-null and has a reasonable size for a string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the input string and ensure null-termination
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0'; // Null-terminate the string

    // Use a variety of integers to explore different code paths
    int intValues[] = {0, 1, -1, 42, 100, -100, 2147483647, -2147483648}; // Added edge cases for int
    for (int i = 0; i < sizeof(intValues) / sizeof(intValues[0]); ++i) {
        int someInt = intValues[i];

        // Call the function-under-test
        const char *result = magic_getpath(inputString, someInt);

        // Check if the result is not null to ensure the function is being utilized
        if (result != nullptr) {
            // Optionally, perform further operations on the result
            // For example, calculate its length or print it
            size_t resultLength = strlen(result);
            // Log the result length to ensure it's being used
            printf("Result Length: %zu\n", resultLength);
        }
    }

    // Clean up allocated memory
    delete[] inputString;

    // Return 0 to indicate successful execution
    return 0;
}