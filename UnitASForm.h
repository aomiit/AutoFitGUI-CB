//---------------------------------------------------------------------------

#ifndef UnitASFormH
#define UnitASFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

//---------------------------------------------------------------------------
class TFormASForm : public TForm
{
__published:	// IDE-managed Components

private:	// User declarations
	double fScrResolutionRateW;
	double fScrResolutionRateH;
	bool fIsFitDeviceDone;
	DynamicArray<TRect> fPosition;

	void FitDeviceResolution();
	void ResizeBitmap(TBitmap *Bitmap,double fRateW,double fRateH);
protected:
	__property bool IsFitDeviceDone = {read=fIsFitDeviceDone};
	__property double ScrResolutionRateH = {read=fScrResolutionRateH};
	__property double ScrResolutionRateW = {read=fScrResolutionRateW};

public:		// User declarations

	__fastcall TFormASForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormASForm *FormASForm;
//---------------------------------------------------------------------------
#endif
