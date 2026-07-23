#pragma once
#include "guistructs.h"

enum class BuffStatus : uint32_t
{
	ATK = 1 << 0,
	ACC = 1 << 1,
	DEF = 1 << 2,
	EVA = 1 << 3,
	Crit = 1 << 4,
	Crit2 = 1 << 5,
	AilmentSusceptability = 1 << 6,
	AffFire = 1 << 7,
	AffIce = 1 << 8,
	AffWind = 1 << 9,
	AffElec = 1 << 10,
	AffNuke = 1 << 11,
	AffPsy = 1 << 12,
	ResistFire = 1 << 13,
	ResistIce = 1 << 14,
	ResistElec = 1 << 15,
	ResistWind = 1 << 16,
	ResistNuke = 1 << 17,
	ResistPsy = 1 << 18,
	bit19 = 1 << 19,
	ResistPhys = 1 << 20,
	ResistMagic = 1 << 21,
	Charge = 1 << 22,
	Concentrate = 1 << 23,
	bit24 = 1 << 24,
	bit25 = 1 << 25,
	ResistInstakill = 1 << 26,
	bit27 = 1 << 27,
	bit28 = 1 << 28,
	bit29 = 1 << 29,
	bit30 = 1 << 30,
	bit31 = 1 << 31
};

template<>
struct magic_enum::customize::enum_range<BuffStatus>
{
	static constexpr uint32_t min = 0;
	static constexpr uint32_t max = 32;
	static constexpr bool is_flags = true;
};

struct BuffMeta
{
	union
	{ 
		uint64_t bitfield0;
		uint64_t bitfield1;
		struct
		{
			uint32_t BuffDir_ACC : 4;
			uint32_t BuffDir_ATK : 4;
			uint32_t BuffDir_EVA : 4;
			uint32_t BuffDir_DEF : 4;
			uint32_t BuffDir_CRIT : 4;
			uint32_t BuffDir_CRIT2 : 4;
			uint32_t BuffDir_Suscep : 4;
			uint32_t BuffDir_AffFire : 4;
			uint32_t BuffDir_AffIce : 4;
			uint32_t BuffDir_AffWind : 4;
			uint32_t BuffDir_AffElec : 4;
			uint32_t BuffDir_AffNuke : 4;
			uint32_t BuffDir_AffPsy : 4;
			uint32_t BuffDir_ResistFire : 4;
			uint32_t BuffDir_ResistIce : 4;
			uint32_t BuffDir_ResistElec : 4;
			uint32_t BuffDir_ResistWind : 4;
			uint32_t BuffDir_ResistPsy : 4;
			uint32_t BuffDir_ : 4;
			uint32_t BuffDir_ACC2 : 4;
			uint32_t BuffDir_ATK2 : 4;
			uint32_t BuffDir_EVA2 : 4;
			uint32_t BuffDir_DEF2 : 4;
			uint32_t BuffDir_CRIT3 : 4;
			uint32_t BuffDir_CRIT4 : 4;
			uint32_t BuffDir_Suscep2 : 4;
			uint32_t BuffDir_AffFire2 : 4;
			uint32_t BuffDir_AffIce2 : 4;
			uint32_t BuffDir_AffWind2 : 4;
//			uint32_t BuffDir_AffElec2 : 4;
//			uint32_t BuffDir_AffNuke2 : 4;
//			uint32_t BuffDir_AffPsy2 : 4;
//			uint32_t BuffDir_ResistFire2 : 4;
//			uint32_t BuffDir_ResistIce2 : 4;
//			uint32_t BuffDir_ResistElec2 : 4;
//			uint32_t BuffDir_ResistWind2 : 4;
//			uint32_t BuffDir_ResistNuke2 : 4;
//			uint32_t BuffDir_ResistPsy2 : 4;
//			uint32_t BuffDir_2 : 4;
		};
	};
};

IMGUI_REFLECT(BuffMeta, bitfield0,bitfield1);

struct DatUnit_Skills
{
	std::array<uint16_t,8> skill;
};

IMGUI_REFLECT(DatUnit_Skills,skill);

struct PersonaID
{
	uint16_t id;

	operator uint16_t()
	{
		return id;
	}
};

IMGUI_REFLECT(PersonaID, id);

struct DatUnit_Stats
{
	uint8_t strength;
	uint8_t magic;
	uint8_t endurance;
	uint8_t agility;
	uint8_t luck;
};

IMGUI_REFLECT(DatUnit_Stats, strength, magic, endurance, agility, luck);

#pragma pack(push,4)
struct DatUnit_Persona
{
	BYTE personaFlags;
	bool isUnlocked;
	PersonaID personaID;
	uint8_t personaLevel;
	BYTE _x5;
	uint16_t trait;
	uint32_t personaEXP;
	DatUnit_Skills SkillIDs;
	DatUnit_Stats Stats;
	std::array<uint8_t,5> StatsEx;
	std::array<uint8_t,5> StatsExTemp;
	uint8_t _x2B;
	uint32_t _x2C;
};
#pragma pack(pop)

IMGUI_REFLECT(DatUnit_Persona, personaFlags, isUnlocked, personaID, personaLevel,_x5, trait, personaEXP,SkillIDs,Stats,StatsEx,StatsExTemp,_x2B, _x2C);

#pragma pack(push,1)
struct DatUnit
{
	int32_t flags;
	uint16_t unitType;
	uint16_t Field06;
	uint32_t unitID;
	uint32_t hp;
	uint32_t sp;
	int32_t status;
	uint16_t level;
	uint16_t Field1A;
	uint32_t exp;
	uint32_t phaseID;
	BuffStatus Buffs;
	uint32_t BuffStatus2;
	BuffMeta BuffDuration;
	uint16_t equippedPersona;
	uint16_t Field42;
	uint32_t unk;
	DatUnit_Persona StockPersonas[12];
	uint16_t meleeID;
	uint16_t protectorID;
	uint16_t accessoryID;
	uint16_t outfitID;
	uint16_t rangedWeapon;
	uint16_t Field28E;
	uint16_t Field290;
	uint16_t tactics;
	uint16_t bullets;
	uint32_t Field296;
	uint16_t Field29A;
	uint16_t HPGainOnNextLevel;
	uint16_t SPGainOnNextLevel;
};
#pragma pack(pop)

IMGUI_REFLECT
(DatUnit, flags, unitType, Field06, unitID, hp, sp, status, level, Field1A, exp, phaseID, equippedPersona, Field42,
	meleeID, protectorID, accessoryID, rangedWeapon, Field28E, Field290, tactics, bullets, Field296, Field29A, HPGainOnNextLevel, SPGainOnNextLevel);