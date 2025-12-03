#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int day1_1() {
  std::string newLine;
  std::ifstream FileToRead("inputs/input1.txt");

  int count = 0;
  int curPos = 50;

  while (std::getline(FileToRead, newLine)) {
    int rot = std::stoi(newLine.substr(1));
    bool dir;
    if (newLine.substr(0,1) == "L") {
      curPos = (curPos - rot + 100) % 100;
    } else {
      curPos = (curPos + rot + 100) % 100;
    }

    if(curPos == 0) {
      count ++;
    }
  }

  return count;
}

int day1_2() {
  std::string newLine;
  std::ifstream FileToRead("inputs/input1.txt");

  int count = 0;
  int curPos = 50;
  int prevPos = 50;

  while (std::getline(FileToRead, newLine)) {
    int rot = std::stoi(newLine.substr(1));
    bool dir;

    if (newLine.substr(0,1) == "L") {
      curPos -= rot;
    } else {
      curPos += rot;
    }
    
    if(
      prevPos < 0 && curPos > 0 ||
      prevPos > 0 && curPos < 0 ||
      curPos == 0
     ) {count++;}

    while(curPos <= -100) {
      curPos += 100;
      count++;
    }

    while(curPos >= 100) {
      curPos -= 100;
      count++;
    }

    curPos = curPos % 100;
    prevPos = curPos;
  }

  return count;
}

int main() {
  std::cout << day1_1();
  std::cout << "\n";
  std::cout << day1_2();
}
