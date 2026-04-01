#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *ical_string = static_cast<char*>(malloc(size + 1));
    if (ical_string == nullptr) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);

    // Free the allocated string
    free(ical_string);

    if (component == nullptr) {
        return 0;
    }

    // Fuzzing different icalproperty_kind values
    icalproperty_kind kinds[] = {
        ICAL_ANY_PROPERTY,
        ICAL_NO_PROPERTY,
        ICAL_X_PROPERTY,
        ICAL_ATTACH_PROPERTY,
        ICAL_CATEGORIES_PROPERTY,
        ICAL_CLASS_PROPERTY,
        ICAL_COMMENT_PROPERTY,
        ICAL_DESCRIPTION_PROPERTY,
        ICAL_GEO_PROPERTY,
        ICAL_LOCATION_PROPERTY,
        ICAL_PERCENTCOMPLETE_PROPERTY,
        ICAL_PRIORITY_PROPERTY,
        ICAL_RESOURCES_PROPERTY,
        ICAL_STATUS_PROPERTY,
        ICAL_SUMMARY_PROPERTY,
        ICAL_COMPLETED_PROPERTY,
        ICAL_DTEND_PROPERTY,
        ICAL_DUE_PROPERTY,
        ICAL_DTSTART_PROPERTY,
        ICAL_DURATION_PROPERTY,
        ICAL_FREEBUSY_PROPERTY,
        ICAL_TRANSP_PROPERTY,
        ICAL_TZID_PROPERTY,
        ICAL_TZNAME_PROPERTY,
        ICAL_TZOFFSETFROM_PROPERTY,
        ICAL_TZOFFSETTO_PROPERTY,
        ICAL_TZURL_PROPERTY,
        ICAL_ATTENDEE_PROPERTY,
        ICAL_CONTACT_PROPERTY,
        ICAL_ORGANIZER_PROPERTY,
        ICAL_RECURRENCEID_PROPERTY,
        ICAL_RELATEDTO_PROPERTY,
        ICAL_URL_PROPERTY,
        ICAL_UID_PROPERTY,
        ICAL_EXDATE_PROPERTY,
        ICAL_RDATE_PROPERTY,
        ICAL_RRULE_PROPERTY,
        ICAL_ACTION_PROPERTY,
        ICAL_REPEAT_PROPERTY,
        ICAL_TRIGGER_PROPERTY,
        ICAL_CREATED_PROPERTY,
        ICAL_DTSTAMP_PROPERTY,
        ICAL_LASTMODIFIED_PROPERTY,
        ICAL_SEQUENCE_PROPERTY,
        ICAL_REQUESTSTATUS_PROPERTY
    };

    for (icalproperty_kind kind : kinds) {
        // Call the function-under-test
        icalcomponent_count_properties(component, kind);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}