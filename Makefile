CC := gcc
CFLAGS := -Wall -O2

default:
ifeq ($(OS), Windows_NT)
	$(CC) main.c $(CFLAGS) -o ClearSKSEs.exe
else
	$(CC) main.c $(CFLAGS) -o ClearSKSEs
endif

archives: default
ifeq ($(OS), Windows_NT)
	7z a ClearSKSEs-v6.7z ClearSKSEs.exe
	7z a ClearSKSEs-v6.zip ClearSKSEs.exe
else
	7z a ClearSKSEs-v6.7z ClearSKSEs
	7z a ClearSKSEs-v6.zip ClearSKSEs
endif

run: default
ifeq ($(OS), Windows_NT)
	.\ClearSKSEs.exe -no-wait
else
	./ClearSKSEs
endif
