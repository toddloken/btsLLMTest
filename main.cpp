#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int days_to_beat_streak = 57;
const int games_in_season = 162;
const double multi_game = 1.25;
const double nl_batting_champ = 0.314;
const double al_batting_champ = 0.332;
const double plate_appearances_per_game = 3.5;
const double at_bats = (plate_appearances_per_game * games_in_season);
const double streak_multiplier = 2;
const int max_tries = 10000000;

bool process_day(bool debug, double player_1_avg, double day_streak_multiplier) {
    double random_number = (double)rand() / RAND_MAX;
    double adjusted_batting_average = player_1_avg * streak_multiplier;

    if (debug) {
        cout << "Random Number: " << random_number << endl;
        cout << "Adjusted Batting Average: " << adjusted_batting_average << endl;
    }
    return adjusted_batting_average >= random_number;
}

bool single_season(bool debug, double single_season_avg, double streak_multiplier, int games_in_season, int days_to_beat_streak, double multi_game, int &streak) {
    int games_counter = 0;
    bool season_success = true;
    streak = 0;

    while (games_counter < (games_in_season * multi_game)) {
        games_counter++;
        bool day_result = process_day(debug, single_season_avg, streak_multiplier);

        if (!day_result) {
            season_success = false;
            break;
        } else {
            if (streak >= days_to_beat_streak) {
                season_success = true;
                break;
            } else {
                streak += 1;
                season_success = false;
            }
        }
    }

    if (debug) {
        cout << "Games: " << games_counter << endl;
        cout << "Streak: " << streak << endl;
        cout << "Season Result: " << season_success << endl;
    }
    return season_success;
}

void multi_season_run(bool debug, int max_tries, double al_batting_champ, double streak_multiplier, int games_in_season, int days_to_beat_streak, double multi_game) {
    int season_counter = 0;
    int multi_season_streak = 0;
    bool season_success = false;

    while (season_counter < max_tries) {
        int season_streak = 0;
        season_success = single_season(debug, al_batting_champ, streak_multiplier, games_in_season, days_to_beat_streak, multi_game, season_streak);

        if (multi_season_streak < season_streak) {
            multi_season_streak = season_streak;
        }
        if (season_success) {
            break;
        }
        season_counter++;
    }

    cout << "Number of Seasons: " << season_counter << endl;
    cout << "Number of Longest Streak: " << multi_season_streak << endl;
    cout << "Result of the Run: " << season_success << endl;
}

int main() {
    srand(time(0));
    clock_t start_time = clock();
    bool debug = false;

    multi_season_run(debug, max_tries, al_batting_champ, streak_multiplier, games_in_season, days_to_beat_streak, multi_game);

    clock_t end_time = clock();
    double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Execution time: " << execution_time << " seconds" << endl;

    return 0;
}