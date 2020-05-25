#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <map>


void exc_11_12(){
    std::cout << "Exercise 11.12" << std::endl;
    std::vector<int> int_v{1, 2, 3, 4, 5, 6};
    std::vector<std::pair<int, std::string>> pairs;
    for (int item : int_v){
        std::string s = "string: "+std::to_string(item);
        pairs.push_back(std::make_pair(item, s));
    }
    for (auto item : pairs){
        std::cout << item.first << " " << item.second << std::endl;
    }
}

void exc_11_31(){
    std::cout << "Exercise 11.27" << std::endl;
	std::multimap<std::string, std::string> authors{
		{ "alan", "DMA" },
		{ "pezy", "LeetCode" },
		{ "alan", "CLRS" },
		{ "wang", "FTP" },
		{ "pezy", "CP5" },
		{ "wang", "CPP-Concurrency" } };

    std::string key = "alan";
    std::string value = "CLRS";

    std::size_t counts = authors.count(key);
    std::multimap<std::string, std::string>::iterator iter = authors.find(key);
    
    while (counts){
        if (iter->second == value){
            authors.erase(key);
            break;
        }
        ++iter;
        --counts;
    }

    for (auto beg = authors.begin(), end = authors.end(); beg != end; ++beg){
        std::cout << beg->first << " " << beg->second << std::endl;
    }
}

std::map<std::string, std::string> buildMap(std::ifstream &rule_file){
    std::map<std::string, std::string> map;
    std::string key, values;

    while (rule_file >> key && std::getline(rule_file, values)){
        if (values.size() > 1)
            map.insert({key, values.substr(1)});
        else
            throw std::runtime_error("No rule for " + key);
    }

    return map;
}

std::string transform(const std::string& s, std::map<std::string, std::string> rules){
    std::map<std::string, std::string>::const_iterator iter = rules.find(s);
    if (iter != rules.cend())
        return iter->second;
    else
        return s;
}

void word_transform(std::ifstream& rule_file, std::ifstream& data){
    std::map<std::string, std::string> rules = buildMap(rule_file);
    std::string words;

    while (std::getline(data, words))
    {
        std::istringstream stream(words);
        std::string word;
        bool first_word = true;
        while (stream >> word){
            if (first_word) first_word = false;
            else{
                std::cout << " ";
            }
            std::cout << transform(word, rules);
        }
        std::cout << std::endl;
    }
}

void exc_11_33(){
    std::ifstream rules("./rule.txt");
    std::ifstream data("./data.txt");
    word_transform(rules, data);
}

int main(int argc, char const *argv[])
{
    exc_11_12();
    exc_11_31();
    exc_11_33();
    return 0;
}
