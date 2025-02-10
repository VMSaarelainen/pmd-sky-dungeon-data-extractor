#pragma once

#include <map>
#include <cstdint>
#include <string>

enum class floor_layout {
    LARGE = 0,
    SMALL = 1,
    ONE_ROOM_MONSTER_HOUSE = 2,
    OUTER_RING = 3,
    CROSSROADS = 4,
    TWO_ROOMS_WITH_MONSTER_HOUSE = 5,
    LINE = 6,
    CROSS = 7,
    LARGE_0x8 = 8,
    BEETLE = 9,
    OUTER_ROOMS = 10,
    MEDIUM = 11,
    UNUSED_0xC = 12,
    UNUSED_0xD = 13,
    UNUSED_0xE = 14,
    UNUSED_0xF = 15,
};

// Dungeon floor properties from pmdsky-debug dungeon.h, modified slightly to output to JSON easily
struct floor_properties {
	floor_layout layout; // 0x0
	// 0x1: Affects the number of rooms to be generated. If it's positive, a slight random variation
	// (between -2 and +1) is applied to the value (the final value must be at least 1). If it's
	// negative, its absolute value is used without adding a random variation.
	int8_t room_density;
	uint8_t tileset; // 0x2
	// 0x3: Indexes into the music ID table in overlay 10 to determine the floor's music track.
	// See the relevant descriptions in the overlay 10 symbols for more information.
	uint8_t music_table_idx;
	uint8_t weather; // 0x4
	// 0x5: Controls how many connections will be made between grid cells
	uint8_t floor_connectivity;
	// 0x6: Controls how many enemies will be spawned. If 0, no enemies will spawn, even as the
	// player walks. If > 0, the final value will be randomized between density / 2 and density - 1.
	// If < 0, its absolute value will be used without adding a random variation.
	uint8_t enemy_density;
	uint8_t kecleon_shop_spawn_chance;  // 0x7: Percentage chance from 0-100
	uint8_t monster_house_spawn_chance; // 0x8: Percentage chance from 0-100
	uint8_t maze_room_chance;           // 0x9: Percentage chance from 0-100
	uint8_t sticky_item_chance;         // 0xA
	// 0xB: Whether or not dead ends are allowed in the floor layout. If false, dead ends will be
	// corrected during floor generation (or rather, they should be, but the implementation is
	// buggy)
	bool allow_dead_ends;
	// 0xC: Maximum number of secondary structures that can be generated on the floor
	uint8_t max_secondary_structures;
	// 0xD: room_flags: 1-byte bitfield
	bool f_secondary_structures; // Whether secondary structures are allowed
	uint8_t room_flags_unk1;
	bool f_room_imperfections; // Whether room imperfections are allowed
	uint8_t room_flags_unk3;

	uint8_t field_0xe;
	uint8_t item_density; // 0xF: Controls how many items will be spawned
	uint8_t trap_density; // 0x10: Controls how many traps will be spawned
	uint8_t floor_number; // 0x11: The current floor number within the overall dungeon
	uint8_t fixed_room_id; // 0x12
	uint8_t extra_hallways;               // 0x13: Number of extra hallways to generate
	uint8_t buried_item_density; // 0x14: Controls how many buried items (in walls) will be spawned
	// 0x15: Controls how much secondary terrain (water, lava, and this actually applies to chasms
	// too) will be spawned
	uint8_t secondary_terrain_density;
	// 0x16: Vision range (in tiles) when standing on a hallway.
	// A value of 0 means no limit, a value > 0 enables darkness on the floor.
	uint8_t visibility_range;
	uint8_t max_money_amount_div_5; // 0x17: 1/5 the maximum amount for Poké spawns
	// 0x18: Chance of an item spawning on each tile in a Kecleon shop
	uint8_t shop_item_positions;
	// 0x19: Chance that a Monster House will be an itemless one
	uint8_t itemless_monster_house_chance;
	// 0x1A: Values are shifted relative to enum hidden_stairs_type.
	// 0 means HIDDEN_STAIRS_SECRET_BAZAAR, 1 means HIDDEN_STAIRS_SECRET_ROOM, and
	// 255 still means HIDDEN_STAIRS_RANDOM_SECRET_BAZAAR_OR_SECRET_ROOM.
	uint8_t hidden_stairs_type;
	uint8_t hidden_stairs_spawn_chance; // 0x1B
	int16_t enemy_iq;                   // 0x1C: IQ stat of enemies
	int16_t iq_booster_value; // 0x1E: IQ increase from the IQ booster item upon entering the floor
	bool has_extra_item;
	bool nonstory_flag;
};

extern std::map<uint8_t, std::string> dungeonNames;