//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "score.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tsort *sort;
//---------------------------------------------------------------------------
__fastcall Tsort::Tsort(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------