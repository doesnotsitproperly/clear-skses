#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif

using namespace std;
using namespace std::filesystem;

bool arg_compare(const char* arg, const char* short_arg, const char* long_arg);

int main(const int argc, const char* argv[])
{
    bool list = false;
    bool quiet = false;
    string save_dir = "";
    for (int i = 1; i < argc; i++)
    {
        if (arg_compare(argv[i], "h", "help"))
        {
#ifdef _WIN32
            cout << "Usage: <executable> [options] [directory]" << NEWLINE;
#else
            cout << "Usage: <executable> [options] <directory>" << NEWLINE;
#endif
            cout << "Options:" << NEWLINE;
            cout << "h, help    Display this info" << NEWLINE;
            cout << "l, list    List files that get deleted" << NEWLINE;
            cout << "q, quiet   Do not display any output besides errors (overrides l/list)" << NEWLINE;
            cout << "Note: All options must be preceded by - or --" << NEWLINE;
            return EXIT_SUCCESS;
        }
        else if (arg_compare(argv[i], "l", "list"))
            list = true;
        else if (arg_compare(argv[i], "q", "quiet"))
            quiet = true;
        else
            save_dir = argv[i];
    }

    if (save_dir == "")
    {
#ifndef _WIN32
        cerr << "No directory was provided!" << NEWLINE;
        return EXIT_FAILURE;
#endif

        const char* user_profile = getenv("USERPROFILE");
        if (!user_profile)
        {
            cerr << "Unable to find user directory" << NEWLINE;
            return EXIT_FAILURE;
        }

        save_dir = string(user_profile) + "\\Documents\\My Games\\Skyrim Special Edition\\Saves";
        if (!exists(save_dir))
        {
            save_dir = string(user_profile) + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition\\Saves";
            if (!exists(save_dir))
            {
                cerr << "Unable to find Skyrim save directory" << NEWLINE;
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        if (!exists(save_dir))
        {
            cerr << "Unable to find provided directory" << NEWLINE;
            return EXIT_FAILURE;
        }
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
        cout << "Deleted " << deleted << " file(s)" << NEWLINE;
        if (list)
        {
            for (string file : deleted_files)
                cout << "Deleted \"" << file << "\"" << NEWLINE;
        }
    }

#if defined(_WIN32) && !defined(NO_WAIT)
    system("pause");
#endif

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
