#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <map>
#include <iomanip>

#include <floor_props.hpp>
#include <nlohmann/json.hpp>

using namespace std;

const uint arm9datastart = 0x0009e924;
const uint arm9datasize = 0x0009ebf4 - arm9datastart;
const uint mappadatastart = 0x00041d90;
const uint mappadatasize = 0x00042310 +  - mappadatastart;
const uint mappafloordatastart = 0x00008db0;
const uint mappaindextablestart = 0x00008c20;
const uint mappafloornumberstart = 0x8dc1;

const uint beachcavestartingame = 0x02133074;

// Source: https://docs.google.com/spreadsheets/d/1uT7W6puY4JUh1PM92X7L888fH0HXwrwqaBSEJvKbRMA/edit#gid=1361710261 
std::map<uint8_t, std::string> dungeonNames = {
	{0, "Test Dungeon"},                            
	{1, "Beach Cave"},
	{2, "Beach Cave Pit"},
	{3, "Drenched Bluff"},
	{4, "Mt. Bristle"},
	{5, "Mt. Bristle Peak"},
	{6, "Waterfall Cave"},
	{7, "Apple Woods"},
	{8, "Craggy Coast"},
	{9, "Side Path"},
	{10, "Mt. Horn"},
	{11, "Rock Path"},
	{12, "Foggy Forest"},
	{13, "Forest Path"},
	{14, "Steam Cave"},
	{15, "Upper Steam Cave"},
	{16, "Steam Cave Peak"},
	{17, "Amp Plains"},
	{18, "Far Amp Plains"},
	{19, "Amp Clearing"},
	{20, "Northern Desert"},
	{21, "Quicksand Cave"},
	{22, "Quicksand Pit"},
	{23, "Underground Lake"},
	{24, "Crystal Cave"},
	{25, "Crystal Crossing"},
	{26, "Crystal Lake"},       //TODO: Regional difference, it's either shining or crystal lake...
	{27, "Chasm Cave"},
	{28, "Dark Hill"},
	{29, "Sealed Ruin"},
	{30, "Deep Sealed Ruin"},
	{31, "Sealed Ruin Pit"},
	{32, "Dusk Forest"},
	{33, "Deep Dusk Forest"},
	{34, "Treeshroud Forest"},
	{35, "Brine Cave"},
	{36, "Lower Brine Cave"},
	{37, "Brine Cave Pit"},
	{38, "Hidden Land"},
	{39, "Hidden Highland"},
	{40, "Old Ruins"},
	{41, "Temporal Tower"},
	{42, "Temporal Spire"},
	{43, "Temporal Pinnacle"},
	{44, "Mystifying Forest"},
	{45, "Mystifying Forest Clearing"},
	{46, "Blizzard Island"},
	{47, "Crevice Cave"},
	{48, "Lower Crevice Cave"},
	{49, "Crevice Cave Pit"},
	{50, "Surrounded Sea"},
	{51, "Miracle Sea"},
	{52, "Deep Miracle Sea"},
	{53, "Miracle Seabed"},
	{54, "Ice Aegis Cave"},
	{55, "Regice Chamber"},
	{56, "Rock Aegis Cave"},
	{57, "Regirock Chamber"},
	{58, "Steel Aegis Cave"},
	{59, "Registeel Chamber"},
	{60, "Aegis Cave Pit"},
	{61, "Regigigas Chamber"},
	{62, "Mt. Travail"},
	{63, "The Nightmare"},
	{64, "Spacial Rift"},
	{65, "Deep Spacial Rift"},
	{66, "Spacial Rift Bottom"},
	{67, "Dark Crater"},
	{68, "Deep Dark Crater"},
	{69, "Dark Crater Pit"},
	{70, "Concealed Ruins"},
	{71, "Deep Concealed Ruins"},
	{72, "Marine Resort"},
	{73, "Bottomless Sea"},
	{74, "Bottomless Sea Depths"},
	{75, "Shimmer Desert"},
	{76, "Shimmer Desert Pit"},
	{77, "Mt. Avalanche"},
	{78, "Mt. Avalanche Peak"},
	{79, "Giant Volcano"},
	{80, "Giant Volcano Peak"},
	{81, "World Abyss"},
	{82, "World Abyss Pit"},
	{83, "Sky Stairway"},
	{84, "Sky Stairway Apex"},
	{85, "Mystery Jungle"},
	{86, "Deep Mystery Jungle"},
	{87, "Serenity River"},
	{88, "Landslide Cave"},
	{89, "Lush Prairie"},
	{90, "Tiny Meadow"},
	{91, "Labyrinth Cave"},
	{92, "Oran Forest"},
	{93, "Lake Afar"},
	{94, "Happy Outlook"},
	{95, "Mt. Mistral"},
	{96, "Shimmer Hill"},
	{97, "Lost Wilderness"},
	{98, "Midnight Forest"},
	{99, "Zero Isle North"},
	{100, "Zero Isle East"},
	{101, "Zero Isle West"},
	{102, "Zero Isle South"},
	{103, "Zero Isle Center"},
	{104, "Destiny Tower"},
	{105, "[M:D1]Dummy"},
	{106, "[M:D1]Dummy"},
	{107, "Oblivion Forest"},
	{108, "Treacherous Waters"},
	{109, "Southeastern Islands"},
	{110, "Inferno Cave"},
	{111, "1st Station Pass"},
	{112, "2nd Station Pass"},
	{113, "3rd Station Pass"},
	{114, "4th Station Pass"},
	{115, "5th Station Pass"},
	{116, "6th Station Pass"},
	{117, "7th Station Pass"},
	{118, "8th Station Pass"},
	{119, "9th Station Pass"},
	{120, "Sky Peak Summit Pass"},
	{121, "5th Station Clearing"},
	{122, "Sky Peak Summit"},
	{123, "Star Cave"},
	{124, "Deep Star Cave"},
	{125, "Deep Star Cave"},
	{126, "Star Cave Depths"},
	{127, "Star Cave Pit"},
	{128, "Murky Forest"},
	{129, "Eastern Cave"},
	{130, "Fortune Ravine"},
	{131, "Fortune Ravine Depths"},
	{132, "Fortune Ravine Pit"},
	{133, "Barren Valley"},
	{134, "Deep Barren Valley"},
	{135, "Barren Valley Clearing"},
	{136, "Dark Wasteland"},
	{137, "Temporal Tower"},
	{138, "Temporal Spire"},
	{139, "Dusk Forest"},
	{140, "Black Swamp"},
	{141, "Spacial Cliffs"},
	{142, "Dark Ice Mountain"},
	{143, "Dark Ice Mountain Peak"},
	{144, "Dark Ice Mountain Pinnacle"},
	{145, "Icicle Forest"},
	{146, "Vast Ice Mountain"},
	{147, "Vast Ice Mountain Peak"},
	{148, "Vast Ice Mountain Pinnacle"},
	{149, "Southern Jungle"},
	{150, "Boulder Quarry"},
	{151, "Deep Boulder Quarry"},
	{152, "Boulder Quarry Clearing"},
	{153, "Right Cave Path"},
	{154, "Left Cave Path"},
	{155, "Limestone Cavern"},
	{156, "Deep Limestone Cavern"},
	{157, "Limestone Cavern Depths"},
	{158, "Spring Cave"},
	{159, "Upper Spring Cave"},
	{160, "Upper Spring Cave"},
	{161, "Middle Spring Cave"},
	{162, "Lower Spring Cave"},
	{163, "Spring Cave Depths"},
	{164, "Spring Cave Pit"},
	{165, "Little Plains"},
	{166, "Mt. Clear"},
	{167, "Challenge River"},
	{168, "Trial Forest"},
	{169, "Guiding Sea"},
	{170, "Hidden Shopkeeper Village"},
	{171, "[M:D1]Dummy"},
	{172, "[M:D1]Dummy"},
	{173, "[M:D1]Dummy"},
	{174, "Star Cave"},
	{175, "Shaymin Village"},
	{176, "Armaldo's Shelter"},
	{177, "Luminous Spring"},
	{178, "Hot Spring"},
	{179, "Rescue"},
	{180, "Normal/Fly Maze"},
	{181, "Dark/Fire Maze"},
	{182, "Rock/Water Maze"},
	{183, "Grass Maze"},
	{184, "Elec/Steel Maze"},
	{185, "Ice/Ground Maze"},
	{186, "Fight/Psych Maze"},
	{187, "Poison/Bug Maze"},
	{188, "Dragon Maze"},
	{189, "Ghost Maze"},
	{190, "Explorer Maze"},
	{191, "Final Maze"},
	{192, "[M:D1]Dojo"},
	{193, "[M:D1]Dojo"},
	{194, "[M:D1]Dojo"},
	{195, "[M:D1]Dojo"},
	{196, "[M:D1]Dojo"},
	{197, "[M:D1]Dojo"},
	{198, "[M:D1]Dojo"},
	{199, "[M:D1]Dojo"},
	{200, "[M:D1]Dojo"},
	{201, "[M:D1]Dojo"},
	{202, "[M:D1]Dojo"},
	{203, "[M:D1]Dojo"},
	{204, "[M:D1]Dojo"},
	{205, "[M:D1]Dojo"},
	{206, "[M:D1]Dojo"},
	{207, "[M:D1]Dojo"},
	{208, "[M:D1]Dojo"},
	{209, "[M:D1]Dojo"},
	{210, "[M:D1]Dojo"},
	{211, "[M:D1]Dojo"},
	{212, "[M:D1]Rescue Dungeon"},
	{213, "[M:D1]Base"},
	{214, "???"},
	{215, "Beach"},
	{216, "Unknown"},
	{217, "[M:D1]Bidoof"},
	{218, "[M:D1]Grovyle"},
	{219, "[M:D1]Celebi"},
	{220, "[M:D1]Chatot"},
	{221, "[M:D1]Cresselia"},
	{222, "[M:D1]Dummy"},
	{223, "[M:D1]Dummy"},
	{224, "[M:D1]Dummy"},
	{225, "[M:D1]Dummy"},
	{226, "[M:D1]Dummy"},
	{227, "[M:D1]Dummy"},
	{228, "[M:D1]Dummy"},
	{229, "[M:D1]Dummy"},
	{230, "[M:D1]Dummy"},
	{231, "[M:D1]Dummy"},
	{232, "[M:D1]Dummy"},
	{233, "[M:D1]Dummy"},
	{234, "[M:D1]Dummy"},
	{235, "[M:D1]Dummy"},
	{236, "[M:D1]Dummy"},
	{237, "[M:D1]Dummy"},
	{238, "[M:D1]Dummy"},
	{239, "[M:D1]Dummy"},
	{240, "[M:D1]Dummy"},
	{241, "[M:D1]Dummy"},
	{242, "[M:D1]Dummy"},
	{243, "[M:D1]Dummy"},
	{244, "[M:D1]Dummy"},
	{245, "[M:D1]Dummy"},
	{246, "[M:D1]Dummy"},
	{247, "Treasure Town"},
	{248, "Treasure Town"},
	{249, "[M:D1]Outside"},
	{250, "[M:D1]Client"},
	{251, "[M:D1]Dummy"},
	{252, "[M:D1]Dummy"},
	{253, "[M:D1]Dummy"},
	{254, "[M:D1]Dummy"},
	{255, "[M:D1]Dummy"}
};

