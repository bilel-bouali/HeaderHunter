#ifndef HEADER_HUNTER_INC_TEXT_REPORT__H
#define HEADER_HUNTER_INC_TEXT_REPORT__H

#include "report.h"

namespace HeaderHunter{

class TextReport: public IReport<TextReport>{

public:

    TextReport(const std::string &output_file,
                const DirectedGraph &directed_graph,
                const std::unordered_map<int, std::string>& files_indexes) :
                IReport<TextReport>(output_file, directed_graph, files_indexes){

    }

    ~TextReport() = default;

    void writeToFile();
};



}; 

#endif // HEADER_HUNTER_INC_TEXT_REPORT__H