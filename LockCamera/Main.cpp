#include "Main.h"
#include "stdafx.h"

static const int DRAW_TIME = 100;
static int currentDrawTime = 0;

static std::string curMsg = "";

bool ms_bEnabled = false;

void ToggleMod()
{
	if (ms_bEnabled)
	{
		ms_bEnabled = false;
		curMsg = "LockCameraV Deactivated";
	}
	else
	{
		curMsg = "LockCameraV Activated";
		ms_bEnabled = true;
	}
	currentDrawTime = 0;
}

void OnTick()
{
	if (ms_bEnabled)
	{
		//Fix camera jitteriness
		if (!PLAYER::IS_PLAYER_FREE_AIMING(0))
		{
			PAD::DISABLE_CONTROL_ACTION(0, 1, true);
			PAD::DISABLE_CONTROL_ACTION(0, 2, true);
		}
		else
		{
			PAD::ENABLE_CONTROL_ACTION(0, 1, true);
			PAD::ENABLE_CONTROL_ACTION(0, 2, true);
		}

		CAM::_SET_GAMEPLAY_CAM_RELATIVE_ROTATION(0, 0, 0);
	}

	if (currentDrawTime <= DRAW_TIME)
	{
		DrawScreenText(curMsg, { .5f, .8f }, .4, {255, 255, 255}, false);
		currentDrawTime += 1;
	}
}

namespace Main
{
	void OnRun()
	{
		while (true)
		{
			OnTick();
			scriptWait(0);
		}
	}

	void OnKeyboardInput(DWORD ulKey, WORD usRepeats, BYTE ucScanCode, BOOL bIsExtended, BOOL bIsWithAlt, BOOL bWasDownBefore, BOOL bIsUpNow)
	{
		static bool c_bIsCtrlPressed = false;

		if (ulKey == VK_CONTROL)
		{
			c_bIsCtrlPressed = !bIsUpNow;
		}
		else if (c_bIsCtrlPressed && !bWasDownBefore)
		{
			if (ulKey == VK_OEM_PLUS)
			{
				ToggleMod();
			}
		}
	}
}
