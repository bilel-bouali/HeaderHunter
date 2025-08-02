#ifndef HEADER_HUNTER_INC_GRAPHIZ_REPORT__H
#define HEADER_HUNTER_INC_GRAPHIZ_REPORT__H

#include "report.h"

namespace HeaderHunter{

class GraphizReport: public IReport<GraphizReport>{

public:

    GraphizReport(const std::string &output_file,
                const DirectedGraph &directed_graph,
                const std::unordered_map<int, std::string>& files_indexes) :
                IReport<GraphizReport>(output_file, directed_graph, files_indexes){

    }

    ~GraphizReport() = default;

    void writeToFile();
};



}; 

#endif // HEADER_HUNTER_INC_GRAPHIZ_REPORT__H