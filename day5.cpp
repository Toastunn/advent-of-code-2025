#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cmath>
#include <map>

bool isFresh(std::vector<std::pair<long long, long long>> map, long long input);

size_t indexOfSmallest(std::deque<std::pair<long long, long long>> map, size_t start);

int day5_1() {
  std::string inputBuf;
  std::ifstream FileToRead("inputs/input5.txt");

  int count = 0;

  bool inputSwitch = false;
  std::vector<std::pair<long long, long long>> freshRanges;

  int line = 0;
  while (std::getline(FileToRead, inputBuf)) {
    if (inputBuf == "") {
      inputSwitch = true;
      continue;
    }

    if (inputSwitch == false) { // get the ranges
      int split = inputBuf.find('-') + 1;
      long long lower = stoll(inputBuf.substr(0, split));
      long long upper = stoll(inputBuf.substr(split));
      
      freshRanges.push_back({ lower, upper });
    }
    
    if (inputSwitch == true) {
      if ( isFresh(freshRanges, stoll(inputBuf)) ) {
        count++;
      }
    }

    line++;
  }

  return count;
}

long long day5_2_v1() {
  std::string range;
  std::ifstream FileToRead("inputs/input5.txt");

  long long count = 0;

  std::vector<std::pair<long long, long long>> freshRanges;

  int line = 0;
  while (std::getline(FileToRead, range)) {
    bool foundChain = false;

    if (range == "") {
      break;
    }

    int split = range.find('-') + 1;
    long long lower = stoll(range.substr(0, split));
    long long upper = stoll(range.substr(split));

    
    //check upper and lower bounds in relation to new bounds and adjust appropriately

    for (auto &&freshBounds : freshRanges) {
      //if the lower fresh bound is surrounded by new bounds
      if (lower <= freshBounds.first && freshBounds.first <= upper) {
        freshBounds = { lower, freshBounds.second };
        foundChain = true;
        break;
      } else
      //if the upper fresh bound is surrounded by new bounds
      if (lower <= freshBounds.second && freshBounds.second <= upper) {
        freshBounds = { freshBounds.first, upper };
        foundChain = true;
        break;
      } else 
      //if the fresh bounds are surrounded by new bounds
      if (lower < freshBounds.first && freshBounds.second < upper) {
        freshBounds = { lower, upper };
        foundChain = true;
        break;
      } else 
      //if the fresh bounds surround the new bounds (or equal to the original one)
      if ( freshBounds.first <= lower && upper <= freshBounds.second ) {
        //do nothing* lol
        foundChain = true;
        break;

      }
    }

    if (!foundChain) {
      freshRanges.push_back({ lower, upper }); 
    }

    line++;
  }

  //actually count
  for (auto &&range : freshRanges) {
    count += range.second - range.first;
  }

  return count;
}

long long day5_2_v2() {
  std::string range;
  std::ifstream FileToRead("inputs/input5.txt");

  long long count = 0;

  std::deque<std::pair<long long, long long>> freshRanges;

  while (std::getline(FileToRead, range)) {
    bool foundChain = false;

    if (range == "") {
      break;
    }

    int split = range.find('-') + 1;
    long long lower = stoll(range.substr(0, split));
    long long upper = stoll(range.substr(split));
    freshRanges.push_back({ lower, upper }); 

  }

  //sort
  for (size_t i = 0; i < freshRanges.size()-1; i++) {
    int index = indexOfSmallest(freshRanges, i);
    auto range = freshRanges.at(index);
    freshRanges.erase(freshRanges.begin() + index);
    freshRanges.push_front(range);
  }
  
  //trim
  for (size_t i = 1; i < freshRanges.size()-1; i++) {
    std::pair<long long, long long> prevRange = freshRanges.at(i-1);
    std::pair<long long, long long> curRange = freshRanges.at(i);

    //extension
    if(prevRange.first <= curRange.second && curRange.second <= prevRange.second) {
      freshRanges.at(i-1) = { curRange.first, prevRange.second };
      freshRanges.erase(freshRanges.begin() + i);
      i--; //decrement to compensate for the removal
    } else

    //if surrounded
    if(prevRange.first <= curRange.second && prevRange.second <= curRange.second) {
      freshRanges.erase(freshRanges.begin() + i-1); //erase the previous interval
      i -= 2;
    }
  }

  //count
  for (auto &&range : freshRanges) {
    count += range.second - range.first + 1; //+1 because fence post problem
  }

  return count;
}

int main() {
  std::cout << "\n";
  std::cout << day5_1();
  std::cout << "\n";
  std::cout << day5_2_v2();
}

bool isFresh(std::vector<std::pair<long long, long long>> map, long long input) {
  for (auto &&range : map) {
    if (range.first <= input && input <= range.second) {
      return true;
    }
  }

  return false;
}

size_t indexOfSmallest(std::deque<std::pair<long long, long long>> map, size_t start) {
  long long smallestNumber = 100000000000000000;
  size_t index = -1;
  for (size_t i = start; i < map.size()-1; i++) {
    auto range = map[i];
    if (range.first < smallestNumber) {
      smallestNumber = range.first;
      index = i;
    }
  }
  
  return index;
}