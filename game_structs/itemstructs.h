#pragma once
#include "guistructs.h"

enum class ItemType : int
{
	Dagger = 1 << 0,
	Crowbar = 1 << 1,
	Whip = 1 << 2,
	BanditSword = 1 << 3,
	Katana = 1 << 4,
	Fists = 1 << 5,
	Axe = 1 << 6,
	BeamSword = 1 << 7,
	Rapier = 1 << 8,
	Unk0 = 1 << 9,
	Handgun = 1 << 10,
	Shotgun = 1 << 11,
	SMG = 1 << 12,
	Slingshot = 1 << 13,
	AssaultRifle = 1 << 14,
	Revolver = 1 << 15,
	GrenadeLauncher = 1 << 16,
	LaserGun = 1 << 17,
	Winchester = 1 << 18,
	Unk1 = 1 << 19,
	Protector = 1 << 20,
	Accessory = 1 << 21,
	Consumable = 1 << 22,
	Key = 1 << 23,
	Treasure = 1 << 24,
	SkillCard = 1 << 25,
	Outfit = 1 << 26,
	Tool = 1 << 27,
	Material = 1 << 28,
	Essential = 1 << 29,
	Unk2 = 1 << 30,
	Unk3 = 1 << 31 
};

template<>
struct magic_enum::customize::enum_range<ItemType>
{
	static constexpr bool is_flags = true;
};

enum class EquippableUser : int
{
    Anyone = 1 << 0,
	Joker = 1 << 1,
	Ryuji = 1 << 2,
	Morgana = 1 << 3,
	Ann = 1 << 4,
	Yusuke = 1 << 5,
	Makoto = 1 << 6,
	Haru = 1 << 7,
	Futaba = 1 << 8,
	Akechi = 1 << 9,
	Kasumi = 1 << 10
};

template<>
struct magic_enum::customize::enum_range<EquippableUser>
{
	static constexpr bool is_flags = true;
};

enum class ShowInShop : uint16_t
{
	ShowInShop,
	DontShowInShop,
	Unk0 = 3,
	Unk1 = 12
};

struct ItemStatBoost
{
	uint8_t strength;
	uint8_t magic;
	uint8_t endurance;
	uint8_t agility;
	uint8_t luck;
};
IMGUI_REFLECT(ItemStatBoost, strength, magic, endurance, agility, luck);

