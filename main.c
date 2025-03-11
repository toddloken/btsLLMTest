#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int days_to_beat_streak = 57;
const int games_in_season = 162;
const double multi_game = 1.25;
const double nl_batting_champ = 0.314;
const double al_batting_champ = 0.332;
const double plate_appearances_per_game = 3.5;
const double at_bats = (plate_appearances_per_game * games_in_season);
const double streak_multiplier = 2.1;
const int max_tries = 10000000;

int process_day(int debug, double player_1_avg, double day_streak_multiplier) {
    double random_number = (double)rand() / RAND_MAX;
    double adjusted_batting_average = player_1_avg * streak_multiplier;

    if (debug) {
        printf("Random Number: %f\n", random_number);
        printf("Adjusted Batting Average: %f\n", adjusted_batting_average);
    }
    return adjusted_batting_average >= random_number ? 1 : 0;
}

int single_season(int debug, double single_season_avg, double streak_multiplier, int games_in_season, int days_to_beat_streak, double multi_game, int *streak) {
    int games_counter = 0;
    int season_success = 1;
    *streak = 0;

    while (games_counter < (games_in_season * multi_game)) {
        games_counter++;
        int day_result = process_day(debug, single_season_avg, streak_multiplier);

        if (!day_result) {
            season_success = 0;
            break;
        } else {
            if (*streak >= days_to_beat_streak) {
                season_success = 1;
                break;
            } else {
                (*streak)++;
                season_success = 0;
            }
        }
    }

    if (debug) {
        printf("Games: %d\n", games_counter);
        printf("Streak: %d\n", *streak);
        printf("Season Result: %d\n", season_success);
    }
    return season_success;
}

void multi_season_run(int debug, int max_tries, double al_batting_champ, double streak_multiplier, int games_in_season, int days_to_beat_streak, double multi_game) {
    int season_counter = 0;
    int multi_season_streak = 0;
    int season_success = 0;

    while (season_counter < max_tries) {
        int season_streak = 0;
        season_success = single_season(debug, al_batting_champ, streak_multiplier, games_in_season, days_to_beat_streak, multi_game, &season_streak);

        if (multi_season_streak < season_streak) {
            multi_season_streak = season_streak;
        }
        if (season_success) {
            break;
        }
        season_counter++;
    }

    printf("Number of Seasons: %d\n", season_counter);
    printf("Number of Longest Streak: %d\n", multi_season_streak);
    printf("Result of the Run: %d\n", season_success);
}

int main() {
    srand(time(0));
    clock_t start_time = clock();
    int debug = 0;

    multi_season_run(debug, max_tries, al_batting_champ, streak_multiplier, games_in_season, days_to_beat_streak, multi_game);

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", execution_time);

    return 0;
}