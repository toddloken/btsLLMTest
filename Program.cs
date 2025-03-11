using System;

class Program
{
    const int DaysToBeatStreak = 57;
    const int GamesInSeason = 162;
    const double MultiGame = 1.25;
    const double NLBattingChamp = 0.314;
    const double ALBattingChamp = 0.332;
    const double PlateAppearancesPerGame = 3.5;
    const double AtBats = PlateAppearancesPerGame * GamesInSeason;
    const double StreakMultiplier = 2;
    const int MaxTries = 10000000;

    static bool ProcessDay(bool debug, double playerAvg, double dayStreakMultiplier)
    {
        Random rand = new Random();
        double randomNumber = rand.NextDouble();
        double adjustedBattingAverage = playerAvg * StreakMultiplier;

        if (debug)
        {
            Console.WriteLine($"Random Number: {randomNumber}");
            Console.WriteLine($"Adjusted Batting Average: {adjustedBattingAverage}");
        }
        return adjustedBattingAverage >= randomNumber;
    }

    static bool SingleSeason(bool debug, double singleSeasonAvg, double streakMultiplier, int gamesInSeason, int daysToBeatStreak, double multiGame, out int streak)
    {
        int gamesCounter = 0;
        bool seasonSuccess = true;
        streak = 0;

        while (gamesCounter < (gamesInSeason * multiGame))
        {
            gamesCounter++;
            bool dayResult = ProcessDay(debug, singleSeasonAvg, streakMultiplier);

            if (!dayResult)
            {
                seasonSuccess = false;
                break;
            }
            else
            {
                if (streak >= daysToBeatStreak)
                {
                    seasonSuccess = true;
                    break;
                }
                else
                {
                    streak += 1;
                    seasonSuccess = false;
                }
            }
        }

        if (debug)
        {
            Console.WriteLine($"Games: {gamesCounter}");
            Console.WriteLine($"Streak: {streak}");
            Console.WriteLine($"Season Result: {seasonSuccess}");
        }
        return seasonSuccess;
    }

    static void MultiSeasonRun(bool debug, int maxTries, double alBattingChamp, double streakMultiplier, int gamesInSeason, int daysToBeatStreak, double multiGame)
    {
        int seasonCounter = 0;
        int multiSeasonStreak = 0;
        bool seasonSuccess = false;

        while (seasonCounter < maxTries)
        {
            int seasonStreak;
            seasonSuccess = SingleSeason(debug, alBattingChamp, streakMultiplier, gamesInSeason, daysToBeatStreak, multiGame, out seasonStreak);

            if (multiSeasonStreak < seasonStreak)
            {
                multiSeasonStreak = seasonStreak;
            }
            if (seasonSuccess)
            {
                break;
            }
            seasonCounter++;
        }

        Console.WriteLine($"Number of Seasons: {seasonCounter}");
        Console.WriteLine($"Number of Longest Streak: {multiSeasonStreak}");
        Console.WriteLine($"Result of the Run: {seasonSuccess}");
    }

    static void Main()
    {
        Random rand = new Random();
        DateTime startTime = DateTime.Now;
        bool debug = false;

        MultiSeasonRun(debug, MaxTries, ALBattingChamp, StreakMultiplier, GamesInSeason, DaysToBeatStreak, MultiGame);

        DateTime endTime = DateTime.Now;
        double executionTime = (endTime - startTime).TotalSeconds;
        Console.WriteLine($"Execution time: {executionTime} seconds");
    }
}
