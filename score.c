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
	config_destroy(&cfg);

	return -1;
}


int update_high_score(int score)
{
	char *config_file_name = "config.txt";
	config_t cfg;
	config_setting_t *high_score;
	int current_high_score = 0;
	config_init(&cfg);

	current_high_score = load_high_score();
	if (current_high_score > score) {
		return 0;
	}

	if (!config_read_file(&cfg, config_file_name))
	{
			printf("\n%s:%d - %s", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
			config_destroy(&cfg);
			return -1;
	}

 	high_score = config_lookup(&cfg, "max_score");
	config_setting_set_int(high_score, score);
	config_write_file(&cfg, config_file_name);
 	config_destroy(&cfg);
}
