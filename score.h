//---------------------------------------------------------------------------

#ifndef scoreH
#define scoreH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tsort : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label13;
    TButton *Button1;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
private:	// User declarations
public:		// User declarations
    __fastcall Tsort(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tsort *sort;
//---------------------------------------------------------------------------
#endif
