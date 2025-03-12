use rand::Rng;
use std::time::Instant;

const DAYS_TO_BEAT_STREAK: i32 = 57;
const GAMES_IN_SEASON: i32 = 162;
const MULTI_GAME: f64 = 1.25;
const NL_BATTING_CHAMP: f64 = 0.314;
const AL_BATTING_CHAMP: f64 = 0.332;
const PLATE_APPEARANCES_PER_GAME: f64 = 3.5;
const AT_BATS: f64 = PLATE_APPEARANCES_PER_GAME * GAMES_IN_SEASON as f64;
const STREAK_MULTIPLIER: f64 = 2.0;
const MAX_TRIES: i32 = 10_000_000;

fn process_day(debug: bool, player_1_avg: f64, day_streak_multiplier: f64) -> bool {
    let mut rng = rand::thread_rng();
    let random_number: f64 = rng.gen();
    let adjusted_batting_average = player_1_avg * STREAK_MULTIPLIER;

    if debug {
        println!("Random Number: {}", random_number);
        println!("Adjusted Batting Average: {}", adjusted_batting_average);
    }
    adjusted_batting_average >= random_number
}

fn single_season(
    debug: bool,
    single_season_avg: f64,
    streak_multiplier: f64,
    games_in_season: i32,
    days_to_beat_streak: i32,
    multi_game: f64,
) -> (bool, i32) {
    let mut games_counter = 0;
    let mut season_success = true;
    let mut streak = 0;

    while games_counter < (games_in_season as f64 * multi_game) as i32 {
        games_counter += 1;
        let day_result = process_day(debug, single_season_avg, streak_multiplier);

        if !day_result {
            season_success = false;
            break;
        } else {
            if streak >= days_to_beat_streak {
                season_success = true;
                break;
            } else {
                streak += 1;
                season_success = false;
            }
        }
    }

    if debug {
        println!("Games: {}", games_counter);
        println!("Streak: {}", streak);
        println!("Season Result: {}", season_success);
    }
    (season_success, streak)
}

fn multi_season_run(
    debug: bool,
    max_tries: i32,
    al_batting_champ: f64,
    streak_multiplier: f64,
    games_in_season: i32,
    days_to_beat_streak: i32,
    multi_game: f64,
) {
    let mut season_counter = 0;
    let mut multi_season_streak = 0;
    let mut season_success = false;

    while season_counter < max_tries {
        let (season_result, season_streak) = single_season(
            debug, al_batting_champ, streak_multiplier, games_in_season, days_to_beat_streak, multi_game,
        );

        if multi_season_streak < season_streak {
            multi_season_streak = season_streak;
        }
        if season_result {
            season_success = true;
            break;
        }
        season_counter += 1;
    }

    println!("Number of Seasons: {}", season_counter);
    println!("Number of Longest Streak: {}", multi_season_streak);
    println!("Result of the Run: {}", season_success);
}

fn main() {
    let start_time = Instant::now();
    let debug = false;

    multi_season_run(debug, MAX_TRIES, AL_BATTING_CHAMP, STREAK_MULTIPLIER, GAMES_IN_SEASON, DAYS_TO_BEAT_STREAK, MULTI_GAME);

    let execution_time = start_time.elapsed().as_secs_f64();
    println!("Execution time: {:.6} seconds", execution_time);
}