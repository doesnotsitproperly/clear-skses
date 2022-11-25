@echo off
g++ main.cpp -O2 -Wall -o ClearSKSEs.exe
7z a ClearSKSEs-%1.7z ClearSKSEs.exe
7z a ClearSKSEs-%1.zip ClearSKSEs.exe
