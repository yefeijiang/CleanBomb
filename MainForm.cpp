//---------------------------------------------------------------------------
//   ��ʵ�����д��һ��pascal�汾��ɨ����Ϸ,�ܼ�ª��,���ò�̫��,���ù�����ʱ��
//   �õ�BCB,����дһ��BCB�汾��ɨ����Ϸ,��ʵ�����Լ�д������.
//   �ӿ�ʼд��д��,����ܾ�,�м����¾�����д��,ûд���ܹ��ǲ�ˬ��,ʲô�¶�Ҫ
//   ��ʼ����,�԰�.
//
//   ����:2004.02.28
//   ����:�Ͻ�(fjye)
//   Email:fjye@fjye.com
//   HomePage:http://www.YEStudio.cn
//
//   ����˼·:
//   1,���ȳ�ʼ����ά����,�ṹ����,��������Լ��ṹ��
//   2,���ȫ���ո�,����(),�������.
//   3,���������������¼�,��ʾ��������(����0-8,�յ�,����)
//   4,����Ҽ���������.�ٵ�����������
//   5,������Ҽ����,�Զ����������ܱ��Ѿ���ʾȫ��������3*3��Χ�����ּ��ո�
//   6,����ע����¼�ɼ���Ϣ,�¼�¼�ɼ���¼д��ע���,��¼���һ�δ򿪵ļ���
//   7,��Ϣ����,����F2������Ϣ,���¿�ʼ��Ϸ.
//   8,ʹ��TStringList������
//   9,��Դ��ʹ��,ʹ�����Ժ�ĳ��������,���ֶ�̬��ʾ
//
//   2024��3��27�գ���дΪ����c++builder11 ������
//
//
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "set.h"
#include "score.h"
#include "imagehlp.h"
#include <dialogs.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TCleanBomb_main_windows *CleanBomb_main_windows;
//---------------------------------------------------------------------------
//��������������,�½�λͼ��Դָ��,��ʼ��
__fastcall TCleanBomb_main_windows::TCleanBomb_main_windows(TComponent* Owner)
        : TForm(Owner)
{
    wastetime = 0;
    label_bomb = 0;
    virtual_num = 0;
    globa_width = WIDTH;
    globa_height = HEIGHT;
    globa_bomb_num = BOMB_NUMBER;
    //regkey = new TRegistry();
    //TStringList * aList = new TStringList();
    TStringList *aList = read_last_config();
    if(aList->DelimitedText!="")
        {
        globa_width = StrToInt(aList->Strings[0]);
        globa_height = StrToInt(aList->Strings[1]);
        globa_bomb_num = StrToInt(aList->Strings[2]);
        }
    delete aList;
    for (int i=0;i<50;i++)
      for (int j=0;j<30;j++)
          {
		  POS[i][j] = new BOMB(i,j);
          POS[i][j]->show();
          }
    gameover = false;
    //������γ����Ǽ����ִ�г������У��͵�,��ֹ���򱻸�д
    //��Ҫ��ͷ�ļ��м���#include "imagehlp.h"   
   /* DWORD HeadChksum=1,Chksum=0;
    char Fn[512];
    GetModuleFileName(GetModuleHandle(NULL),Fn,512);
    if(MapFileAndCheckSum(Fn,&HeadChksum,&Chksum)!=CHECKSUM_SUCCESS)
    {
        MessageBox(NULL,"�ļ�������!","����",MB_OK);
    }
    else
    {
        if(HeadChksum!=Chksum)
            {
            MessageBox(NULL,"�ļ��ѱ��Ķ�,����ʧ�ܣ�","����",MB_OK);
            FormDestroy(NULL);
            Close();
            }    
    //--------    

    }        */


}
//---------------------------------------------------------------------------


void TCleanBomb_main_windows::init_interface(int p_width=WIDTH,int p_height=HEIGHT,int bomb_num=BOMB_NUMBER)
{
        //TODO: Add your source code here
    wastetime = 0;
    time_pic(wastetime);
    bombnum_pic(globa_bomb_num-virtual_num);
    Refresh();
    wastetime = 0;
    label_bomb = 0;
    virtual_num = 0;
    //Timer1->Enabled = true;

	Width = p_width*16+17;               //�趨������
	Height = p_height*16+77+14;            //�趨����߶�
    Set(p_width,p_height,bomb_num);  //�趨����

    for (int i=0;i<p_width;i++)         //���Ƴ�ʼ����
        for (int j=0;j<p_height;j++)
            {
            Draw(i,j,"button");
            }


}

