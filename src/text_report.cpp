#include "../inc/text_report.h"

using namespace HeaderHunter;

void TextReport::writeToFile(){
    m_outfile << "--------NOT INCLUDED FILES--------\n";
    auto files_not_included = m_directed_graph.getNodesWithoutIncomingEdges();
    for(auto file_id : files_not_included){
        m_outfile << m_files_indexes[file_id] << "\n";
    }
    m_outfile << "\n";

    m_outfile << "--------FILES WITHOUT ANY INCLUDE--------\n";
    auto files_without_include = m_directed_graph.getNodesWithoutOutcomingEdges();
    for(auto file_id : files_without_include){
        m_outfile << m_files_indexes[file_id] << "\n";
    }
    m_outfile << "\n";

    m_outfile << "--------DETECTED CYCLES--------\n";
    auto cycles = m_directed_graph.detectCycles();
    for(size_t i = 0; i < cycles.size(); ++i){
        for(size_t c = 0; c < cycles[i].size(); ++c){
            if(i != cycles[i].size() - 1){
                m_outfile << m_files_indexes[cycles[i][c]] << "-->";
            }else{
                m_outfile << m_files_indexes[cycles[i][c]] << "\n";
            }
        }
        m_outfile << "\n";
    }
    
    m_outfile << "\n";
}