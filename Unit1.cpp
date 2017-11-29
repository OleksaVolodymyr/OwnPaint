//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#define Pi 3.14159;
#include "Unit1.h"
#include "math.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

Graphics::TBitmap *BitMap = new Graphics::TBitmap;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 Image3->Canvas->FillRect(ClientRect);
 Form1->DoubleBuffered = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
Image1->Canvas->Brush->Color = clBlack;
Image2->Canvas->Brush->Color = clWhite;
Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
Image2->Canvas->FillRect(Rect(0,0,Image2->Width,Image2->Height));
int HW = Image4->Width/10;
int i;
for(i=1;i<=100;i++)
{
switch (i)
{
case 1:Image4->Canvas->Brush->Color = clBlack;
        break;
case 2:Image4->Canvas->Brush->Color = clAqua;
        break;
case 312:Image4->Canvas->Brush->Color = clBlue;
        break;
case 4:Image4->Canvas->Brush->Color = clFuchsia;
        break;
case 5:Image4->Canvas->Brush->Color = clGreen;
        break;
case 6:Image4->Canvas->Brush->Color = clLime;
        break;
case 7:Image4->Canvas->Brush->Color = clMaroon;
        break;
case 8:Image4->Canvas->Brush->Color = clRed;
        break;
case 9:Image4->Canvas->Brush->Color = clYellow;
        break;
case 10:Image4->Canvas->Brush->Color = clWhite;
        break;
}
Image4->Canvas->Rectangle((i-1)*HW,0,i*HW,Image4->Height);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
BitMap->Free();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Open1Click(TObject *Sender)
{
if (OpenPictureDialog1->Execute()){
if (strstr (OpenPictureDialog1->FileName.c_str(), ".jpg") != NULL ){
TJPEGImage *jpg1 = new TJPEGImage();
jpg1->LoadFromFile(OpenPictureDialog1->FileName);
Image3->Canvas->Draw(0,0,jpg1);
delete jpg1;
jpg1=NULL;

 }
else
Image3->Picture->LoadFromFile(OpenPictureDialog1->FileName);
BitMap->Assign(Image3->Picture) ;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MCutClick(TObject *Sender)
{
Image3->Picture->Assign(BitMap);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBBrushClick(TObject *Sender)
{
if (((TSpeedButton *)Sender)->Down)
BitMap->Assign(Image3->Picture);
 RBegin = false;
 RDrag = false;
 REnd = false;


}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBColorClick(TObject *Sender)
{
if (((TSpeedButton *)Sender)->Down)
BitMap->Assign(Image3->Picture);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if((Sender == Image4) || SBColor->Down)
{
if (Button == mbLeft)
{Image1->Canvas->Brush->Color =((TImage *)Sender)->Canvas->Pixels[X][Y];
Image1->Canvas->FillRect(Rect(0,0, Image1->Width,Image1->Height) ) ;
}
else
{
Image2->Canvas->Brush->Color =((TImage *)Sender)->Canvas->Pixels[X][Y];
Image2->Canvas->FillRect(Rect(0,0,Image2->Width,Image2->Height));
}
}
else if (SBBrush->Down)
{
if (Button==mbLeft)
Image3->Canvas->Brush->Color = Image1->Canvas->Brush->Color;
else Image3->Canvas->Brush->Color = Image2->Canvas->Brush->Color;
Image3->Canvas->FloodFill(X, Y, Image3->Canvas->Pixels[X][Y],fsSurface);
} 

else
{
  X0 = X;
  Y0 = Y;
  if (SBPen->Down)
  {
// олівець
    Image3->Canvas->MoveTo(X,Y);
    Image3->Canvas->Pen->Color = Image1->Canvas->Brush->Color;
  }
  else if (SBLine->Down)
// линія
  {
   X1 = X;
   Y1 = Y;
   Image3->Canvas->Pen->Mode = pmNotXor;
   Image3->Canvas->Pen->Color = Image1->Canvas->Brush->Color;
  }

  else if (SBBrush->Down)
//заливка
  {
   if (Button==mbLeft)
    Image3->Canvas->Brush->Color = Image1->Canvas->Brush->Color;
   else Image3->Canvas->Brush->Color = Image2->Canvas->Brush->Color;
   Image3->Canvas->FloodFill(X,Y,Image3->Canvas->Pixels[X][Y],fsSurface);
  }
  else if (SBErase->Down)
  {
// резинка
    Form1->Edit2->Show();
    R = Rect(X-A,Y-A,X+A,Y+A);
    Image3->Canvas->DrawFocusRect(R);
    Image3->Canvas->Brush->Color = Image2->Canvas->Brush->Color;
    Image3->Canvas->FillRect(Rect(X-(A-1),Y-(A-1),X+(A-1),Y+(A-1)));
   }
//коло
else if (SBElips->Down)
{
Painting = true;
FixX = X;
FixY = Y;
CurrentX = X;
CurrentY = Y;
}
//текст
else if (SBText->Down)
{
RText=true;
FixX = X;
FixY = Y;
CurrentX = X;
CurrentY = Y;
}
else if (SBRect->Down || SBRectang->Down || SBFillRec->Down)
{
if (REnd)
// дел рамку стару
    {
    Image3->Canvas->DrawFocusRect(R);
    if ((X < R.Right) && (X > R.Left) && (Y > R.Top) && (Y < R.Bottom))
// переміщення виділеного
    {

      RDrag = true;
      REnd = false;
// початкове потоження
      R0 = R;

      BitMap->Assign(Image3->Picture);

      Image3->Canvas->Brush->Color = Image2->Canvas->Brush->Color;
      MCopy->Enabled = false;
      MCut->Enabled = false;
    }
    }
    else
//  рамка фрагмента
    {
      RBegin = true;
      REnd = false;
      R.Top = X;
      R.Bottom = X;
      R.Left = Y;
      R.Right = Y;
      Image3->Canvas->DrawFocusRect(R);
     }
   }
 }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Image4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
//вибір колору
if((Sender == Image4) || SBColor->Down)
{
if (Button == mbLeft)
{Image1->Canvas->Brush->Color =((TImage *)Sender)->Canvas->Pixels[X][Y];
Image1->Canvas->FillRect(Rect(0,0, Image1->Width,Image1->Height) ) ;
}
else
{
Image2->Canvas->Brush->Color =((TImage *)Sender)->Canvas->Pixels[X][Y];
Image2->Canvas->FillRect(Rect(0,0,Image2->Width,Image2->Height));
}
}
else if (SBBrush->Down)
{
if (Button==mbLeft)
Image3->Canvas->Brush->Color = Image1->Canvas->Brush->Color;
else Image3->Canvas->Brush->Color = Image2->Canvas->Brush->Color;
Image3->Canvas->FloodFill(X, Y, Image3->Canvas->Pixels[X][Y],fsSurface);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image3MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
 if (! Shift.Contains(ssLeft))  return;

// лінія
if (SBLine->Down)
{
// стираєм лінію
  Image3->Canvas->MoveTo(X0,Y0);
  Image3->Canvas->LineTo(X1,Y1);
// нова лінія
  Image3->Canvas->MoveTo(X0,Y0);
  Image3->Canvas->LineTo(X,Y);
// координати кінця лінії
  X1 = X;
  Y1 = Y;
}
//олівець
else if (SBPen->Down){
Image3->Canvas->Pen->Width = S;
 Image3->Canvas->LineTo(X,Y);}
 //коло
 else if (SBElips->Down)
 {
 Image3->Canvas->Pen->Mode = pmNotXor;
 Image3->Canvas->Ellipse(FixX, FixY, CurrentX, CurrentY);
 CurrentX = X;
 CurrentY = Y;
 Image3->Canvas->Ellipse(FixX, FixY, CurrentX, CurrentY);
}
//текст
else if (SBText->Down)
{
Image3->Canvas->Brush->Style = bsClear;
Image3->Canvas->TextOutA(CurrentX, CurrentY,Edit4->Text);
CurrentX = X;
CurrentY = Y;
Image3->Canvas->TextOutA(CurrentX, CurrentY,Edit4->Text);
}
else if (SBErase->Down)
   {
// Резинка
    Image3->Canvas->DrawFocusRect(R);
    R = Rect(X-A,Y-A,X+A,Y+A);
    Image3->Canvas->DrawFocusRect(R);
    Image3->Canvas->FillRect(Rect(X-(A-1),Y-(A-1),X+(A-1),Y+(A-1)));
   }
 else if ((SBRect->Down && (RBegin || RDrag))
          || SBRectang->Down || SBFillRec->Down)
 {
  if (RBegin)
   {
// Рамка фрагменту
    Image3->Canvas->DrawFocusRect(R);
    if (X0 < X) { R.Left = X0; R.Right = X; }
    else { R.Left = X; R.Right = X0; }
    if (Y0 < Y) { R.Top = Y0; R.Bottom = Y; }
    else { R.Top = Y; R.Bottom = Y0; }
    Image3->Canvas->DrawFocusRect(R);
   }
  else if (SBRect->Down)
  {
// переміщення
// збереження зображення під фрагментом
   Image3->Canvas->CopyRect(R,BitMap->Canvas,R);
// якщо не натиснутий Ctrl - витираємо старе зображення
   if (! Shift.Contains(ssCtrl))
    Image3->Canvas->FillRect(R0);
//  нове положення фрагмента
   R.Left = R.Left + X - X0;
   R.Right = R.Right + X - X0;
   R.Top = R.Top + Y - Y0;
   R.Bottom = R.Bottom + Y - Y0;
// збереження координат курсору
   X0 = X;
   Y0 = Y;
// фрагмен в новому положені
   Image3->Canvas->CopyRect(R,BitMap->Canvas,R0);
// рамка
   Image3->Canvas->DrawFocusRect(R);
  }
 }
else if (SBPen->Down) {
Image3->Canvas->Pen->Width = S;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image3MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if (SBLine->Down)
{
 Image3->Canvas->MoveTo(X0,Y0);
 Image3->Canvas->LineTo(X1,Y1);
 Image3->Canvas->Pen->Mode = pmCopy;
 Image3->Canvas->MoveTo(X0,Y0);
 Image3->Canvas->LineTo(X,Y);
}
else if (SBRect->Down)
{
 if (RDrag) Image3->Canvas->DrawFocusRect(R);
 if (RBegin && ! REnd)
  {
   REnd = true;
   MCopy->Enabled = true;
   MCut->Enabled = true;
  }
}
 else if (SBRectang->Down)
 {
  Image3->Canvas->Brush->Color = Image1->Canvas->Brush->Color;
  Image3->Canvas->FrameRect(R);
 }
 else if (SBFillRec->Down)
 {
  Image3->Canvas->Brush->Color = Image2->Canvas->Brush->Color;
  Image3->Canvas->Pen->Color = Image1->Canvas->Brush->Color;
  Image3->Canvas->Rectangle(R.Left,R.Top,R.Right,R.Bottom);
 }
 else if (SBElips->Down)
 {
 Image3->Canvas->Pen->Mode = pmCopy;
 Image3->Canvas->Ellipse(FixX, FixY, CurrentX, CurrentY);
 Painting = false;
}
else if (SBText->Down)
{
Image3->Canvas->Brush->Style=bsClear;
Image3->Canvas->Pen->Width = Z;
Image3->Canvas->Pen->Mode = pmCopy;
Image3->Canvas->TextOutA(CurrentX, CurrentY,Edit4->Text);
RText=false;
}
 else if (SBErase->Down) Image3->Canvas->DrawFocusRect(R);
 RBegin = false;
 RDrag = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{

A = StrToFloat(Edit2->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
S = StrToInt(Edit3->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
{
 if (SaveDialog1->Execute())
  {
    BitMap->Assign(Image3->Picture);
    BitMap->SaveToFile(SaveDialog1->FileName);
  }
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
if (ColorDialog1->Execute())
{
Image1->Canvas->Brush->Color=ColorDialog1->Color;
Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BColorClick(TObject *Sender)
{
if (ColorDialog1->Execute())
{
Image1->Canvas->Brush->Color=ColorDialog1->Color;
Image1->Canvas->FillRect(Rect(0,0,Image1->Width,Image1->Height));

}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::New1Click(TObject *Sender)
{
Image3->Canvas->FillRect(ClientRect);
//Image3->Canvas->FillRect(Rect(0,0,Image3->Width,Image3->Height));

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 if(FontDialog1->Execute())
{
Image3->Canvas->Font = FontDialog1->Font;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{

int R,G,B; COLORREF crColor; int F;
 for(int y=0;y<Image3->Height;y++)
 for(int x=0;x<Image3->Width;x++)
 {
    crColor = (COLORREF) Image3->Canvas->Pixels[x][y]; //Визначаємо колір вікна
       R=GetRValue(crColor);
       G=GetGValue(crColor);
       B=GetBValue(crColor);
       F = (R+G+B)/3;
    Image3->Canvas->Pixels[x][y] = (TColor) RGB(F,F,F);  //міняємо колір точок
 }
}

//---------------------------------------------------------------------------

 void blur(Graphics::TBitmap *Dest, Graphics::TBitmap *Source, int radius)
{
BitMap->PixelFormat=pf24bit;
Graphics::TBitmap *mask_bitmap = new Graphics::TBitmap;
mask_bitmap->Width = Source->Width;
mask_bitmap->Height = Source->Height;
int counter;
mask_bitmap->Canvas->Brush->Style = bsSolid;
struct col {int r,g,b;} temp;
for(int i=0;i<Source->Width;i++)
{
   for(int j=0;j<Source->Height;j++)
   {
      ZeroMemory(&temp,sizeof(temp));
      counter=0;
      mask_bitmap->Canvas->Brush->Color = clBlack;
      mask_bitmap->Canvas->Ellipse(i-radius,j-radius,i+radius,j+radius);
      for(int i2=i-radius;i2<i+radius;i2++)
      {
         for(int j2=j-radius;j2<j+radius;j2++)
         {
            if(i2>0&j2>0&i2<mask_bitmap->Width&j2<mask_bitmap->Height)
            {
               if(mask_bitmap->Canvas->Pixels[i][j]==clBlack)
               {
                  temp.r+=GetRValue(TColor(Source->Canvas->Pixels[i2][j2]));
                  temp.g+=GetGValue(TColor(Source->Canvas->Pixels[i2][j2]));
                  temp.b+=GetBValue(TColor(Source->Canvas->Pixels[i2][j2]));
                  counter++;
               }
            }
         }
      }
      if(counter!=0)
      {
         temp.r/=counter;
         temp.g/=counter;
         temp.b/=counter;
         Dest->Canvas->Pixels[i][j] = TColor(RGB(temp.r,temp.g,temp.b));
         mask_bitmap->Canvas->Brush->Color = clWhite;
         mask_bitmap->Canvas->FillRect(Rect(i-radius,j-radius,i+radius,j+radius));
      }
      else {Dest->Canvas->Pixels[i][j] = Source->Canvas->Pixels[i][j];}
   }
}
delete mask_bitmap;
}
void __fastcall TForm1::Button4Click(TObject *Sender)
{
Graphics::TBitmap *test2 = new Graphics::TBitmap;
test2->Width=Image3->Width;test2->Height = Image3->Height;
blur(test2,BitMap,2);
Image3->Canvas->Draw(0,0,test2);
delete test2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MCopyClick(TObject *Sender)
{

 Graphics::TBitmap *BMCopy = new Graphics::TBitmap;
 Image3->Canvas->DrawFocusRect(R);
 BMCopy->Width = R.Right - R.Left;
 BMCopy->Height = R.Bottom - R.Top;
 try
 {
  BMCopy->Canvas->CopyRect(Rect(0,0,BMCopy->Width,BMCopy->Height),Image3->Canvas,R);
  Image3->Canvas->DrawFocusRect(R);

  Clipboard()->Assign(BMCopy);
  if (Sender == MCut)
   {
    Image3->Canvas->Brush->Color = clWhite;
    Image3->Canvas->FillRect(R);
   }
 }
__finally
{
  BMCopy->Free();
}
}        

//---------------------------------------------------------------------------

void __fastcall TForm1::MPasteClick(TObject *Sender)
{
 Graphics::TBitmap *BMCopy = new Graphics::TBitmap;
 try
 {
  try
  {
   BMCopy->LoadFromClipboardFormat(CF_BITMAP,
                  Clipboard()->GetAsHandle(CF_BITMAP),0);
//   BMCopy->Assign(Clipboard());
   Image3->Canvas->CopyRect(Rect(0,0,BMCopy->Width,BMCopy->Height),
         BMCopy->Canvas,Rect(0,0,BMCopy->Width,BMCopy->Height));
  }       
  __finally
  {
   BMCopy->Free();
  }
 }
  catch (EInvalidGraphic&)
 {
  ShowMessage("Error формат графіки");
 }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
Form1->Close();
}
//---------------------------------------------------------------------------


