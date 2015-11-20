class CMenuSystem
{
public:
	CMenuSystem();
};

float VAR_RENDER = 0.0f; // Again, another example value

CMenuSystem::CMenuSystem()
{

	int SizeX = 512;
	int SizeY = 512;

	LWindow* MainWindow = new LWindow();
	MainWindow->SetSize( SizeX, SizeY );
	MainWindow->SetPos( 200, 200 );
	MainWindow->SetTitle("LoliSmasher");

	LTabPanel* TabProperty = new LTabPanel();
	TabProperty->SetParent( MainWindow );
	TabProperty->SetPos( 10, 35 );
	TabProperty->SetSize( SizeX - 20, SizeY - 70 );
	
	LBaseObject* AimbotTab = TabProperty->AddTab("Aimbot");
	LBaseObject* VisualTab = TabProperty->AddTab("Visual");
	LBaseObject* MiscTab   = TabProperty->AddTab("Misc");
	LBaseObject* HvhTab    = TabProperty->AddTab("HvH");
	LBaseObject* ColorTab  = TabProperty->AddTab("Color");
	
	int BoxOffset = 25;
	int Padding = 10;

	// Aimbot

	LCheckBox* AimbotEnabled = new LCheckBox();
	AimbotEnabled->SetPos(Padding, Padding);
	AimbotEnabled->SetText( "Enabled" );
	AimbotEnabled->SetVar( Variables.GetVar("aimbot_enabled")->GetPointer() );
	AimbotEnabled->SetParent( AimbotTab );

	LCheckBox* AimbotIgnoreTeam = new LCheckBox();
	AimbotIgnoreTeam->SetPos(Padding, Padding + BoxOffset);
	AimbotIgnoreTeam->SetText( "Ignore Team" );
	AimbotIgnoreTeam->SetVar( Variables.GetVar("aimbot_ignoreteam")->GetPointer() );
	AimbotIgnoreTeam->SetParent( AimbotTab );

	LCheckBox* AimbotIgnoreFriends = new LCheckBox();
	AimbotIgnoreFriends->SetPos(Padding, Padding + BoxOffset * 2);
	AimbotIgnoreFriends->SetText( "Ignore Friends" );
	AimbotIgnoreFriends->SetVar( Variables.GetVar("aimbot_ignorefriends")->GetPointer() );
	AimbotIgnoreFriends->SetParent( AimbotTab );

	LCheckBox* AimbotNextShot = new LCheckBox();
	AimbotNextShot->SetPos(Padding, Padding + BoxOffset * 3);
	AimbotNextShot->SetText( "Next Shot" );
	AimbotNextShot->SetVar( Variables.GetVar("aimbot_nextshot")->GetPointer() );
	AimbotNextShot->SetParent( AimbotTab );

	LCheckBox* AimbotLoudAim = new LCheckBox();
	AimbotLoudAim->SetPos(Padding, Padding + BoxOffset * 4);
	AimbotLoudAim->SetText( "Loud Aim" );
	AimbotLoudAim->SetVar( Variables.GetVar("aimbot_loudaim")->GetPointer() );
	AimbotLoudAim->SetParent( AimbotTab );

	int OP1 = 1;
	int OP2 = 2;
	int OP3 = 3;

	LComboBox* AimbotType = new LComboBox();
	AimbotType->SetPos(200, 10);
	AimbotType->SetSize(120, 20); // You can change the width but keep the height at 20
	AimbotType->SetParent(AimbotTab);
	AimbotType->SetText("Aimbot Type");
	AimbotType->AddOption("Normal", &OP1);
	AimbotType->AddOption("Legit", &OP2);
	AimbotType->AddOption("Rage", &OP3);

	// Visual

	LCheckBox* VisualShowPlayers = new LCheckBox();
	VisualShowPlayers->SetPos(Padding, Padding);
	VisualShowPlayers->SetText( "Show Players" );
	VisualShowPlayers->SetVar( Variables.GetVar("visuals_showplayers")->GetPointer() );
	VisualShowPlayers->SetParent( VisualTab );

	LCheckBox* VisualUse3DBox = new LCheckBox();
	VisualUse3DBox->SetPos(Padding, Padding + BoxOffset);
	VisualUse3DBox->SetText( "Use 3D Box" );
	VisualUse3DBox->SetVar( Variables.GetVar("visuals_use3dbox")->GetPointer() );
	VisualUse3DBox->SetParent( VisualTab );

	LCheckBox* VisualHealthBars = new LCheckBox();
	VisualHealthBars->SetPos(Padding, Padding + BoxOffset * 2);
	VisualHealthBars->SetText( "Healthbars" );
	VisualHealthBars->SetVar( Variables.GetVar("visuals_healthbars")->GetPointer() );
	VisualHealthBars->SetParent( VisualTab );

	LCheckBox* VisualCrosshair = new LCheckBox();
	VisualCrosshair->SetPos(Padding, Padding + BoxOffset * 3);
	VisualCrosshair->SetText( "Show Crosshair" );
	VisualCrosshair->SetVar( Variables.GetVar("visuals_crosshair")->GetPointer() );
	VisualCrosshair->SetParent( VisualTab );

	// Misc

	LCheckBox* MiscSpreadCompensate = new LCheckBox();
	MiscSpreadCompensate->SetPos( Padding, Padding );
	MiscSpreadCompensate->SetText( "Spread Compensation" );
	MiscSpreadCompensate->SetVar( Variables.GetVar("misc_spreadcompensation")->GetPointer() );
	MiscSpreadCompensate->SetParent( MiscTab );

	LCheckBox* MiscSafeMode = new LCheckBox();
	MiscSafeMode->SetPos(Padding, Padding + BoxOffset);
	MiscSafeMode->SetText( "CAC/SMAC Safe" );
	MiscSafeMode->SetVar( Variables.GetVar("misc_cacsafe")->GetPointer() );
	MiscSafeMode->SetParent( MiscTab );

	LCheckBox* MiscSpeedhack = new LCheckBox();
	MiscSpeedhack->SetPos(Padding, Padding + BoxOffset * 2);
	MiscSpeedhack->SetText( "Speedhack" );
	MiscSpeedhack->SetVar( Variables.GetVar("misc_speedhack")->GetPointer() );
	MiscSpeedhack->SetParent( MiscTab );

	LSlider* MiscSpeedFactor = new LSlider();
	MiscSpeedFactor->SetPos(Padding, Padding + BoxOffset * 4);
	MiscSpeedFactor->SetSize( SizeX - 30 - Padding, 10 );
	MiscSpeedFactor->SetText( "Speedhack Factor" );
	MiscSpeedFactor->SetVar( (float*)Variables.GetVar("misc_speedfactor")->GetPointer() );
	MiscSpeedFactor->SetRange( 1, 15 );
	MiscSpeedFactor->SetDefault( 1 );
	MiscSpeedFactor->SetParent( MiscTab );

	LCheckBox* MiscBunnyhop = new LCheckBox();
	MiscBunnyhop->SetPos(Padding, Padding + BoxOffset * 5);
	MiscBunnyhop->SetText( "Bunnyhop" );
	MiscBunnyhop->SetVar( Variables.GetVar("misc_bunnyhop")->GetPointer() );
	MiscBunnyhop->SetParent( MiscTab );

	LCheckBox* MiscAutostrafe = new LCheckBox();
	MiscAutostrafe->SetPos(Padding, Padding + BoxOffset * 6);
	MiscAutostrafe->SetText( "Autostrafe" );
	MiscAutostrafe->SetVar( Variables.GetVar("misc_autostrafe")->GetPointer() );
	MiscAutostrafe->SetParent( MiscTab );

	LCheckBox* MiscHitsounds = new LCheckBox();
	MiscHitsounds->SetPos(Padding, Padding + BoxOffset * 7);
	MiscHitsounds->SetText( "Hitsounds" );
	MiscHitsounds->SetVar( Variables.GetVar("misc_hitsounds")->GetPointer() );
	MiscHitsounds->SetParent( MiscTab );

	/*
	Variables.CreateVar( "hvh_aaa" );
	Variables.CreateVar( "hvh_aptaaa" );
	Variables.CreateVar( "hvh_aa" );
	Variables.CreateVar( "hvh_aptaa" );
	Variables.CreateVar( "hvh_yawtype" );
	Variables.CreateVar( "hvh_pitchtype" );
	Variables.CreateVar( "hvh_fakeduck" );
	Variables.CreateVar( "hvh_fakelag" );
	Variables.CreateVar( "hvh_fakelagfactor" );
	Variables.CreateVar( "hvh_killstreaks" );
	*/

	// HvH

	LCheckBox* HvhAntiAntiAim = new LCheckBox();
	HvhAntiAntiAim->SetPos(Padding, Padding);
	HvhAntiAntiAim->SetText( "Anti-Anti-Aim" );
	HvhAntiAntiAim->SetVar( Variables.GetVar("hvh_aaa")->GetPointer() );
	HvhAntiAntiAim->SetParent( HvhTab );

	LCheckBox* HvhAptAntiAntiAim = new LCheckBox();
	HvhAptAntiAntiAim->SetPos(Padding, Padding + BoxOffset);
	HvhAptAntiAntiAim->SetText( "Adaptive Anti-Anti-Aim" );
	HvhAptAntiAntiAim->SetVar( Variables.GetVar("hvh_aptaaa")->GetPointer() );
	HvhAptAntiAntiAim->SetParent( HvhTab );

	LCheckBox* HvhAntiAim = new LCheckBox();
	HvhAntiAim->SetPos(Padding, Padding + BoxOffset * 2);
	HvhAntiAim->SetText( "Anti-Aim" );
	HvhAntiAim->SetVar( Variables.GetVar("hvh_aa")->GetPointer() );
	HvhAntiAim->SetParent( HvhTab );

	LCheckBox* HvhAptAntiAim = new LCheckBox();
	HvhAptAntiAim->SetPos(Padding, Padding + BoxOffset * 3);
	HvhAptAntiAim->SetText( "Adaptive Anti-Aim" );
	HvhAptAntiAim->SetVar( Variables.GetVar("hvh_aptaa")->GetPointer() );
	HvhAptAntiAim->SetParent( HvhTab );

	LSlider* HvhYawType = new LSlider();
	HvhYawType->SetPos(Padding, Padding + BoxOffset * 5);
	HvhYawType->SetSize(SizeX - 30 - Padding, 10);
	HvhYawType->SetText( "Yaw AA Setting" );
	HvhYawType->SetVar( (float*)Variables.GetVar("hvh_yawtype")->GetPointer() );
	HvhYawType->SetRange( 1, 5 );
	HvhYawType->SetDefault( 1 );
	HvhYawType->SetParent( HvhTab );

	LSlider* HvhPitchType = new LSlider();
	HvhPitchType->SetPos(Padding, Padding + BoxOffset * 7);
	HvhPitchType->SetSize(SizeX - 30 - Padding, 10);
	HvhPitchType->SetText( "Pitch AA Setting" );
	HvhPitchType->SetVar( (float*)Variables.GetVar("hvh_pitchtype")->GetPointer() );
	HvhPitchType->SetRange( 1, 5 );
	HvhPitchType->SetDefault( 1 );
	HvhPitchType->SetParent( HvhTab );

	LCheckBox* HvhFakeDuck = new LCheckBox();
	HvhFakeDuck->SetPos(Padding, Padding + BoxOffset * 8);
	HvhFakeDuck->SetText( "Fake Duck" );
	HvhFakeDuck->SetVar( Variables.GetVar("hvh_fakeduck")->GetPointer() );
	HvhFakeDuck->SetParent( HvhTab );

	LCheckBox* HvhFakeLag = new LCheckBox();
	HvhFakeLag->SetPos(Padding, Padding + BoxOffset * 9);
	HvhFakeLag->SetText( "Fake Lag" );
	HvhFakeLag->SetVar( Variables.GetVar("hvh_fakelag")->GetPointer() );
	HvhFakeLag->SetParent( HvhTab );

	LSlider* HvhFakeLagFactor = new LSlider();
	HvhFakeLagFactor->SetPos(Padding, Padding + BoxOffset * 11);
	HvhFakeLagFactor->SetSize( SizeX - 30 - Padding, 10 );
	HvhFakeLagFactor->SetText( "Fake Lag Factor" );
	HvhFakeLagFactor->SetVar( (float*)Variables.GetVar("hvh_fakelagfactor")->GetPointer() );
	HvhFakeLagFactor->SetRange( 1, 15 );
	HvhFakeLagFactor->SetDefault( 1 );
	HvhFakeLagFactor->SetParent( HvhTab );

	// Color

	LColorPicker* FGColor = new LColorPicker();
	FGColor->SetPos(Padding, Padding);
	FGColor->SetVar(&LMenuFG);
	FGColor->SetColor(LMenuFG);
	FGColor->SetText("Foreground Color");
	FGColor->SetParent(ColorTab);

	LColorPicker* BGColor = new LColorPicker();
	BGColor->SetPos(Padding, Padding + 120);
	BGColor->SetVar(&LMenuBG);
	BGColor->SetColor(LMenuBG);
	BGColor->SetText("Background Color");
	BGColor->SetParent(ColorTab);

	//

	TabProperty->SetCurrentTab(0);

}