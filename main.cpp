#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#ifdef _WIN32
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif

using namespace std;
using namespace std::filesystem;

int main(const int argc, const char* argv[])
{
    string save_dir;

    if (argc > 1)
    {
        save_dir = argv[1];
        if (!exists(save_dir))
        {
            cerr << "Unable to find provided directory" << NEWLINE;
            return EXIT_FAILURE;
        }
    }
    else
    {
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

    int deleted = 0;
    for (const directory_entry &entry : directory_iterator(save_dir))
    {
        path entry_path = entry.path();
        if (entry_path.extension() == ".skse")
        {            
            if (!exists(entry_path.parent_path().string() + "\\" + entry_path.stem().string() + ".ess"))
            {
                remove(entry_path.string().c_str());
                deleted++;
            }
        }
    }

    cout << "Deleted " << deleted << " files" << NEWLINE;

    return EXIT_SUCCESS;
}