enum class GearEffect : uint16_t
{
    NoGearEffect = 0,
    Plus10HP = 1,
    Plus20HP = 2,
    Plus30HP = 3,
    Plus40HP = 4,
    Plus50HP = 5,
    Plus100HP = 6,
    Plus10SP = 7,
    Plus20SP = 8,
    Plus30SP = 9,
    Plus40SP = 10,
    Plus50SP = 11,
    Plus100SP = 12,
    BurnLow = 13,
    BurnMedium = 14,
    BurnHigh = 15,
    FreezeLow = 16,
    FreezeMedium = 17,
    FreezeHigh = 18,
    ShockLow = 19,
    ShockMedium = 20,
    ShockHigh = 21,
    DizzyLow = 22,
    DizzyMedium = 23,
    DizzyHigh = 24,
    ConfuseLow = 25,
    ConfuseMedium = 26,
    ConfuseHigh = 27,
    FearLow = 28,
    FearMedium = 29,
    FearHigh = 30,
    ForgetLow = 31,
    ForgetMedium = 32,
    ForgetHigh = 33,
    BrainwashLow = 34,
    BrainwashMedium = 35,
    BrainwashHigh = 36,
    SleepLow = 37,
    SleepMedium = 38,
    SleepHigh = 39,
    RageLow = 40,
    RageMedium = 41,
    RageHigh = 42,
    DespairLow = 43,
    DespairMedium = 44,
    DespairHigh = 45,
    RandomAilmentLow = 46,
    RandomAilmentMedium = 47,
    RandomAilmentHigh = 48,
    CritRateUpLow = 49,
    CritRateUpMedium = 50,
    CritRateUpHigh = 51,
    FireAttacksUp = 52,
    IceAttacksUp = 53,
    ElectricAttacksUp = 54,
    WindAttacksUp = 55,
    NukeAttacksUp = 56,
    PsyAttacksUp = 57,
    BlessAttacksUp = 58,
    CurseAttacksUp = 59,
    RepelPhysicalLow = 60,
    RepelPhysicalMedium = 61,
    RepelPhysicalHigh = 62,
    ResistBurn_Gear = 63,
    ResistFreeze_Gear = 64,
    ResistShock_Gear = 65,
    ResistDizzy_Gear = 66,
    ResistConfuse_Gear = 67,
    ResistFear_Gear = 68,
    ResistForget_Gear = 69,
    ResistHunger_Gear = 70,
    ResistSleep_Gear = 71,
    ResistRage_Gear = 72,
    ResistDespair_Gear = 73,
    ResistMouse_Gear = 74,
    ResistBrainwash_Gear = 75,
    AutoTarukaja = 76,
    AutoRakukaja = 77,
    AutoSukukaja = 78,
    ReducePhysicalDamageLow = 79,
    ReducePhysicalDamageMedium = 80,
    ReducePhysicalDamageHigh = 81,
    ReduceFireDamageLow = 82,
    ReduceFireDamageMedium = 83,
    ReduceFireDamageHigh = 84,
    ReduceIceDamageLow = 85,
    ReduceIceDamageMedium = 86,
    ReduceIceDamageHigh = 87,
    ReduceElectricDamageLow = 88,
    ReduceElectricDamageMedium = 89,
    ReduceElectricDamageHigh = 90,
    ReduceWindDamageLow = 91,
    ReduceWindDamageMedium = 92,
    ReduceWindDamageHigh = 93,
    ReduceNukeDamageLow = 94,
    ReduceNukeDamageMedium = 95,
    ReduceNukeDamageHigh = 96,
    ReducePsyDamageLow = 97,
    ReducePsyDamageMedium = 98,
    ReducePsyDamageHigh = 99,
    ReduceBlessDamageLow = 100,
    ReduceBlessDamageMedium = 101,
    ReduceBlessDamageHigh = 102,
    ReduceCurseDamageLow = 103,
    ReduceCurseDamageMedium = 104,
    ReduceCurseDamageHigh = 105,
    ReduceMagicDamageLow = 106,
    ReduceMagicDamageMedium = 107,
    ReduceMagicDamageHigh = 108,
    EvadePhysicalLow = 109,
    EvadePhysicalMedium = 110,
    EvadePhysicalHigh = 111,
    EvadeFireLow = 112,
    EvadeFireMedium = 113,
    EvadeFireHigh = 114,
    EvadeIceLow = 115,
    EvadeIceMedium = 116,
    EvadeIceHigh = 117,
    EvadeElectricLow = 118,
    EvadeElectricMedium = 119,
    EvadeElectricHigh = 120,
    EvadeWindLow = 121,
    EvadeWindMedium = 122,
    EvadeWindHigh = 123,
    EvadeNukeLow = 124,
    EvadeNukeMedium = 125,
    EvadeNukeHigh = 126,
    EvadePsyLow = 127,
    EvadePsyMedium = 128,
    EvadePsyHigh = 129,
    EvadeBlessLow = 130,
    EvadeBlessMedium = 131,
    EvadeBlessHigh = 132,
    EvadeCurseLow = 133,
    EvadeCurseMedium = 134,
    EvadeCurseHigh = 135,
    EvadeMagicLow = 136,
    EvadeMagicMedium = 137,
    EvadeMagicHigh = 138,
    Plus50PercentEXP = 139,
    FireAttacksUpStackable = 140,
    IceAttacksUpStackable = 141,
    WindAttacksUpStackable = 142,
    ElectricAttacksUpStackable = 143,
    ResistFire_Gear = 144,
    ResistIce_Gear = 145,
    ResistWind_Gear = 146,
    ResistElectric_Gear = 147,
    NukeAttacksUpStackable = 148,
    PsyAttacksUpStackable = 149,
    BlessAttacksUpStackable = 150,
    CurseAttacksUpStackable = 151,
    ResistNuke_Gear = 152,
    ResistPsy_Gear = 153,
    ResistBless_Gear = 154,
    ResistCurse_Gear = 155,
    StrongerWhenEnraged = 156,
    DecreaseEnemySightRange = 157,
    IncreaseEnemyAlertTime = 158,
    DecreaseEnemyAlertTime = 159,
    Plus1Clip = 160,
    Plus2Clips = 161,
    Plus3Clips = 162,
    NullBurn_Gear = 163,
    NullFreeze_Gear = 164,
    NullShock_Gear = 165,
    NullDizzy_Gear = 166,
    NullConfuse_Gear = 167,
    NullFear_Gear = 168,
    NullForget_Gear = 169,
    NullHunger_Gear = 170,
    NullSleep_Gear = 171,
    NullRage_Gear = 172,
    NullDespair_Gear = 173,
    NullMouse_Gear = 174,
    NullBrainwash_Gear = 175,
    Regenerate1_Gear = 176,
    Regenerate2_Gear = 177,
    Regenerate3_Gear = 178,
    Invigorate1_Gear = 179,
    Invigorate2_Gear = 180,
    Invigorate3_Gear = 181,
    PreventBlessInstakill = 182,
    PreventCurseInstakill = 183,
    HalfEnemyAccuracy = 184,
    NullAllExceptAlmighty = 185,
    HalfDamageNoEvasion = 186,
    PlusEXPFromBattles = 192,
    PlusMoneyFromBattles = 193,
    TargetedChanceDown = 194,
    NullBlessCurse2 = 195,
    AllOutAttackPowerUp = 197,
    Plus1BulletAfterBattle = 198,
    CritRateUpEvadeMagic = 199,
    LowerSkillCost25Percent = 200,
    ReduceStatusAilment50Percent = 201
};

