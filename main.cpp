#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#ifndef _WIN32
#error "This program is meant only for Windows!" 
#endif

using namespace std;
using namespace std::filesystem;

int main()
{
    string user_profile = getenv("USERPROFILE");

    string save_dir = user_profile + "\\Documents\\My Games\\Skyrim Special Edition\\Saves";
    if (!exists(save_dir))
    {
        save_dir = user_profile + "\\OneDrive\\Documents\\My Games\\Skyrim Special Edition\\Saves";
        if (!exists(save_dir))
        {
            cerr << "Unable to find Skyrim save directory\r\n";
            return EXIT_FAILURE;
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

    cout << "Deleted " << deleted << " files\r\n";

    return EXIT_SUCCESS;
}
