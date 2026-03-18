// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsSetAdaptationStateTHR at cmsxform.c:57:28 in lcms2.h
// _cms15Fixed16toDouble at cmsplugin.c:377:28 in lcms2_plugin.h
// _cmsDoubleTo15Fixed16 at cmsplugin.c:383:31 in lcms2_plugin.h
// _cmsRead15Fixed16Number at cmsplugin.c:224:20 in lcms2_plugin.h
// _cmsWrite15Fixed16Number at cmsplugin.c:337:20 in lcms2_plugin.h
// cmsSetAdaptationState at cmsxform.c:77:28 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"
#include "lcms2_plugin.h"

static cmsBool DummyReadHandler(struct _cms_io_handler* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count) {
    if (size * count > iohandler->ReportedSize - iohandler->UsedSpace) return FALSE;
    memcpy(Buffer, ((uint8_t*)iohandler->stream) + iohandler->UsedSpace, size * count);
    iohandler->UsedSpace += size * count;
    return TRUE;
}

static cmsBool DummyWriteHandler(struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer) {
    if (size > iohandler->ReportedSize - iohandler->UsedSpace) return FALSE;
    memcpy(((uint8_t*)iohandler->stream) + iohandler->UsedSpace, Buffer, size);
    iohandler->UsedSpace += size;
    return TRUE;
}

static cmsBool DummySeekHandler(struct _cms_io_handler* iohandler, cmsUInt32Number offset) {
    if (offset > iohandler->ReportedSize) return FALSE;
    iohandler->UsedSpace = offset;
    return TRUE;
}

static cmsUInt32Number DummyTellHandler(struct _cms_io_handler* iohandler) {
    return iohandler->UsedSpace;
}

static cmsBool DummyCloseHandler(struct _cms_io_handler* iohandler) {
    free(iohandler->stream);
    return TRUE;
}

int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number) + sizeof(cmsS15Fixed16Number)) return 0;

    cmsContext context = NULL;
    cmsFloat64Number adaptationValue = *(cmsFloat64Number*)Data;
    cmsSetAdaptationStateTHR(context, adaptationValue);

    cmsS15Fixed16Number fixedValue = *(cmsS15Fixed16Number*)(Data + sizeof(cmsFloat64Number));
    cmsFloat64Number resultDouble = _cms15Fixed16toDouble(fixedValue);

    cmsS15Fixed16Number convertedFixed = _cmsDoubleTo15Fixed16(resultDouble);

    uint8_t* ioBuffer = (uint8_t*)malloc(Size);
    if (!ioBuffer) return 0;
    memcpy(ioBuffer, Data, Size);

    cmsIOHANDLER ioHandler = {
        .stream = ioBuffer,
        .ContextID = context,
        .UsedSpace = 0,
        .ReportedSize = Size,
        .Read = DummyReadHandler,
        .Seek = DummySeekHandler,
        .Close = DummyCloseHandler,
        .Tell = DummyTellHandler,
        .Write = DummyWriteHandler
    };

    cmsFloat64Number readValue;
    _cmsRead15Fixed16Number(&ioHandler, &readValue);

    _cmsWrite15Fixed16Number(&ioHandler, adaptationValue);

    cmsSetAdaptationState(adaptationValue);

    ioHandler.Close(&ioHandler);

    return 0;
}