# Clear SKSE's

Command-line tool to delete SKSE files left behind after their corresponding saves have been deleted

The name is a reference to the "Clear Skies" shout

**Deletes any SKSE file that does not have a matching ESS file, use at your own risk**

## Usage

Command-line options (must be preceded by - or --):
```
h, help      Display this info
l, list      List files that get deleted
q, quiet     Do not display any output besides errors (overrides l/list)
v, version   Display Clear SKSE's version
```

On Windows, there is an additional `no-wait` option; if `no-wait` is not passed, the program calls `pause` before ending

If on Windows, providing a directory on the command-line is optional; if not provided, a few directories are checked for automatically:
- `%USERPROFILE%\Documents\My Games\Skyrim Special Edition\Saves`
- `%USERPROFILE%\OneDrive\Documents\My Games\Skyrim Special Edition\Saves`
- `%USERPROFILE%\Documents\My Games\Skyrim Special Edition GOG\Saves`
- `%USERPROFILE%\OneDrive\Documents\My Games\Skyrim Special Edition GOG\Saves`

## Compiling

Clear SKSE's can be compiled as C or C++; compiling as C requires the POSIX `dirent.h` header, while compiling as C++ requires the C++17 `filesystem` header
