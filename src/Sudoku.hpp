#include <array>
#include <cstdio>
#include <string>
#include <iostream>
#include <tuple>
#include <initializer_list>

class Sudoku{
  public:
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& puzzle);
  public:

    enum Status{
      Success,
      OutOfBounds,
      InvalidValue
    };


    Sudoku() = default;
    Sudoku(std::initializer_list<std::tuple<int,int,int>> list);

    const int& get(int i, int j) const;
    int set(int i, int j, int value);

    Sudoku(const Sudoku& other) = delete;
    Sudoku& operator=(const Sudoku&) = delete;

    Sudoku(Sudoku&&) noexcept = default;
    Sudoku& operator=(Sudoku&&) noexcept = default;

    int sum_row(int i) const;
    int sum_col(int j) const;
    int sum_block(int i, int j) const;


    int& operator() (int i, int j);
    const int& operator() (int i, int j) const;

  private:

  std::array<int,9*9> values = {0};
};

std::ostream& operator<<(std::ostream& os, const Sudoku& puzzle);

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

inline Sudoku::Sudoku(std::initializer_list<std::tuple<int,int,int>> list){


  for (auto& triplet : list){

    int i = std::get<0>(triplet);
    int j = std::get<1>(triplet);
    int v = std::get<2>(triplet);

    set(i,j,v);
  }

}


inline int& Sudoku::operator() (int i, int j){
  return values[j + 9 * i];
}

inline const int& Sudoku::operator() (int i, int j) const{
  return values[j + 9 * i];
}

inline int Sudoku::set(int i, int j, int value){


  if ( i < 0 || i > 9) return Status::OutOfBounds;
  if ( j < 0 || j > 9) return Status::OutOfBounds;
  if ( value < 1 || value > 9) return Status::InvalidValue;


  values[j + 9 * i] = value;
  return Status::Success;
}

inline const int& Sudoku::get(int i, int j) const {
  return values[j + 9 * i];
}

inline int Sudoku::sum_row(int i) const{
  
  int sum = 0;
  for(int j = 0; j < 9; ++j){
    sum += get(i,j);
  }

  return sum;
}

inline int Sudoku::sum_col(int j) const{

  int sum = 0;
  for(int i = 0; i < 9; ++j){
    sum += get(i,j);
  }

  return sum;

}

inline int Sudoku::sum_block(int i, int j) const{

  int sum = 0;

  int ii = i*3;
  int jj = j*3; 
  
  sum += get(ii  ,jj) + get(ii  ,jj+1), get(ii  ,jj+2);
  sum += get(ii+1,jj) + get(ii+1,jj+1), get(ii+1,jj+2);
  sum += get(ii+2,jj) + get(ii+2,jj+1), get(ii+2,jj+2);

  return sum;
}


inline std::ostream& operator<<(std::ostream& os, const Sudoku& puzzle){


  auto row = [](const Sudoku& puzzle, int i) -> std::string{

    std::string out = "";

    for (int j = 0; j < 9; ++j){
      const int& value = puzzle.get(i,j);
      if ( j % 3 == 0 ) out += "|";
      out += (value == 0) ? " " : std::to_string(value);
      out += " ";
    }


    out += "|\n";
    return out;
  };


  os << "+------+------+------+\n";
  os << row(puzzle, 0);
  os << row(puzzle, 1);
  os << row(puzzle, 2);
  os << "+------+------+------+\n";
  os << row(puzzle, 3);
  os << row(puzzle, 4);
  os << row(puzzle, 5);
  os << "+------+------+------+\n";
  os << row(puzzle, 6);
  os << row(puzzle, 7);
  os << row(puzzle, 8);
  os << "+------+------+------+\n";

  return os;
}





