#include "../inc/config.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <fstream>
#include <regex>
#include "../inc/graph.h"
#include "../inc/text_report.h"
#include "../inc/graphiz_report.h"

using namespace HeaderHunter;

Config::Config(const std::vector<std::string> &args){

    parseArguments(args);
}

static bool isSafeInteger(const std::string& str, int &ans) {
    if (str.empty()) return false;

    size_t i = 0;

    long long result = 0;
    for (; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) return false;
        result = result * 10 + (str[i] - '0');

        // Check bounds early
        if (result > std::numeric_limits<int>::max()) return false;
    }

    ans = result;
    return true;
}

void Config::parseArguments(const std::vector<std::string> & args){
    if(args.size() < MIN_SIZE_ARGS || args.size() > MAX_SIZE_ARGS){
        helper();
    }

    size_t args_size = args.size();
    if(auto found = std::find(args.begin(), args.end(), "-t"); found != args.end()){
        int idx = found - args.begin() + 1;
        if(idx >= args.size()){
            helper("should specify input folder");
        }
        if(!std::filesystem::is_directory(args[idx])){
            std::string message = args[idx] + " is not a directory";
            helper(message);
        }
        m_input_folder = args[idx];
        args_size -= 2;

    }else{
        helper();
    }

    if(auto found = std::find(args.begin(), args.end(), "-o"); found != args.end()){
        int idx = found - args.begin() + 1;
        if(idx >= args.size()){
            helper("should specify output file");
        }
        std::filesystem::path file_path  = std::filesystem::path(args[idx]).parent_path();  // Removes the filename
        if(!std::filesystem::is_directory(file_path)){
            std::string message = "could not find path for output file";
            helper(message);
        }
        m_output_file = args[idx];
        args_size -= 2;

    }else{
        helper();
    }

    if(auto found = std::find(args.begin(), args.end(), "-i"); found != args.end()){
        m_ignore_system_includes = true;
        args_size -= 1;
    }

    if(auto found = std::find(args.begin(), args.end(), "-m"); found != args.end()){
        int idx = found - args.begin() + 1;
        if(idx >= args.size()){
            helper("should specify max lines number");
        }
        
        if(!isSafeInteger(args[idx], m_max_line)){
            helper("input number is out of range or not a number");
        }
        args_size -= 2;
    }

    if(args_size > 0){
        helper("unknown arguments");
    }

}

std::unordered_map<int, std::vector<int>> Config::buildDependencies(){
    std::unordered_map<int, std::vector<int>> deps;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(m_input_folder)) {
        if (std::filesystem::is_regular_file(entry.path())) {
            auto file_extension = entry.path().extension();
            //not a c or c++ file then continue
            if(file_extension != ".hpp" && file_extension != ".h" && 
                file_extension != ".c" && file_extension != ".cpp" && 
                file_extension != ".cxx" && file_extension != ".cc"){
                    continue;
            }
            auto file_path = entry.path().string();
            int file_id = getFileId(file_path, false);
            auto included_files = getAllIncludedFiles(file_path);
            if(!included_files.empty()){
                deps[file_id] = included_files;
            }
            m_list_local_files.insert(file_id);
        }
    }

    return deps;
}

void Config::helper(std::string_view message){
    std::cout << "header_hunter -t [input folder] -o [output file]\n";
    std::cout << "options: \n";
    std::cout << "  -i: ignore include filesystem\n";
    std::cout << "  -m [max number of lines]\n";
    if(!message.empty()){
        std::cout << "\n";
        std::cout << "Error: " << message << "\n";
    }
    exit(1);
}

std::vector<int> Config::getAllIncludedFiles(const std::string &file_path){
    std::vector<int> files_id;

    std::string line;
    std::ifstream input_file(file_path);
    if(!input_file.is_open()){
        std::string message = "can not open file: " + file_path;
        helper(message);
    }

    int line_counter = 0;

    std::regex local_include(R"(#include\s*"([^"]+))");
    std::regex system_include(R"(#include\s*<([^>]+)>)");
    while(std::getline(input_file, line)){

        std::smatch match;
        if(m_ignore_system_includes){
            if (std::regex_search(line, match, local_include)) {
                int file_id = getFileId(match[1], false);
                m_list_local_files.insert(file_id);
                files_id.push_back(file_id);
            }
        }else{
            if(std::regex_search(line, match, local_include)){
                int file_id = getFileId(match[1], false);
                m_list_local_files.insert(file_id);
                files_id.push_back(file_id);
            }

            if(std::regex_search(line, match, system_include)){
                int file_id = getFileId(match[1], true);
                m_list_system_files.insert(file_id);
                files_id.push_back(file_id);
            }
        }

        line_counter++;
        if(line_counter >= m_max_line && m_max_line != 0){
            break;
        }
    }


    return files_id;
}

int Config::getFileId(const std::string &file_name, bool is_system_file){

    std::string file_path = std::filesystem::path(file_name).filename();

    int file_id = -1;
    if(m_list_files_name.find(file_path) == m_list_files_name.end()){
        file_id = m_file_id_counter;
        m_list_files_name[file_path] = file_id;
        m_list_files_index[file_id] = file_path;
        m_file_id_counter++;
    }else{
        file_id = m_list_files_name[file_path];
    }

    return file_id;
}

void Config::generateReport(){

    auto adj_list = buildDependencies();

    DirectedGraph directed_graph (adj_list); 

    std::filesystem::path file_path(m_output_file);
    if(file_path.extension() == ".dot"){// output file graphiz tool
        IReport<GraphizReport> graph_report(m_output_file, directed_graph, m_list_files_index);
        graph_report.writeToFile();
    }else{ //normal output text file
        IReport<TextReport> standard_report(m_output_file, directed_graph, m_list_files_index);
        standard_report.writeToFile();
    }


    
}
