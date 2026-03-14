// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsReadUInt16Number at cmsplugin.c:124:20 in lcms2_plugin.h
// _cmsWriteUInt16Array at cmsplugin.c:281:20 in lcms2_plugin.h
// _cmsReadUInt16Array at cmsplugin.c:137:20 in lcms2_plugin.h
// _cmsWriteAlignment at cmsplugin.c:462:19 in lcms2_plugin.h
// _cmsWriteUInt16Number at cmsplugin.c:268:20 in lcms2_plugin.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcms2_plugin.h"
#include "lcms2.h"

static cmsUInt32Number customRead(cmsIOHANDLER* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count) {
    FILE *stream = (FILE*) iohandler->stream;
    return fread(Buffer, size, count, stream);
}

static cmsBool customSeek(cmsIOHANDLER* iohandler, cmsUInt32Number offset) {
    FILE *stream = (FILE*) iohandler->stream;
    return fseek(stream, offset, SEEK_SET) == 0;
}

static cmsBool customClose(cmsIOHANDLER* iohandler) {
    FILE *stream = (FILE*) iohandler->stream;
    return fclose(stream) == 0;
}

static cmsUInt32Number customTell(cmsIOHANDLER* iohandler) {
    FILE *stream = (FILE*) iohandler->stream;
    return ftell(stream);
}

static cmsBool customWrite(cmsIOHANDLER* iohandler, cmsUInt32Number size, const void* Buffer) {
    FILE *stream = (FILE*) iohandler->stream;
    return fwrite(Buffer, size, 1, stream) == 1;
}

int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number)) {
        return 0;
    }

    FILE *dummyFile = fopen("./dummy_file", "wb+");
    if (!dummyFile) {
        return 0;
    }

    fwrite(Data, 1, Size, dummyFile);
    rewind(dummyFile);

    cmsIOHANDLER iohandler = {
        .stream = dummyFile,
        .Read = customRead,
        .Seek = customSeek,
        .Close = customClose,
        .Tell = customTell,
        .Write = customWrite
    };

    cmsUInt16Number number;
    _cmsReadUInt16Number(&iohandler, &number);

    cmsUInt16Number writeArray[5] = {0, 1, 2, 3, 4};
    _cmsWriteUInt16Array(&iohandler, 5, writeArray);

    _cmsReadUInt16Array(&iohandler, 5, writeArray);

    _cmsWriteAlignment(&iohandler);

    _cmsWriteUInt16Number(&iohandler, number);

    cmsCloseIOhandler(&iohandler);

    return 0;
}