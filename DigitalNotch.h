// �ȉ��� ifdef �u���b�N�� DLL ����ȒP�ɃG�N�X�|�[�g������}�N�����쐬����W���I�ȕ��@�ł��B 
// ���� DLL ���̂��ׂẴt�@�C���̓R�}���h���C���Œ�`���ꂽ ATS_EXPORTS �V���{��
// �ŃR���p�C������܂��B���̃V���{���͂��� DLL ���g�p����ǂ̃v���W�F�N�g��ł�����`�łȂ�
// ��΂Ȃ�܂���B���̕��@�ł̓\�[�X�t�@�C���ɂ��̃t�@�C�����܂ނ��ׂẴv���W�F�N�g�� DLL 
// ����C���|�[�g���ꂽ���̂Ƃ��� ATS_API �֐����Q�Ƃ��A���̂��߂��� DLL �͂��̃}�N 
// ���Œ�`���ꂽ�V���{�����G�N�X�|�[�g���ꂽ���̂Ƃ��ĎQ�Ƃ��܂��B
//#pragma data_seg(".shared")
//#pragma data_seg()
#include <vector>


int g_emgBrake; // ���m�b�`
int g_svcBrake; // ��p�ő�m�b�`
int g_brakeNotch; // �u���[�L�m�b�`
int g_powerNotch; // �͍s�m�b�`
int g_brakeNotchOld; // �u���[�L�m�b�`
int g_powerNotchOld; // �͍s�m�b�`
int g_reverser; // ���o�[�T
bool g_pilotlamp; // �p�C���b�g�����v
float g_speed; // ���x�v�̑��x[km/h]

int BrakeData;
int PowerData;
bool NotchUpdate;
bool NotchUpdateOld;
bool PanelUpdate;
bool PanelUpdateOld;

ATS_HANDLES g_output; // �o��
doorCloseingSecurity g_doorCloseingSecurity; // �˕ۈ�
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

