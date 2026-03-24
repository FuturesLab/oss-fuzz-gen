#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include "libical/ical.h"
#include <cstdint>

static void test_icalcomponent_new_vavailability() {
    icalcomponent *component = icalcomponent_new_vavailability();
    if (component) {
        icalcomponent_free(component);
    }
}

static void test_icalcomponent_new_vreply() {
    icalcomponent *component = icalcomponent_new_vreply();
    if (component) {
        icalcomponent_free(component);
    }
}

static void test_icalcomponent_new(icalcomponent_kind kind) {
    icalcomponent *component = icalcomponent_new(kind);
    if (component) {
        icalcomponent_free(component);
    }
}

static void test_icalcomponent_new_vpoll() {
    icalcomponent *component = icalcomponent_new_vpoll();
    if (component) {
        icalcomponent_free(component);
    }
}

static void test_icalcomponent_new_vcalendar() {
    icalcomponent *component = icalcomponent_new_vcalendar();
    if (component) {
        icalcomponent_free(component);
    }
}

static void test_icalcomponent_get_next_component(icalcomponent *component, icalcomponent_kind kind) {
    icalcomponent *next_component = icalcomponent_get_next_component(component, kind);
    if (next_component) {
        // Do something with next_component if needed
    }
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) return 0;

    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);

    test_icalcomponent_new_vavailability();
    test_icalcomponent_new_vreply();
    test_icalcomponent_new(kind);
    test_icalcomponent_new_vpoll();
    test_icalcomponent_new_vcalendar();

    icalcomponent *component = icalcomponent_new(kind);
    if (component) {
        test_icalcomponent_get_next_component(component, kind);
        icalcomponent_free(component);
    }

    return 0;
}