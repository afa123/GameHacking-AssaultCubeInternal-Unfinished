#include "Player.h"

#pragma region OFFSETS
const int PLAYER_HEALTH_OFFSET = 0xF8;
const int PLAYER_ARMOR_OFFSET = 0xFC;
const int PLAYER_POSITION_OFFSET = 0x34;
const int PLAYER_NAME_OFFSET = 0x225;
const int PLAYER_TEAM_OFFSET = 0x32C;
const int PLAYER_CAMERA_OFFSET = 0x40;
const int PLAYER_HEAD_POSITION_OFFSET = 0x4;

const int PLAYER_ENTITY_OFFSET = 0x10F4F4;
#pragma endregion

#pragma region VARIABLES
uintptr_t baseModule = NULL;
uintptr_t baseAddress = NULL;

int* health = nullptr;
int* armor = nullptr;
int* team = nullptr;
float* playerPosition = nullptr;
float* playerHeadPosition = nullptr;
float* cameraPosition = nullptr;
char* name = nullptr;
#pragma endregion

Player::Player()
{
	baseModule = (uintptr_t)GetModuleHandle(NULL);
	baseAddress = *(int *)((DWORD)baseModule + PLAYER_ENTITY_OFFSET);
	initialize();
}

Player::Player(uintptr_t a_baseAddress)
{
	baseAddress = a_baseAddress;
	initialize();
}

Player::~Player()
{
}

void Player::initialize()
{
	health = (int*)(baseAddress + PLAYER_HEALTH_OFFSET);
	armor = (int*)(baseAddress + PLAYER_ARMOR_OFFSET);
	team = (int*)(baseAddress + PLAYER_TEAM_OFFSET);
	playerPosition = (float*)(baseAddress + PLAYER_POSITION_OFFSET);
	playerHeadPosition = (float*)(baseAddress + PLAYER_HEAD_POSITION_OFFSET);
	cameraPosition = (float*)(baseAddress + PLAYER_CAMERA_OFFSET);
	name = (char*)(baseAddress + PLAYER_NAME_OFFSET);
}

void Player::print()
{
	std::cout << "Base Module: " << std::hex << baseModule << std::dec << std::endl;
	std::cout << "Base Address: " << std::hex << baseAddress << std::dec << std::endl;

	std::cout << "Health Address: " << std::hex << health << std::dec << " Health Value: " << *health << std::endl;
	std::cout << "Armor Address: " << std::hex << armor << std::dec << " Armor Value: " << *armor << std::endl;
	std::cout << "team Address: " << std::hex << team << std::dec << " team Value: " << *team << std::endl;

	std::cout << "PlayerPOS Address: " << std::hex << playerPosition << std::dec << std::endl;
	std::cout << "PlayerPOS  x value: " << *playerPosition << std::endl;
	std::cout << "PlayerPOS  y value: " << *(playerPosition + 1) << std::endl;
	std::cout << "PlayerPOS  z value: " << *(playerPosition + 2) << std::endl;

	std::cout << "PlayerHEADPOS Address: " << std::hex << playerHeadPosition << std::dec << std::endl;
	std::cout << "PlayerHEADPOS  x value: " << *playerHeadPosition << std::endl;
	std::cout << "PlayerHEADPOS  y value: " << *(playerHeadPosition + 1) << std::endl;
	std::cout << "PlayerHEADPOS  z value: " << *(playerHeadPosition + 2) << std::endl;

	std::cout << "cameraPOS Address: " << std::hex << cameraPosition << std::dec << std::endl;
	std::cout << "cameraPOS  yaw value: " << *cameraPosition << std::endl;
	std::cout << "cameraPOS  pitch value: " << *(cameraPosition + 1) << std::endl;

	std::cout << "name: " << name << std::endl;
	std::cout << std::endl;
}
