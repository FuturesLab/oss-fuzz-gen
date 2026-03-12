// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsWriteUInt32Number at cmsplugin.c:295:20 in lcms2_plugin.h
// _cmsWriteUInt8Number at cmsplugin.c:258:20 in lcms2_plugin.h
// _cmsWriteAlignment at cmsplugin.c:462:19 in lcms2_plugin.h
// _cmsReadAlignment at cmsplugin.c:445:19 in lcms2_plugin.h
// _cmsReadUInt32Number at cmsplugin.c:156:20 in lcms2_plugin.h
// _cmsReadUInt8Number at cmsplugin.c:111:20 in lcms2_plugin.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2_plugin.h"

#define TRUE 1
#define FALSE 0

static cmsUInt32Number DummyRead(struct _cms_io_handler* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count) {
    return fread(Buffer, size, count, (FILE*) iohandler->stream);
}

static cmsBool DummySeek(struct _cms_io_handler* iohandler, cmsUInt32Number offset) {
    return fseek((FILE*) iohandler->stream, offset, SEEK_SET) == 0 ? TRUE : FALSE;
}

static cmsBool DummyClose(struct _cms_io_handler* iohandler) {
    return fclose((FILE*) iohandler->stream) == 0 ? TRUE : FALSE;
}

static cmsUInt32Number DummyTell(struct _cms_io_handler* iohandler) {
    return (cmsUInt32Number) ftell((FILE*) iohandler->stream);
}

static cmsBool DummyWrite(struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer) {
    return fwrite(Buffer, size, 1, (FILE*) iohandler->stream) == 1 ? TRUE : FALSE;
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) + sizeof(cmsUInt8Number)) {
        return 0;
    }

    cmsIOHANDLER ioHandler;
    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) {
        return 0;
    }

    ioHandler.stream = file;
    ioHandler.Read = DummyRead;
    ioHandler.Seek = DummySeek;
    ioHandler.Close = DummyClose;
    ioHandler.Tell = DummyTell;
    ioHandler.Write = DummyWrite;

    cmsUInt32Number uint32Number = *((cmsUInt32Number*)Data);
    cmsUInt8Number uint8Number = *(Data + sizeof(cmsUInt32Number));

    _cmsWriteUInt32Number(&ioHandler, uint32Number);
    _cmsWriteUInt8Number(&ioHandler, uint8Number);

    _cmsWriteAlignment(&ioHandler);
    _cmsReadAlignment(&ioHandler);

    cmsUInt32Number readUInt32;
    cmsUInt8Number readUInt8;

    ioHandler.Seek(&ioHandler, 0);
    _cmsReadUInt32Number(&ioHandler, &readUInt32);
    _cmsReadUInt8Number(&ioHandler, &readUInt8);

    ioHandler.Close(&ioHandler);
    return 0;
}