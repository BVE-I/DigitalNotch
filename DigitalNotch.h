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

int BrakeData; // 制動段数情報
int PowerData; // 力行段数情報
bool NotchUpdate; // ノッチ更新
bool NotchUpdateOld; // 1F前のノッチ更新
bool PanelUpdate; // パネル更新
bool PanelUpdateOld; // 1F前のパネル更新

ATS_HANDLES g_output; // 出力
doorCloseingSecurity g_doorCloseingSecurity; // 戸閉保安
DigitalNotchIni g_ini; // iniファイル対応

std::vector<int> BrakeChangeTime; // 制動段数変更時間履歴
std::vector<int> BrakeValue; // 制動段数変更履歴
std::vector<int> PowerChangeTime; // 力行段数変更時間履歴
std::vector<int> PowerValue; // 力行段数変更履歴
std::vector<int> PanelChangeTime{0}; // パネル変更時間履歴
std::vector<int> PanelValue{0}; // パネル変更履歴

std::vector<int> PanelData(256, 0); // すべてのパネルデータ
std::vector<int> PanelDataOld(256, 0); // 1F前のすべてのパネルデータ

void BrakeLagMain(int* pTargetIndex, int CurrentTime, int ValueData, int ValueOld) {
	if (ValueData != ValueOld) {
		// 1F前の制動段数と現在の制動段数が異なれば、履歴に時間と段数を入れる
		BrakeChangeTime.push_back(CurrentTime);
		BrakeValue.push_back(ValueData);
	}
	for (unsigned int i = 0; i <= BrakeChangeTime.size() + 1; i++) {
		if (BrakeValue.size() != NULL) {
			if (CurrentTime - BrakeChangeTime[i - 2] >= g_ini.NotchValue.Delay) {
				// 遅延時間を満たす場合、表示を更新
				*pTargetIndex = BrakeValue[i - 2];
				if (BrakeChangeTime.size() > g_ini.NotchValue.BrakeSaveDataNumber) {
					// セーブデータの個数より多くなれば、最初の一個目を削除
					BrakeChangeTime.erase(BrakeChangeTime.begin());
					BrakeValue.erase(BrakeValue.begin());
				}
			}
		}
	}
}

void PowerLagMain(int* pTargetIndex, int CurrentTime, int ValueData, int ValueOld) {
	if (ValueData != ValueOld) {
		// 1F前の力行段数と現在の力行段数が異なれば、履歴に時間と段数を入れる
		PowerChangeTime.push_back(CurrentTime);
		PowerValue.push_back(ValueData);
	}
	for (unsigned int i = 0; i <= PowerChangeTime.size() + 1; i++) {
		if (PowerValue.size() != NULL) {
			if (CurrentTime - PowerChangeTime[i - 2] >= g_ini.NotchValue.Delay) {
				// 遅延時間を満たす場合、表示を更新
				*pTargetIndex = PowerValue[i - 2];
				if (PowerChangeTime.size() > g_ini.NotchValue.PowerSaveDataNumber) {
					// セーブデータの個数より多くなれば、最初の一個目を削除
					PowerChangeTime.erase(PowerChangeTime.begin());
					PowerValue.erase(PowerValue.begin());
				}
			}
		}
	}
}

void PanelLagMain(int* pOutputTargetIndex, int CurrentTime) {
	if (PanelData[g_ini.PanelValue.InputIndex] != PanelDataOld[g_ini.PanelValue.InputIndex]) {
		// 1F前のパネルと現在のパネルが異なれば、履歴に時間と段数を入れる
		PanelChangeTime.push_back(CurrentTime);
		PanelValue.push_back(PanelData[g_ini.PanelValue.InputIndex]);
	}
	for (unsigned int i = 0; i <= PanelChangeTime.size() + 1; i++) {
		if (PanelValue.size() != NULL) {
			if (CurrentTime - PanelChangeTime[i - 2] >= g_ini.PanelValue.Delay) {
				// 遅延時間を満たす場合、表示を更新
				*pOutputTargetIndex = PanelValue[i - 2];
				if (PanelChangeTime.size() > g_ini.PanelValue.SaveDataNumber) {
					// セーブデータの個数より多くなれば、最初の一個目を削除
					PanelChangeTime.erase(PanelChangeTime.begin());
					PanelValue.erase(PanelValue.begin());
				}
			}
		}
	}
}

