#include <stdio.h>
#include <libconfig.h>

int load_high_score()
{
  char *config_file_name = "config.txt";
	int high_score = 0;
	config_t cfg;
	config_setting_t *setting;
  config_init(&cfg);

  if (!config_read_file(&cfg, config_file_name))
  {
      printf("\n%s:%d - %s", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
      config_destroy(&cfg);
      return -1;
  }

  if (config_lookup_int(&cfg, "max_score", &high_score))
  {
      return high_score;
  }
  else
      return -1;
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