template<>
struct magic_enum::customize::enum_range<GearEffect>
{
    static constexpr uint32_t min = 0;
    static constexpr uint32_t max = 201;
};

enum class Month : uint8_t
{
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12,
};

struct AccessoryItem
{
    static constexpr int ACCESSORY_SIZE = 512;
    static void SwapData(std::array<AccessoryItem, ACCESSORY_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(AccessoryItem))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            for (int j = 0; j < 12; j += 4)
            {
                uint32_t* bit32Swap = (uint32_t*)(byteBase + j);
                *bit32Swap = _byteswap_ulong(*bit32Swap);
            }

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 12);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x14);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x16);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)((byteBase + 0x18));
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1a);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1c);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            uint32_t* bit32Swap = (uint32_t*)(byteBase + 0x20);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
            bit32Swap = (uint32_t*)(byteBase + 0x24);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
            bit32Swap = (uint32_t*)(byteBase + 0x2c);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
            bit32Swap = (uint32_t*)(byteBase + 0x30);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
            bit32Swap = (uint32_t*)(byteBase + 0x34);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
            bit32Swap = (uint32_t*)(byteBase + 0x38);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
            bit32Swap = (uint32_t*)(byteBase + 0x3c);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
        }
    }

	ItemType icon;
    uint16_t shopMenuSort;
	uint16_t fieldMenuSort;
	EquippableUser equippableUser;
    
    ShowInShop showInShop;
	ItemStatBoost statBoosts;
	uint8_t RESERVE;
    std::array<GearEffect, 3> gearEffects;
    uint16_t level;
    uint16_t value;
    uint16_t RESERVE2;
    uint32_t price;
    uint32_t sellPrice;
    Month monthAvailable;
    uint8_t dayAvailable;
    uint8_t RESERVE3;
    std::array<uint32_t, 5> materials;
};
IMGUI_REFLECT(AccessoryItem, icon, fieldMenuSort, shopMenuSort, equippableUser, showInShop, statBoosts, RESERVE, gearEffects, level, value, RESERVE2, price,
    sellPrice, monthAvailable, dayAvailable, RESERVE3, materials);

struct Armor
{
    static constexpr int ARMOR_SIZE = 301;
    static void SwapBytes(std::array<Armor, ARMOR_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(Armor))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x8);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0xc);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xe);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x10);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x18);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1a);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1c);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1e);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x20);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x24);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x28);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x2e);
            *bit16Swap = _byteswap_ushort(*bit16Swap);
        }
    }

    ItemType icon;
    uint16_t weaponShopSort;
    uint16_t weaponMenuSort;
    EquippableUser equippableUser;
    ShowInShop showInShop;
    uint16_t defense;
    uint16_t evasion;
    ItemStatBoost statBoosts;
    uint8_t RESERVE;
    std::array<GearEffect, 3> gearEffects;
    uint16_t level;
    uint16_t value;
    uint16_t RESERVE2;
    uint32_t price;
    uint32_t sellPrice;
    Month monthAvailable;
    uint8_t dayAvailable;
    uint16_t unk;
};
IMGUI_REFLECT(Armor, icon, weaponMenuSort, weaponShopSort, equippableUser, defense, evasion, showInShop, statBoosts, RESERVE, gearEffects, level, value,
    RESERVE2, price, sellPrice, monthAvailable, dayAvailable, unk);

enum class Usage : short
{
    NotUsable = 0,
    UsableinBattle = 1,
    UsableinField = 2,
    UsableinBattleandField = 3,
    FishBait = 4,
    Book = 10,
    DVD = 18,
    CD = 34,
    Gift = 66,
    Lunch = 130,
    EssentialsMisc = 258,
    RetroGame = 514,
    Incense = 1024
};

