#pragma once 

#include "FS.h"
#include <LittleFS.h>

class FileSystem_{

private:
    FileSystem_() =  default; //Constructor private
public:
    static FileSystem_ &getInstance(); // Accessor for singleton instance
    FileSystem_(const FileSystem_ &) = delete; // no copying
    FileSystem_ &operator=(const FileSystem_ &) = delete;

public: 
    void begin(bool formatIfFailed = false);
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void createDir(fs::FS &fs, const char * path);
    void removeDir(fs::FS &fs, const char * path);
    String readFile(fs::FS &fs, const char * path);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void renameFile(fs::FS &fs, const char * path1, const char * path2);
    bool deleteFile(fs::FS &fs, const char * path);
    void testFileIO(fs::FS &fs, const char * path);

};

extern FileSystem_ &Files;