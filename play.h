void play(SDL_Surface *screen);
void print_integer_informations(SDL_Surface *screen, char *label, int number, SDL_Rect *position);
void initialize_game();
void draw_game(SDL_Surface *screen);
void draw_game_borders(SDL_Surface *screen);
void draw_tetrominos(SDL_Surface *screen);
void erase_surface(SDL_Surface *screen);
void put_pixel(SDL_Surface* screen, int x, int y, Pixel_t* p);
