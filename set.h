//---------------------------------------------------------------------------

#ifndef setH
#define setH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tset_bomb : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TUpDown *UpDown1;
    TEdit *Edit1;
    TUpDown *UpDown2;
    TEdit *Edit2;
    TUpDown *UpDown3;
    TEdit *Edit3;
    TButton *Button1;
    TButton *Button2;
    void __fastcall UpDown3Changing(TObject *Sender, bool &AllowChange);
    void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall Tset_bomb(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tset_bomb *set_bomb;
//---------------------------------------------------------------------------
#endif
