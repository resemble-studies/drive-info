/**
 * License: MIT. See LICENSE in root directory.
 * \date 2020/11/21
 */

#include <io.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <direct.h>

#include <ensemble/drive-info.hpp>

namespace Ensemble {

int compareFilenameStrings(void* e1, void* e2)
{
    return strcmp((const char*)e1, (const char*)e2);
}

int driveAsLetter(int d)
{
    return d + 64;
}

int driveAsInt(char d)
{
    return d - 64;
}

DriveInformation::DriveInformation()
    :
    initialDriveValue(::_getdrive()),
    currentDriveValue(initialDriveValue)
{
    updateDirectory();
    initialDirectoryValue = currentDirectoryValue;
}

int DriveInformation::initialDrive() const
{
    return initialDriveValue;
}

char DriveInformation::initialDriveAsLetter() const
{
    return driveAsLetter(initialDriveValue);
}

const char* DriveInformation::initialDirectory()
{
    return initialDirectoryValue.c_str();
}

int DriveInformation::currentDrive() const
{
    return currentDriveValue;
}

char DriveInformation::currentDriveAsLetter() const
{
    return driveAsLetter(currentDriveValue);
}

const char* DriveInformation::currentDirectory()
{
    return currentDirectoryValue.c_str();
}

int DriveInformation::maxNumberDrives() const
{
    return sizeof(driveValues) / sizeof(*driveValues);
}

int DriveInformation::numberDrives()
{
    return driveValues[0];
}

int DriveInformation::validDrive(int v)
{
    return driveValues[v];
}

void DriveInformation::checkDrives()
{
    driveValues[0] = 0;
    for (int i = 1; i < sizeof(driveValues) / sizeof(*driveValues); ++i)
    {
        if (::_chdrive(i))
        {
            driveValues[i] = 0;
        }
        else
        {
            driveValues[0] += 1;
            driveValues[i] = 1;
        }
    }
    ::_chdrive(currentDriveValue);
}

int DriveInformation::numberOfFilesWithFilename(const char* n)
{
    ::_finddata_t fileInfo {};
    int found = ::_findfirst(n, &fileInfo);
    if (found != -1)
    {
        int num_files = 1;
        while (::_findnext(found, &fileInfo) != -1)
        {
            num_files++;
        }

        return num_files;
    }

    return 0;
}

int DriveInformation::numberOfFilesWithAttribute(int a)
{
    ::_finddata_t fileInfo {};
    int found = ::_findfirst("*.*", &fileInfo);
    if (found != -1)
    {
        int num_files = 1;
        while (::_findnext(found, &fileInfo) != -1)
        {
            if (a & fileInfo.attrib)
            {
                num_files++;
            }
        }

        return num_files;
    }

    return 0;
}

int DriveInformation::numberOfFilesWithFilenameOrAttribute(const char* n, int a)
{
    ::_finddata_t fileInfo {};
    int found = ::_findfirst("*.*", &fileInfo);
    if (found != -1)
    {
        int num_files = 1;
        while (::_findnext(found, &fileInfo) != -1)
        {
            if (a & fileInfo.attrib || std::strstr(fileInfo.name, n))
            {
                num_files++;
            }
        }

        return num_files;
    }

    return 0;
}

bool DriveInformation::resetCurrentDriveAndDirectory()
{
    return resetCurrentDrive() && resetCurrentDirectory();
}

bool DriveInformation::resetCurrentDrive()
{
    return changeDrive(initialDriveValue);
}

bool DriveInformation::resetCurrentDirectory()
{
    return changeDirectory(initialDirectoryValue.c_str());
}

bool DriveInformation::changeDrive(int d)
{
    if (::_chdrive(d) == 0)
    {
        currentDriveValue = d;

        return true;
    }

    return false;
}

bool DriveInformation::changeDirectory(const char* d)
{
    if (::_chdir(d) == 0)
    {
        updateDirectory();

        return true;
    }

    return false;
}

void DriveInformation::updateDirectory()
{
    char fullPath[_MAX_PATH] {};
    ::_getcwd(fullPath, sizeof(fullPath));

    char cDrive[_MAX_DRIVE], filename[_MAX_FNAME], extension[_MAX_EXT];
    ::_wsplitpath(
        (wchar_t*)fullPath,
        (wchar_t*)cDrive,
        (wchar_t*)currentDirectoryValue.c_str(),
        (wchar_t*)filename,
        (wchar_t*)extension);

    char tempString[_MAX_DIR];
    ::snprintf(
        tempString,
        sizeof(tempString),
        "%s%s%s",
        currentDirectoryValue.c_str(),
        filename,
        extension);

    currentDirectoryValue = tempString;
}

} // namespace Ensemble