void TCleanBomb_main_windows::Draw(int i, int j, UnicodeString state)
{
  try
  {
    Bitmap1 = new Graphics::TBitmap();
    Bitmap1->LoadFromResourceName((int)HInstance,state);
    //Bitmap1->LoadFromResourceName((int)HInstance,POS[i][j]->state);
    Canvas->Draw(i*16,j*16+32,Bitmap1);
  }
  catch (...)
  {
    MessageBeep(0);
  }
  delete Bitmap1;
}
void __fastcall TCleanBomb_main_windows::N5Click(TObject *Sender)
{
    globa_width = 12;
    globa_height = 12;
    globa_bomb_num = 12;
    click_label(true,false,false,false);
    init_interface(globa_width,globa_height,globa_bomb_num);
}
//---------------------------------------------------------------------------

void __fastcall TCleanBomb_main_windows::N6Click(TObject *Sender)
{
    globa_width = 16;
    globa_height = 16;
    globa_bomb_num = 40;
    click_label(false,true,false,false);
    init_interface(globa_width,globa_height,globa_bomb_num);
}
//---------------------------------------------------------------------------

void __fastcall TCleanBomb_main_windows::N7Click(TObject *Sender)
{
    globa_width = 30;
    globa_height = 16;
    globa_bomb_num = 65;
    click_label(false,false,true,false);
    init_interface(globa_width,globa_height,globa_bomb_num);
}
//---------------------------------------------------------------------------
void __fastcall TCleanBomb_main_windows::N12Click(TObject *Sender)
{
    click_label(false,false,false,true);
    set_bomb->ShowModal();
}
//---------------------------------------------------------------------------
void TCleanBomb_main_windows::click_label(bool k1,bool k2,bool k3,bool k4)
{
     N5->Checked = k1;
     N6->Checked = k2;
     N7->Checked = k3;
     N12->Checked = k4;
}
//---------------------------------------------------------------------------

void __fastcall TCleanBomb_main_windows::FormDestroy(TObject *Sender)
{
    for (int i=0;i<50;i++)
      for (int j=0;j<30;j++)
          {
          delete POS[i][j];
          }
}
//---------------------------------------------------------------------------
void __fastcall TCleanBomb_main_windows::N9Click(TObject *Sender)
{
ShowMessage("����Windows��ɨ����Ϸ����,����Ҫ��˵�˰�");
}


void __fastcall TCleanBomb_main_windows::N10Click(TObject *Sender)
{
ShowMessage("v1.07 C++Build 11 by fjye"+UnicodeString('\n')+"Email:fjye@yestudio.co.nz");
}
//---------------------------------------------------------------------------


bool TCleanBomb_main_windows::Set(int p_width,int p_height,int bomb_num)
{
  int num;
  num = 0;
  for (int i=0;i<p_width;i++)
    for (int j=0;j<p_height;j++)
        {
        POS[i][j]->updata(i,j);
        }
  while(num<bomb_num)
    {
    if(Lay_Bomb(p_width,p_height))
      num++;
    }
    calculate_around_bomb();
    return true;
}


void __fastcall TCleanBomb_main_windows::N3Click(TObject *Sender)
{
    Close();   
}
//---------------------------------------------------------------------------

void __fastcall TCleanBomb_main_windows::N2Click(TObject *Sender)
{
    gameover = false;
    init_interface(globa_width,globa_height,globa_bomb_num);

}
//---------------------------------------------------------------------------
BOMB::BOMB(int x,int y)
{
    //TODO: Add your source code here
    updata(x,y);
}
//---------------------------------------------------------------------------
void BOMB::updata(int x,int y)
{
    //TODO: Add your source code here
    around_bomb = 0;
    be_flaged = false;
    opened = false;
    are_you_bomb = 0;
    bombed = false;
    x_position = x;
    y_position = y;
    state = "button";
}
//---------------------------------------------------------------------------
void BOMB::show()
{
    //TODO: Add your source code here
    CleanBomb_main_windows->Draw(x_position,y_position,state);
}

void __fastcall TCleanBomb_main_windows::Timer1Timer(TObject *Sender)
{
//��ʱ
wastetime++;
time_pic(wastetime);
bombnum_pic(globa_bomb_num-virtual_num);

}
//---------------------------------------------------------------------------



