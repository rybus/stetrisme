#include <libconfig.h>
#include "colors.h"

void load_colors(struct color *a, struct color *b)
{
  char *config_file_name = "config.txt";
  int high_score = 0;
  config_t cfg;
  config_setting_t *setting;
  const char *first_color, *second_color;
  config_init(&cfg);

  if (!config_read_file(&cfg, config_file_name))
  {
    printf("\n%s:%d - %s", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
  }

  setting = config_lookup(&cfg, "colors");
  if (config_setting_lookup_string(setting, "a", &first_color))
  {
    sscanf(first_color, "%d;%d;%d", &(a->r), &(a->g), &(a->b));
  } else {
    a->r = 200;
    a->g = 200;
    a->b = 200;
  }

  if (config_setting_lookup_string(setting, "b", &second_color))
  {
    sscanf(second_color, "%d;%d;%d", &(b->r), &(b->g), &(b->b));
  }
  else {
    b->r = 200;
    b->g = 200;
    b->b = 200;
  }
}
