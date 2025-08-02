#ifndef HEADER_HUNTER_INC_REPORT__H
#define HEADER_HUNTER_INC_REPORT__H

#include <string>
#include <fstream>
#include "graph.h"

namespace HeaderHunter{

//use crtp
template <typename DERIVED>
class IReport{

public:

    IReport(const std::string &output_file,
            const DirectedGraph &directed_graph,
            const std::unordered_map<int, std::string>& files_indexes) 
            : m_outfile(output_file),
             m_directed_graph(directed_graph),
             m_files_indexes(files_indexes){
        if(!m_outfile){
            throw std::runtime_error("error opening file for writing");
        }
    }

    virtual ~IReport(){
        m_outfile.close();
    }

    void writeToFile(){

        static_cast<DERIVED*>(this)->writeToFile();
    }

protected:

    std::ofstream m_outfile;
    DirectedGraph m_directed_graph;
    std::unordered_map<int, std::string> m_files_indexes;

};



}; 

#endif // HEADER_HUNTER_INC_REPORT__H