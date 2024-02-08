#pragma once

enum TileType
{
	NONE,
    PATH,
	OBSTACLE,
    RESOURCE,
    TILE_USED_UP,
};

enum GrassType
{
	GRASS1, 
	GRASS2, 
	GRASS3, 
	GRASS4, 
	GRASS5, 
	MOUNTAINS,

    BRIDGE1, 
    BRIDGE2, 
    BRIDGE3, 
    BRIDGE4, 
    BRIDGE5,
    BRIDGE6,
    BRIDGE7,
    BRIDGE8,
    PATH1, 
    PATH2, 
    PATH3, 
    PATH4, 
    PATH5, 
    PATH6, 
    PATH7, 
    PATH8, 
    PATH9, 
    PATH10,

    WATER1,
    WATER2,
    WATER3,
    WATER4,
    WATER5,
    WATER6,
    WATER7,
    WATER8,
    WATER9,
    WATER10, 
    WATER11, 
    WATER12, 
    WATER13, 

    GOLD_ORE,
    WASTE,
    OIL_POOL
};

enum ResourceType
{
    NO_RESOURCE,
    GOLD,
    OIL,
    TOXIC_WASTE
};