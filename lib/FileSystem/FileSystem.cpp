#include "FileSystem.h"

/* You only need to format LittleFS the first time you run a
   test or else use the LittleFS plugin to create a partition
   https://github.com/lorol/arduino-esp32littlefs-plugin */
void FileSystem_::begin( bool formatIfFailed ){
    if(!LittleFS.begin(formatIfFailed)){
        Serial.println("[Files][E]- LittleFS Mount Failed");
        return;
    }
} 


void FileSystem_::listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("[Files][i]- Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("[Files][E]- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("[Files][i]- not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");

#ifdef CONFIG_LITTLEFS_FOR_IDF_3_2
            Serial.println(file.name());
#else
            Serial.print(file.name());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);
#endif

            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");

#ifdef CONFIG_LITTLEFS_FOR_IDF_3_2
            Serial.println(file.size());
#else
            Serial.print(file.size());
            time_t t= file.getLastWrite();
            struct tm * tmstruct = localtime(&t);
            Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n",(tmstruct->tm_year)+1900,( tmstruct->tm_mon)+1, tmstruct->tm_mday,tmstruct->tm_hour , tmstruct->tm_min, tmstruct->tm_sec);
#endif
        }
        file = root.openNextFile();
    }
}

void FileSystem_::createDir(fs::FS &fs, const char * path){
    Serial.printf("[Files][i]- Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("[Files][i]- Dir created");
    } else {
        Serial.println("[Files][E]- mkdir failed");
    }
}

void FileSystem_::removeDir(fs::FS &fs, const char * path){
    Serial.printf("[Files][i]- Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("[Files][i]- Dir removed");
    } else {
        Serial.println("[Files][E] rmdir failed");
    }
}

// Reads the file defined by path. If success return string with content of file, else return empty string ("")
String FileSystem_::readFile(fs::FS &fs, const char * path){
    Serial.printf("[Files][i]- Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("[Files][E]- failed to open file for reading");
        return "";
    }

    String data;

    // uint8_t size = file.size() + 1;
    // Serial.printf("file size: %d\n", size);

    // char _data[size];
    // uint8_t index = 0;
    while(file.available()){
        data += (char) file.read();
        // _data[index] = (char) file.read();
        // index++;
    }
    file.close();
    // Serial.printf("index: %d\n", index);
    // Serial.printf("_data: %s\n", _data);

    // char* data = &_data[0];
    // char* data = "Fake data";
    return data;
}

void FileSystem_::writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("[Files][i]- Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("[Files][E]- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("[Files][i]- file written");
    } else {
        Serial.println("[Files][E]- write failed");
    }
    file.close();
}

void FileSystem_::appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("[Files][i]- Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("[Files][E]- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("[Files][i]- message appended");
    } else {
        Serial.println("[Files][E]- append failed");
    }
    file.close();
}

void FileSystem_::renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("[Files][i]- Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("[Files][i]- file renamed");
    } else {
        Serial.println("[Files][E]- rename failed");
    }
}

void FileSystem_::deleteFile(fs::FS &fs, const char * path){
    Serial.printf("[Files][i]- Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("[Files][i]- file deleted");
    } else {
        Serial.println("[Files][E]- delete failed");
    }
}

void FileSystem_::testFileIO(fs::FS &fs, const char * path){
    Serial.printf("[Files][i]-Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("[Files][E]- failed to open file for writing");
        return;
    }

    size_t i;
    Serial.print("[Files][i]- writing" );
    uint32_t start = millis();
    for(i=0; i<2048; i++){
        if ((i & 0x001F) == 0x001F){
          Serial.print(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    Serial.printf("[Files][i]- %u bytes written in %u ms\r\n", 2048 * 512, end);
    file.close();

    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.print("[Files][i]- reading" );
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F){
              Serial.print(".");
            }
            len -= toRead;
        }
        Serial.println("");
        end = millis() - start;
        Serial.printf("[Files][i]- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    } else {
        Serial.println("[Files][E]- failed to open file for reading");
    }
}

FileSystem_ &FileSystem_::getInstance() {
  static FileSystem_ instance;
  return instance;
}

FileSystem_ &Files = Files.getInstance();