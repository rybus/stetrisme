#include <libconfig.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "constants.h"
#include "config.h"

Config_t load_config(void)
{
    Config_t config;
    FILE *configuration_file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char first_color[10], second_color[10];

    configuration_file = fopen("config.txt", "r");
    if (configuration_file == NULL)
        exit(EXIT_FAILURE);

    getline(&line, &len, configuration_file);
    sscanf(line, "max_score %d", &(config.high_score));
    getline(&line, &len, configuration_file);
    sscanf(line, "left_eye_color %s", first_color);
    getline(&line, &len, configuration_file);
    sscanf(line, "right_eye_color %s", second_color);

    fclose(configuration_file);
    if (line)
        free(line);

    sscanf(
        first_color,
        "%d;%d;%d",
        &(config.left_eye_color.r),
        &(config.left_eye_color.g),
        &(config.left_eye_color.b)
    );

    sscanf(
        second_color,
        "%d;%d;%d",
        &(config.right_eye_color.r),
        &(config.right_eye_color.g),
        &(config.right_eye_color.b)
    );

    return config;
}

void save_config(Config_t config)
{
  FILE *configuration_file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char first_color[10], second_color[10];

  configuration_file = fopen("config.txt", "w");
  if (configuration_file == NULL)
      exit(EXIT_FAILURE);

  sprintf(
      first_color,
      "%d;%d;%d",
      config.left_eye_color.r,
      config.left_eye_color.g,
      config.left_eye_color.b
  );

  sprintf(
      second_color,
      "%d;%d;%d",
      config.right_eye_color.r,
      config.right_eye_color.g,
      config.right_eye_color.b
  );

  fprintf(configuration_file, "max_score %d\n", config.high_score);
  fprintf(configuration_file, "left_eye_color %s\n", first_color);
  fprintf(configuration_file, "right_eye_color %s\n", second_color);

  fclose(configuration_file);
}
