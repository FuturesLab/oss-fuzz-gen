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
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalerror.h"

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
    // If the input data is too small, return immediately
    if (Size < 1) {
        return 0;
    }

    // Use the first byte to determine an icalerrorenum value
    icalerrorenum errorEnum = static_cast<icalerrorenum>(Data[0] % (ICAL_UNKNOWN_ERROR + 1));

    // Test icalerror_get_error_state
    icalerrorstate state = icalerror_get_error_state(errorEnum);

    // Check if setting this error would cause a fatal error
    if (state != ICAL_ERROR_FATAL) {
        // Test icalerror_set_errno
        icalerror_set_errno(errorEnum);
    }

    // Test icalerror_icalerrno

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalerror_get_error_state to icalerror_restore
    char* ret_icalenum_reqstat_code_r_uqyjx = icalenum_reqstat_code_r(ICAL_2_0_SUCCESS_STATUS);
    if (ret_icalenum_reqstat_code_r_uqyjx == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalenum_reqstat_code_r_uqyjx) {
    	return 0;
    }
    icalerror_restore(ret_icalenum_reqstat_code_r_uqyjx, state);
    // End mutation: Producer.APPEND_MUTATOR
    
    icalerrorenum *currentErrno = icalerror_icalerrno();
    if (currentErrno) {
        *currentErrno = errorEnum;
    }

    // Test icalerror_strerror
    const char *errorStr = icalerror_strerror(errorEnum);

    // If there is more data, use it as a string for icalerror_error_from_string
    if (Size > 1) {
        char buffer[256];
        size_t copySize = (Size - 1 < sizeof(buffer) - 1) ? Size - 1 : sizeof(buffer) - 1;
        memcpy(buffer, Data + 1, copySize);
        buffer[copySize] = '\0';
        icalerrorenum fromString = icalerror_error_from_string(buffer);
    }

    // Test icalerror_set_error_state with different states
    icalerrorstate newState = static_cast<icalerrorstate>(Data[0] % (ICAL_ERROR_UNKNOWN + 1));
    icalerror_set_error_state(errorEnum, newState);

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

    LLVMFuzzerTestOneInput_165(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
