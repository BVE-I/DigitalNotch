// 以下の ifdef ブロックは DLL から簡単にエクスポートさせるマクロを作成する標準的な方法です。 
// この DLL 内のすべてのファイルはコマンドラインで定義された ATS_EXPORTS シンボル
// でコンパイルされます。このシンボルはこの DLL が使用するどのプロジェクト上でも未定義でなけ
// ればなりません。この方法ではソースファイルにこのファイルを含むすべてのプロジェクトが DLL 
// からインポートされたものとして ATS_API 関数を参照し、そのためこの DLL はこのマク 
// ロで定義されたシンボルをエクスポートされたものとして参照します。
//#pragma data_seg(".shared")
//#pragma data_seg()
#include <vector>


int g_emgBrake; // 非常ノッチ
int g_svcBrake; // 常用最大ノッチ
int g_brakeNotch; // ブレーキノッチ
int g_powerNotch; // 力行ノッチ
int g_brakeNotchOld; // ブレーキノッチ
int g_powerNotchOld; // 力行ノッチ
int g_reverser; // レバーサ
bool g_pilotlamp; // パイロットランプ
float g_speed; // 速度計の速度[km/h]

int BrakeData;
int PowerData;
bool NotchUpdate;
bool NotchUpdateOld;
bool PanelUpdate;
bool PanelUpdateOld;

ATS_HANDLES g_output; // 出力
doorCloseingSecurity g_doorCloseingSecurity; // 戸閉保安
DigitalNotchIni g_ini;

std::vector<int> BrakeChangeTime;
std::vector<int> BrakeValue;
std::vector<int> PowerChangeTime;
std::vector<int> PowerValue;
std::vector<int> PanelChangeTime{0};
std::vector<int> PanelValue{0};

std::vector<int> PanelData(256, 0);
std::vector<int> PanelDataOld(256, 0);

void BrakeLagMain(int* pTargetIndex, int CurrentTime, int ValueData, int ValueOld) {
	if (ValueData != ValueOld) {
		BrakeChangeTime.push_back(CurrentTime);
		BrakeValue.push_back(ValueData);
	}
	for (unsigned int i = 0; i <= BrakeChangeTime.size() + 1; i++) {
		if (BrakeValue.size() != NULL) {
			if (CurrentTime - BrakeChangeTime[i - 2] >= g_ini.NotchValue.Delay) {
				*pTargetIndex = BrakeValue[i - 2];
				if (BrakeChangeTime.size() > g_ini.NotchValue.BrakeSaveDataNumber) {
					BrakeChangeTime.erase(BrakeChangeTime.begin());
					BrakeValue.erase(BrakeValue.begin());
				}
			}
		}
	}
}

void PowerLagMain(int* pTargetIndex, int CurrentTime, int ValueData, int ValueOld) {
	if (ValueData != ValueOld) {
		PowerChangeTime.push_back(CurrentTime);
		PowerValue.push_back(ValueData);
	}
	for (unsigned int i = 0; i <= PowerChangeTime.size() + 1; i++) {
		if (PowerValue.size() != NULL) {
			if (CurrentTime - PowerChangeTime[i - 2] >= g_ini.NotchValue.Delay) {
				*pTargetIndex = PowerValue[i - 2];
				if (PowerChangeTime.size() > g_ini.NotchValue.PowerSaveDataNumber) {
					PowerChangeTime.erase(PowerChangeTime.begin());
					PowerValue.erase(PowerValue.begin());
				}
			}
		}
	}
}

void PanelLagMain(int* pTargetIndex, int CurrentTime) {
	if (PanelData[g_ini.PanelValue.InputIndex] != PanelDataOld[g_ini.PanelValue.InputIndex]) {
		PanelChangeTime.push_back(CurrentTime);
		PanelValue.push_back(PanelData[g_ini.PanelValue.InputIndex]);
	}
	for (unsigned int i = 0; i <= PanelChangeTime.size() + 1; i++) {
		if (PanelValue.size() != NULL) {
			if (CurrentTime - PanelChangeTime[i - 2] >= g_ini.PanelValue.Delay) {
				*pTargetIndex = PanelValue[i - 2];
				if (PanelChangeTime.size() > g_ini.PanelValue.SaveDataNumber) {
					PanelChangeTime.erase(PanelChangeTime.begin());
					PanelValue.erase(PanelValue.begin());
				}
			}
		}
	}
}