void __fastcall TCleanBomb_main_windows::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        X = X/16;
        Y = (Y-32)/16;
    if(gameover) return;
    if(!Timer1->Enabled)
        {
        Timer1->Enabled = true;
        }
    if ((Shift.Contains(ssLeft))&&(!Shift.Contains(ssRight))) //�������
        {
        //ShowMessage(IntToStr(X)+","+IntToStr(Y));
        Open(X,Y);
        }
    if ((!Shift.Contains(ssLeft))&&(Shift.Contains(ssRight))) //�Ҽ�����
        {
        if(POS[X][Y]->state == "button")
            {
            Draw(X,Y,"flag");
            POS[X][Y]->state = "flag";
            POS[X][Y]->opened = true;
            if(POS[X][Y]->are_you_bomb==1)
                {
                label_bomb++;
                }
            virtual_num++;
            bombnum_pic(globa_bomb_num-virtual_num);
            }
        else
        if(POS[X][Y]->state == "flag")
            {
            Draw(X,Y,"wenhao");
            POS[X][Y]->state = "wenhao";
            if(POS[X][Y]->are_you_bomb==1)
                {
                label_bomb--;
                }
            virtual_num--;
            bombnum_pic(globa_bomb_num-virtual_num);
            }
        else
        if(POS[X][Y]->state == "wenhao")
            {
            Draw(X,Y,"button");
            POS[X][Y]->state = "button";
            POS[X][Y]->opened = false;

            }

        }
    if ((Shift.Contains(ssLeft))&&(Shift.Contains(ssRight)))  //���Ҽ����
        {
        left_right_click(X,Y);
        }
    if(label_bomb==globa_bomb_num)
        {
        Timer1->Enabled = false;
        ShowMessage("ɨ�׳ɹ�!");
        //---дע���
        check_log();
        return;
        }

}
//---------------------------------------------------------------------------


bool TCleanBomb_main_windows::Lay_Bomb(int i, int j)
{
    //TODO: Add your source code here
    Randomize();
    int m,n;
    //m=random(i);
    //n=random(j);
    m= random(GetTickCount()) % i;
    n= random(GetTickCount()/2) % j;
    if (POS[m][n]->are_you_bomb!=1)
      {
      POS[m][n]->are_you_bomb = 1;
      POS[m][n]->around_bomb = -1;
      return true;
      }
    else return false;
}

void TCleanBomb_main_windows::calculate_around_bomb()
{
    //TODO: Add your source code here
    int m,n;
    m = (Width/16)-1;
    n = ((Height-32)/16)-3;
    //�ĸ����ϵĵ�������
    POS[0][0]->around_bomb = POS[0][1]->are_you_bomb+POS[1][0]->are_you_bomb+POS[1][1]->are_you_bomb;
    POS[0][n]->around_bomb = POS[0][n-1]->are_you_bomb+POS[1][n]->are_you_bomb+POS[1][n-1]->are_you_bomb;
    POS[m][0]->around_bomb = POS[m][1]->are_you_bomb+POS[m-1][0]->are_you_bomb+POS[m-1][1]->are_you_bomb;
    POS[m][n]->around_bomb = POS[m][n-1]->are_you_bomb+POS[m-1][n]->are_you_bomb+POS[m-1][n-1]->are_you_bomb;
    for(int i=1;i<n;i++)     //���������
        {
        POS[0][i]->around_bomb = POS[0][i-1]->are_you_bomb+POS[0][i+1]->are_you_bomb+POS[1][i]->are_you_bomb+POS[1][i-1]->are_you_bomb+POS[1][i+1]->are_you_bomb;
        }
    for(int i=1;i<m;i++)     //���������
        {
        POS[i][0]->around_bomb = POS[i-1][0]->are_you_bomb+POS[i+1][0]->are_you_bomb+POS[i-1][1]->are_you_bomb+POS[i+1][1]->are_you_bomb+POS[i][1]->are_you_bomb;
        }
    for(int i=1;i<n;i++)     //���ұ�����
        {
        POS[m][i]->around_bomb = POS[m][i-1]->are_you_bomb+POS[m][i+1]->are_you_bomb+POS[m-1][i]->are_you_bomb+POS[m-1][i-1]->are_you_bomb+POS[m-1][i+1]->are_you_bomb;
        }

    for(int i=1;i<m;i++)     //���������
        {
        POS[i][n]->around_bomb = POS[i-1][n]->are_you_bomb+POS[i+1][n]->are_you_bomb+POS[i][n-1]->are_you_bomb+POS[i-1][n-1]->are_you_bomb+POS[i+1][n-1]->are_you_bomb;
        }
    for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
            {
            POS[i][j]->around_bomb = POS[i][j-1]->are_you_bomb+POS[i][j+1]->are_you_bomb+POS[i-1][j]->are_you_bomb+\
            POS[i-1][j-1]->are_you_bomb+POS[i-1][j+1]->are_you_bomb+POS[i+1][j-1]->are_you_bomb+POS[i+1][j]->are_you_bomb+POS[i+1][j+1]->are_you_bomb;
            }

}


