//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OpenButtonClick(TObject *Sender)
{
  OpenDialog1->Filter = TMediaCodecManager::GetFilterString();
  if (OpenDialog1->Execute())
  {
	PauseButton->Enabled = true;
	ClearButton->Enabled = true;
	MediaPlayer1->FileName = OpenDialog1->FileName;

	if (MediaPlayer1->Media != NULL)
	{
	  Label1->Text = IntToStr((int) MediaPlayer1->Media->VideoSize.Truncate().X) + "x" +
					 IntToStr((int) MediaPlayer1->Media->VideoSize.Truncate().Y) + "px " +
					 IntToStr((__int64) MediaPlayer1->Media->Duration / MediaTimeScale) + "s";
	  TrackBar1->Max = MediaPlayer1->Media->Duration;
	  VolumeTrack->Value = 1 - MediaPlayer1->Media->Volume;

	  MediaPlayer1->Play();
	}
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PauseButtonClick(TObject *Sender)
{
  if (MediaPlayer1->State == TMediaState::Playing)
  {
	PauseButton->Text = "Play";
	MediaPlayer1->Stop();
  }
  else
  {
	PauseButton->Text = "Pause";
	MediaPlayer1->Play();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TrackBar1Change(TObject *Sender)
{
  if (TrackBar1->Tag == 0)
  {
	MediaPlayer1->CurrentTime = (__int64) TrackBar1->Value;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
  TrackBar1->Tag = 1;
  TrackBar1->Value = MediaPlayer1->CurrentTime;
  TrackBar1->Tag = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CheckBox1Change(TObject *Sender)
{
  MediaPlayerControl1->Visible = CheckBox1->IsChecked;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::VolumeTrackChange(TObject *Sender)
{
  MediaPlayer1->Volume = 1 - VolumeTrack->Value;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ClearButtonClick(TObject *Sender)
{
  MediaPlayer1->Clear();
  PauseButton->Enabled = false;
  ClearButton->Enabled = false;
}
//---------------------------------------------------------------------------
