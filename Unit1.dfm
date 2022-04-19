object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 484
  ClientWidth = 822
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 336
    Top = 16
    Width = 113
    Height = 15
  end
  object Label2: TLabel
    Left = 336
    Top = 88
    Width = 113
    Height = 17
  end
  object Label3: TLabel
    Left = 336
    Top = 160
    Width = 113
    Height = 17
  end
  object Label4: TLabel
    Left = 352
    Top = 53
    Width = 24
    Height = 15
    Caption = #1048#1084#1103
  end
  object Label5: TLabel
    Left = 352
    Top = 125
    Width = 55
    Height = 15
    Caption = #1054#1087#1080#1089#1072#1085#1080#1077
  end
  object Label6: TLabel
    Left = 352
    Top = 200
    Width = 40
    Height = 15
    Caption = #1056#1072#1079#1084#1077#1088
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 16
    Width = 265
    Height = 268
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = #1048#1085#1076#1077#1082#1089
        Width = 68
      end
      item
        Position = 1
        Text = #1048#1084#1103
        Width = 189
      end>
  end
  object Button1: TButton
    Left = 32
    Top = 290
    Width = 75
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 128
    Top = 290
    Width = 75
    Height = 25
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 336
    Top = 290
    Width = 75
    Height = 25
    Caption = 'Button3'
    TabOrder = 3
  end
  object Button4: TButton
    Left = 440
    Top = 290
    Width = 75
    Height = 25
    Caption = 'Button4'
    TabOrder = 4
  end
end
