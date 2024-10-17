//
// Created by Cory Kacal on 8/20/24.
//

#ifndef UNTITLED_FILEHELPER_H
#define UNTITLED_FILEHELPER_H

#include <fstream>
#include <iostream>
#include <cassert>

class FileHelper {
public:
    static std::ifstream openFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            assert(file.is_open());
        }
        return file;
    }
};

#endif //UNTITLED_FILEHELPER_H
