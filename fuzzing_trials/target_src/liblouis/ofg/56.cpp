#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {
    #include "/src/liblouis/liblouis/liblouis.h" // Correct path for the header file
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    // Ensure the input size is adequate for the test
    if (size < 4) return 0;

    // Initialize the parameters for lou_hyphenate
    const char *lang = "en-us"; // Example language code
    widechar text[256]; // Buffer for widechar text
    char hyphens[256]; // Buffer for hyphenation points
    int textLength = (size < 256) ? size : 255; // Limit text length to buffer size

    // Convert input data to widechar text
    for (int i = 0; i < textLength; ++i) {
        text[i] = (widechar)data[i];
    }
    text[textLength] = 0; // Null-terminate the widechar string

    // Call the function-under-test
    int result = lou_hyphenate(lang, text, textLength, hyphens, textLength);

    // Optional: Print result for debugging
    std::cout << "Hyphenation result: " << result << std::endl;

    return 0;
}