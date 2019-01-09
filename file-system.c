//
// Created by Marcus Novoa on 2019-01-08.
//

#include "file-system.h"

void runJavaScriptBundler()
{
    int numOfFiles;
    static long int totalByteSize;

    printf("Welcome to the JavaScript Bundler program!\n");
    printf("(C) 2019 MiniWebpack developed by Marcus Novoa\n\n");
    printf("(Note: Please make sure all JS files are within a local directory named \"files\")\n\n");
    printf("How many files would you like to include in your bundle? ");
    scanf("%d", &numOfFiles);

    // Run readFilesAndWriteToBundle() - Returns Bundle file and total file(s) byte size
    BundleResults res = readFilesAndWriteToBundle(numOfFiles, totalByteSize);

    FILE *bundle = res.file;
    totalByteSize = res.totalBytes;

    printf("\nTotal sum of file sizes: %li bytes\n", totalByteSize);
    printf("Total size of bundle.js: %li bytes\n", ftell(bundle));
    printf("Bundle completed! (%li bytes removed)\n", (totalByteSize - ftell(bundle)));
    fclose(bundle);

    exit(0);
}

BundleResults readFilesAndWriteToBundle(int numOfFiles, long int totalByteSize)
{
    BundleFile *filesArr;
    char errorMsg[101];
    char *c;
    int i;

    // Mallocate memory for files array
    filesArr = (BundleFile *)malloc(numOfFiles * sizeof(BundleFile));

    // Input local file names
    for (i = 0; i < numOfFiles; i++)
    {
        printf("File %d/%d. Please enter the file name (no extension): ", i + 1, numOfFiles);
        scanf("%s", filesArr[i].fileName);
    }

    char filePath[101];

    // Open and read all files in files array. Return error if null
    for (i = 0; i < numOfFiles; i++)
    {
        sprintf(filePath, "../files/%s.js", filesArr[i].fileName);
        filesArr[i].file = fopen(filePath, "r");
        if (filesArr[i].file == NULL)
        {
            snprintf(errorMsg, sizeof errorMsg, "The file '%s' does not exist", filesArr[i].fileName);
            perror(errorMsg);
            exit(1);
        }
    }

    // Initialize Bundle write file
    FILE *bundle;
    bundle = fopen("../files/bundle.js", "w");

    // Write to Bundle file; Add to total byte size sum
    for (i = 0; i < numOfFiles; i++)
    {
        getAndPutChars(&c, filesArr[i].file, bundle, filesArr[i].fileName);
        totalByteSize += getAndPutChars(&c, filesArr[i].file, bundle, filesArr[i].fileName);
        printf("Total size of %s.js: %li bytes\n", filesArr[i].fileName, ftell(filesArr[i].file));
        fclose(filesArr[i].file);
    }

    // Return Bundle file and total byte size of file(s) using BundleResults Struct
    BundleResults res = {.file = bundle, .totalBytes = totalByteSize};
    return res;
}

long int getAndPutChars(char *c, FILE *getFile, FILE *putFile, char fileName[51])
{
    while ((*c = getc(getFile)) != EOF)
    {
        if (*c == '\n')
        {
            while ((*c = getc(getFile)) == '\n') {}
            fseek(putFile, -1, SEEK_CUR);
        }
        if (*c == 32)
        {
            while ((*c = getc(getFile)) == 32) {}
            putc(' ', putFile);
        }
        putc(*c, putFile);
    }
    long int byteSize = ftell(getFile);
    return byteSize;
}
