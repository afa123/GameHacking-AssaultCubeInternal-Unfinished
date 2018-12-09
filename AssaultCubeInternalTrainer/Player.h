#pragma once
#include <Windows.h>
#include <iostream>
class Player
{
public:
	uintptr_t baseAddress;

	Player();
	Player(uintptr_t a_baseAddress);
	~Player();
	void initialize();
	void print();
};

