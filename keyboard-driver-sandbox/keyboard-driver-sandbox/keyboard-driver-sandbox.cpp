// keyboard-driver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define WINVER 0x0500
#include <windows.h>
#include<vector>

void presskeys(std::string s)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	HKL kbl = GetKeyboardLayout(0);
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		ip.ki.wVk = VkKeyScanExA(c, kbl); //<== don't mix ANSI with UNICODE
		ip.ki.dwFlags = 0; //<= Add this to indicate key-down
		SendInput(1, &ip, sizeof(ip));
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(ip));
	}
}

INPUT createScanCodeEvent(WORD scancode, bool isDown)
{
	INPUT input = {};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = 0;
	input.ki.wScan = MapVirtualKey(scancode, MAPVK_VK_TO_VSC);
	input.ki.dwFlags = (isDown ? 0 : KEYEVENTF_KEYUP) | KEYEVENTF_SCANCODE;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	return input;
}

void pressKey(int key) {
	std::vector<INPUT> keystroke;
	keystroke.push_back(createScanCodeEvent(key, true));
	SendInput(keystroke.size(), keystroke.data(), sizeof(keystroke[0]));
}

void releaseKey(int key) {
	std::vector<INPUT> keystroke;
	keystroke.push_back(createScanCodeEvent(key, false));
	SendInput(keystroke.size(), keystroke.data(), sizeof(keystroke[0]));
}

void pressAndReleaseKey(int key) {
	std::vector<INPUT> keystroke;
	keystroke.push_back(createScanCodeEvent(key, true));
	keystroke.push_back(createScanCodeEvent(key, false));
	SendInput(keystroke.size(), keystroke.data(), sizeof(keystroke[0]));
}


int main(int argc, char* argv[])
{
	HKL kbl = GetKeyboardLayout(0);
	// This structure will be used to create the keyboard
	// input event.

	INPUT ip;
	char key = (char)'l'; // TODO check for only one char

	std::cout << key << std::endl;
	uint8_t code = (uint8_t)key;
	std::cout << code << std::endl;

	Sleep(3000);
	

	std::vector<INPUT> keystroke;
	//keystroke.push_back(createScanCodeEvent(VK_CONTROL, true));
	pressKey(VK_CONTROL);
	
	//SendInput(keystroke.size(), keystroke.data(), sizeof(keystroke[0]));
	

	if (code == 32) {
		std::vector<INPUT> keystroke;
		keystroke.push_back(createScanCodeEvent(VK_SPACE, true));
		SendInput(keystroke.size(), keystroke.data(), sizeof(keystroke[0]));
	}	

	if (code >= 97 || code < 123) {
		code = code - 32;

		pressAndReleaseKey(code);
	}

	//releaseKey(code);
	releaseKey(VK_CONTROL);
	
	// 32 space
	// 8 space


/*
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "A" key
	ip.ki.wVk = VkKeyScanExA(key, kbl);
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "A" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
*/
	// Exit normally
	return 0;
}