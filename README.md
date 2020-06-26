# Ensemble Drive Information

A simple drive and directory information encapsulation, reversed from Ensemble.

## Usage

```c++
using Ensemble::DriveInformation;
```

```c++
auto driveInfo = new DriveInformation();
```

```c++
printf("Initial drive as integer: %d\n", driveInfo->initialDrive());
printf("Initial drive as letter: %c\n", driveInfo->initialDriveAsLetter());
printf("Initial directory: %s\n", driveInfo->initialDirectory());
```

```c++
printf("Current drive as integer: %d\n", driveInfo->currentDrive());
printf("Current drive as letter: %c\n", driveInfo->currentDriveAsLetter());
printf("Current directory: %s\n", driveInfo->currentDirectory());
```

```c++
driveInfo->checkDrives();
auto numDrives = driveInfo->numberDrives();
printf("Number of drives: %d\n", numDrives);

for (int i = 1; i < driveInfo->maxNumberDrives(); ++i)
{
    printf("Drive %d valid: %d\n", i, driveInfo->validDrive(i));
}
```

```c++
std::string s;
s = "sample";
printf("Number of files with name \"%s\": %d", s.c_str(), DriveInformation::numberOfFilesWithFilename(s.c_str()));
```