bool TCleanBomb_main_windows::Open(int x, int y)
{
    //TODO: Add your source code here
    int m,n;
    m = (Width/16);
    n = ((Height-32)/16)-2;
    if((POS[x][y]->opened)&&(POS[x][y]->state == "flag")&&(POS[x][y]->are_you_bomb == 0))
        {
        Draw(x,y,"not_bomb");
        }
    if (POS[x][y]->opened) return false;
    if ((POS[x][y]->are_you_bomb!=1)&&(POS[x][y]->around_bomb>0))
        {
        Draw(x,y,IntToStr(POS[x][y]->around_bomb)+"-");
        POS[x][y]->opened = true;
        POS[x][y]->state = IntToStr(POS[x][y]->around_bomb)+"-";
        }
    if (POS[x][y]->are_you_bomb==1)
        {
        Timer1->Enabled = false;
        for (int i=0;i<globa_width;i++)
        for (int j=0;j<globa_height;j++)
            {
            if(POS[i][j]->are_you_bomb==1)
                {
                Draw(i,j,"bomb");
                POS[i][j]->opened = true;
                POS[i][j]->state = "bomb";
                }
            POS[i][j]->opened = true;
            }
        Draw(x,y,"bomb_bomb");
        POS[x][y]->opened = true;
        POS[x][y]->state = "bomb_bomb";
        gameover = true;
        return false;
        }
    if ((POS[x][y]->around_bomb==0)&&(x<=m-1)&&(y<=n-1)&&(x>=0)&&(y>=0))
        {
        Draw(x,y,"0-");
        POS[x][y]->opened = true;
        POS[x][y]->state = "0-";
        if(y!=0)
        Open(x,y-1);
        if(y!=n-1)
        Open(x,y+1);
        if(x!=0)
        Open(x-1,y);
        if(x!=m-1)
        Open(x+1,y);
        if((x!=0)&&(y!=0))
        Open(x-1,y-1);
        if((x!=0)&&(y!=n-1))
        Open(x-1,y+1);
        if((x!=m-1)&&(y!=0))
        Open(x+1,y-1);
        if((x!=m-1)&&(y!=n-1))
        Open(x+1,y+1);
        }

    return true;
}

//---------------------------------------------------------------------------


void __fastcall TCleanBomb_main_windows::FormCreate(TObject *Sender)
{
    Randomize();
    init_interface(globa_width,globa_height,globa_bomb_num);
}
//---------------------------------------------------------------------------


void __fastcall TCleanBomb_main_windows::FormPaint(TObject *Sender)
{
    for (int i=0;i<globa_width;i++)
    for (int j=0;j<globa_height;j++)
      {
      POS[i][j]->show();
      }
}

//---------------------------------------------------------------------------
void TCleanBomb_main_windows::left_right_click(int x,int y)
{
    if(!POS[x][y]->opened) return;
    int around_num=0;
    try
    {
    if((x-1>=0)&&(y-1>=0))
        {
        if(POS[x-1][y-1]->state == "flag")
            around_num++;
        }
    if(x-1>=0)
        {
        if(POS[x-1][y]->state == "flag")
            around_num++;
        }
    if((x-1>=0)&&(y+1<=globa_height-1))
        {
        if(POS[x-1][y+1]->state == "flag")
            around_num++;
        }
    if(y-1>=0)
        {
        if(POS[x][y-1]->state == "flag")
            around_num++;
        }
    if(y+1<=globa_height-1)
        {
        if(POS[x][y+1]->state == "flag")
            around_num++;
        }
    if((x+1<=globa_width-1)&&(y-1>=0))
        {
        if(POS[x+1][y-1]->state == "flag")
            around_num++;
        }
    if(x+1<=globa_width-1)
        {
        if(POS[x+1][y]->state == "flag")
            around_num++;
        }
    if((x+1<=globa_width-1)&&(y+1<=globa_height-1))
        {
        if(POS[x+1][y+1]->state == "flag")
            around_num++;
        }

    if(around_num==POS[x][y]->around_bomb)
        {
        if((x-1>=0)&&(y-1>=0))
        Open(x-1,y-1);
        if(x-1>=0)
        Open(x-1,y);
        if((x-1>=0)&&(y+1<=globa_height-1))
        Open(x-1,y+1);
        if(y-1>=0)
        Open(x,y-1);
        if(y+1<=globa_height-1)
        Open(x,y+1);
        if((x+1<=globa_width-1)&&(y-1>=0))
        Open(x+1,y-1);
        if(x+1<=globa_width-1)
        Open(x+1,y);
        if((x+1<=globa_width-1)&&(y+1<=globa_height-1))
        Open(x+1,y+1);
        }
    }
    catch(...)
    {
    }


}