int main () {
	ifstream arm9;
	arm9.open("arm9.bin", ios::binary);
	arm9.seekg(arm9datastart);

	struct arm9datastruct {
		string name;
		uint8_t floorCount;
		uint8_t mappa_s_data_index;
		uint8_t floorStartOffset;
		uint8_t totalDungeonGroupFloorCount;
		map<int, floor_properties> floors;
	};

	int totalFloorsInGame = 0;
	vector<arm9datastruct> arm9data;

	for (int i = 0; i<170; i++) {
		arm9datastruct data;
		data.floorCount = arm9.get();
		data.mappa_s_data_index = arm9.get();
		data.name = dungeonNames[i];
		data.floorStartOffset = arm9.get();
		data.totalDungeonGroupFloorCount = arm9.get();
		totalFloorsInGame += data.floorCount;
		arm9data.push_back(data);
	}

	arm9.close();
	cout << "Finished reading arm9 binary\n";
	cout << "Reading mappa_s binary\n";

	ifstream mappa;
	mappa.open("mappa_s.bin", ios::binary);
	mappa.seekg(mappafloordatastart);

	cout << "Creating mappa_s index\n";

	mappa.seekg(mappafloornumberstart);	//first floor number in data structs
	vector<uint32_t> mappaIndices;
	int addr = mappafloordatastart;
	int dungeons = 0;
	int floors = 0;
	while (true) {	//will read too much data, but it's ok since those locations shouldnt be indexed anyway
		if (mappa.peek() == 1) {	//check the floor count byte to find the start of a new dungeons data
			mappaIndices.push_back(addr);	//and remember the address to *the start* of that chunk of data
			dungeons++;
		}
		if (!mappa.good()) {
			break;
		} else { floors++; }
		addr += 32;
		mappa.seekg(32, ios::cur);
	}

	cout << "Found " << dungeons << " potential dungeons and " << floors << " potential floors\n";

	int curr = 0;
	for (auto& dungeon : arm9data) {
		if (dungeon.name == "Deep Concealed Ruins") { continue; } 	//these dungeons have no floor data, are not actually used or have other issues
		else if (dungeon.name == "Shaymin Village") { continue; }
		else if (dungeon.name == "Armaldo's Shelter") { continue; }
		else if (dungeon.name == "Luminous Spring") { continue; }
		else if (dungeon.name == "Hot Spring") { continue; }
		else if (dungeon.name == "Black Swamp") { continue; }
		else if (dungeon.name == "Little Plains") { continue; }
		else if (dungeon.name == "Mt. Clear") { continue; }
		else if (dungeon.name == "Challenge River") { continue; }
		else if (dungeon.name == "Trial Forest") { continue; }
		else if (dungeon.name == "[M:D1]Dummy") { continue; }

		if (dungeon.mappa_s_data_index >= 64 && dungeon.mappa_s_data_index != 80) {		//TODO: does this catch all the special cases?
			mappa.seekg(mappaIndices[dungeon.mappa_s_data_index -1] + (dungeon.floorStartOffset * 32));
		}
		else {
			mappa.seekg(mappaIndices[dungeon.mappa_s_data_index] + (dungeon.floorStartOffset * 32));
		}

		map<int, floor_properties> floorData;
		for (int i = 1; i <= dungeon.floorCount; i++) {
			floor_properties data;

			data.layout = static_cast<floor_layout>(mappa.get());
			data.room_density = static_cast<int8_t>(mappa.get());
			data.tileset = mappa.get();
			data.music_table_idx = mappa.get();
			data.weather = mappa.get();
			data.floor_connectivity = mappa.get();
			data.enemy_density = mappa.get();
			data.kecleon_shop_spawn_chance = mappa.get();
			data.monster_house_spawn_chance = mappa.get();
			data.maze_room_chance = mappa.get();
			data.sticky_item_chance = mappa.get();
			data.allow_dead_ends = static_cast<bool>(mappa.get());
			data.max_secondary_structures = mappa.get();
			uint8_t terrainBitflags = mappa.get();
			data.f_secondary_structures = (terrainBitflags & 0x1);
			//data.room_flags_unk1 = static_cast<uint8_t>((terrainBitflags >> 1) & 0x1);
			data.f_room_imperfections = (terrainBitflags & 0x8);
			//data.room_flags_unk3 = static_cast<uint8_t>((terrainBitflags>> 3) & 0x1F);
			data.field_0xe = mappa.get();
			data.item_density = mappa.get();
			data.trap_density = mappa.get();
			data.floor_number = mappa.get();
			if (data.floor_number != i + dungeon.floorStartOffset) {
				cout << "WARN expected floor " << i << " actual: " << static_cast<int>(data.floor_number) << " dungeon: " << dungeon.name << "\n";
				cout << mappaIndices[dungeon.mappa_s_data_index] + (dungeon.floorStartOffset * 32) << "\n";
			}
			data.fixed_room_id = mappa.get();
			data.extra_hallways = mappa.get();
			data.buried_item_density = mappa.get();
			data.secondary_terrain_density = mappa.get();
			data.visibility_range = mappa.get();
			data.max_money_amount_div_5 = mappa.get();
			data.shop_item_positions = mappa.get();
			data.itemless_monster_house_chance = mappa.get();
			data.hidden_stairs_type = mappa.get();
			data.hidden_stairs_spawn_chance = mappa.get();
			data.enemy_iq = static_cast<int16_t>((mappa.get() | mappa.get() << 8));
			data.iq_booster_value = static_cast<int16_t>((mappa.get() | mappa.get() << 8));
			
			floorData[i] = data;
			curr++;
		}
		dungeon.floors = floorData;

		if (dungeon.floorCount + dungeon.floorStartOffset == dungeon.totalDungeonGroupFloorCount) {
			mappa.seekg(17, ios::cur);
			if (mappa.peek() == dungeon.totalDungeonGroupFloorCount +1) {
				cout << "WARN " << dungeon.name << " appears to have more floors than were parsed\n";
			}
		}

	}




	::nlohmann::ordered_json j;

	int i = 0;
	for (auto& entry : arm9data) {
		if (entry.name == "Deep Concealed Ruins") { i++; continue; } 	//these dungeons have no floor data, are not actually used or have other issues
		else if (entry.name == "Shaymin Village") { i++; continue; }
		else if (entry.name == "Armaldo's Shelter") { i++; continue; }
		else if (entry.name == "Luminous Spring") { i++; continue; }
		else if (entry.name == "Hot Spring") { i++; continue; }
		else if (entry.name == "Black Swamp") { i++; continue; }
		else if (entry.name == "Little Plains") { i++; continue; }
		else if (entry.name == "Mt. Clear") { i++; continue; }
		else if (entry.name == "Challenge River") { i++; continue; }
		else if (entry.name == "Trial Forest") { i++; continue; }
		else if (entry.name == "[M:D1]Dummy") { i++; continue; }
		j[i]["name"]["en"] = entry.name;
		j[i]["floorCount"] = entry.floorCount;
		j[i]["dungeonGroupID"] = entry.mappa_s_data_index;
		j[i]["dungeonID"] = i;
		j[i]["floorStartOffset"] = entry.floorStartOffset;
		j[i]["totalDungeonGroupFloorCount"] = entry.totalDungeonGroupFloorCount;

		for (int f = 1; f <= entry.floorCount; f++) {
		    j[i]["floors"][to_string(f)]["layout"] = entry.floors[f].layout;
		    j[i]["floors"][to_string(f)]["room_density"] = entry.floors[f].room_density;
		    j[i]["floors"][to_string(f)]["tileset"] = entry.floors[f].tileset;
		    j[i]["floors"][to_string(f)]["music_table_idx"] = entry.floors[f].music_table_idx;
		    j[i]["floors"][to_string(f)]["weather"] = entry.floors[f].weather;
		    j[i]["floors"][to_string(f)]["floor_connectivity"] = entry.floors[f].floor_connectivity;
		    j[i]["floors"][to_string(f)]["enemy_density"] = entry.floors[f].enemy_density;
		    j[i]["floors"][to_string(f)]["kecleon_shop_spawn_chance"] = entry.floors[f].kecleon_shop_spawn_chance;
		    j[i]["floors"][to_string(f)]["monster_house_spawn_chance"] = entry.floors[f].monster_house_spawn_chance;
		    j[i]["floors"][to_string(f)]["maze_room_chance"] = entry.floors[f].maze_room_chance;
		    j[i]["floors"][to_string(f)]["sticky_item_chance"] = entry.floors[f].sticky_item_chance;
		    j[i]["floors"][to_string(f)]["allow_dead_ends"] = entry.floors[f].allow_dead_ends;
		    j[i]["floors"][to_string(f)]["max_secondary_structures"] = entry.floors[f].max_secondary_structures;
		    j[i]["floors"][to_string(f)]["f_secondary_structures"] = entry.floors[f].f_secondary_structures;
		    //j[i]["floors"][f]["room_flags_unk1"] = entry.floors[f].room_flags_unk1;
		    j[i]["floors"][to_string(f)]["f_room_imperfections"] = entry.floors[f].f_room_imperfections;
		    //j[i]["floors"][to_string(f)]["room_flags_unk3"] = entry.floors[f].room_flags_unk3;
		    //j[i]["floors"][to_string(f)]["field_0xe"] = entry.floors[f].field_0xe;
		    j[i]["floors"][to_string(f)]["item_density"] = entry.floors[f].item_density;
		    j[i]["floors"][to_string(f)]["trap_density"] = entry.floors[f].trap_density;
		    j[i]["floors"][to_string(f)]["floor_number"] = entry.floors[f].floor_number;
		    j[i]["floors"][to_string(f)]["fixed_room_id"] = entry.floors[f].fixed_room_id;
		    j[i]["floors"][to_string(f)]["extra_hallways"] = entry.floors[f].extra_hallways;
		    j[i]["floors"][to_string(f)]["buried_item_density"] = entry.floors[f].buried_item_density;
		    j[i]["floors"][to_string(f)]["secondary_terrain_density"] = entry.floors[f].secondary_terrain_density;
		    j[i]["floors"][to_string(f)]["visibility_range"] = entry.floors[f].visibility_range;
		    j[i]["floors"][to_string(f)]["max_money_amount_div_5"] = entry.floors[f].max_money_amount_div_5;
		    j[i]["floors"][to_string(f)]["shop_item_positions"] = entry.floors[f].shop_item_positions;
		    j[i]["floors"][to_string(f)]["itemless_monster_house_chance"] = entry.floors[f].itemless_monster_house_chance;
		    j[i]["floors"][to_string(f)]["hidden_stairs_type"] = entry.floors[f].hidden_stairs_type;
		    j[i]["floors"][to_string(f)]["hidden_stairs_spawn_chance"] = entry.floors[f].hidden_stairs_spawn_chance;
		    j[i]["floors"][to_string(f)]["enemy_iq"] = entry.floors[f].enemy_iq;
		    j[i]["floors"][to_string(f)]["iq_booster_value"] = entry.floors[f].iq_booster_value;
			j[i]["floors"][to_string(f)]["has_guaranteed_item"] = false;	//TODO: get a list of all floors with a guaranteed item spawn
			j[i]["floors"][to_string(f)]["nonstory_flag"] = false;	//TODO: get a list dungeons with this flag set

		}
		i++;
	}


	ofstream json ("PMD_Sky_dungeon_data.json");
	json << j.dump(1, ' ') << endl;
	cout << "Wrote JSON to file.\n";
	json.close();
	return 0;
}


































































































