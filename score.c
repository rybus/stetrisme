#include <stdio.h>

int load_high_score()
{
    int score = -1;
    FILE *score_file = fopen("./high_score.txt", "r");

   if (score_file) {
       fscanf (score_file, "%d", &score);
       fclose(score_file);
    }

   return score;
}


int update_high_score(int score)
{
    int current_high_score = load_high_score();
    if (score > current_high_score) {
      FILE *score_file = fopen("./high_score.txt", "w");

     if (score_file) {
         fprintf (score_file, "%d", score);
         fclose(score_file);
      }
    }
}
