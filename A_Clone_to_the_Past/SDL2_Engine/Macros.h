// Alle

#pragma once
#include <iostream>

// numbers
#define UNIT 64
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Files
#define F_MUSIC_FARM	GetAssetPath("Sound/Music/M_Farm.wav", 5).c_str()
#define F_MUSIC_TOWN	GetAssetPath("Sound/Music/M_Town.wav", 5).c_str()
#define F_MUSIC_FOREST	GetAssetPath("Sound/Music/M_Forest.wav", 5).c_str()

#define F_PLAYER		GetAssetPath("Texture/Character/T_Character.png", 5).c_str()
#define F_ENEMY			GetAssetPath("Texture/Character/T_Wolf.png", 5).c_str()
#define F_PIGSEL		GetAssetPath("Texture/Character/T_Pigsel.png", 5).c_str()
#define F_HEALTHBAR		GetAssetPath("Texture/Character/T_HealthBar.png", 5).c_str()
#define F_RUNBAR		GetAssetPath("Texture/Character/T_RunBar.png", 5).c_str()
#define F_FOOT			GetAssetPath("Texture/Character/T_Foot.png", 5).c_str()
#define F_PIXEL_FONT	GetAssetPath("Texture/Font/T_Pixel.ttf", 5).c_str()
#define F_STAMINAPOTION GetAssetPath("Texture/Items/T_Stamina_Potion.png", 5).c_str()
#define F_HEALTHPOTION	GetAssetPath("Texture/Items/T_Health_Potion.png", 5).c_str()
#define F_CHEST			GetAssetPath("Texture/Objects/T_Chest.png", 5).c_str()
#define F_TOOLTIP		GetAssetPath("Texture/UI/T_Tooltip.png", 5).c_str()
#define F_ATLASMAP		GetAssetPath("Texture/World/T_Atlas.png", 5).c_str()
#define F_WORLD			GetAssetPath("Texture/World/T_World.bmp", 5).c_str()
#define F_GOLD			GetAssetPath("Texture/UI/T_Gold.png", 5).c_str()	

// tags
#define PLAYER "Player"
#define ENEMY "Enemy"
#define CHEST "Chest"
#define FOLLOWENTITY "FollowEntity"
#define PICKUP "Pickup"

// console
#define LOG(TEXT) std::cout << TEXT << std::endl;