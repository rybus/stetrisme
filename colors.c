#include <libconfig.h>
#include <stdint.h>

#include "constants.h"
#include "colors.h"

void load_colors(struct color *a, struct color *b)
{
  char *config_file_name = "config.txt";
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

	config_destroy(&cfg);
}

void save_colors(struct color a, struct color b)
{
  char *config_file_name = "config.txt";
  config_t cfg;
  config_setting_t *setting_color_a, *setting_color_b;
  char first_color[11], second_color[11];
  config_init(&cfg);

  if (!config_read_file(&cfg, config_file_name))
  {
    printf("\n%s:%d - %s", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
  }

  sprintf(first_color, "%d;%d;%d", a.r, a.g, a.b);
  sprintf(second_color, "%d;%d;%d", b.r, b.g, b.b);
  setting_color_a = config_lookup(&cfg, "colors.a");
  setting_color_b = config_lookup(&cfg, "colors.b");
  config_setting_set_string(setting_color_a, first_color);
  config_setting_set_string(setting_color_b, second_color);

  config_write_file(&cfg, config_file_name);

	config_destroy(&cfg);
}
