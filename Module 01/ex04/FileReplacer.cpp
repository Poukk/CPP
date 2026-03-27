#include "FileReplacer.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

FileReplacer::FileReplacer(const std::string &inputFileName,
                           const std::string &search,
                           const std::string &replacement)
    : inputFileName(inputFileName), search(search), replacement(replacement) {}

FileReplacer::~FileReplacer() {}

std::string FileReplacer::replaceAll(const std::string &content) const {
    std::string result;
    std::string::size_type start;
    std::string::size_type found;

    start = 0;
    found = content.find(search, start);
    while (found != std::string::npos) {
        result.append(content, start, found - start);
        result += replacement;
        start = found + search.length();
        found = content.find(search, start);
    }
    result.append(content, start, content.length() - start);
    return (result);
}

bool FileReplacer::process() const {
    std::ifstream inputFile(inputFileName.c_str());
    std::ofstream outputFile;
    std::ostringstream buffer;
    std::string outputFileName;

    if (search.empty()) {
        std::cerr << "Error: s1 must not be empty." << std::endl;
        return (false);
    }
    if (!inputFile.is_open()) {
        std::cerr << "Error: could not open input file." << std::endl;
        return (false);
    }
    buffer << inputFile.rdbuf();
    if (inputFile.bad()) {
        std::cerr << "Error: could not read input file." << std::endl;
        return (false);
    }
    outputFileName = inputFileName + ".replace";
    outputFile.open(outputFileName.c_str());
    if (!outputFile.is_open()) {
        std::cerr << "Error: could not create output file." << std::endl;
        return (false);
    }
    outputFile << replaceAll(buffer.str());
    if (!outputFile) {
        std::cerr << "Error: could not write output file." << std::endl;
        return (false);
    }
    return (true);
}
