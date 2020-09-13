// keyboard-driver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define WINVER 0x0500
#include <windows.h>
#include <vector>

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

void pressAndReleaseKey(int key) {
	std::vector<INPUT> keystroke;
	keystroke.push_back(createScanCodeEvent(key, true));
	keystroke.push_back(createScanCodeEvent(key, false));
	SendInput(keystroke.size(), keystroke.data(), sizeof(keystroke[0]));
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

int main(int argc, char* argv[])
{
	// This structure will be used to create the keyboard
	// input event.
	//std::vector<INPUT> keystroke;
	//std::cout << argv[0] << std::endl;
	//INPUT ip;
	
	std::string key = argv[1];
	uint8_t code = (uint8_t)argv[1][0]; // TODO check for only one char
	std::string ctrl = argv[2];
	std::string alt = argv[3];

	printf("code: %d", '.');
 // TODO tab more special chars

	if (ctrl == "true") { pressKey(VK_CONTROL); }
	if (alt == "true") { pressKey(VK_MENU); }
	
	if (key == "backspace") { pressAndReleaseKey(VK_BACK); }
	else if (key == "space") { pressAndReleaseKey(VK_SPACE); }
	else if (key == "tab") { pressAndReleaseKey(VK_TAB); }
	else if (key == "return") {
		pressAndReleaseKey(VK_RETURN);
		std::vector<INPUT> keystroke;
	}
	else if (code == 46) { pressAndReleaseKey(VK_OEM_PERIOD); }
    else if (code >= 97 || code < 123) {
		code = code - 32;
	//	printf("pressandrelease code");
		pressAndReleaseKey(code);
	}

	if (ctrl == "true") { releaseKey(VK_CONTROL); }
	if (alt == "true") { releaseKey(VK_MENU); }

	
	// Exit normally
	return 0;
}



