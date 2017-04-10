void play(SDL_Surface *screen);
void print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position);
void erase_surface(SDL_Surface *screen);
void draw_game(SDL_Surface *screen, block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB]);
void initialize_game(block current_grid[][VERTICAL_BLOCK_NB], block grid[][VERTICAL_BLOCK_NB], int * score);
void draw_game_borders(SDL_Surface *screen);
void put_pixel(SDL_Surface* screen, int x, int y, Pixel_t* p);
void draw_game_set(SDL_Surface *screen, int score, int high_score, int level);
void refresh_high_score(SDL_Surface *screen, int score);
