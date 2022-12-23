#include "main.hpp"

int main(int argc, char* argv[])
{
	bool list = false;
#ifdef _WIN32
	bool no_wait = false;
#endif
	bool quiet = false;
	std::string save_dir = "";
	for (int i = 1; i < argc; i++)
	{
		if (arg_compare(argv[i], "h", "help"))
		{
#ifdef _WIN32
			std::cout << "Usage: <executable> [options] [directory]\n";
#else
			std::cout << "Usage: <executable> [options] <directory>\n";
#endif
			std::cout << "Options:\n";
			std::cout << "h, help      Display this info\n";
			std::cout << "l, list      List files that get deleted\n";
#ifdef _WIN32
			std::cout << "no-wait      Do not wait for input before program ends\n";
#endif
			std::cout << "q, quiet     Do not display any output besides errors (overrides l/list)\n";
			std::cout << "v, version   Display Clear SKSE's version\n";
			std::cout << "Note: All options must be preceded by - or --\n";
			return EXIT_SUCCESS;
		}
		else if (arg_compare(argv[i], "v", "version"))
		{
			std::cout << "Clear SKSE's v5\n";
			return EXIT_SUCCESS;
		}
	}

	for (int i = 1; i < argc; i++)
	{
		if (arg_compare(argv[i], "l", "list"))
			list = true;
#ifdef _WIN32
		else if (arg_compare(argv[i], "no-wait", ""))
			no_wait = true;
#endif
		else if (arg_compare(argv[i], "q", "quiet"))
			quiet = true;
		else
			save_dir = argv[i];
	}

	if (save_dir == "")
	{
#ifdef _WIN32
		save_dir = get_save_dir();
#else
		std::cerr << "No directory was provided!\n";
		return EXIT_FAILURE;
#endif
	}
	else if (!fs::exists(save_dir))
	{
		std::cerr << "Unable to find provided directory\n";
		return EXIT_FAILURE;
	}

	size_t deleted = 0;
	for (const fs::directory_entry& entry : fs::directory_iterator(save_dir))
	{
		fs::path entry_path = entry.path();
		if (entry_path.extension() == ".skse")
		{
			if (!fs::exists((entry_path.parent_path() / entry_path.stem()).string() + ".ess"))
			{
				std::remove(entry_path.string().c_str());
				deleted++;
				if (list && !quiet)
					std::cout << "Deleted \"" << entry_path.string() << "\"\n";
			}
		}
	}

	if (!quiet)
	{
		std::cout << "Deleted " << deleted << " files\n";
#ifdef _WIN32
		if (!no_wait)
			std::system("pause");
#endif
	}

	return EXIT_SUCCESS;
}
