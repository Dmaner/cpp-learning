#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>

class TeXtQuery
{
public:
    TeXtQuery(std::ifstream &ifs)
    {
        std::string line;
        int index_of_line = 0;
        while (std::getline(ifs, line))
        {
            text.push_back(line);
            std::istringstream words(line);
            std::string word;
            std::set<int> temp;
            while (words >> word)
            {
                if (map.find(word) != map.end())
                    temp = map[word];
                else
                    temp = std::set<int>();
                temp.insert(index_of_line);
                map[word] = temp;
            }
            ++index_of_line;
        }
    }
    std::string query(std::string word)
    {
        if (map.find(word) == map.end())
        {
            return "No such key word";
        }
        else
        {
            std::set<int> temp = map.at(word);
            std::string s = "";
            for(std::set<int>::iterator iter = temp.begin(); iter != temp.end(); ++iter){
                
                s += "(Line: " + std::to_string(*iter) + ") " + text[(*iter)] + "\n";
            }
            return s;
        }
    }

private:
    std::vector<std::string> text;
    std::unordered_map<std::string, std::set<int>> map;
};

#endif