/**
 * License: MIT. See LICENSE in root directory.
 * \date 2020/06/27
 */

#pragma once

#include <string>

namespace Ensemble {

/**
 *
 */
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

    int maxNumberDrives() const
    { return sizeof(driveValues) / sizeof(*driveValues); }

    int numberDrives();

    int validDrive(int);

    void checkDrives();

    static int numberOfFilesWithFilename(const char*);

    static int numberOfFilesWithAttribute(int);

    static int numberOfFilesWithFilenameOrAttribute(const char*, int);

    bool resetCurrentDriveAndDirectory();

private:

    bool resetCurrentDrive();

    bool resetCurrentDirectory();

    bool changeDrive(int);

    bool changeDirectory(const char*);

    void updateDirectory();
};

} // namespace Ensemble
