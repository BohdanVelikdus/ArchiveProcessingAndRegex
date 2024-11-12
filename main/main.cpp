#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <regex>
#include <filesystem>


#include <fmt/core.h>
#include <archive.h>
#include <archive_entry.h>

std::string regexp;
std::regex rgx;

void processArchives(std::string path)
{
    struct archive *a = nullptr;
    struct archive_entry *entry = nullptr;
    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    int r; 
    r = archive_read_open_filename(a, path.c_str(), 10240);
    if(r != ARCHIVE_OK)
    {
        std::cerr << "Error with an archive\n";
        return;
    }
    while (archive_read_next_header(a, &entry ) == ARCHIVE_OK) {
        std::string fullPath = archive_entry_pathname(entry);
        auto start = fullPath.rfind("/");
        std::string fileName = fullPath.substr(start+1);
        if(fileName.size() != 0)
        {
            if(std::regex_match(fileName, rgx))
            {
                std::cout << "Match found in archive: " << path << "\n-File: " << fileName << "\n";
            }
        } 
        archive_read_data_skip(a);  
    }    
    r = archive_read_free(a);  
    if (r != ARCHIVE_OK)
        exit(1);

    return;
}

int main() {   
    std::string directoryPath = "../Archives";
    std::getline(std::cin, regexp);       
    rgx = std::regex(regexp);
    std::filesystem::path path(directoryPath);
    std::filesystem::directory_iterator it(path);
    std::filesystem::directory_iterator end;
    for(; it!= end; ++it)
    {
        std::string extension = it->path().extension().string();
        //std::cout << extension << "\n"; 
        const std::vector<std::string> archive_extensions = {".zip", ".rar", ".tar", ".gz", ".7z", ".tgz"};
        auto vectorIt = std::find(archive_extensions.begin(), archive_extensions.end(), extension);
        if(vectorIt != archive_extensions.end())
            processArchives(it->path().string());
    }
}