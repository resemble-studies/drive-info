/**
 * License: MIT. See LICENSE in root directory.
 * \date 2020/11/21
 */

#pragma once

#include <string>

namespace Ensemble {

inline int compareFilenameStrings(void* e1, void* e2);

inline int driveAsLetter(int d);
inline int driveAsInt(char d);

class DriveInformation {

protected:

    int initialDriveValue = 0;
    std::string initialDirectoryValue {};

    int currentDriveValue = 0;
    std::string currentDirectoryValue {};

    int driveValues[1 + 26] {};

public:

    DriveInformation();

public:

    int initialDrive() const;
    char initialDriveAsLetter() const;
    const char* initialDirectory();

    int currentDrive() const;
    char currentDriveAsLetter() const;
    const char* currentDirectory();

    int maxNumberDrives() const;
    int numberDrives();
    int validDrive(int);

    void checkDrives();

    static int numberOfFilesWithFilename(const char*);
    static int numberOfFilesWithAttribute(int);
    static int numberOfFilesWithFilenameOrAttribute(const char*, int);

private:

    bool resetCurrentDriveAndDirectory();
    bool resetCurrentDrive();
    bool resetCurrentDirectory();

    bool changeDrive(int);
    bool changeDirectory(const char*);

    void updateDirectory();
};

} // namespace Ensemble
