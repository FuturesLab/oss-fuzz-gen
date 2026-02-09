#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Mock definition of sqlite3_context for fuzzing purposes
struct sqlite3_context {
    // Add any necessary fields to mimic the context behavior
    // For this example, we can leave it empty or add dummy fields
};

// Redefine sqlite3_context as the mock version
typedef struct sqlite3_context sqlite3_context;

int LLVMFuzzerTestOneInput_183(const uint8_t *data, size_t size) {
    sqlite3_context *context;
    double value;

    // Ensure the context is not NULL by allocating a new sqlite3_context
    context = (sqlite3_context *)sqlite3_malloc(sizeof(sqlite3_context));
    if (context == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize the double value from the input data
    // Use the first 8 bytes of data to create a double, if size is sufficient
    if (size >= sizeof(double)) {
        value = *(double *)data; // Cast the data to double
    } else {
        value = 0.0; // Default value if not enough data
    }

    // Call the function under test
    sqlite3_result_double(context, value);

    // Clean up
    sqlite3_free(context);

    return 0;
}