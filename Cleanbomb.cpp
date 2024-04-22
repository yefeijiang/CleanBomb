//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("score.cpp", sort);
USEFORM("set.cpp", set_bomb);
USEFORM("MainForm.cpp", CleanBomb_main_windows);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TCleanBomb_main_windows), &CleanBomb_main_windows);
		Application->CreateForm(__classid(Tsort), &sort);
		Application->CreateForm(__classid(Tset_bomb), &set_bomb);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
