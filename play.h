int play(SDL_Surface *screen);
void draw_game_set(SDL_Surface *screen, int current_score, int current_level, int max_score);
void print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position);
void erase_surface(SDL_Surface *screen);
void draw_game(SDL_Surface *screen, block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB]);
void initialize_game(block current_grid[][HEIGHT_BLOCK_NB], block grid[][HEIGHT_BLOCK_NB], int * score);
int load_score();
void draw_game_borders(SDL_Surface *screen);
void put_pixel(SDL_Surface* screen, int x, int y,pixel* p);
