//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "set.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tset_bomb *set_bomb;
//---------------------------------------------------------------------------
__fastcall Tset_bomb::Tset_bomb(TComponent* Owner)
    : TForm(Owner)
{
	Edit2->Text = CleanBomb_main_windows->globa_width;
	Edit1->Text = CleanBomb_main_windows->globa_height;
	Edit3->Text = CleanBomb_main_windows->globa_bomb_num;
}
//---------------------------------------------------------------------------
void __fastcall Tset_bomb::UpDown3Changing(TObject *Sender,
      bool &AllowChange)
{
UpDown3->Max = (StrToInt(Edit1->Text))*(StrToInt(Edit2->Text))-10;
}
//---------------------------------------------------------------------------

void __fastcall Tset_bomb::Edit2KeyPress(TObject *Sender, char &Key)
{
    Key = 0;    
}
//---------------------------------------------------------------------------

void __fastcall Tset_bomb::Button1Click(TObject *Sender)
{
	CleanBomb_main_windows->globa_width = StrToInt(Edit2->Text);
	CleanBomb_main_windows->globa_height = StrToInt(Edit1->Text);
	CleanBomb_main_windows->globa_bomb_num = StrToInt(Edit3->Text);
	CleanBomb_main_windows->init_interface(CleanBomb_main_windows->globa_width,CleanBomb_main_windows->globa_height,CleanBomb_main_windows->globa_bomb_num);
}
//---------------------------------------------------------------------------


