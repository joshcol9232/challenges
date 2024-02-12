
fn random_board<const N: usize>() -> [[char; N]; N] {
    use rand::seq::SliceRandom;

    const PLAYERS: [char; 2] = ['X', 'O'];

    let mut board = [['#'; N]; N];
    let mut rg = rand::thread_rng();

    for row in 0..N {
        for col in 0..N {
            board[row][col] = *PLAYERS.choose(&mut rg).unwrap();
        }
    }
    board
}

pub fn bench<const N: usize>(algo: &dyn Fn(&[[char; N]; N]) -> String, num: usize) {
    use std::time::Instant;

    // Create boards.
    let boards : Vec<[[char; N]; N]> = vec![random_board(); num];

    let now = Instant::now();
    for board in boards.iter() {
        algo(board);
    }
    let time_per_op = now.elapsed() / num as u32;

    println!("{} ns/op", time_per_op.as_nanos());
}

