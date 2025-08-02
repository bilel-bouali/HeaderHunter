#include<iostream>
#include "../inc/config.h"

using namespace HeaderHunter; 
int main(int argc, char* argv[]){
    std::vector<std::string> args(argv + 1, argv + argc);
    
    Config config(args);
    config.generateReport();
}