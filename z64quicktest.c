//
// z64quicktest <z64.me>
//
// a micro utility to help Zelda64 modders rapidly iterate
//

#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define PROGNAME "z64quicktest"

// Global variables
HWND hwndFilepathEmulator;
HWND hwndFilepathRom;
HWND hwndOptionCharacterAdultLink;
HWND hwndOptionCharacterYoungLink;
HWND hwndTextEditEntrance;
HWND hwndTextEditTime;
HWND hwndTextEditCutscene;

// Function prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateControls(HWND hwnd);
void OnPlayButtonClick();
void OnAboutButtonClick();
void OnFilePathButtonClick(HWND hwndFilePath, const char *filter);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Register the window class
	const char *CLASS_NAME = PROGNAME "WindowClass";
	
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	
	RegisterClass(&wc);
	
	// Create the window
	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		PROGNAME,
		WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 280,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	
	if (hwnd == NULL) {
		return 0;
	}
	
	CreateControls(hwnd);
	
	// Display the window
	ShowWindow(hwnd, nCmdShow);
	
	// Run the message loop
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE:
			// Window creation
			return 0;
		
		case WM_COMMAND:
			// Handle button click
			if (LOWORD(wParam) == 1) {
				OnPlayButtonClick();
			}
			else if (LOWORD(wParam) == 2) {
				OnFilePathButtonClick(hwndFilepathEmulator, "Executable Files (*.exe)\0*.exe\0");
			}
			else if (LOWORD(wParam) == 3) {
				OnFilePathButtonClick(hwndFilepathRom, "Zelda 64 ROM Files (*.z64)\0*.z64\0");
			}
			else if (LOWORD(wParam) == 4) {
				OnAboutButtonClick();
			}
			return 0;
		
		case WM_DESTROY:
			// Window destruction
			PostQuitMessage(0);
			return 0;
		
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void CreateControls(HWND hwnd) {
	// Create the file path fields
	hwndFilepathEmulator = CreateWindowEx(
		0, "EDIT",
		"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY,
		140, 20, 200, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	hwndFilepathRom = CreateWindowEx(
		0, "EDIT",
		"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY,
		140, 50, 200, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	// Create the file selection buttons
	CreateWindowEx(
		0, "BUTTON",
		"...",
		WS_CHILD | WS_VISIBLE,
		350, 20, 30, 20,
		hwnd,
		(HMENU)2,
		NULL,
		NULL
	);
	
	CreateWindowEx(
		0, "BUTTON",
		"...",
		WS_CHILD | WS_VISIBLE,
		350, 50, 30, 20,
		hwnd,
		(HMENU)3,
		NULL,
		NULL
	);
	
	// Create the radio button
	hwndOptionCharacterAdultLink = CreateWindowEx(
		0, "BUTTON",
		"Adult Link",
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		140, 80, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	hwndOptionCharacterYoungLink = CreateWindowEx(
		0, "BUTTON",
		"Young Link",
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		240, 80, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	// Set the "Adult Link" radio button as selected by default
	SendMessage(hwndOptionCharacterAdultLink, BM_SETCHECK, BST_CHECKED, 0);
	
	// Create the text edit fields
	hwndTextEditEntrance = CreateWindowEx(
		0, "EDIT",
		"0x0000",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		140, 110, 200, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	hwndTextEditTime = CreateWindowEx(
		0, "EDIT",
		"0x8000",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		140, 140, 200, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	hwndTextEditCutscene = CreateWindowEx(
		0, "EDIT",
		"0x0000",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		140, 170, 200, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	// Create the placeholder text labels
	CreateWindowEx(
		0, "STATIC",
		"Emulator",
		WS_CHILD | WS_VISIBLE,
		20, 20, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	CreateWindowEx(
		0, "STATIC",
		"ROM",
		WS_CHILD | WS_VISIBLE,
		20, 50, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	CreateWindowEx(
		0, "STATIC",
		"Character",
		WS_CHILD | WS_VISIBLE,
		20, 80, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	CreateWindowEx(
		0, "STATIC",
		"Entrance",
		WS_CHILD | WS_VISIBLE,
		20, 110, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	CreateWindowEx(
		0, "STATIC",
		"Time",
		WS_CHILD | WS_VISIBLE,
		20, 140, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	CreateWindowEx(
		0, "STATIC",
		"Cutscene",
		WS_CHILD | WS_VISIBLE,
		20, 170, 100, 20,
		hwnd,
		NULL,
		NULL,
		NULL
	);
	
	// Create the Play button
	CreateWindowEx(
		0, "BUTTON",
		"Play",
		WS_CHILD | WS_VISIBLE,
		20, 210, 80, 25,
		hwnd,
		(HMENU)1,
		NULL,
		NULL
	);
	
	// Create the About button
	CreateWindowEx(
		0, "BUTTON",
		"About",
		WS_CHILD | WS_VISIBLE,
		120, 210, 80, 25,
		hwnd,
		(HMENU)4,
		NULL,
		NULL
	);
}

bool strchrs(const char *haystack, const char *needles)
{
	for (int i = 0; i < (int)strlen(needles); ++i)
			if (strchr(haystack, needles[i]))
					return true;
	
	return false;
}

int DoValue(HWND wnd)
{
	char tmp[MAX_PATH];
	int v;
	
	GetWindowText(wnd, tmp, sizeof(tmp));
	
	// hex
	if (strchrs(tmp, "xabcdefXABCDEF0123456789"))
	{
		unsigned vv;
		
		if (sscanf(tmp, "%x", &vv) != 1)
			v = -1;
		else
			v = vv;
	}
	// decimal
	else if (sscanf(tmp, "%d", &v) != 1)
		v = -1;
	
	if (v < 0)
	{
		char error[MAX_PATH];
		
		snprintf(error, sizeof(error), "failed to extract value from string '%s'", tmp);
		
		MessageBox(NULL, error, "Error", MB_OK | MB_ICONERROR);
	}
	
	return v;
}

bool IsRadioButtonSelected(HWND hwnd) {
	return (SendMessage(hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED);
}

const char *MyCopyFile(const char *dst, const char *src)
{
	static char error[MAX_PATH];
	FILE *sourceFile = fopen(src, "rb");
	FILE *destinationFile = fopen(dst, "wb");
	char buffer[4096];
	size_t bytesRead;
	
	if (!sourceFile)
	{
		snprintf(error, sizeof(error), "failed to open '%s' for reading", src);
		return error;
	}
	
	if (!destinationFile)
	{
		snprintf(error, sizeof(error), "failed to open '%s' for writing", src);
		return error;
	}
	
	while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
		fwrite(buffer, 1, bytesRead, destinationFile);
	}
	
	fclose(sourceFile);
	fclose(destinationFile);
	
	return 0;
}

void fput16(FILE *fp, uint16_t v)
{
	fputc(v >> 8, fp);
	fputc(v, fp);
}

void fput32(FILE *fp, uint32_t v)
{
	fputc(v >> 24, fp);
	fputc(v >> 16, fp);
	fputc(v >> 8, fp);
	fputc(v, fp);
}

void fgoto(FILE *fp, uint32_t addr)
{
	fseek(fp, addr, SEEK_SET);
}

void ApplyPatchOoT10uNTSC(FILE *fp, int character, int entrance, int time, int cutscene)
{
	const unsigned ovl_title = 0x00B9DA40;
	const unsigned ovl_opening = 0x00BA1160;
	const unsigned code = 0x00A87000;
	
	/* time of day (0x8000 for noon) */
	fgoto(fp, ovl_title + 0x714);
	fput32(fp, 0x240C0000 | time);
	fput32(fp, 0xA04313E0);
	fput32(fp, 0xA04313E1);
	fput32(fp, 0xA44C000C);
	
	/* removes n64 logo */
	fgoto(fp, ovl_title + 0x6C);
	fput32(fp, 0x00000000);
	
	/* link's age */
	fgoto(fp, ovl_opening + 0x10);
	fput32(fp, 0x240E0000 | character);
	fput32(fp, 0xAC40135C);
	fput32(fp, 0xAC800098);
	fput32(fp, 0xAC4E0004);
	
	/* cutscene header (should be 0000 usually) */
	fgoto(fp, ovl_opening + 0x32);
	fput16(fp, cutscene);
	
	/* entrance id */
	fgoto(fp, code + 0x7F1EA);
	fput16(fp, entrance);
}

int ApplyPatch(const char *rom, int character, int entrance, int time, int cutscene)
{
	FILE *fp = fopen(rom, "rb+");
	
	if (!fp)
		return -1;
	
	/* hardcoded oot 1.0 u ntsc stuff */
	ApplyPatchOoT10uNTSC(fp, character, entrance, time, cutscene);
	
	fclose(fp);
	return 0;
}

int PlayRom(const char *emulator, const char *rom)
{
	// Create process information structure
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&processInfo, sizeof(processInfo));
	
	// Create startup information structure
	STARTUPINFO startupInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	
	// Create the command-line string
	char commandLine[MAX_PATH];
	sprintf(commandLine, "\"%s\" \"%s\"", emulator, rom);
	
	// Create the process
	if (CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo))
		return 0;
	else
		return -1;
}

void OnPlayButtonClick() {
	// Get the text from the edit fields
	char emulator[MAX_PATH];
	char rom[MAX_PATH];
	char romCopy[MAX_PATH];
	int character = IsRadioButtonSelected(hwndOptionCharacterYoungLink);
	int entrance;
	int time;
	int cutscene;
	
	GetWindowText(hwndFilepathEmulator, emulator, sizeof(emulator));
	GetWindowText(hwndFilepathRom, rom, sizeof(rom));
	
	if (strlen(emulator) == 0 || strlen(rom) == 0)
	{
		MessageBox(NULL, "Please select both an emulator and a rom.", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	
	snprintf(
		 romCopy
		 , sizeof(romCopy)
		 , "%.*s.%s.z64"
		 , (int)(strrchr(rom, '.') - rom)
		 , rom
		 , PROGNAME
	);
	
	{
		const char *tmp = MyCopyFile(romCopy, rom);
		
		if (tmp)
		{
			MessageBox(NULL, tmp, "Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
	
	if ((entrance = DoValue(hwndTextEditEntrance)) < 0
		|| (time = DoValue(hwndTextEditTime)) < 0
		|| (cutscene = DoValue(hwndTextEditCutscene)) < 0
	)
		return;
	
	if (ApplyPatch(romCopy, character, entrance, time, cutscene))
	{
		MessageBox(NULL, "Something went wrong applying patch", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	
	if (PlayRom(emulator, romCopy))
	{
		MessageBox(NULL, "Something went wrong launching the emulator", "Error", MB_OK | MB_ICONERROR);
		return;
	}
}

void OnAboutButtonClick() {
	// Display the text in a message box
	MessageBox(
		NULL
		, PROGNAME " by z64me <z64.me>\n\n"
		"special thanks to Aegiker for the base patch\n\n"
		"also special thanks to OniHelix for needing this tool\n\n"
		, PROGNAME
		, MB_OK | MB_ICONINFORMATION
	);
}

void OnFilePathButtonClick(HWND hwndFilePath, const char *filter) {
	OPENFILENAME ofn;
	char szFile[MAX_PATH] = {0};
	
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	
	if (GetOpenFileName(&ofn) == TRUE) {
		SetWindowText(hwndFilePath, szFile);
	}
}
