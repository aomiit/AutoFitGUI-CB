//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Datasnap.Provider.hpp>
#include "UnitASFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TASFrame *ASFrame;
const int OriWidth = 1200;
const int OriHeight = 800;

//---------------------------------------------------------------------------
__fastcall TASFrame::TASFrame(TComponent* Owner)
	: TFrame(Owner)
{
	fScrResolutionRateH = 1;
	fScrResolutionRateW = 1;
    fIsFitDeviceDone = false;
	try
	{
		if(!fIsFitDeviceDone)
		{
			FitDeviceResolution();
			fIsFitDeviceDone = true;
        }
	}
	catch(...)
	{
		fIsFitDeviceDone = false;
	}
}
//---------------------------------------------------------------------------
void TASFrame::FitDeviceResolution()
{
	int i;
	TList *LocList = new TList();
	int LocFontSize;
	TFont *LocFont;
	TComponent *LocCmp;
	double LocFontRate;
	TRect LocRect;
	TControl *LocCtl;

	try
	{
		try
		{
			if (Screen->Width != OriWidth || Screen->Height != OriHeight)
			{
				fScrResolutionRateH = (double)Screen->Height/OriHeight;
				fScrResolutionRateW = (double)Screen->Width/OriWidth;
				try
				{
					if(fScrResolutionRateH < fScrResolutionRateW)
					{
						LocFontRate = fScrResolutionRateH;
					}
					else
					{
						LocFontRate = fScrResolutionRateW;
					}
				}
				__finally
				{
				  	ReleaseDC(0, GetDC(0));
				}

				for(i = this->ComponentCount-1; i >= 0; --i)
				{
					LocCmp = this->Components[i];
					if(LocCmp->InheritsFrom(__classid(TControl)))
					{
						LocList->Add(LocCmp);

						LocFont = (TFont *)GetObjectProperty(LocCmp,"Font");
						if(LocFont != NULL)
						{
							LocFontSize = int(LocFontRate*LocFont->Size);
							LocFont->Size = LocFontSize;
						}

						if(LocCmp->InheritsFrom(__classid(TListView)))
						{
							int cc = ((TListView*)LocCmp)->Columns->Count;
							for(int ik = 0; ik < cc; ++ik)
							{
								TListColumn *it = ((TListView*)LocCmp)->Columns->Items[ik];
								it->MaxWidth = int(it->MaxWidth*fScrResolutionRateW);
								it->MinWidth = int(it->MinWidth*fScrResolutionRateW);
								it->Width = int(it->Width*fScrResolutionRateW);
							}
						}
					}
				}

				fPosition.Length = LocList->Count+1;

				for(i = 0; i < LocList->Count; ++i)
				{
					fPosition[i+1] = ((TControl*)(LocList->Items[i]))->BoundsRect;
				}

				fPosition[0] = this->BoundsRect;

				LocRect.Left = int(fPosition[0].Left*fScrResolutionRateW);
				LocRect.Right = int(fPosition[0].Right*fScrResolutionRateW);
				LocRect.Top = int(fPosition[0].Top*fScrResolutionRateH);
				LocRect.Bottom = int(fPosition[0].Bottom*fScrResolutionRateH);
				this->SetBounds(LocRect.Left,LocRect.Top,LocRect.Right-LocRect.Left,LocRect.Bottom-LocRect.Top);

				i = LocList->Count-1;
				while( i >= 0)
				{
					LocCtl = (TControl*)(LocList->Items[i]);

					if(LocCtl->Align==alClient)
					{
						--i;
						continue;
					}

					LocRect.Left = int(fPosition[i+1].Left*fScrResolutionRateW);
					LocRect.Right = int(fPosition[i+1].Right*fScrResolutionRateW);
					LocRect.Top = int(fPosition[i+1].Top*fScrResolutionRateH);
					LocRect.Bottom = int(fPosition[i+1].Bottom*fScrResolutionRateH);
					LocCtl->SetBounds(LocRect.Left,LocRect.Top,LocRect.Right-LocRect.Left,LocRect.Bottom-LocRect.Top);

				  	--i;
				}
			}
		}
		catch(Exception &e)
		{
			throw Exception(e.Message);
		}
	}
	__finally
	{
		LocList->Free();
    }
}
//---------------------------------------------------------------------------
