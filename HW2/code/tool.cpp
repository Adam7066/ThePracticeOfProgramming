#include "tool.h"

std::vector<std::string> tool::splitStr(std::string &str, std::string del) {
    std::vector<std::string> res;
    int start = 0, end = str.find(del);
    while(end != -1) {
        res.push_back(str.substr(start, end - start));
        start = end + del.size();
        end = str.find(del, start);
    }
    res.push_back(str.substr(start, end - start));
    return res;
}