#pragma once 

#include "FS.h"
#include <LittleFS.h>

class FileSystem_{

private:
    FileSystem_(); //Constructor private
public:
    static FileSystem_ &getInstance(); // Accessor for singleton instance
    FileSystem_(const FileSystem_ &) = delete; // no copying
    FileSystem_ &operator=(const FileSystem_ &) = delete;

public: 
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void createDir(fs::FS &fs, const char * path);
    void removeDir(fs::FS &fs, const char * path);
    void readFile(fs::FS &fs, const char * path);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void renameFile(fs::FS &fs, const char * path1, const char * path2);
    void deleteFile(fs::FS &fs, const char * path);
    void testFileIO(fs::FS &fs, const char * path);

};

extern FileSystem_ &Files;