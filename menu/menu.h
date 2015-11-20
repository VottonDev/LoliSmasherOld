#include <vector>

std::vector<void*> PanelObjects;
std::vector<void*> PanelObjectsSorted;

Color LMenuFG = Color( 0, 150, 255, 255 );
Color LMenuBG = Color( 0, 0, 0, 230 );

#include "inputsystem.h"
#include "elements/baseobject.h"
#include "elements/window.h"
#include "elements/checkbox.h"
#include "elements/form.h"
#include "elements/slider.h"
#include "elements/tabs.h"
#include "elements/colorpicker.h"
#include "elements/combobox.h"

#include "setup.h"

void MenuThink()
{

	if ( GetAsyncKeyState( VK_INSERT ) )
	{
		InputManager.ToggleMenu();
		Sleep(300);
	}

	if (GetAsyncKeyState( VK_LBUTTON ))
	{
		InputManager.Clicked = true;
	}
	else
	{
		InputManager.Clicked = false;
	}

	if ( !InputManager.IsMenuEnabled() )
	{
		return;
	}

	for (void* vPanel : PanelObjects)
	{
		LBaseObject* Panel = (LBaseObject*)vPanel;
		if (Panel == NULL) continue;
		if (!Panel->GetVisible()) continue;
		Panel->Tick();
	}

}

void MenuPaint()
{

	if ( !InputManager.IsMenuEnabled() )
	{
		return;
	}

	for (void* vPanel : PanelObjects)
	{
		LBaseObject* Panel = (LBaseObject*)vPanel;
		if (Panel == NULL) continue;
		if (!Panel->GetVisible()) continue;
		Panel->Paint();
	}
}
