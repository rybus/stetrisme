int initialize_color_blocks(Config_t config);
void draw_game(SDL_Surface *screen, Block grid[][VERTICAL_BLOCK_NB], Tetromino_t, int next_tetromino_type, Config_t config, int score, int level, int nb_fallen_blocks);
void draw_tetrominos(SDL_Surface *screen, Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino, int nb_fallen_blocks);
void draw_next_tetromino(SDL_Surface *screen, int next_tetromino_type);
void draw_game_borders(SDL_Surface *screen);
void put_pixel(SDL_Surface* screen, int x, int y, Pixel_t* p);
void print_positioned_game_information(SDL_Surface *screen, char *label_text, int number, SDL_Rect *position);
void erase_surface(SDL_Surface *surface);
void draw_ghost_tetromino(SDL_Surface *screen, Block grid[][VERTICAL_BLOCK_NB], Tetromino_t tetromino, int nb_fallen_blocks);
