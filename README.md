# Clear SKSE Files

Command-line tool to delete SKSE files left behind after their corresponding saves have been deleted

Optional command-line argument for directory to scan, otherwise looks for `%USERPROFILE%\Documents\My Games\Skyrim Special Edition\Saves` or `%USERPROFILE%\OneDrive\Documents\My Games\Skyrim Special Edition\Saves`

**Deletes any SKSE file that does not have a matching ESS file, use at your own risk**

```
Usage: <executable> [options] [directory]
Options:
h, help    Display this info
l, list    List files that get deleted
q, quiet   Do not display any output besides errors (overrides l/list)
Note: All options must be preceded by - or --
```
