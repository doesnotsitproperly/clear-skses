#ifdef __cplusplus

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <filesystem>

using namespace std;
using namespace std::filesystem;

#else

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#endif

bool arg_compare(const char* a, const char* b)
{
	char* arg = (char*) malloc(sizeof(char) * (strlen(b) + 2));
	strcpy(arg, "-");
	strcat(arg, b);
	if (strcmp(a, arg) == 0)
	{
		free(arg);
		return true;
	}

	arg = (char*) realloc(arg, sizeof(char) * (strlen(b) + 3));
	strcpy(arg, "--");
	strcat(arg, b);
	if (strcmp(a, arg) == 0)
	{
		free(arg);
		return true;
	}

	free(arg);
	return false;
}

bool dir_exists(const char* path)
{
#ifdef __cplusplus
	if (exists(path))
		return true;
	return false;
#else
	DIR* dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return true;
	}
	return false;
#endif
}

// Functions just for C

#ifndef __cplusplus

char* join_paths(const char* a, const char* b)
{
	char* path = (char*) malloc(sizeof(char) * (strlen(a) + strlen(b) + 2));
	strcpy(path, a);

#ifdef _WIN32
	strcat(path, "\\");
#else
	strcat(path, "/");
#endif

	strcat(path, b);

	return path;
}

char* get_stem(const char* path)
{
	char* stem = (char*) malloc(sizeof(char) * (strlen(path) + 1));
	strcpy(stem, path);

	char* extension = strrchr(stem, '.');

	if (!extension)
		return stem;

	for (size_t i = 0; i < strlen(extension); i++)
		extension[i] = '\0';

	return stem;
}

char* get_extension(const char* path)
{
	char* extension = (char*) malloc(sizeof(char));
	strcpy(extension, "");
	char* temp = strrchr(path, '.');
	if (temp)
	{
		extension = (char*) realloc(extension, sizeof(char) * (strlen(temp) + 1));
		strcat(extension, temp);
	}
	return extension;
}

bool file_exists(const char* path)
{
	FILE* f = fopen(path, "r");
	if (f)
	{
		fclose(f);
		return true;
	}
	else
		return false;
}

#endif

// Function just for Windows

#ifdef _WIN32

char* get_save_dir(void)
{
	const char* user_profile = getenv("USERPROFILE");
	if (!user_profile)
	{
		fprintf(stderr, "Unable to find user directory\n");
		exit(EXIT_FAILURE);
	}

	char* save_dir = (char*) malloc(sizeof(char) * 200);
	strcpy(save_dir, user_profile);
	strcat(save_dir, "\\Documents\\My Games\\Skyrim Special Edition\\Saves");
	if (dir_exists(save_dir))
		return save_dir;

	strcpy(save_dir, user_profile);
	strcat(save_dir, "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition\\Saves");
	if (dir_exists(save_dir))
		return save_dir;

	strcpy(save_dir, user_profile);
	strcat(save_dir, "\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves");
	if (dir_exists(save_dir))
		return save_dir;

	strcpy(save_dir, user_profile);
	strcat(save_dir, "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves");
	if (dir_exists(save_dir))
		return save_dir;

	fprintf(stderr, "Unable to find Skyrim save directory\n");
	exit(EXIT_FAILURE);
}

#endif