void TCleanBomb_main_windows::f2(TMessage m)
{
    //TODO: Add your source code here
    if(m.WParam == 113)
        N2Click(NULL);
}
void __fastcall TCleanBomb_main_windows::N13Click(TObject *Sender)
{
    UnicodeString P[3],s[3],str;
    TStringList * aList;
    aList = read_score();
    //  ��OK�ˣ�����aList->Strings[0]����fjye,20���Դ�����
    for(int i=0;i<aList->Count;i++)
        {
        UnicodeString temp = aList->Strings[i];
        P[i] = temp.SubString(1,temp.Pos(",")-1);
        s[i] = temp.SubString(temp.Pos(",")+1,temp.Length());
        }

    for(int i=aList->Count;i<3;i++)
        {
		P[i] = "NO Name";
        s[i] = 999;
        }
    delete aList;
    sort->Label13->Caption = P[0];
	sort->Label14->Caption = s[0]+"s";

    sort->Label15->Caption = P[1];
	sort->Label16->Caption = s[1]+"s";

    sort->Label17->Caption = P[2];
	sort->Label18->Caption = s[2]+"s";
    sort->ShowModal();

}
//---------------------------------------------------------------------------




void TCleanBomb_main_windows::bombnum_pic(int num)
{
/*    //TODO: Add your source code here
    int p1,p2,p3;
    p1 = num/100;
    p2 = (num-p1*100)/10;
    p3 = num-p1*100-p2*10;
    UnicodeString state;
    try
    {
        Bitmap1 = new Graphics::TBitmap();
        state = "JPG"+IntToStr(p1);
        Bitmap1->LoadFromResourceName((int)HInstance,state);
        //Bitmap1->LoadFromResourceName((int)HInstance,POS[i][j]->state);
        Canvas->Draw(0,4,Bitmap1);
        p1 = Bitmap1->Width;
        state = "JPG"+IntToStr(p2);
        Bitmap1->LoadFromResourceName((int)HInstance,state);
        //Bitmap1->LoadFromResourceName((int)HInstance,POS[i][j]->state);
        Canvas->Draw(p1,4,Bitmap1);
        p2 = Bitmap1->Width;
        state = "JPG"+IntToStr(p3);
        Bitmap1->LoadFromResourceName((int)HInstance,state);
        //Bitmap1->LoadFromResourceName((int)HInstance,POS[i][j]->state);
        Canvas->Draw(p2+p1,4,Bitmap1);

    }
    catch (...)
    {
      MessageBeep(0);
    }
    delete Bitmap1;      */
    Label1->Caption = num;
}

void TCleanBomb_main_windows::time_pic(int time)
{
    //TODO: Add your source code here
/*    int s1,s2,s3;
    s1 = time/100;
    s2 = (time-s1*100)/10;
    s3 = time-s1*100-s2*10;
    UnicodeString state;
    try
    {
        Bitmap1 = new Graphics::TBitmap();
        state = "JPG"+IntToStr(s3);
        Bitmap1->LoadFromResourceName((int)HInstance,state);
        //Bitmap1->LoadFromResourceName((int)HInstance,POS[i][j]->state);
        Canvas->Draw(Width-Bitmap1->Width-5,4,Bitmap1);
        s3 = Width-Bitmap1->Width;
        state = "JPG"+IntToStr(s2);
        Bitmap1->LoadFromResourceName((int)HInstance,state);
        //Bitmap1->LoadFromResourceName((int)HInstance,POS[i][j]->state);
        Canvas->Draw(s3-Bitmap1->Width-5,4,Bitmap1);
        s2 = s3-Bitmap1->Width;
        state = "JPG"+IntToStr(s1);
        Bitmap1->LoadFromResourceName((int)HInstance,state);
        //Bitmap1->LoadFromResourceName((int)HInstance,POS[i][j]->state);
        Canvas->Draw(s2-Bitmap1->Width-5,4,Bitmap1);

    }
    catch (...)
    {
      MessageBeep(0);
    }
    delete Bitmap1;  */
    Label2->Caption = time;
    Label2->Left = Panel1->Width-Label2->Width-10 ;
}

