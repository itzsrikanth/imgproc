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
    char *type = NULL;
    uint8_t len = 0;
    vecStr dirlist, recursiveList;

    printf("debug: %s\n", dirName);
    dirhold = opendir(dirName);
    if(!dirhold) {
        printf("Unable to open %s\n", dirName);
    } else {
        while((drnt = readdir(dirhold))) {
            len = strlen(dirName) + strlen(drnt->d_name) + 1;
            if (type != NULL && strlen(type) < len) {
                delete[] type;
                type = NULL;
            }
            if (type == NULL) {
                type = new char[len];
            }
            if (dirName[strlen(dirName) - 1] == '/') {
                sprintf(type, "%s%s", dirName, drnt->d_name);
            } else {
                sprintf(type, "%s/%s", dirName, drnt->d_name);
            }
            // printf("%-20s\t%llu\n", drnt->d_name, drnt->d_ino);
            if(strcmp(drnt->d_name, ".") && strcmp(drnt->d_name, "..")) {
                switch(drnt->d_type) {
                    case DT_DIR:
                        recursiveList = dir(type);
                        dirlist.insert(dirlist.end(), recursiveList.begin(), recursiveList.end());
                        break;
                    case DT_REG:
                        dirlist.push_back(type);
                        break;
                }
            }
        }
        closedir(dirhold);
    }
    if (type != NULL) {
        delete[] type;
    }
    return dirlist;
}