int play(SDL_Surface *screen);
void draw_game_set(SDL_Surface *screen, int current_score, int current_level, int max_score);
void print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position);
void erase_surface(SDL_Surface *screen);
void draw_game(SDL_Surface *screen, block_types grid[][HEIGHT_BLOCK_NB + 3]);
void init_game(block_types grid[][HEIGHT_BLOCK_NB + 3]);
int isLeftMovable(block_types grid[][HEIGHT_BLOCK_NB +3]);
void moveLeft(block_types grid[][HEIGHT_BLOCK_NB +3]);