//---------------------------------------------------------------------------


TStringList* TCleanBomb_main_windows::read_score()
{
    //TODO: Add your source code here
    TStringList * aList = new TStringList();
    try
    {
    regkey = new TRegistry();
    regkey->RootKey=HKEY_LOCAL_MACHINE;//���ø��� //���Զ���¼���ڵļ�
    regkey->OpenKey("SOFTWARE\\fjye\\cleanbomb\\score",true);
    aList->Delimiter = ';';
    aList->DelimitedText = regkey->ReadString("score");;
    delete regkey;
    }
    catch(...)
    {
    aList->DelimitedText = "";
    }
    return aList;
}

void TCleanBomb_main_windows::write_score(UnicodeString m)
{
    //TODO: Add your source code here
    regkey = new TRegistry();
    regkey->RootKey=HKEY_LOCAL_MACHINE;//���ø��� //���Զ���¼���ڵļ�
    regkey->OpenKey("SOFTWARE\\fjye\\cleanbomb\\score",true);
    regkey->WriteString("score",m);
    delete regkey;
}

TStringList* TCleanBomb_main_windows::read_last_config()
{
    TStringList * aList = new TStringList();
    regkey = new TRegistry();
    regkey->RootKey=HKEY_LOCAL_MACHINE;//���ø��� //���Զ���¼���ڵļ�
    regkey->OpenKey("SOFTWARE\\fjye\\cleanbomb\\score",true);
    aList->Delimiter = ',';
    aList->DelimitedText = regkey->ReadString("last_config");
    delete regkey;
    return aList;
}

void TCleanBomb_main_windows::write_last_config(UnicodeString con)
{
    regkey = new TRegistry();
    regkey->RootKey=HKEY_LOCAL_MACHINE;//���ø��� //���Զ���¼���ڵļ�
    regkey->OpenKey("SOFTWARE\\fjye\\cleanbomb\\score",true);
    regkey->WriteString("last_config",con);
    delete regkey;
}
void __fastcall TCleanBomb_main_windows::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    write_last_config(IntToStr(globa_width)+","+IntToStr(globa_height)+","+IntToStr(globa_bomb_num));
}
//---------------------------------------------------------------------------


void TCleanBomb_main_windows::check_log()
{
	//TODO: Add your source code here
    TStringList * aList;
    aList = read_score();
    if(aList->DelimitedText=="")
        {
		write_score("NO Name,999;NO Name,999;NO Name,999");
        aList = read_score();
        }
	UnicodeString temp;
    if(N5->Checked)
        {
        temp = aList->Strings[0];
        if(wastetime<StrToInt(temp.SubString(temp.Pos(",")+1,temp.Length())))
            {
			UnicodeString name;
			if (InputQuery(L"Congratulations, you have refreshed the record for this level.", L"Please input your name:      ", name))
				{
                }
            else
                {
				name = "NO Name";
                }
            aList->Strings[0] = name+","+IntToStr(wastetime);
            }
        }
    if(N6->Checked)
        {
        temp = aList->Strings[1];
        if(wastetime<StrToInt(temp.SubString(temp.Pos(",")+1,temp.Length())))
			{
            UnicodeString name;
			if (InputQuery(L"Congratulations, you have refreshed the record for this level.", L"Please input your name:      ", name))
				{
                }
            else
                {
				name = "NO Name";
                }
            aList->Strings[1] = name+","+IntToStr(wastetime);
            }
        }
    if(N7->Checked)
        {
        temp = aList->Strings[2];
		if(wastetime<StrToInt(temp.SubString(temp.Pos(",")+1,temp.Length())))
            {
            UnicodeString name;
			if (InputQuery(L"Congratulations, you have refreshed the record for this level.", L"Please input your name:      ", name))
				{
				}
            else
                {
				name = "NO Name";
                }
            aList->Strings[2] = name+","+IntToStr(wastetime);
			}
        }
    write_score(aList->DelimitedText);
    delete aList;

}
void __fastcall TCleanBomb_main_windows::FormResize(TObject *Sender)
{
    Label2->Left = Panel1->Width-Label2->Width-10 ;
    SpeedButton1->Left = (Panel1->Width-SpeedButton1->Width)/2;
}
//---------------------------------------------------------------------------

