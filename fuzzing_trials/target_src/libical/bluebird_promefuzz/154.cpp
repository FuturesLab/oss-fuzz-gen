#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalvalue.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

static icalvalue_kind GetRandomIcalValueKind() {
    const icalvalue_kind kinds[] = {
        ICAL_ANY_VALUE, ICAL_ACTION_VALUE, ICAL_ATTACH_VALUE, ICAL_BINARY_VALUE,
        ICAL_BOOLEAN_VALUE, ICAL_BUSYTYPE_VALUE, ICAL_CALADDRESS_VALUE,
        ICAL_CARLEVEL_VALUE, ICAL_CLASS_VALUE, ICAL_CMD_VALUE, ICAL_DATE_VALUE,
        ICAL_DATETIME_VALUE, ICAL_DATETIMEDATE_VALUE, ICAL_DATETIMEPERIOD_VALUE,
        ICAL_DURATION_VALUE, ICAL_FLOAT_VALUE, ICAL_GEO_VALUE, ICAL_INTEGER_VALUE,
        ICAL_LINK_VALUE, ICAL_METHOD_VALUE, ICAL_PARTICIPANTTYPE_VALUE,
        ICAL_PERIOD_VALUE, ICAL_POLLCOMPLETION_VALUE, ICAL_POLLMODE_VALUE,
        ICAL_PROXIMITY_VALUE, ICAL_QUERY_VALUE, ICAL_QUERYLEVEL_VALUE,
        ICAL_RECUR_VALUE, ICAL_RELATEDTO_VALUE, ICAL_REQUESTSTATUS_VALUE,
        ICAL_RESOURCETYPE_VALUE, ICAL_STATUS_VALUE, ICAL_STRING_VALUE,
        ICAL_TASKMODE_VALUE, ICAL_TEXT_VALUE, ICAL_TRANSP_VALUE, ICAL_TRIGGER_VALUE,
        ICAL_UID_VALUE, ICAL_URI_VALUE, ICAL_UTCOFFSET_VALUE, ICAL_X_VALUE,
        ICAL_XLICCLASS_VALUE, ICAL_XMLREFERENCE_VALUE, ICAL_NO_VALUE
    };
    size_t index = rand() % (sizeof(kinds) / sizeof(kinds[0]));
    return kinds[index];
}

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *inputStr = static_cast<char *>(malloc(Size + 1));
    if (!inputStr) {
        return 0;
    }
    memcpy(inputStr, Data, Size);
    inputStr[Size] = '\0';

    // Fuzz icalvalue_new_from_string
    icalvalue_kind kind = GetRandomIcalValueKind();
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of icalvalue_new_from_string
    icalvalue *value = icalvalue_new_from_string(ICAL_TRIGGER_VALUE, inputStr);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (value) {
        // Fuzz icalvalue_clone
        icalvalue *clonedValue = icalvalue_clone(value);
        if (clonedValue) {
            // Fuzz icalvalue_compare
            icalparameter_xliccomparetype compareResult = icalvalue_compare(value, clonedValue);
            (void)compareResult; // Suppress unused variable warning
            icalvalue_free(clonedValue);
        }

        // Fuzz icalvalue_isa
        icalvalue_kind isaKind = icalvalue_isa(value);
        (void)isaKind; // Suppress unused variable warning

        // Fuzz icalvalue_reset_kind
        icalvalue_reset_kind(value);

        icalvalue_free(value);
    }

    // Fuzz icalvalue_new
    icalvalue *newValue = icalvalue_new(kind);
    if (newValue) {
        icalvalue_free(newValue);
    }

    free(inputStr);
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

    LLVMFuzzerTestOneInput_154(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