struct SkillID
{
    uint16_t skillID;
};
IMGUI_REFLECT(SkillID, skillID);

struct Consumable
{
    static constexpr int CONSUMABLE_SIZE = 696;
    static void SwapBytes(std::array<Consumable, CONSUMABLE_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(Consumable))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0x8);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xa);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xc);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x10);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x14);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x1c);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x20);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x24);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x28);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x2c);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
        }
    }

    ItemType icon;
    uint32_t menuSort;
    uint16_t flags;
    Usage usage;
    SkillID skill;
    uint16_t RESERVE;
    uint32_t price;
    uint32_t sellPrice;
    Month monthAvailable;
    uint8_t dayAvailable;
    uint16_t RESERVE2;
    std::array<uint32_t, 5> materials;
};
IMGUI_REFLECT(Consumable, icon, menuSort, flags, usage, skill, RESERVE, price, sellPrice, monthAvailable, dayAvailable, RESERVE2, materials);

struct KeyItem
{
    static constexpr int KEY_ITEM_SIZE = 256;
    static void SwapBytes(std::array<KeyItem, KEY_ITEM_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(KeyItem))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0x8);
            *bit16Swap = _byteswap_ushort(*bit16Swap);
        }
    }

    ItemType icon;
    uint32_t menuSorting;
    uint16_t flags;
    uint16_t RESERVE;
};
IMGUI_REFLECT(KeyItem, icon, menuSorting, flags, RESERVE);

struct Treasure
{
    static constexpr int TREASURE_SIZE = 256;
    static void SwapBytes(std::array<Treasure, TREASURE_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(Treasure))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0x8);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xa);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit32Swap = (uint32_t*)(byteBase + 0xc);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x10);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x18);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x1c);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x20);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x24);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x28);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
        }
    }

    ItemType icon;
    uint32_t menuSorting;
    uint16_t flags;
    uint16_t value;
    uint32_t price;
    uint32_t sellPrice;
    Month monthAvailable;
    uint8_t dayAvailable;
    uint16_t RESERVE;
    std::array<uint32_t, 5> materials;
};
IMGUI_REFLECT(Treasure, icon, menuSorting, flags, value, price, sellPrice, monthAvailable, dayAvailable, RESERVE, materials);

struct Melee
{
    static constexpr int MELEE_SIZE = 296;
    static void SwapBytes(std::array<Melee, MELEE_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(Melee))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x8);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0xc);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x10);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x12);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1a);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1c);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1e);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x20);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x22);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x24);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x28);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x2e);
            *bit16Swap = _byteswap_ushort(*bit16Swap);
        }
    }

    ItemType icon;
    uint16_t shopSort;
    uint16_t fieldSort;
    EquippableUser users;
    
    ShowInShop showInShop;
    uint16_t RESERVE;
    uint16_t attack;
    uint16_t accuracy;
    ItemStatBoost statBoost;
    uint8_t RESERVE2;
    std::array<GearEffect, 3> gearEffects;
    uint16_t level;
    uint16_t value;
    uint32_t price;
    uint32_t sellPrice;
    Month monthAvailable;
    uint8_t dayAvailable;
    uint16_t unk;
};
IMGUI_REFLECT(Melee,icon, fieldSort, shopSort, users, showInShop, RESERVE, attack, accuracy, statBoost, RESERVE2, gearEffects, level, value, price, 
    sellPrice, monthAvailable, dayAvailable, unk);

struct Outfit
{
    static constexpr int OUTFIT_SIZE = 286;
    static void SwapBytes(std::array<Outfit, OUTFIT_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(Outfit))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x8);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0xc);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xe);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x10);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x12);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x14);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x18);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
        }
    }

    ItemType icon;
    uint16_t shopSort;
    uint16_t fieldSort;
    EquippableUser users;
    
    std::array<GearEffect, 3> gearEffects;
    uint32_t price;
    uint32_t sellPrice;
    Month monthAvailable;
    uint8_t dayAvailable;
    uint16_t RESERVE;
};
IMGUI_REFLECT(Outfit, icon, fieldSort, shopSort, users, gearEffects, price, sellPrice, monthAvailable, dayAvailable, RESERVE);

