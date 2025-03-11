import java.util.Random;

public class BattingStreakSimulation {
    // Constants
    static final int DAYS_TO_BEAT_STREAK = 57;
    static final int GAMES_IN_SEASON = 162;
    static final double MULTI_GAME = 1.25;
    static final double NL_BATTING_CHAMP = 0.314;
    static final double AL_BATTING_CHAMP = 0.332;
    static final double PLATE_APPEARANCES_PER_GAME = 3.5;
    static final double AT_BATS = (PLATE_APPEARANCES_PER_GAME * GAMES_IN_SEASON);
    static final double STREAK_MULTIPLIER = 2;
    static final int MAX_TRIES = 10000000;

    // Random number generator
    static Random random = new Random();

    // Process a single day's result
    static boolean processDay(boolean debug, double playerAvg, double dayStreakMultiplier) {
        double randomNumber = random.nextDouble();
        double adjustedBattingAverage = playerAvg * STREAK_MULTIPLIER;

        if (debug) {
            System.out.println("Random Number: " + randomNumber);
            System.out.println("Adjusted Batting Average: " + adjustedBattingAverage);
        }
        return adjustedBattingAverage >= randomNumber;
    }

    // Simulate a single season
    static boolean singleSeason(boolean debug, double singleSeasonAvg, double streakMultiplier,
                                int gamesInSeason, int daysToBeatStreak, double multiGame, int[] streakHolder) {
        int gamesCounter = 0;
        boolean seasonSuccess = true;
        streakHolder[0] = 0;

        while (gamesCounter < (gamesInSeason * multiGame)) {
            gamesCounter++;
            boolean dayResult = processDay(debug, singleSeasonAvg, streakMultiplier);

            if (!dayResult) {
                seasonSuccess = false;
                break;
            } else {
                if (streakHolder[0] >= daysToBeatStreak) {
                    seasonSuccess = true;
                    break;
                } else {
                    streakHolder[0] += 1;
                    seasonSuccess = false;
                }
            }
        }

        if (debug) {
            System.out.println("Games: " + gamesCounter);
            System.out.println("Streak: " + streakHolder[0]);
            System.out.println("Season Result: " + seasonSuccess);
        }
        return seasonSuccess;
    }

    // Run multiple seasons
    static void multiSeasonRun(boolean debug, int maxTries, double alBattingChamp, double streakMultiplier,
                               int gamesInSeason, int daysToBeatStreak, double multiGame) {
        int seasonCounter = 0;
        int multiSeasonStreak = 0;
        boolean seasonSuccess = false;

        while (seasonCounter < maxTries) {
            int[] seasonStreak = new int[1]; // Using array to simulate pass-by-reference
            seasonSuccess = singleSeason(debug, alBattingChamp, streakMultiplier,
                    gamesInSeason, daysToBeatStreak, multiGame, seasonStreak);

            if (multiSeasonStreak < seasonStreak[0]) {
                multiSeasonStreak = seasonStreak[0];
            }

            if (seasonSuccess) {
                break;
            }
            seasonCounter++;
        }

        System.out.println("Number of Seasons: " + seasonCounter);
        System.out.println("Number of Longest Streak: " + multiSeasonStreak);
        System.out.println("Result of the Run: " + seasonSuccess);
    }

    // Main function
    public static void main(String[] args) {
        long startTime = System.nanoTime();
        boolean debug = false;

        multiSeasonRun(debug, MAX_TRIES, AL_BATTING_CHAMP, STREAK_MULTIPLIER,
                GAMES_IN_SEASON, DAYS_TO_BEAT_STREAK, MULTI_GAME);

        long endTime = System.nanoTime();
        double executionTime = (endTime - startTime) / 1.0e9;
        System.out.println("Execution time: " + executionTime + " seconds");
    }
}