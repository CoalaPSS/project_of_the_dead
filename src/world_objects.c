#include "../include/world_objects.h"

color_t tile_color_table[MAX_TILE_COLOR_TYPES];

const u8 floors[MAP_WIDTH * MAP_HEIGTH] = {0};

const u8 walls[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 4, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void print_object(static_object_t *obj) {
    printf("Position: (%f, %f)\n", obj->aabb.position.x, obj->aabb.position.y);
    printf("Half-Size: (%f, %f)\n", obj->aabb.half_size.x, obj->aabb.half_size.y);
    printf("color_id: %d\n\n", obj->color_id);
}

vec2_t absolute_pos(vec2_t relative_pos, vec2_t half_size) {
    vec2_t position;
    
    position = vec2_mult(relative_pos, TILE_SIZE);
    position = vec2_add(position, half_size);

    return position;
}

void init_tile_color_table(color_t *table) {
    table[TILE_COLOR_EMPTY] = (color_t){0,0,0};
    table[TILE_COLOR_GRAY_FLOOR] = (color_t){96,96,96};
    table[TILE_COLOR_BLUE_FLOOR] = (color_t){0,128,230};
    table[TILE_COLOR_DARK_GREEN_FLOOR] = (color_t){0,100,0};
    table[TILE_COLOR_RED_WALL] = (color_t){255,0,0};
    table[TILE_COLOR_YELLOW_WALL] = (color_t){255,255,0};
}

world_objects_t *init_world_objects(physics_state_t *physics_state, const u8 *floor_tiles, const u8 *wall_tiles, int width, int height, i32 tile_size) {
    world_objects_t *world_objs = (world_objects_t*)malloc(sizeof(world_objects_t));
    
    world_objs->floors = array_list_create(sizeof(static_object_t), DEFAULT_INITIAL_CAPACITY);

    world_objs->walls = array_list_create(sizeof(static_object_t), DEFAULT_INITIAL_CAPACITY);
    
    int x, y, index;

    f32 hs = (f32)tile_size/2.0;
    static_object_t tile;
    tile.aabb.half_size = (vec2_t){hs, hs};

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            tile.aabb.position = absolute_pos((vec2_t){x, y}, tile.aabb.half_size);
            index = (y * width) + x;

            tile.color_id = floor_tiles[index];
            array_list_append(world_objs->floors, &tile);
            
            tile.color_id = wall_tiles[index];

            if (tile.color_id > 0){
                array_list_append(world_objs->walls, &tile);
                physics_add_static_body(physics_state, tile.aabb);
            }
            
        }   
    }
    // ERROR_RETURN(1, "Debug exit");
    return world_objs;
}

// world_tilemap_t *create_world_tilemap(const u8 *tile_coordinates, int w, int h, 
//     int tile_size) {

//     int x, y;
//     int index;

//     world_tilemap_t *tilemap = (world_tilemap_t*)malloc(sizeof(world_tilemap_t));
//     tilemap->width = w;
//     tilemap->height = h;
//     tilemap->tile_size = tile_size;

//     tilemap->tiles = (tile_t*)malloc(((w*h)*sizeof(tile_t)));
//     tile_t tt; //temporary tile for storing the new tile

//     for (y = 0; y < h; y++) {
//         for (x = 0; x < w; x++) {
//             index = (y * w) + x;
            
//             tt.color_id = tile_coordinates[index];
//             // tt.x = ((x*tile_size) + (tile_size/2));
//             // tt.y = ((y*tile_size) + (tile_size/2));
//             tt.x = (x * tile_size);
//             tt.y = (y * tile_size);

//             tilemap->tiles[index] = tt;
//         }
//     }
//     return tilemap;
// }

// const tile_t *load_world_map_file(char *map_file) {
//     FILE *wf = fopen(map_file, "rb");
//     if (wf == NULL)
//         ERROR_RETURN(-1, "Could not load map file");

//     color_iddef struct _file_header {int w; int h;} fh_t;
//     fh_t fh;

//     fread(&fh, sizeof(fh_t), 1, wf);
//     int block_size = (fh.w * fh.h * sizeof(tile_t));

//     tile_t *tiles = (tile_t*)malloc((block_size * sizeof(tile_t)));
//     fread(tiles, block_size, 1, wf);

//     if (tiles == NULL) return NULL;

//     return tiles;
// }

// void print_tilemap(world_tilemap_t *tilemap) {
//     int x, y, id;
//     tile_t temp_tile;

//     for (y = 0; y < tilemap->height; y++) {
//         for (x = 0; x < tilemap->height; x++) {
//             id = (y * tilemap->width) + x;
//             temp_tile = tilemap->tiles[id];
//             printf("Tile ID %d\n", id);
//             printf("\tPosition: [%f, %f]\n", temp_tile.x, temp_tile.y);
//             printf("\tcolor_id: ");

//             switch (temp_tile.color_id) {
//                 case FLOOR:
//                     printf("FLOOR\n");
//                     break;
//                 case WALL:
//                     printf("WALL\n");
//                     break;
//                 case BOX:
//                     printf("BOX\n");
//                     break;
//                 default:
//                     printf("NONE\n");
//             }
//         }
//     }
// }