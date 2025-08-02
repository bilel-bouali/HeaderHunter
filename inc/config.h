#ifndef HEADER_HUNTER_INC_CONFIG__H
#define HEADER_HUNTER_INC_CONFIG__H

#include <vector>
#include <string>
#include <unordered_map>
#include <string_view>
#include <unordered_set>

#define MIN_SIZE_ARGS 4
#define MAX_SIZE_ARGS 7

namespace HeaderHunter{

class Config{

public:
    Config(const std::vector<std::string> &args);
    ~Config() = default;
    void generateReport();

private:

    bool m_ignore_system_includes = false;
    int m_max_line = 0;
    std::string m_output_file;
    std::string m_input_folder;
    int m_file_id_counter = 0;

    std::unordered_map<int, std::string> m_list_files_index;
    std::unordered_map<std::string, int> m_list_files_name;
    std::unordered_set<int> m_list_system_files;
    std::unordered_set<int> m_list_local_files;

    void parseArguments(const std::vector<std::string> &args);

    std::unordered_map<int, std::vector<int>> buildDependencies();

    void helper(std::string_view message = "");

    std::vector<int> getAllIncludedFiles(const std::string &file_path);

    int getFileId(const std::string &file_name, bool is_system_file);
};
};
#endif // HEADER_HUNTER_INC_CONFIG__H