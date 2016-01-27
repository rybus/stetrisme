int play(SDL_Surface *screen);
int draw_game_set(SDL_Surface *screen, int current_score, int current_level, int max_score);
int print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position);
int erase_surface(SDL_Surface *screen);
int draw_game(SDL_Surface *screen, SDL_Rect block_position, SDL_Surface *block);