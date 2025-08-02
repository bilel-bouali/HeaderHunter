# HeaderHunter
HeaderHunter is a C++ analysis tool designed to audit and improve the structure of C++ codebases by inspecting header file usage. It performs a comprehensive scan of a project’s source files to detect:
cycle in c++ project.
get all files which are not included.
get all files without any include.
the report can be generated as text file or as .dot file (graphiz file )

## 🚀 Getting Started

### Prerequisites

- C++20 or newer
- CMake 3.22+
- A C++ compiler (GCC, Clang, MSVC)

### Build Instructions

```bash
cd HeaderHunter
mkdir build && cd build
cmake ..
make
```

### How to run it
./header_hunter -t [input folder] -o [output file]
options:
  -i: ignore include filesystem
  -m [max number of lines to parse]

