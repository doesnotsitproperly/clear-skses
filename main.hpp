#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

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

#ifdef _WIN32

std::string get_save_dir()
{
	const char* user_profile = std::getenv("USERPROFILE");
	if (!user_profile)
	{
		std::cerr << "Unable to find user directory\n";
		std::exit(EXIT_FAILURE);
	}

	std::string save_dir = std::string(user_profile) + "\\Documents\\My Games\\Skyrim Special Edition\\Saves";
	if (fs::exists(save_dir))
		return save_dir;
	save_dir = std::string(user_profile) + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition\\Saves";
	if (fs::exists(save_dir))
		return save_dir;
	save_dir = std::string(user_profile) + "\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves";
	if (fs::exists(save_dir))
		return save_dir;
	save_dir = std::string(user_profile) + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves";
	if (fs::exists(save_dir))
		return save_dir;

	std::cerr << "Unable to find Skyrim save directory\n";
	exit(EXIT_FAILURE);
}

#endif
