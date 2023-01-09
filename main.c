#include "main.h"

int main(int argc, char* argv[])
{
	bool list = false;
#ifdef _WIN32
	bool no_wait = false;
#endif
	bool quiet = false;
	char* save_dir = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (arg_compare(argv[i], "h") || arg_compare(argv[i], "help"))
		{
#ifdef _WIN32
			printf("Usage: <executable> [options] [directory]\n");
#else
			printf("Usage: <executable> [options] <directory>\n");
#endif
			printf(
				"Options:\n"
				"h, help      Display this info\n"
				"l, list      List files that get deleted\n"
#ifdef _WIN32
				"no-wait      Do not wait for input before program ends\n"
#endif
				"q, quiet     Do not display any output besides errors (overrides l/list)\n"
				"v, version   Display Clear SKSE's version\n"
				"Note: All options must be preceded by - or --\n"
			);
			return EXIT_SUCCESS;
		}
		else if (arg_compare(argv[i], "v") || arg_compare(argv[i], "version"))
		{
#ifdef __cplusplus
			printf("Clear SKSE's v6 (C++)\n");
#else
			printf("Clear SKSE's v6 (C)\n");
#endif
			return EXIT_SUCCESS;
		}
	}

	for (int i = 1; i < argc; i++)
	{
		if (arg_compare(argv[i], "l") || arg_compare(argv[i], "list"))
			list = true;
#ifdef _WIN32
		else if (arg_compare(argv[i], "no-wait"))
			no_wait = true;
#endif
		else if (arg_compare(argv[i], "q") || arg_compare(argv[i], "quiet"))
			quiet = true;
		else
			save_dir = argv[i];
	}

	if (!save_dir)
	{
#ifdef _WIN32
		save_dir = get_save_dir();
#else
		fprintf(stderr, "No directory was provided!\n");
		return EXIT_FAILURE;
#endif
	}
	else if (!dir_exists(save_dir))
	{
		fprintf(stderr, "Unable to find provided directory\n");
		return EXIT_FAILURE;
	}

	size_t deleted = 0;
	files* f = get_files(save_dir);
	for (size_t i = 0; i < f->size; i++)
	{
		char* extension = get_extension(f->paths[i]);
		if (strcmp(extension, ".skse") == 0)
		{
			char* stem = get_stem(f->paths[i]);
			char* path = join_paths(save_dir, stem);
			free(stem);
			path = (char*) realloc(path, sizeof(char) * (strlen(path) + 5));
			strcat(path, ".ess");
			if (!file_exists(path))
			{
				free(path);
				path = join_paths(save_dir, f->paths[i]);
				remove(path);
				deleted++;
				if (list && !quiet)
					printf("Deleted \"%s\"\n", path);
			}
			free(path);
		}
		free(extension);

		free(f->paths[i]);
	}
	free(f->paths);
	free(f);

	if (!quiet)
	{
		printf("Deleted %zu files\n", deleted);
#ifdef _WIN32
		if (!no_wait)
			system("pause");
#endif
	}

	free(save_dir);

	return EXIT_SUCCESS;
}
