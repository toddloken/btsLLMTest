import numpy as np
import time

days_to_beat_streak = 57
games_in_season = 162
multi_game = 1.25 #gives the user to pick more than 1 player at a time
nl_batting_champ = 0.314
al_batting_champ = 0.332
plate_appearances_per_game = 3.5
at_bats = (plate_appearances_per_game * games_in_season)
streak_multiplier = 2 #this is the increase in likelihood that a streaking player is going to get a hit between 1 and 3 - basically multiplies the average with no bound checking to be better than 1
max_tries = 10000000

start_time = time.time()
debug = False

def process_day(debug, player_1_avg, day_streak_multiplier):
    """This processes a single day assuming 1 player at a time is picked"""
    day_result = 0
    random_number = np.random.random()
    adjusted_batting_average = player_1_avg * streak_multiplier #assumes streaking player has higher likelihood

    if debug:
        print(random_number)
        print(adjusted_batting_average)

    if adjusted_batting_average >= random_number:
        day_result = 1
    return day_result

def single_season(debug, single_season_avg, streak_multiplier,games_in_season, days_to_beat_streak, multi_game):
    """This processes a single season maximum tries number of times """
    games_counter = 0
    season_success = True
    streak = 0

    while games_counter < (games_in_season * multi_game):
        games_counter += 1
        day_result_counter = day_result_counter = process_day(debug=False,
                                 player_1_avg=single_season_avg,
                                 day_streak_multiplier=streak_multiplier)

        if day_result_counter == 0:
            season_success = False
            break
        else:
            if streak >= days_to_beat_streak:
                season_success = True
                break
            else:
                streak = streak + day_result_counter
                season_success = False

    if debug:
        print(f'Games  = {games_counter}')
        print(f'Streak  = {streak}')
        print(f'Season Result  = {season_success}')


    return season_success, streak

def multi_season_run(debug, max_tries, al_batting_champ, streak_multiplier,games_in_season, days_to_beat_streak, multi_game):
    """This processes a single season maximum tries number of times """
    season_counter = 0
    multi_season_streak = 0

    while season_counter < max_tries:
        season_success, season_streak = single_season(debug, al_batting_champ, streak_multiplier,games_in_season, days_to_beat_streak, multi_game)
        if multi_season_streak < season_streak:
            multi_season_streak = season_streak
        if season_success:
            break
        season_counter += 1

    return season_counter, multi_season_streak, season_success

season_counter, multi_season_streak, season_success = multi_season_run(debug,
                                                                       max_tries,
                                                                       al_batting_champ,
                                                                       streak_multiplier,
                                                                       games_in_season,
                                                                       days_to_beat_streak,
                                                                       multi_game)
print(f'Number of Seasons  = {season_counter}')
print(f'Number of Longest Streak  = {multi_season_streak}')
print(f'Result of Run  = {season_success}')
end_time = time.time()  # Record the end time

print(f"Execution time: {end_time - start_time:.4f} seconds")