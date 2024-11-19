#include <iostream>

#include "Sudoku.hpp"




int main (int argc, char *argv[]) {
  
  Sudoku puzzle({
                {0,1, 3},
                {0,2, 2},

                {0,4, 5},

                {0,6, 1},

                {1,1, 4},

                {1,3, 6},
                {1,5, 2},

                {1,8, 7},
  });


  std::cout << puzzle << std::endl;
  return 0;
}
