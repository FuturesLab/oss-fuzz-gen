#include <stdint.h>
#include <stddef.h>
#include <janet.h>

extern void janet_schedule(JanetFiber *, Janet);

int LLVMFuzzerTestOneInput_338(const uint8_t *data, size_t size) {
    if (size < sizeof(JanetFiber) + sizeof(Janet)) {
        return 0;
    }

    JanetFiber *fiber = (JanetFiber *)data;
    Janet *janet_data = (Janet *)(data + sizeof(JanetFiber));

    // Ensure the Janet value is valid
    Janet janet_value = janet_wrap_nil();
    if (size >= sizeof(JanetFiber) + sizeof(Janet)) {
        janet_value = *janet_data;
    }

    janet_schedule(fiber, janet_value);
    return 0;
}