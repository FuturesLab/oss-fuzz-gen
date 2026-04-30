#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Since the correct header file is not available, we need to declare the function and type manually
extern "C" {
    // Assuming this is the correct signature for the function and type
    typedef enum {
        ICAL_NO_COMPONENT,
        ICAL_VEVENT_COMPONENT,
        ICAL_VTODO_COMPONENT,
        ICAL_VJOURNAL_COMPONENT,
        ICAL_VFREEBUSY_COMPONENT,
        ICAL_VTIMEZONE_COMPONENT,
        ICAL_X_COMPONENT,
        ICAL_VCALENDAR_COMPONENT,
        ICAL_VAGENDA_COMPONENT,
        ICAL_VQUERY_COMPONENT,
        ICAL_VCAR_COMPONENT,
        ICAL_VCOMMAND_COMPONENT,
        ICAL_VDISPLAY_COMPONENT,
        ICAL_VDIALER_COMPONENT,
        ICAL_VEMAIL_COMPONENT,
        ICAL_VMESSAGE_COMPONENT,
        ICAL_VNOTE_COMPONENT,
        ICAL_VRESOURCE_COMPONENT,
        ICAL_VALARM_COMPONENT,
        ICAL_XAUDIOALARM_COMPONENT,
        ICAL_XDISPLAYALARM_COMPONENT,
        ICAL_XEMAILALARM_COMPONENT,
        ICAL_XPROCEDUREALARM_COMPONENT,
        ICAL_XSOUNDALARM_COMPONENT,
        ICAL_XVTODO_COMPONENT,
        ICAL_XVEVENT_COMPONENT,
        ICAL_XVFREEBUSY_COMPONENT,
        ICAL_XVTIMEZONE_COMPONENT,
        ICAL_XVCALENDAR_COMPONENT,
        ICAL_XVAGENDA_COMPONENT,
        ICAL_XVQUERY_COMPONENT,
        ICAL_XVCAR_COMPONENT,
        ICAL_XVCOMMAND_COMPONENT,
        ICAL_XVDISPLAY_COMPONENT,
        ICAL_XVDIALER_COMPONENT,
        ICAL_XVEMAIL_COMPONENT,
        ICAL_XVMESSAGE_COMPONENT,
        ICAL_XVNOTE_COMPONENT,
        ICAL_XVRESOURCE_COMPONENT,
        ICAL_XVALARM_COMPONENT
    } icalproperty_resourcetype;

    icalproperty_resourcetype icalproperty_string_to_resourcetype(const char *str);
}

extern "C" int LLVMFuzzerTestOneInput_1211(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for safe string operations
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Call the function-under-test
    icalproperty_resourcetype result = icalproperty_string_to_resourcetype(null_terminated_data);

    // Clean up
    free(null_terminated_data);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_1211(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
