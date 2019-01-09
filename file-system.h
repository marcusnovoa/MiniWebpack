//
// Created by Marcus Novoa on 2019-01-08.
//

#ifndef JSBUNDLER_FILE_SYSTEM_H
#define JSBUNDLER_FILE_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BUNDLEFILE
{
    FILE *file;
    char fileName[51];
} BundleFile;

typedef struct BUNDLERESULTS
{
    FILE *file;
    long int totalBytes;
} BundleResults;

void runJavaScriptBundler();
BundleResults readFilesAndWriteToBundle(int numOfFiles, long int totalByteSize);
long int getAndPutChars();

#endif //JSBUNDLER_FILE_SYSTEM_H
