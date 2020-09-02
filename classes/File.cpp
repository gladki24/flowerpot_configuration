//
// Created by seweryn.gladysz on 02.09.2020.
//

#include "File.h"
#include "../exceptions/FileNotFoundException.h"
#include <fstream>
#include <iostream>
#include <regex>

namespace FlowerpotConfiguration {

    File::File(const std::string path) : _path(path) {}

    void File::setPath(const std::string path) {
        _path = path;
    }

    std::string File::getPath() const {
        return _path;
    }

    std::map<std::string, std::string> File::load(const std::string path) {
        std::ifstream file(path);

        if (file.is_open()) {
            // TODO refactor regex
            std::regex keyRegex(R"(([\w\d])+(?=[\s\=]))");
            std::regex valueRegex(R"()");

            std::smatch keyMatch;
            std::smatch valueMatch;

            std::string line;
            std::map<std::string, std::string> configuration;

            while (std::getline(file, line)) {
                std::cout << line << std::endl;
                bool hasKey = std::regex_search(line, keyMatch, keyRegex);
                bool hasValue = std::regex_search(line, valueMatch, valueRegex);

                if (hasKey && hasValue) {
                    configuration.insert(keyMatch.str(), valueMatch.str());
                }
            }

            file.close();

            return std::map<std::string, std::string>();
        } else {
            throw FileNotFoundException();
        }
    }

    std::map<std::string, std::string> File::load() {
        return load(_path);
    }
}