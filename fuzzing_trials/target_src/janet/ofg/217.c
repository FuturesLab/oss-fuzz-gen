#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern void janet_var(JanetTable *table, const char *name, Janet value, const char *doc);

int LLVMFuzzerTestOneInput_217(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < 2) return 0;

    // Initialize Janet environment
    janet_init();

    // Create a new JanetTable
    JanetTable *table = janet_table(10);

    // Use the first byte of data to determine the length of the name
    size_t name_len = data[0] % (size - 1); // Ensure name_len is within bounds
    if (name_len == 0) name_len = 1; // Ensure name_len is not zero

    // Use the next bytes for the name
    char name[256];
    if (name_len >= sizeof(name)) name_len = sizeof(name) - 1; // Ensure name fits in buffer
    for (size_t i = 0; i < name_len; i++) {
        name[i] = (char)data[i + 1];
    }
    name[name_len] = '\0'; // Null-terminate the string

    // Use the next byte as a simple Janet integer value
    Janet value = janet_wrap_integer(data[1 + name_len]);

    // Use the remaining bytes for the doc string
    const char *doc = (const char *)(data + 2 + name_len);
    size_t doc_len = size - 2 - name_len;
    if (doc_len >= sizeof(name)) doc_len = sizeof(name) - 1; // Ensure doc fits in buffer
    char doc_buffer[256];
    for (size_t i = 0; i < doc_len; i++) {
        doc_buffer[i] = doc[i];
    }
    doc_buffer[doc_len] = '\0'; // Null-terminate the string

    // Call the function-under-test
    janet_var(table, name, value, doc_buffer);

    // Clean up Janet environment
    janet_deinit();

    return 0;
}