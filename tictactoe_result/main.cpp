#include <array>
#include <cassert>
#include <iostream>
#include <string>

enum State : char {
  ePlayer1,
  ePlayer2,
  eEmpty,
  eNumStates
};

constexpr size_t kBoardSize = 3;

namespace firstAttempt {

void convert_to_state(const std::array<std::array<char, kBoardSize>, kBoardSize>& in,
                      std::array<std::array<State, kBoardSize>, kBoardSize>& out)
{
  for (size_t r = 0; r < kBoardSize; ++r) {
    for (size_t c = 0; c < kBoardSize; ++c) {
      switch (in[r][c]) {
        case 'X':
          out[r][c] = ePlayer1;
          break;
        case 'O':
          out[r][c] = ePlayer2;
          break;
        case '#':
          out[r][c] = eEmpty;
      }
    }
  }
}

// First "add then use if" implementation
std::string ticTacToe(const std::array<std::array<char, kBoardSize>, kBoardSize> board) {
  // Convert board from string to "State"
  std::array<std::array<State, kBoardSize>, kBoardSize> states;
  convert_to_state(board, states);

  constexpr std::array<size_t, eNumStates> startScores {0, 0, 0};

  std::array<std::array<size_t, eNumStates>, kBoardSize> rowScores;
  rowScores.fill(startScores);
  std::array<std::array<size_t, eNumStates>, kBoardSize> columnScores;
  columnScores.fill(startScores);
  std::array<std::array<size_t, eNumStates>, 2> diagScores;
  diagScores.fill(startScores);

  // Calculate scores
  for (size_t r = 0; r < kBoardSize; ++r) {
    for (size_t c = 0; c < kBoardSize; ++c) {
      const auto& state = states[r][c];
      rowScores[r][state]++;
      columnScores[c][state]++;
    }
  }
  // Diagonal scores
  for (size_t d = 0; d < kBoardSize; ++d) {
    diagScores[0][states[d][d]]++;
    diagScores[1][states[d][kBoardSize - 1 - d]]++;
  }

  // Check scores!
  for (size_t s = 0; s < kBoardSize; ++s) {
    for (size_t player = 0; player < 2; ++player) {
      if (rowScores[s][player] == kBoardSize ||
          columnScores[s][player] == kBoardSize) {
        return "Player " + std::to_string(player + 1) + " wins";
      }
    }
  }
  for (size_t d = 0; d < 2; ++d) {
    for (size_t player = 0; player < 2; ++player) {
      if (diagScores[d][player] == kBoardSize) {
        return "Player " + std::to_string(player + 1) + " wins";
      }
    }
  }

  return "It's a Tie";
}

}  // namespace firstAttempt

int main(int argc, char* argv[]) {
  std::array<std::array<char, kBoardSize>, kBoardSize> board = {{
    {'X', 'O', 'O'},
    {'O', 'X', 'O'},
    {'O', '#', 'X'}
  }};
  auto answer = firstAttempt::ticTacToe(board);
  std::cout << answer << std::endl;

  board = {{
    {'X', 'O', 'O'},
    {'O', 'X', 'O'},
    {'X', '#', 'O'}
  }};
  answer = firstAttempt::ticTacToe(board);
  std::cout << answer << std::endl;

  board = {{
    {'X', 'X', 'O'},
    {'O', 'X', 'O'},
    {'X', 'O', '#'}
  }};
  answer = firstAttempt::ticTacToe(board);
  std::cout << answer << std::endl;

  return 0;
}
