#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


template <typename T>
std::vector<std::vector<T>> transposeMatrix(std::vector<std::vector<T>>& matrix) {
  int rows = matrix.size();
  int cols = 0;

  for (std::vector<T> row : matrix) {
    if(row.size() > cols) {
      cols = row.size();
    }
  }
  
  std::vector<std::vector<T>> transpose(cols, std::vector<T>(rows));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      transpose[j][i] = matrix[i][j];
    }
  }

  return transpose;
}

template <typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix) {
  for (std::vector<T> row : matrix) {
    for (T val : row) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}

long long day6_1() {
  long long count = 0;
  
  std::string inputBuf;
  std::ifstream FileToRead("inputs/input6.txt");

  std::vector<std::vector<std::string>> inputMatrix;
  std::vector<std::vector<std::string>> problems;

  while (std::getline(FileToRead, inputBuf)) {
    std::stringstream rowStream(inputBuf);
    std::vector<std::string> rowVec;
    std::string unit;
    while (std::getline(rowStream, unit, ' ')) {
      if (unit == "") continue;

      rowVec.push_back(unit);

    }

    inputMatrix.push_back(rowVec);

    rowVec.clear();
    unit.clear();
    rowStream.clear();
  }

  problems = transposeMatrix(inputMatrix);

  int num;
  long long calc;
  for (std::vector<std::string> problem : problems) {
    if (problem[problem.size()-1] == "*") {
      calc = 1;
      for (std::string numString : problem) {
        try {num = std::stoi(numString);}
         catch (const std::invalid_argument& e) {
          num = 1;
        }
        
        calc *= num;

      }
    } else
    if (problem[problem.size()-1] == "+") {
      calc = 0;
      for (std::string numString : problem) {
        try {num = std::stoi(numString);}
         catch (const std::invalid_argument& e) {
          num = 0;
        }
        
        calc += num;

      }
    }

    count += calc;
  }

  return count;
}

long long day6_2() {
  long long count = 0;
  
  std::string inputBuf;
  std::ifstream FileToRead("inputs/input6.txt");

  std::vector<std::vector<char>> inputMatrix;

  while (std::getline(FileToRead, inputBuf)) {
    std::vector<char> rowVec;
    const char* charInput = inputBuf.c_str();
    char unit;
    for (size_t i = 0; i < inputBuf.size(); i++) {
      unit = charInput[i];
      rowVec.push_back(unit);
    }

    inputMatrix.push_back(rowVec);

    rowVec.clear();
  }

  std::vector<std::vector<char>> posedInput = transposeMatrix(inputMatrix);
  
  //printMatrix(posedInput);

  //find the lines
  std::vector<std::vector<std::vector<char>>> problems;
  std::vector<std::vector<char>> problemBuf;
  for (std::vector<char> row : posedInput) {
    bool onlyWhitespace = true;
    for (char unit : row) {
      if(!isspace(unit)) {
        onlyWhitespace = false;
        break;
      }
    }
    
    if(!onlyWhitespace) {
      problemBuf.push_back(row);
    } else {
      problems.push_back(problemBuf);
      problemBuf.clear();
    }
  }
  
  problems.push_back(problemBuf);


  long long calc;
  std::vector<int> concatProblem;
  for (std::vector<std::vector<char>> problem : problems) {
    char operand = problem[0][problem[0].size()-1];

    calc = (operand == '*') ? 1 : 0;
    //convert chars to int
    for (int i = 0; i < problem.size(); ++i) {
      std::string num = "";
      for (int j = 0; j < problem[0].size(); ++j) {
        char digit = problem[i][j];
        if(isalnum(digit)) {
          num.push_back(digit);
        }
      }
      concatProblem.push_back(stoi(num));
    }

    for (int num : concatProblem) {
      calc = operand == '*' ? calc * num : calc + num;
    }

    count += calc;

    concatProblem.clear();
  }

  return count;
}

int main() {
  std::cout << "\n";
  std::cout << day6_1();
  std::cout << "\n\n\n\n";
  std::cout << day6_2();
  std::cout << "\n";

  return 0;
}