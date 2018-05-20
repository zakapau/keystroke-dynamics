object Form4: TForm4
  Left = 0
  Top = 0
  Caption = #1056#1077#1075#1080#1089#1090#1088#1072#1094#1080#1103' '#1085#1086#1074#1086#1075#1086' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
  ClientHeight = 315
  ClientWidth = 465
  Color = clBtnFace
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
    Left = 48
    Top = 24
    Width = 362
    Height = 19
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1085#1086#1074#1086#1075#1086' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103' '#1073#1077#1079' '#1087#1088#1086#1073#1077#1083#1086#1074':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 104
    Top = 160
    Width = 269
    Height = 19
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1082#1086#1085#1090#1088#1086#1083#1100#1085#1091#1102' '#1092#1088#1072#1079#1091' 50 '#1088#1072#1079':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label3: TLabel
    Left = 15
    Top = 185
    Width = 433
    Height = 27
    Caption = 'the quick brown fox jumps over the lazy dog'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -22
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label4: TLabel
    Left = 184
    Top = 264
    Width = 68
    Height = 19
    Caption = #1054#1089#1090#1072#1083#1086#1089#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label5: TLabel
    Left = 258
    Top = 264
    Width = 18
    Height = 19
    Caption = '__'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Edit1: TEdit
    Left = 104
    Top = 64
    Width = 257
    Height = 21
    TabOrder = 0
  end
  object Button1: TButton
    Left = 152
    Top = 104
    Width = 153
    Height = 33
    Caption = #1043#1086#1090#1086#1074#1086'!'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 116
    Top = 218
    Width = 257
    Height = 21
    TabOrder = 2
    Visible = False
    OnKeyDown = Edit2KeyDown
    OnKeyUp = Edit2KeyUp
  end
end
