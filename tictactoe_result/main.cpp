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

State convert_to_state(char in) {
  switch (in) {
    case 'X':
      return ePlayer1;
    case 'O':
      return ePlayer2;
    case '#':
      return eEmpty;
  }
}

template<int N>
void convert_to_state(const std::array<std::array<char, N>, N>& in,
                      std::array<std::array<State, N>, N>& out)
{
  for (size_t r = 0; r < N; ++r) {
    for (size_t c = 0; c < N; ++c) {
      out[r][c] = convert_to_state(in[r][c]);
    }
  }
}

namespace firstAttempt {

template<int N>
std::string ticTacToe(const std::array<std::array<char, N>, N> board) {
  // Convert board from string to "State"
  std::array<std::array<State, N>, N> states;
  convert_to_state<N>(board, states);

  constexpr std::array<size_t, eNumStates> startScores {0, 0, 0};

  std::array<std::array<size_t, eNumStates>, N> rowScores;
  rowScores.fill(startScores);
  std::array<std::array<size_t, eNumStates>, N> columnScores;
  columnScores.fill(startScores);
  std::array<std::array<size_t, eNumStates>, 2> diagScores;
  diagScores.fill(startScores);

  // == Calculate scores
  // Idea here is that if a player has won, then they
  // have three in a row on any given column, row or diagonal.
  // Compute these as "scores" and check them at the end.
  // Reduces looping I think, and less 'if' within nested loops

  // Row / column scores.
  for (size_t r = 0; r < N; ++r) {
    for (size_t c = 0; c < N; ++c) {
      const auto& state = states[r][c];
      rowScores[r][state]++;
      columnScores[c][state]++;
    }
  }
  // Diagonal scores
  for (size_t d = 0; d < N; ++d) {
    diagScores[0][states[d][d]]++;
    diagScores[1][states[d][N - 1 - d]]++;
  }

  // Check scores!
  for (size_t s = 0; s < N; ++s) {
    for (size_t player = 0; player < 2; ++player) {
      if (rowScores[s][player] == N ||
          columnScores[s][player] == N) {
        return "Player " + std::to_string(player + 1) + " wins";
      }
    }
  }
  for (size_t d = 0; d < 2; ++d) {
    for (size_t player = 0; player < 2; ++player) {
      if (diagScores[d][player] == N) {
        return "Player " + std::to_string(player + 1) + " wins";
      }
    }
  }

  return "It's a Tie";
}

}  // namespace firstAttempt


namespace secondAttempt {

template<int N>
std::string ticTacToe(const std::array<std::array<char, N>, N> board) {
  // Linear search until a state in a given direction no longer matches the
  // first element in that direction.

  // Check diagonals
  const auto topLeft = board[0][0];
  size_t s;
  for (s = 0; s < N; ++s) {
    if (board[s][s] != topLeft) break;
  }
  if (s == N) { // Winner!
    return "Player " + std::to_string(convert_to_state(topLeft) + 1) + " wins";
  }

  const auto topRight = board[0][N - 1];
  for (s = 0; s < N; ++s) {
    if (board[s][N - 1 - s] != topRight) break;
  }
  if (s == N) { // Winner!
    return "Player " + std::to_string(convert_to_state(topLeft) + 1) + " wins";
  }
  // Check rows
  for (size_t r = 0; r < N; ++r) {
    const auto firstInRow = board[r][0];
    size_t c;
    for (c = 0; c < N; ++c) {
      if (board[r][c] != firstInRow) {
        goto nextRow;  // weird but oh well
      }
    }
    if (c == N) {  // It will be! Quite strange code. Kept if statement so I can still tell what's going on.
      return "Player " + std::to_string(convert_to_state(firstInRow) + 1) + " wins"; 
    }
    nextRow:;
  }

  // Check columns
  for (size_t c = 0; c < N; ++c) {
    const auto firstInCol = board[0][c];
    size_t r;
    for (r = 0; r < N; ++r) {
      if (board[r][c] != firstInCol) {
        goto nextCol;
      }
    }
    if (r == N) {
      return "Player " + std::to_string(convert_to_state(firstInCol) + 1) + " wins"; 
    }
    nextCol:;
  }

  return "It's a tie.";
}


}  // namespace secondAttempt

int main(int argc, char* argv[]) {
  std::array<std::array<char, 3>, 3> board = {{
    {'X', 'O', 'O'},
    {'O', 'X', 'O'},
    {'O', '#', 'X'}
  }};
  auto answer = firstAttempt::ticTacToe<board.size()>(board);
  std::cout << answer << std::endl;

  board = {{
    {'X', 'O', 'O'},
    {'O', 'X', 'O'},
    {'X', '#', 'O'}
  }};
  answer = firstAttempt::ticTacToe<board.size()>(board);
  std::cout << answer << std::endl;

  board = {{
    {'X', 'X', 'O'},
    {'O', 'X', 'O'},
    {'X', 'O', '#'}
  }};
  answer = firstAttempt::ticTacToe<board.size()>(board);
  std::cout << answer << std::endl;

  // ======
  std::array<std::array<char, 5>, 5> largeBoard = {{
    {'X', 'O', 'O', 'O', 'O'},
    {'O', 'X', 'O', 'X', 'X'},
    {'O', '#', 'X', '#', 'X'},
    {'O', 'X', 'O', 'X', '#'},
    {'X', 'O', 'O', '#', 'X'}
  }};
  answer = firstAttempt::ticTacToe<largeBoard.size()>(largeBoard);
  std::cout << answer << std::endl;

  // ===================== Second attempt ====================
  std::cout << "===================== Second attempt ====================" << std::endl;
  board = {{
    {'X', 'O', 'O'},
    {'O', 'X', 'O'},
    {'O', '#', 'X'}
  }};
  answer = secondAttempt::ticTacToe<board.size()>(board);
  std::cout << answer << std::endl;

  board = {{
    {'X', 'O', 'O'},
    {'O', 'X', 'O'},
    {'X', '#', 'O'}
  }};
  answer = secondAttempt::ticTacToe<board.size()>(board);
  std::cout << answer << std::endl;

  board = {{
    {'X', 'X', 'O'},
    {'O', 'X', 'O'},
    {'X', 'O', '#'}
  }};
  answer = secondAttempt::ticTacToe<board.size()>(board);
  std::cout << answer << std::endl;

  // ======
  largeBoard = {{
    {'X', 'O', 'O', 'O', 'O'},
    {'O', 'X', 'O', 'X', 'X'},
    {'O', '#', 'X', '#', 'X'},
    {'O', 'X', 'O', 'X', '#'},
    {'X', 'O', 'O', '#', 'X'}
  }};
  answer = secondAttempt::ticTacToe<largeBoard.size()>(largeBoard);
  std::cout << answer << std::endl;

  return 0;
}
