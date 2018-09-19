object set_bomb: Tset_bomb
  Left = 324
  Top = 277
  Width = 239
  Height = 168
  BorderIcons = [biSystemMenu]
  Caption = #33258#23450#20041#35774#32622'...'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 64
    Width = 41
    Height = 13
    AutoSize = False
    Caption = #23485#24230
  end
  object Label2: TLabel
    Left = 24
    Top = 24
    Width = 41
    Height = 13
    AutoSize = False
    Caption = #39640#24230
  end
  object Label3: TLabel
    Left = 24
    Top = 104
    Width = 41
    Height = 13
    AutoSize = False
    Caption = #38647#25968
  end
  object UpDown1: TUpDown
    Left = 127
    Top = 56
    Width = 15
    Height = 21
    Associate = Edit1
    Min = 10
    Max = 50
    Position = 15
    TabOrder = 0
    Wrap = False
  end
  object Edit1: TEdit
    Left = 70
    Top = 56
    Width = 57
    Height = 21
    TabOrder = 1
    Text = '15'
    OnKeyPress = Edit2KeyPress
  end
  object UpDown2: TUpDown
    Left = 127
    Top = 16
    Width = 15
    Height = 21
    Associate = Edit2
    Min = 10
    Max = 30
    Position = 15
    TabOrder = 2
    Wrap = False
  end
  object Edit2: TEdit
    Left = 70
    Top = 16
    Width = 57
    Height = 21
    TabOrder = 3
    Text = '15'
    OnKeyPress = Edit2KeyPress
  end
  object UpDown3: TUpDown
    Left = 127
    Top = 96
    Width = 15
    Height = 21
    Associate = Edit3
    Min = 10
    Position = 40
    TabOrder = 4
    Wrap = False
    OnChanging = UpDown3Changing
  end
  object Edit3: TEdit
    Left = 70
    Top = 96
    Width = 57
    Height = 21
    TabOrder = 5
    Text = '40'
    OnKeyPress = Edit2KeyPress
  end
  object Button1: TButton
    Left = 160
    Top = 32
    Width = 65
    Height = 25
    Caption = #30830#23450
    ModalResult = 1
    TabOrder = 6
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 160
    Top = 80
    Width = 65
    Height = 25
    Caption = #21462#28040
    ModalResult = 2
    TabOrder = 7
  end
end
