#ifndef  _SYSTEMCLASS_H_
#define  _SYSTEMCLASS_H_

#include <Windows.h>

#include "gameClass.h"
#include "InputClass.h"

template<typename T>
void SafeDelete(T*& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

class SystemClass
{
public:
	SystemClass();
	~SystemClass();
	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	HWND m_hwnd;
	HINSTANCE m_hInstance;
	LPCWSTR m_gameName;
	
	bool Frame();
	void InitializeWindows(int&,int&);
	void ShutdownWindows();

	GameClass* m_Game;
	InputClass* m_Input;
};

/////////
//GLOBALS
/////////
static SystemClass* GameHandle = 0;

static LRESULT CALLBACK Wndproc(HWND, UINT, WPARAM, LPARAM);

#endif // ! _SystemClass_H_

