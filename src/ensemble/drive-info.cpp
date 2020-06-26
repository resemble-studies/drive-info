/**
 * License: MIT. See LICENSE in root directory.
 * \date 2020/06/27
 */

#include <cstdio>
#include <cstring>
#include <direct.h>

#include <ensemble/drive-info.hpp>

namespace Ensemble {

////////////////////////////////////////////////////////////////////////////////////////////////////

DriveInformation::DriveInformation()
    :
    initialDriveValue(::_getdrive()),
    currentDriveValue(initialDriveValue)
{
    updateDirectory();
    initialDirectoryValue = currentDirectoryValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int DriveInformation::initialDrive() const
{
    return initialDriveValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

char DriveInformation::initialDriveAsLetter() const
{
    return initialDriveValue + 64;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const char* DriveInformation::initialDirectory()
{
    return initialDirectoryValue.c_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int DriveInformation::currentDrive() const
{
    return currentDriveValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

char DriveInformation::currentDriveAsLetter() const
{
    return currentDriveValue + 64;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

const char* DriveInformation::currentDirectory()
{
    return currentDirectoryValue.c_str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int DriveInformation::numberDrives()
{
    return driveValues[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int DriveInformation::validDrive(int v)
{
    return driveValues[v];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////

int DriveInformation::numberOfFilesWithFilenameOrAttribute(const char* n, int a)
{
    ::_finddata_t fileInfo {};
    auto found = ::_findfirst("*.*", &fileInfo);
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

////////////////////////////////////////////////////////////////////////////////////////////////////

bool DriveInformation::resetCurrentDriveAndDirectory()
{
    return resetCurrentDrive() ? resetCurrentDirectory() : false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool DriveInformation::resetCurrentDrive()
{
    return changeDrive(initialDriveValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool DriveInformation::resetCurrentDirectory()
{
    return changeDirectory(initialDirectoryValue.c_str());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool DriveInformation::changeDrive(int d)
{
    if (::_chdrive(d) == 0)
    {
        currentDriveValue = d;

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool DriveInformation::changeDirectory(const char* d)
{
    if (::_chdir(d) == 0)
    {
        updateDirectory();

        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DriveInformation::updateDirectory()
{
    char fullPath[FILENAME_MAX] {};
    ::_getcwd(fullPath, sizeof(fullPath));

    char cDrive[3], filename[256], extension[256];
    ::_wsplitpath(
        (wchar_t*)fullPath,
        (wchar_t*)cDrive,
        (wchar_t*)currentDirectoryValue.c_str(),
        (wchar_t*)filename,
        (wchar_t*)extension);

    char tempString[0x100];
    ::snprintf(
        tempString,
        sizeof(tempString),
        "%s%s%s",
        currentDirectoryValue.c_str(),
        filename,
        extension);
    currentDirectoryValue = tempString;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Ensemble
