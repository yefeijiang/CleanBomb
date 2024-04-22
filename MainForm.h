//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <ImgList.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <OleCtrls.hpp>
#include <jpeg.hpp>
#include <Registry.hpp>
#include <Buttons.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
#define WIDTH 12
#define HEIGHT 12
#define BOMB_NUMBER 12
//---------------------------------------------------------------------------

class BOMB
{
public:
    int around_bomb;  //周边的雷数
    bool be_flaged;   //是否被标记类
    bool opened;      //是否已经打开
    int are_you_bomb;  //是否是雷
    bool bombed;        //是否已经爆
    UnicodeString state;   //类型

    int x_position;   //x轴坐标
    int y_position;   //y轴坐标
    BOMB(int x,int y);
    void show();
    void updata(int x,int y);      //显示状态图片

} ;


class TCleanBomb_main_windows : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TImageList *ImageList1;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *N6;
    TMenuItem *N7;
    TMenuItem *N8;
    TMenuItem *N9;
    TMenuItem *N10;
    TTimer *Timer1;
    TMenuItem *N12;
    TMenuItem *N13;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TSpeedButton *SpeedButton1;
    void __fastcall N5Click(TObject *Sender);
    void __fastcall N6Click(TObject *Sender);
    void __fastcall N7Click(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall N10Click(TObject *Sender);
    void __fastcall N3Click(TObject *Sender);
    void __fastcall N2Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall N12Click(TObject *Sender);
    void __fastcall N13Click(TObject *Sender);
    void __fastcall N9Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormResize(TObject *Sender);
private:
        	// User declarations
public:		// User declarations
    __fastcall TCleanBomb_main_windows(TComponent* Owner);
    void init_interface(int p_width,int p_height,int bomb_num);
    void Draw(int i, int j, UnicodeString state); //绘制所在区域,i,j表示左上角的坐标
    Graphics::TBitmap *Bitmap1;
    bool Set(int p_width,int p_height,int bomb_num);
    BOMB *POS[50][30];
    bool Lay_Bomb(int i, int j); //置雷
    void calculate_around_bomb();
    bool Open(int x, int y);
    void left_right_click(int x,int y);
    int globa_width,globa_height,globa_bomb_num,virtual_num;
    void f2(TMessage m);
    int wastetime;
    int label_bomb;
    void bombnum_pic(int num);
    void time_pic(int time);
    TRegistry *regkey;
    //TStringList *aList;
    TStringList * read_score();
    void write_score(UnicodeString m);
    TStringList * read_last_config();
    void write_last_config(UnicodeString con);
    void click_label(bool k1,bool k2,bool k3,bool k4);
    void check_log();
    bool gameover;
protected:
    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_KEYDOWN,TMessage,f2)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TCleanBomb_main_windows *CleanBomb_main_windows;
//---------------------------------------------------------------------------
#endif
 