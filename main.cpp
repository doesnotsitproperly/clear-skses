#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

bool arg_compare(const char* arg, const char* short_arg, const char* long_arg);

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
		const char* user_profile = std::getenv("USERPROFILE");
		if (!user_profile)
		{
			std::cerr << "Unable to find user directory\n";
			return EXIT_FAILURE;
		}

		save_dir = std::string(user_profile) + "\\Documents\\My Games\\Skyrim Special Edition\\Saves";
		if (!fs::exists(save_dir))
		{
			save_dir = std::string(user_profile) + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition\\Saves";
			if (!fs::exists(save_dir))
			{
				save_dir = std::string(user_profile) + "\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves";
				if (!fs::exists(save_dir))
				{
					save_dir = std::string(user_profile) + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves";
					if (!fs::exists(save_dir))
					{
						std::cerr << "Unable to find Skyrim save directory\n";
						return EXIT_FAILURE;
					}
				}
			}
		}
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
	std::vector<std::string> deleted_files;
	for (const fs::directory_entry& entry : fs::directory_iterator(save_dir))
	{
		fs::path entry_path = entry.path();
		if (entry_path.extension() == ".skse")
		{
#ifdef _WIN32
			if (!fs::exists(entry_path.parent_path().string() + "\\" + entry_path.stem().string() + ".ess"))
#else
			if (!fs::exists(entry_path.parent_path().string() + "/" + entry_path.stem().string() + ".ess"))
#endif
			{
				std::remove(entry_path.string().c_str());
				deleted++;
				if (list)
					deleted_files.push_back(entry_path.string());
			}
		}
	}

	if (!quiet)
	{
		std::cout << "Deleted " << deleted << " file(s)\n";
		if (list)
		{
			for (std::string file : deleted_files)
				std::cout << "Deleted \"" << file << "\"\n";
		}
#ifdef _WIN32
		if (!no_wait)
			std::system("pause");
#endif
	}

	return EXIT_SUCCESS;
}

bool arg_compare(const char* arg, const char* short_arg, const char* long_arg)
{
	const std::string ARG_STR = arg;
	const std::string SHORT_ARG_STR = short_arg;
	const std::string LONG_ARG_STR = long_arg;

	if (ARG_STR == "-" + SHORT_ARG_STR)
		return true;
	if (ARG_STR == "--" + SHORT_ARG_STR)
		return true;

	if (ARG_STR == "-" + LONG_ARG_STR)
		return true;
	if (ARG_STR == "--" + LONG_ARG_STR)
		return true;

	return false;
}
