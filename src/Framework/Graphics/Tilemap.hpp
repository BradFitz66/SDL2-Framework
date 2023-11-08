#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Layer.hpp>

#include "Texture.hpp"
#include "Transform.hpp"
#include "../Miscellaneous/IRenderable.hpp"

/*
Code is derived from the following example:
https://github.com/connorkuehl/sdl2-tiled-example/tree/master
*/

class Tilemap : public Transform, public IRenderable
{

    typedef long int id;

    struct Tile : public IRenderable
    {
        // This seems to cause a segfault when calling the render function of the texture
        Texture *sheet;
        // Reference to the tilemap it belongs to
        Tilemap *tilemap;

        int index;
        int x, y; // World coordinates
        int width, height;
        SDL_Rect *src_rect;
        SDL_Rect *dst_rect;
        // Constructor
        Tile(
            Texture *sheet,
            Tilemap *tilemap,
            int x = 0,
            int y = 0,
            int src_x = 0,
            int src_y = 0,
            int width = 0,
            int height = 0)
        {

            this->sheet = sheet;
            this->tilemap = tilemap;

            this->x = x;
            this->y = y;

            src_rect = new SDL_Rect{
                src_x,
                src_y,
                width,
                height};

            dst_rect = new SDL_Rect{
                x,
                y,
                width,
                height
            };

            this->width = width;
            this->height = height;
        }

        void Render(SDL_Renderer *renderer, int OffsetX = 0, int OffsetY = 0) override
        {
            if (!sheet || !renderer)
            {
                return;
            }
            // Offset position
            dst_rect->x = x + OffsetX;
            dst_rect->y = y + OffsetY;
            dst_rect->w = width * tilemap->GetScale().x;
            dst_rect->h = height * tilemap->GetScale().y;

            sheet->Render(
                renderer,
                src_rect,
                dst_rect);
        }
    };

public:
    // Constructor
    Tilemap(
        std::string texture_path,
        SDL_Renderer *renderer) : Transform(vector2D<float>(0, 0), 0, vector2D<float>(1, 1))
    {
        // Construct the Transform class
        Load(texture_path, renderer);
    }

    Tilemap(
        std::string texture_path,
        SDL_Renderer *renderer,
        vector2D<float> position,
        float rotation,
        vector2D<float> scale) : Transform(position, rotation, scale)
    {
        // Construct the Transform class
        Load(texture_path, renderer);
    }

    void Load(const std::string &path, SDL_Renderer *renderer)
    {
        tmx::Map map = tmx::Map();
        map.load(path);
        tmx::Vector2u dimensions = map.getTileCount();
        rows = dimensions.y;
        cols = dimensions.x;

        tmx::Vector2u tile_dimensions = map.getTileSize();
        tile_width = tile_dimensions.x;
        tile_height = tile_dimensions.y;

        std::vector<tmx::Tileset> tileset_list = map.getTilesets();

        for (tmx::Tileset tset : tileset_list)
        {
            tilesets.insert(std::pair<id, Texture *>(tset.getFirstGID(), new Texture(renderer, tset.getImagePath(), 0, 0, true)));
        }

        // Count tilesets map length
        int i = 0;
        for (auto &tileset : tilesets)
        {
            i++;
        }

        auto &layers = map.getLayers();
        for (auto &layer : layers)
        {
            // Create a copy of the loop variable to capture it.

            if (layer->getType() != tmx::Layer::Type::Tile)
            {
                continue;
            }

            auto *tile_layer = dynamic_cast<const tmx::TileLayer *>(layer.get());
            std::vector<tmx::TileLayer::Tile> layer_tiles = tile_layer->getTiles();

            for (int y = 0; y < rows; ++y)
            {
                for (int x = 0; x < cols; ++x)
                {
                    int tile_index = x + (y * cols);
                    int cur_gid = layer_tiles[tile_index].ID;
                    tmx::TileLayer::Tile tile = layer_tiles[tile_index];
                    if (cur_gid == 0)
                    {
                        continue;
                    }

                    int tileset_gid = -1;
                    for (std::pair<id, Texture *> tileset : tilesets)
                    {
                        if (tile.ID >= tileset.first)
                        {
                            tileset_gid = tileset.first;
                        }
                    }

                    if (tileset_gid == -1)
                    {
                        continue;
                    }

                    cur_gid -= tileset_gid;

                    int tileset_width = 0;
                    int tileset_height = 0;
                    SDL_Texture *tileset_texture = *tilesets[tileset_gid];
                    SDL_QueryTexture(tileset_texture, NULL, NULL, &tileset_width, &tileset_height);

                    int region_x = (cur_gid % (tileset_width / tile_width)) * tile_width;
                    int region_y = (cur_gid / (tileset_width / tile_width)) * tile_height;

                    int tile_x = x * tile_width;
                    int tile_y = y * tile_height;

                    Tile t = Tile(
                        tilesets[tileset_gid],
                        this,
                        tile_x,
                        tile_y,
                        region_x,
                        region_y,
                        tile_width,
                        tile_height
                    );

                    tiles.push_back(t);
                }
            }
        }
    }

    void Render(SDL_Renderer *r, int xOffset = 0, int yOffset = 0) override
    {
        for (Tile t : tiles)
        {
            t.Render(r, xOffset, yOffset);
        }
    }

private:
    std::vector<Tile> tiles;
    int rows, cols;
    int tile_width, tile_height;
    int map_width, map_height;
    std::map<id, Texture *> tilesets;
};
#endif