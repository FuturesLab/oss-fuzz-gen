#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Randomly decide the type of JSON object to create
    int choice = fuzzed_data.ConsumeIntegralInRange<int>(0, 3);

    struct json_object *obj = nullptr;

    switch (choice) {
        case 0: {
            // Create a JSON integer object
            int32_t int_value = fuzzed_data.ConsumeIntegral<int32_t>();
            obj = json_object_new_int(int_value);
            break;
        }
        case 1: {
            // Create a JSON string object
            std::string str_value = fuzzed_data.ConsumeRandomLengthString();
            obj = json_object_new_string(str_value.c_str());
            break;
        }
        case 2: {
            // Create a JSON boolean object
            bool bool_value = fuzzed_data.ConsumeBool();
            obj = json_object_new_boolean(bool_value);
            break;
        }
        case 3: {
            // Create a JSON double object
            double double_value = fuzzed_data.ConsumeFloatingPoint<double>();
            obj = json_object_new_double(double_value);
            break;
        }
        default:
            break;
    }

    // Clean up the created json_object
    if (obj != nullptr) {
        json_object_put(obj);
    }

    return 0;
}