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
    CleanBomb->globa_width = StrToInt(Edit2->Text);
    CleanBomb->globa_height = StrToInt(Edit1->Text);
    CleanBomb->globa_bomb_num = StrToInt(Edit3->Text);
    CleanBomb->init_interface(CleanBomb->globa_width,CleanBomb->globa_height,CleanBomb->globa_bomb_num);
}
//---------------------------------------------------------------------------

void __fastcall Tset_bomb::FormPaint(TObject *Sender)
{
    Edit2->Text = CleanBomb->globa_width;
    Edit1->Text = CleanBomb->globa_height;
    Edit3->Text = CleanBomb->globa_bomb_num;
}
//---------------------------------------------------------------------------

