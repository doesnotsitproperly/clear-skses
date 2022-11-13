# Clear SKSE's

Command-line tool to delete SKSE files left behind after their corresponding saves have been deleted

**Deletes any SKSE file that does not have a matching ESS file, use at your own risk**

```
Usage: <executable> [options] [directory]
Options:
h, help    Display this info
l, list    List files that get deleted
q, quiet   Do not display any output besides errors (overrides l/list)
Note: All options must be preceded by - or --
```

If on Windows, `[directory]` is optional; if not provided `%USERPROFILE%\Documents\My Games\Skyrim Special Edition\Saves` or `%USERPROFILE%\OneDrive\Documents\My Games\Skyrim Special Edition\Saves` will be searched

If compiled on Windows and without `NO_WAIT` defined, `pause` will be called before the program ends  
This is how the release is compiled

Yes, the name is a reference to the "Clear Skies" shout
