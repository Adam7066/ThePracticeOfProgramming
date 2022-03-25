#ifndef TOOL_H
#define TOOL_H
#include <vector>
#include <string>

class tool {
  public:
    static std::vector<std::string> splitStr(std::string &, std::string);
    static const int d[8][2];
};

#endif