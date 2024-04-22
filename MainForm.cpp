//---------------------------------------------------------------------------
//   其实很早就写过一个pascal版本的扫雷游戏,很简陋的,觉得不太好,正好工作的时候
//   用到BCB,就想写一个BCB版本的扫雷游戏,其实就是自己写着玩玩.
//   从开始写到写完,间隔很久,中间有事就忘了写了,没写完总归是不爽的,什么事都要
//   有始有终,对吧.
//
//   日期:2004.02.28
//   作者:老姜(fjye)
//   Email:fjye@fjye.com
//   HomePage:http://www.YEStudio.cn
//
//   程序思路:
//   1,首先初始化二维数组,结构数组,定义好类以及结构体
//   2,填充全部空格,埋雷(),随机布雷.
//   3,定义鼠标左键单击事件,显示格子属性(数字0-8,空地,雷区)
//   4,鼠标右键单击标雷.再单击测消标雷
//   5,鼠标左右键齐击,自动计算数字周边已经显示全部雷数的3*3范围的数字己空格
//   6,利用注册表记录成绩信息,新纪录成绩记录写入注册表,记录最后一次打开的级别
//   7,消息拦截,拦截F2按键消息,重新开始游戏.
//   8,使用TStringList方便快捷
//   9,资源的使用,使编译以后的程序尽量简洁,数字动态显示
//
//   2024年3月27日，改写为适配c++builder11 社区版
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
//主界面析构函数,新建位图资源指针,初始化
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
    //以下这段程序是检验可执行程序本身的校验和的,防止程序被改写
    //需要在头文件中加上#include "imagehlp.h"   
   /* DWORD HeadChksum=1,Chksum=0;
    char Fn[512];
    GetModuleFileName(GetModuleHandle(NULL),Fn,512);
    if(MapFileAndCheckSum(Fn,&HeadChksum,&Chksum)!=CHECKSUM_SUCCESS)
    {
        MessageBox(NULL,"文件检查出错!","错误",MB_OK);
    }
    else
    {
        if(HeadChksum!=Chksum)
            {
            MessageBox(NULL,"文件已被改动,启动失败！","警告",MB_OK);
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

	Width = p_width*16+17;               //设定程序宽度
	Height = p_height*16+77+14;            //设定程序高度
    Set(p_width,p_height,bomb_num);  //设定雷数

    for (int i=0;i<p_width;i++)         //绘制初始界面
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
ShowMessage("按照Windows的扫雷游戏做的,不需要多说了吧");
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
//计时
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
    if ((Shift.Contains(ssLeft))&&(!Shift.Contains(ssRight))) //左键单击
        {
        //ShowMessage(IntToStr(X)+","+IntToStr(Y));
        Open(X,Y);
        }
    if ((!Shift.Contains(ssLeft))&&(Shift.Contains(ssRight))) //右键单击
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
    if ((Shift.Contains(ssLeft))&&(Shift.Contains(ssRight)))  //左右键齐击
        {
        left_right_click(X,Y);
        }
    if(label_bomb==globa_bomb_num)
        {
        Timer1->Enabled = false;
        ShowMessage("扫雷成功!");
        //---写注册表
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
    //四个角上的单独处理
    POS[0][0]->around_bomb = POS[0][1]->are_you_bomb+POS[1][0]->are_you_bomb+POS[1][1]->are_you_bomb;
    POS[0][n]->around_bomb = POS[0][n-1]->are_you_bomb+POS[1][n]->are_you_bomb+POS[1][n-1]->are_you_bomb;
    POS[m][0]->around_bomb = POS[m][1]->are_you_bomb+POS[m-1][0]->are_you_bomb+POS[m-1][1]->are_you_bomb;
    POS[m][n]->around_bomb = POS[m][n-1]->are_you_bomb+POS[m-1][n]->are_you_bomb+POS[m-1][n-1]->are_you_bomb;
    for(int i=1;i<n;i++)     //最左边纵向
        {
        POS[0][i]->around_bomb = POS[0][i-1]->are_you_bomb+POS[0][i+1]->are_you_bomb+POS[1][i]->are_you_bomb+POS[1][i-1]->are_you_bomb+POS[1][i+1]->are_you_bomb;
        }
    for(int i=1;i<m;i++)     //最上面横向
        {
        POS[i][0]->around_bomb = POS[i-1][0]->are_you_bomb+POS[i+1][0]->are_you_bomb+POS[i-1][1]->are_you_bomb+POS[i+1][1]->are_you_bomb+POS[i][1]->are_you_bomb;
        }
    for(int i=1;i<n;i++)     //最右边纵向
        {
        POS[m][i]->around_bomb = POS[m][i-1]->are_you_bomb+POS[m][i+1]->are_you_bomb+POS[m-1][i]->are_you_bomb+POS[m-1][i-1]->are_you_bomb+POS[m-1][i+1]->are_you_bomb;
        }

    for(int i=1;i<m;i++)     //最下面横向
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
    //  就OK了，现在aList->Strings[0]就是fjye,20，以此类推
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
    regkey->RootKey=HKEY_LOCAL_MACHINE;//设置根键 //打开自动登录所在的键
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
    regkey->RootKey=HKEY_LOCAL_MACHINE;//设置根键 //打开自动登录所在的键
    regkey->OpenKey("SOFTWARE\\fjye\\cleanbomb\\score",true);
    regkey->WriteString("score",m);
    delete regkey;
}

TStringList* TCleanBomb_main_windows::read_last_config()
{
    TStringList * aList = new TStringList();
    regkey = new TRegistry();
    regkey->RootKey=HKEY_LOCAL_MACHINE;//设置根键 //打开自动登录所在的键
    regkey->OpenKey("SOFTWARE\\fjye\\cleanbomb\\score",true);
    aList->Delimiter = ',';
    aList->DelimitedText = regkey->ReadString("last_config");
    delete regkey;
    return aList;
}

void TCleanBomb_main_windows::write_last_config(UnicodeString con)
{
    regkey = new TRegistry();
    regkey->RootKey=HKEY_LOCAL_MACHINE;//设置根键 //打开自动登录所在的键
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

