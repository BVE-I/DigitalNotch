// Ats.cpp : DLL アプリケーション用のエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "atsplugin.h"
#include "DigitalNotchIni.h"
#include "doorCloseingSecurity.h"
#include "DigitalNotch.h"
#include <stdio.h>
#include <cmath>
#include <vector>

/// このATSプラグインの、コンピュータ上の絶対パス
char g_module_dir[MAX_PATH];
using namespace std;

BOOL APIENTRY DllMain(
	HINSTANCE hinstDLL,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:

	{
		char fullpath[MAX_PATH];
		char drive[MAX_PATH],
			dir[MAX_PATH];
		char* posIni;

		GetModuleFileNameA(hinstDLL, fullpath, MAX_PATH);
		_splitpath_s(fullpath, drive, MAX_PATH, dir, MAX_PATH, 0, 0, 0, 0);

		strcpy_s(g_module_dir, drive);
		strcat_s(g_module_dir, dir);

		//パスから.dllの位置を検索
		posIni = strstr(fullpath, ".dll");

		// .dllを.iniに置換
		memmove(posIni, ".ini", 4);

		// INIファイルをロードして結果を取得
		if (!g_ini.load(fullpath))
			g_ini.save(fullpath);
	}

	break;

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

ATS_API int WINAPI GetPluginVersion()
{
	return ATS_VERSION;
}

ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec)
{
	g_svcBrake = vehicleSpec.BrakeNotches;
	g_emgBrake = g_svcBrake + 1;
}

ATS_API void WINAPI Initialize(int brake)
{
	g_speed = 0;
}

ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehicleState, int *panel, int *sound)
{
	g_speed = vehicleState.Speed;
	g_output.Brake = g_brakeNotch;
	g_output.Power = g_powerNotch;
	g_output.Reverser = g_doorCloseingSecurity.main(g_pilotlamp, g_reverser); // 戸閉保安出力
	if (g_ini.NotchValue.Interval <= 0) {
		BrakeData = g_brakeNotch;
		PowerData = g_powerNotch;
	}
	else {
		NotchUpdate = bool((vehicleState.Time / g_ini.NotchValue.Interval) % 2);
		if (!(NotchUpdateOld) && NotchUpdate) {
			BrakeData = g_brakeNotch;
			PowerData = g_powerNotch;
		}
	}
	if (g_ini.PanelValue.Interval <= 0) {
		for (unsigned int i = 0; i <= PanelData.size() + 1; i++) {
			if (PanelData[i] != panel[i]) {
				PanelData[i] = panel[i];
			}
		}
	}
	else {
		PanelUpdate = bool((vehicleState.Time / g_ini.PanelValue.Interval) % 2);
		if (!(PanelUpdateOld) && PanelUpdate) {
			for (unsigned int i = 0; i <= PanelData.size() + 1; i++) {
				if (PanelData[i] != panel[i]) {
					PanelData[i] = panel[i];
				}
			}
		}
	}
	if (0 <= g_ini.NotchValue.PowerIndex && g_ini.NotchValue.PowerIndex <= 255)PowerLagMain(&panel[g_ini.NotchValue.PowerIndex], vehicleState.Time, PowerData, g_powerNotchOld);
	if (0 <= g_ini.NotchValue.BrakeIndex && g_ini.NotchValue.BrakeIndex <= 255)BrakeLagMain(&panel[g_ini.NotchValue.BrakeIndex], vehicleState.Time, BrakeData, g_brakeNotchOld);
	if ((0 <= g_ini.PanelValue.InputIndex && g_ini.PanelValue.InputIndex <= 255) && (0 <= g_ini.PanelValue.OutputIndex && g_ini.PanelValue.OutputIndex <= 255))PanelLagMain(&panel[g_ini.PanelValue.OutPutIndex], vehicleState.Time);
	g_brakeNotchOld = BrakeData;
	g_powerNotchOld = PowerData;
	NotchUpdateOld = NotchUpdate;
	PanelUpdateOld = PanelUpdate;
	PanelDataOld = PanelData;
    return g_output;
}

ATS_API void WINAPI SetPower(int notch)
{
	g_powerNotch = notch;
}

ATS_API void WINAPI SetBrake(int notch)
{
	g_brakeNotch = notch;
}

ATS_API void WINAPI SetReverser(int pos)
{
	g_reverser = pos;
}

ATS_API void WINAPI KeyDown(int atsKeyCode)
{
}


ATS_API void WINAPI KeyUp(int hornType)
{
}

ATS_API void WINAPI HornBlow(int atsHornBlowIndex)
{
}

ATS_API void WINAPI DoorOpen()
{
	g_pilotlamp = false;
}

ATS_API void WINAPI DoorClose()
{
	g_pilotlamp = true;
}

ATS_API void WINAPI SetSignal(int signal)
{
}

ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData)
{
}

ATS_API void WINAPI Load() 
{
}

ATS_API void WINAPI Dispose() 
{
}