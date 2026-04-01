// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_relcalid at icalcomponent.c:2573:6 in icalcomponent.h
// icalcomponent_as_ical_string at icalcomponent.c:215:7 in icalcomponent.h
// icalcomponent_new_x at icalcomponent.c:161:16 in icalcomponent.h
// icalcomponent_new_xvote at icalcomponent.c:2105:16 in icalcomponent.h
// icalcomponent_set_sequence at icalcomponent.c:1955:6 in icalcomponent.h
// icalcomponent_normalize at icalcomponent.c:2832:6 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "ical.h"

static icalcomponent* createRandomComponent(const uint8_t *Data, size_t Size) {
    if (Size < 5) return nullptr;

    // Create a new X component with a random name from the input data
    char x_name[5];
    std::memcpy(x_name, Data, 4);
    x_name[4] = '\0';
    return icalcomponent_new_x(x_name);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment
    icalcomponent* comp = createRandomComponent(Data, Size);
    if (!comp) return 0;

    // Step 2: Invoke the target functions
    // Normalize the component
    icalcomponent_normalize(comp);

    // Set a sequence number using part of the input data
    if (Size > 4) {
        int sequence = static_cast<int>(Data[4]);
        icalcomponent_set_sequence(comp, sequence);
    }

    // Set a relative calendar ID using the rest of the input data
    if (Size > 5) {
        size_t relcalid_len = Size - 5;
        std::vector<char> relcalid(relcalid_len + 1, '\0');
        std::memcpy(relcalid.data(), Data + 5, relcalid_len);
        icalcomponent_set_relcalid(comp, relcalid.data());
    }

    // Convert the component to an iCalendar string
    char* ical_string = icalcomponent_as_ical_string(comp);
    if (ical_string) {
        // Normally, you would use the string here, but libical manages its memory
    }

    // Create an XVOTE component
    icalcomponent* xvote_comp = icalcomponent_new_xvote();
    if (xvote_comp) {
        // Do something with the xvote component if needed
        icalcomponent_free(xvote_comp);
    }

    // Step 3: Cleanup
    icalcomponent_free(comp);

    return 0;
}