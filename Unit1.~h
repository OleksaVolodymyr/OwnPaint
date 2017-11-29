//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <JPEG.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *New1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *N2;
        TMenuItem *Exit1;
        TMenuItem *Help1;
        TMenuItem *About1;
        TImage *Image1;
        TImage *Image2;
        TImage *Image4;
        TOpenPictureDialog *OpenPictureDialog1;
        TMenuItem *Edit1;
        TMenuItem *MCut;
        TMenuItem *MCopy;
        TMenuItem *MPaste;
        TSaveDialog *SaveDialog1;
        TImage *Image3;
        TColorDialog *ColorDialog1;
        TLabel *Label1;
        TEdit *Edit4;
        TFontDialog *FontDialog1;
        TButton *Button2;
        TButton *Button1;
        TGroupBox *GroupBox1;
        TButton *Button3;
        TButton *Button4;
        TGroupBox *GroupBox2;
        TSpeedButton *SBBrush;
        TSpeedButton *SBColor;
        TSpeedButton *SBRect;
        TSpeedButton *SBPen;
        TSpeedButton *SBLine;
        TSpeedButton *SBRectang;
        TSpeedButton *SBFillRec;
        TSpeedButton *SBErase;
        TSpeedButton *SBElips;
        TEdit *Edit2;
        TEdit *Edit3;
        TSpeedButton *SBText;

        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall MCutClick(TObject *Sender);
        void __fastcall SBBrushClick(TObject *Sender);
        void __fastcall SBColorClick(TObject *Sender);
        void __fastcall Image3MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image4MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image3MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image3MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Edit3Change(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall BColorClick(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall MCopyClick(TObject *Sender);
        void __fastcall MPasteClick(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);




    


private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

};
GetBitmap(int Index, Graphics::TBitmap* Image);
Graphics::TBitmap *test = new Graphics::TBitmap;
Graphics::TBitmap *test2 = new Graphics::TBitmap;
TRect R,R0;
int X0,Y0,X1,Y1;
bool RBegin = false, REnd = false, RDrag = false, RText=false;
int A,S,Z;
int FixX, FixY;
int CurrentX, CurrentY;
bool Painting = false;
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------


#endif
