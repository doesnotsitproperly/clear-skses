#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

int main(int argc, char* argv[])
{
	DIR* dir = opendir("C:\\Users\\perid\\Programsdf");
	closedir(dir);

	return 0;
}