struct SkillCard
{
    static constexpr int SKILL_CARD_SIZE = 651;
    static void SwapBytes(std::array<SkillCard, SKILL_CARD_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(SkillCard))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0x8);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xa);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xc);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0xe);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x10);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x14);
            *bit32Swap = _byteswap_ulong(*bit32Swap);
        }
    }

    ItemType icon;
    uint32_t menuSort;
    uint16_t flags;
    SkillID skill;
    uint16_t level;
    uint16_t value;
    uint32_t price;
    uint32_t sellPrice;
};
IMGUI_REFLECT(SkillCard, icon, menuSort, flags, skill, level, value, price, sellPrice);

enum class ElementalType : uint8_t
{
    Passive = 255,
    Physical = 0,
    Gun = 1,
    Fire = 2,
    Ice = 3,
    Electric = 4,
    Wind = 5,
    Psy = 6,
    Nuke = 7,
    Bless = 8,
    Curse = 9,
    Almighty = 10,
    Dizzy = 11,
    Confuse = 12,
    Fear = 13,
    Forget = 14,
    Hunger = 15,
    Sleep = 16,
    Rage = 17,
    Despair = 18,
    Brainwash = 19,
    Healing = 20,
    Support = 21,
    Unknown_ForEnemySupport = 22
};

enum GunUpgradable : uint16_t
{
    NotUpgradable,
    Upgradable
};

struct GunEnhancement
{
    GunUpgradable isUpgradable;
    uint16_t extraAttack;
    uint16_t extraAccuracy;
    uint16_t extraRounds;
    GearEffect extraEffect;
};
IMGUI_REFLECT(GunEnhancement, isUpgradable, extraAttack, extraAccuracy, extraRounds, extraEffect);

struct RangedWeapon
{
    static constexpr int RANGED_SIZE = 256;
    static void SwapBytes(std::array<RangedWeapon, RANGED_SIZE>* arr)
    {
        for (int i = 0; i < sizeof(*arr); i += sizeof(RangedWeapon))
        {
            DWORD_PTR byteBase = (DWORD_PTR)arr + i;

            uint32_t* bit32Swap = (uint32_t*)byteBase;
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x4);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x8);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            uint16_t* bit16Swap = (uint16_t*)(byteBase + 0xc);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x10);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x12);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x14);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1c);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x1e);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x20);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x22);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit16Swap = (uint16_t*)(byteBase + 0x24);
            *bit16Swap = _byteswap_ushort(*bit16Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x28);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            bit32Swap = (uint32_t*)(byteBase + 0x2c);
            *bit32Swap = _byteswap_ulong(*bit32Swap);

            DWORD_PTR byteBase2 = (DWORD_PTR)(byteBase + 0x34);
            for (int j = 2; j != 0; j--)
            {
                byteBase2 = (DWORD_PTR)byteBase2 + 0x28;

                bit16Swap = (uint16_t*)byteBase2 - 0x2a;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x28;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x26;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x24;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x22;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x20;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x1e;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x1c;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x1a;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x18;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x16;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x14;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x12;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x10;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0xe;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0xc;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0xa;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x8;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x6;
                *bit16Swap = _byteswap_ushort(*bit16Swap);

                bit16Swap = (uint16_t*)byteBase2 - 0x4;
                *bit16Swap = _byteswap_ushort(*bit16Swap);
            }
        }
    }

    ItemType icon;
    uint16_t shopSort;
    uint16_t fieldSort;
    EquippableUser users;
    
    ShowInShop showInShop;
    ElementalType element;
    uint8_t RESERVE;
    uint16_t attack;
    uint16_t accuracy;
    uint16_t rounds;
    ItemStatBoost statBoost;
    uint8_t RESERVE2;
    std::array<GearEffect, 3> gearEffects;
    uint16_t field22;
    uint16_t iwaiUpgradeRank;
    uint16_t RESERVE3;
    uint32_t price;
    uint32_t sellPrice;
    Month monthAvailable;
    uint8_t dayAvailable;
    GunEnhancement longBarrel;
    GunEnhancement gigaBarrel;
    GunEnhancement powerReceiver;
    GunEnhancement highPowerReceiver;
    GunEnhancement megaPowerReceiver;
    GunEnhancement fireCamo;
    GunEnhancement electricCamo;
    GunEnhancement iceCamo;
    uint16_t RESERVE4;
};
IMGUI_REFLECT(RangedWeapon, icon, fieldSort, shopSort, users, showInShop, RESERVE, attack, accuracy, rounds, statBoost, RESERVE2, gearEffects,
    field22, iwaiUpgradeRank, RESERVE3, price, sellPrice, monthAvailable, dayAvailable, longBarrel, gigaBarrel, powerReceiver, 
    highPowerReceiver, megaPowerReceiver, fireCamo, electricCamo, iceCamo, RESERVE4);