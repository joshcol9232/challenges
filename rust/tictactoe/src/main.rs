mod benchmark;

fn tic_tac_toe<const N: usize>(board: &[[char; N]; N]) -> String {
    let mut row_scores = [0usize; N];
    let mut column_scores = [0usize; N];
    let mut diag_scores = [0usize; 2];

    // == Calculate scores
    // Idea here is that if a player has won, then they
    // have three in a row on any given column, row or diagonal.
    // Compute these as "scores" and check them at the end.

    // Calc scores.
    for r in 0..N {
        for c in 0..N {
            row_scores[r] += board[r][c] as usize;
            column_scores[c] += board[r][c] as usize;
        }
        // Diagonal scores
        diag_scores[0] += board[r][r] as usize;
        diag_scores[1] += board[r][N - 1 - r] as usize;
    }
    // Check scores!
    for idx in 0..N {
        for (player_idx, player) in ['X', 'O'].into_iter().enumerate() {
            let player_usize = player as usize;
            if row_scores[idx] == N * player_usize || column_scores[idx] == N * player_usize {
                return format!("Player {} wins", player_idx + 1);
            }
        }
    }
    for diag_score in diag_scores {
        for (player_idx, player) in ['X', 'O'].into_iter().enumerate() {
            if diag_score == (N * player as usize) {
                return format!("Player {} wins", player_idx + 1);
            }
        }
    }

    "It's a Tie".to_string()
}


fn main() {
    #[rustfmt::skip]
    let board1 = [['X', 'O', 'O'],
                  ['O', 'X', 'O'],
                  ['O', '#', 'X']];

    println!("Result: {}", tic_tac_toe(&board1));

    benchmark::bench(&tic_tac_toe::<3>, 1e7 as usize);
}
