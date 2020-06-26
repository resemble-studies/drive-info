/**
 * License: MIT. See LICENSE in root directory.
 * \date 2020/06/27
 */

#include <ensemble/drive-info.hpp>

using Ensemble::DriveInformation;

int main()
{
    auto driveInfo = new DriveInformation();

    printf("Initial drive as integer: %d\n", driveInfo->initialDrive());
    printf("Initial drive as letter: %c\n", driveInfo->initialDriveAsLetter());
    printf("Initial directory: %s\n", driveInfo->initialDirectory());

    printf("Current drive as integer: %d\n", driveInfo->currentDrive());
    printf("Current drive as letter: %c\n", driveInfo->currentDriveAsLetter());
    printf("Current directory: %s\n", driveInfo->currentDirectory());

    driveInfo->checkDrives();
    auto numDrives = driveInfo->numberDrives();
    printf("Number of drives: %d\n", numDrives);

    for (int i = 1; i < driveInfo->maxNumberDrives(); ++i)
    {
        printf("Drive %d valid: %d\n", i, driveInfo->validDrive(i));
    }

    std::string s;
    s = "sample";
    printf("Number of files with name \"%s\": %d", s.c_str(), DriveInformation::numberOfFilesWithFilename(s.c_str()));
}
