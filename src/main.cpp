#include <iostream>
#include <cstring>
#include <fstream>

bool checkFile(std::string filename, std::string argv) {
    std::ifstream file(filename);
    bool flag;
    if (file.is_open()) {
        std::string tmp;
        while (getline(file, tmp)) {
            if (argv == tmp) {
                flag = true;
                break;
            }
        }
    }
    file.close();
    return flag;
}

std::string getExtension(std::string filename) {
    std::string extension;
    for (int i = 0; i < filename.length(); i++) {
        if (filename[i] == '.') {
            for (int j = i; j < filename.length(); j++) {
                extension += filename[j];
            }
            break;
        }
    }
    return extension;
}

void insertCode(std::string precode, char filename[]) {
    char insert[precode.length() + strlen(filename) + 1];
    strcpy(insert, precode.c_str());
    strcat(insert, filename);
    system(insert);
}

int main(int argc, char * argv[]) {
    if (argc < 2 || argc > 2) {
        std::cout << "2 arguments required!\n";
        return 1;
    }
    else {
        system("ls > tmp");
        char openVim[4 + strlen(argv[1])] = "vim ";
        strcat(openVim, argv[1]);

        if (checkFile("tmp", argv[1])) {
            system("rm tmp");
            system(openVim);
        }
        else{
            system("rm tmp");
            
            enum Language { c, cpp, rs };

            std::string precode[] = {
                "echo \"#include <stdio.h>\n\nint main(void)\n{\n}\" > ",
                "echo \"#include <iostream>\n\nint main()\n{\n}\" > ",
                "echo \"fn main()\n{\n}\" > "
            };

            if (getExtension(argv[1]) == ".c") {
                insertCode(precode[c], argv[1]);
                system(openVim);
            }
            else if (getExtension(argv[1]) == ".cpp" || getExtension(argv[1]) == ".cc") {
                insertCode(precode[cpp], argv[1]);
                system(openVim);
            }
            else if (getExtension(argv[1]) == ".rs") {
                insertCode(precode[rs], argv[1]);
                system(openVim);
            }
            else {
                system(openVim);
            }
        }
        return 0;
    }
}
