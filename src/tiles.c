#include "../include/tiles.h"

const u8 world_tiles[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 2, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

world_tilemap_t *create_world_tilemap(const u8 *tile_coordinates, int w, int h, 
    int tile_size) {

    int x, y;
    int index;

    world_tilemap_t *tilemap = (world_tilemap_t*)malloc(sizeof(world_tilemap_t));
    tilemap->width = w;
    tilemap->height = h;
    tilemap->tile_size = tile_size;

    tilemap->tiles = (tile_t*)malloc(((w*h)*sizeof(tile_t)));
    tile_t tt; //temporary tile for storing the new tile

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            index = (y * w) + x;
            
            tt.type = tile_coordinates[index];
            // tt.x = ((x*tile_size) + (tile_size/2));
            // tt.y = ((y*tile_size) + (tile_size/2));
            tt.x = (x * tile_size);
            tt.y = (y * tile_size);

            tilemap->tiles[index] = tt;
        }
    }
    return tilemap;
}

const tile_t *load_world_map_file(char *map_file) {
    FILE *wf = fopen(map_file, "rb");
    if (wf == NULL) throw_exception("Could not open world file.");

    typedef struct _file_header {int w; int h;} fh_t;
    fh_t fh;

    fread(&fh, sizeof(fh_t), 1, wf);
    int block_size = (fh.w * fh.h * sizeof(tile_t));

    tile_t *tiles = (tile_t*)malloc((block_size * sizeof(tile_t)));
    fread(tiles, block_size, 1, wf);

    if (tiles == NULL) return NULL;

    return tiles;
}

void print_tilemap(world_tilemap_t *tilemap) {
    int x, y, id;
    tile_t temp_tile;

    for (y = 0; y < tilemap->height; y++) {
        for (x = 0; x < tilemap->height; x++) {
            id = (y * tilemap->width) + x;
            temp_tile = tilemap->tiles[id];
            printf("Tile ID %d\n", id);
            printf("\tPosition: [%f, %f]\n", temp_tile.x, temp_tile.y);
            printf("\tType: ");

            switch (temp_tile.type) {
                case FLOOR:
                    printf("FLOOR\n");
                    break;
                case WALL:
                    printf("WALL\n");
                    break;
                case BOX:
                    printf("BOX\n");
                    break;
                default:
                    printf("NONE\n");
            }
        }
    }
}