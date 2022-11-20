#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::filesystem;

bool arg_compare(const char* arg, const char* short_arg, const char* long_arg);

int main(const int argc, const char* argv[])
{
    bool list = false;
#ifdef _WIN32
    bool no_wait = false;
#endif
    bool quiet = false;
    bool version = false;
    string save_dir = "";
    for (int i = 1; i < argc; i++)
    {
        if (arg_compare(argv[i], "h", "help"))
        {
#ifdef _WIN32
            cout << "Usage: <executable> [options] [directory]\n";
#else
            cout << "Usage: <executable> [options] <directory>\n";
#endif
            cout << "Options:\n";
            cout << "h, help      Display this info\n";
            cout << "l, list      List files that get deleted\n";
#ifdef _WIN32
            cout << "no-wait      Do not wait for input before program ends\n";
#endif
            cout << "q, quiet     Do not display any output besides errors (overrides l/list)\n";
            cout << "v, version   Display Clear SKSE's version\n";
            cout << "Note: All options must be preceded by - or --\n";
            return EXIT_SUCCESS;
        }
        else if (arg_compare(argv[i], "l", "list"))
            list = true;
#ifdef _WIN32
        else if (arg_compare(argv[i], "no-wait", ""))
            no_wait = true;
#endif
        else if (arg_compare(argv[i], "q", "quiet"))
            quiet = true;
        else if (arg_compare(argv[i], "v", "version"))
            version = true;
        else
            save_dir = argv[i];
    }

    if (version)
        cout << "Clear SKSE's v4\n";

    if (save_dir == "")
    {
#ifdef _WIN32
        const char* user_profile = getenv("USERPROFILE");
        if (!user_profile)
        {
            cerr << "Unable to find user directory\n";
            return EXIT_FAILURE;
        }

        save_dir = string(user_profile) + "\\Documents\\My Games\\Skyrim Special Edition\\Saves";
        if (!exists(save_dir))
        {
            save_dir = string(user_profile) + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition\\Saves";
            if (!exists(save_dir))
            {
                save_dir = string(user_profile) + "\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves";
                if (!exists(save_dir))
                {
                    save_dir = string(user_profile) + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition GOG\\Saves";
                    if (!exists(save_dir))
                    {
                        cerr << "Unable to find Skyrim save directory\n";
                        return EXIT_FAILURE;
                    }
                }
            }
        }
#else
        cerr << "No directory was provided!\n";
        return EXIT_FAILURE;
#endif
    }
    else if (!exists(save_dir))
    {
        cerr << "Unable to find provided directory\n";
        return EXIT_FAILURE;
    }

    size_t deleted = 0;
    vector<string> deleted_files;
    for (const directory_entry &entry : directory_iterator(save_dir))
    {
        path entry_path = entry.path();
        if (entry_path.extension() == ".skse")
        {
#ifdef _WIN32
            if (!exists(entry_path.parent_path().string() + "\\" + entry_path.stem().string() + ".ess"))
#else
            if (!exists(entry_path.parent_path().string() + "/" + entry_path.stem().string() + ".ess"))
#endif
            {
                remove(entry_path.string().c_str());
                deleted++;
                if (list)
                    deleted_files.push_back(entry_path.string());
            }
        }
    }

    if (!quiet)
    {
        cout << "Deleted " << deleted << " file(s)\n";
        if (list)
        {
            for (string file : deleted_files)
                cout << "Deleted \"" << file << "\"\n";
        }
#ifdef _WIN32
        if (!no_wait)
            system("pause");
#endif
    }

    return EXIT_SUCCESS;
}

bool arg_compare(const char* arg, const char* short_arg, const char* long_arg)
{
    const string arg_str = arg;
    const string short_arg_str = short_arg;
    const string long_arg_str = long_arg;

    if ("-" + short_arg_str == arg_str)
        return true;
    if ("--" + short_arg_str == arg_str)
        return true;

    if ("-" + long_arg_str == arg_str)
        return true;
    if ("--" + long_arg_str == arg_str)
        return true;

    return false;
}
