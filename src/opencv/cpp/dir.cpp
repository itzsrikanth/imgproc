#include <iostream>
#include <cstring>
#include <vector>
#include <dirent.h>

using namespace std;

typedef vector<string> vecStr;
vecStr dir(char *dirName);

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Please specify a directory\n");
        return 1;
    }
    vecStr list = dir(argv[1]);
    vecStr::iterator it;
    for(it = list.begin(); it < list.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}

vecStr dir(char *dirName) {
    DIR *dirhold = NULL;
    struct dirent *drnt = NULL;
    // char *type = NULL;
    vecStr dirlist, recursiveList;
    dirhold = opendir(dirName);
    if(!dirhold) {
        printf("Unable to open %s\n", dirName);
    } else {
        while((drnt = readdir(dirhold))) {
            printf("%-20s\t%llu\n", drnt->d_name, drnt->d_ino);
            // switch(drnt->d_type) {
            //     case DT_DIR:
            //         recursiveList = dir(drnt->d_name);
            //         dirlist.insert(dirlist.end(), recursiveList.begin(), recursiveList.end());
            //         break;
            //     case DT_REG:
            //         dirlist.push_back(drnt->d_name);
            //         break;
            // }
        }
        // printf("dir: %d\n", DT_DIR);
        closedir(dirhold);
    }
    return dirlist;
}