int play(SDL_Surface *screen);
void draw_game_set(SDL_Surface *screen, int current_score, int current_level, int max_score);
void print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position);
void erase_surface(SDL_Surface *screen);
void draw_game(SDL_Surface *screen, block_types grid[][HEIGHT_BLOCK_NB]);
void init_game(block_types grid[][HEIGHT_BLOCK_NB]);
int isLeftMovable(block_types grid[][HEIGHT_BLOCK_NB]);
int isRightMovable(block_types grid[][HEIGHT_BLOCK_NB]);
int isDownMovable(block_types grid[][HEIGHT_BLOCK_NB]);
void moveLeft(block_types grid[][HEIGHT_BLOCK_NB]);
void moveRight(block_types grid[][HEIGHT_BLOCK_NB]);
void moveDown(block_types grid[][HEIGHT_BLOCK_NB]);
void nextTetrino(block_types grid[][HEIGHT_BLOCK_NB]);
