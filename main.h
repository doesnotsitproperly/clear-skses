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

typedef struct
{
	size_t size;
	char** paths;
} files;

bool arg_compare(const char* a, const char* b)
{
	char* arg = (char*) malloc(sizeof(char) * (strlen(b) + 2)); // 2 extra spaces for "-" and null terminator
	strcpy(arg, "-");
	strcat(arg, b);
	if (strcmp(a, arg) == 0)
	{
		free(arg);
		return true;
	}

	arg = (char*) realloc(arg, sizeof(char) * (strlen(b) + 3)); // 2 extra spaces for "--" and null terminator
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

char* get_stem(const char* path)
{
	char* stem = (char*) malloc(sizeof(char) * (strlen(path) + 1));
	strcpy(stem, path);

	char* extension = strrchr(stem, '.');

	if (!extension)
		return stem;

	for (size_t i = 0; i < strlen(extension); i++)
		extension[i] = '\0'; // Replace the characters representing the extension with null

	return stem;
}

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

files* get_files(const char* path)
{
	files* f = (files*) malloc(sizeof(files));
	f->size = 0;
	f->paths = (char**) malloc(sizeof(char*));

#ifdef __cplusplus

	for (const directory_entry& entry : directory_iterator(path))
	{
		std::filesystem::path name = entry.path().filename();

		f->size++;
		f->paths = (char**) realloc(f->paths, sizeof(char*) * f->size);

		f->paths[f->size - 1] = (char*) malloc(sizeof(char) * (name.string().length() + 1));
		strcpy(f->paths[f->size - 1], name.string().c_str());
	}

#else

	DIR* dir = opendir(path);
	struct dirent* de = readdir(dir);
	while (de)
	{
		if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
		{
			f->size++;
			f->paths = (char**) realloc(f->paths, sizeof(char*) * f->size);

			f->paths[f->size - 1] = (char*) malloc(sizeof(char) * (strlen(de->d_name) + 1));
			strcpy(f->paths[f->size - 1], de->d_name);
		}
		de = readdir(dir);
	}
	closedir(dir);

#endif

	return f;
}

#ifdef _WIN32

#ifdef __cplusplus
char* get_save_dir()
#else
char* get_save_dir(void)
#endif
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

	free(save_dir);
	fprintf(stderr, "Unable to find Skyrim save directory\n");
	exit(EXIT_FAILURE);
}

#endif
