#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int day4_1() {
  std::ifstream FileToRead("inputs/input4.txt");

  int count = 0; 
  char cell;
  std::string rollMap[150];

  int lineCount = 0;
  while (std::getline(FileToRead, rollMap[lineCount])) {
    lineCount++;
  }

  int width = rollMap[0].length();
  int height = lineCount;
  int dRow;
  int dCol;
  int adj;
  std::string buf[150];

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      cell = rollMap[row][col];
      buf[row].push_back(cell);
      if(cell == '@') {
        //check adjacencies;
        adj = 0;
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            dRow = row+i;
            dCol = col+j;
            if(dRow < 0 || dRow >= width || dCol < 0 || dCol >= height) {continue;}
            if(dCol != col || dRow != row) {
              if(rollMap[dRow].at(dCol) == '@') {
                adj++;
              }
            }
          }
        }

        if(adj < 4) {
          count++;
          buf[row].at(col) = 'x';
        }
      }
    }

    std::cout << buf[row] << std::endl;
  }

  return count;
}


long long day4_2() {

  int count = 0; 
  std::string rollMap[150];
  std::ifstream FileToRead("inputs/input4.txt");

  int lineCount = 0;
  while (std::getline(FileToRead, rollMap[lineCount])) {
    lineCount++;
  }

  char cell;
  int subCount = -1;
  int width = rollMap[0].length();
  int height = lineCount;
  std::string buf[150];

  auto checkSurroundingCells = [&rollMap, &width, &height, &buf, &count, &subCount](int row, int col) {
    int adj = 0;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        int dRow = row+i;
        int dCol = col+j;
        if(dRow < 0 || dRow >= width || dCol < 0 || dCol >= height) {continue;}
        if(dCol != col || dRow != row) {
          if(rollMap[dRow].at(dCol) == '@') {
            adj++;
          }
        }
      }
    }

    if(adj < 4) {
      count++;
      subCount++;
      buf[row].at(col) = '.';
    }
  };
  
  //iterative loop
  while (subCount != 0) {
    subCount = 0;

    //main loop
    for (int row = 0; row < height; row++) {
      for (int col = 0; col < width; col++) {
        cell = rollMap[row][col];
        buf[row].push_back(cell);
        if(cell == '@') {
          checkSurroundingCells(row, col);
        }
      }

      std::cout << buf[row] << std::endl;
    }
    
    std::cout << "\n\n\n\n";

    for (int row = 0; row < height; row++){
      rollMap[row] = buf[row];
      buf[row].clear();
    }
    
  }
  return count;
}

int main() {
  std::cout << "\n";
  std::cout << day4_1();
  std::cout << "\n\n\n\n";
  std::cout << day4_2();

  return 1;
}
