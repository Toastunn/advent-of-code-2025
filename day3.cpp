#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int day3_1() {
  std::string bank;
  std::ifstream FileToRead("inputs/input3.txt");

  int count = 0;
  int jolt;
  std::string buf = "";

  while (std::getline(FileToRead, bank)) {
    int biggest_jolt = 0;
    for (size_t i = 0; i < bank.length(); i++){
        char battery1 = bank.at(i);
        std::string db1 = bank.substr(i);
        for (size_t j = i + 1; j < bank.length() - i; j++){
            char battery2 = bank.at(j);
            std::string db2 = bank.substr(j); 
            jolt = std::stoi(buf.append(1, battery1).append(1, battery2));

            if(jolt > biggest_jolt) {
                biggest_jolt = jolt;
            }

            buf.clear();
        }
    }

    count += biggest_jolt;
    
  }

  return count;
}

long long day3_2() {
  std::string bank;
  std::ifstream FileToRead("inputs/input3.txt");

  long long count = 0;
  size_t start;
  std::string jolt;
  std::string biggest_jolt = "000000000000";

  while (std::getline(FileToRead, bank)) {
    for (size_t i = 12; i <= bank.length(); i++){
        for (size_t size = 1; size <= 12; size++){
            start = i - size;
            std::string blockBank = bank.substr(start, size);
            std::string block12 = biggest_jolt.substr(12-size, size);
            if(std::stoll(blockBank) > std::stoll(block12)) {
                biggest_jolt.replace(12-size, size, blockBank);
            }
        }
    }

    count += std::stoll(biggest_jolt);
    
    biggest_jolt = "000000000000";
  }

  return count;
}

int main() {
  std::cout << "\n";
  std::cout << day3_1();
  std::cout << "\n";
  std::cout << day3_2();
}
