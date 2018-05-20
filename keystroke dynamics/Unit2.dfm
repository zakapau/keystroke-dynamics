object Form2: TForm2
  Left = 0
  Top = 0
  Caption = #1042#1074#1086#1076' '#1082#1086#1085#1090#1088#1086#1083#1100#1085#1086#1081' '#1092#1088#1072#1079#1099
  ClientHeight = 200
  ClientWidth = 529
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 64
    Top = 18
    Width = 272
    Height = 13
    Caption = #1055#1088#1086#1074#1077#1088#1100#1090#1077' '#1072#1085#1075#1083#1080#1081#1089#1082#1091#1102' '#1088#1072#1089#1082#1083#1072#1076#1082#1091' '#1080' '#1074#1074#1077#1076#1080#1090#1077' '#1092#1088#1072#1079#1091': '
  end
  object Label2: TLabel
    Left = 312
    Top = 160
    Width = 151
    Height = 13
    Caption = #1058#1091#1090' '#1073#1091#1076#1077#1090' '#1095#1090#1086'-'#1090#1086' '#1087#1086#1103#1074#1083#1103#1090#1100#1089#1103
  end
  object Label3: TLabel
    Left = 64
    Top = 37
    Width = 317
    Height = 19
    Caption = 'the quick brown fox jumps over the lazy dog'
    Color = clBlue
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
  end
  object Edit1: TEdit
    Left = 64
    Top = 64
    Width = 385
    Height = 21
    TabOrder = 0
    OnKeyDown = Edit1KeyDown
    OnKeyUp = Edit1KeyUp
  end
  object Button1: TButton
    Left = 64
    Top = 104
    Width = 161
    Height = 33
    Caption = #1042#1074#1077#1089#1090#1080' '#1079#1072#1085#1086#1074#1086
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 296
    Top = 104
    Width = 153
    Height = 33
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 40
    Top = 155
    Width = 242
    Height = 25
    Caption = #1047#1072#1085#1077#1089#1090#1080' '#1076#1072#1085#1085#1099#1077' '#1086' '#1074#1074#1086#1076#1072#1093' '#1080' '#1086#1096#1080#1073#1082#1072#1093' '#1074' '#1092#1072#1081#1083' '
    TabOrder = 3
    OnClick = Button3Click
  end
end
