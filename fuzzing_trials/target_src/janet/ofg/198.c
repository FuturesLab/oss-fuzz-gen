#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Define a simple struct to use as a JanetAbstract
typedef struct {
    int field1;
    double field2;
} MyAbstract;

// Function to create a JanetAbstract
static JanetAbstract create_abstract() {
    // Allocate memory for the abstract type
    MyAbstract *abstract = (MyAbstract *)malloc(sizeof(MyAbstract));
    if (abstract == NULL) {
        // Handle memory allocation failure
        exit(1);
    }

    // Initialize the fields of the abstract type
    abstract->field1 = 42;
    abstract->field2 = 3.14;

    // Return the abstract as a JanetAbstract
    return (JanetAbstract)abstract;
}

int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Create a JanetAbstract
    JanetAbstract abstract = create_abstract();

    // Call the function-under-test
    Janet result = janet_wrap_abstract(abstract);

    // Clean up
    free((void *)abstract);

    return 0;
}