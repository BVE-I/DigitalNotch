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

ATS_HANDLES g_output; // �o��
doorCloseingSecurity g_doorCloseingSecurity; // �˕ۈ�
std::vector<int> BrakeChangeTime;
std::vector<int> BrakeValue;
std::vector<int> PowerChangeTime;
std::vector<int> PowerValue;
void BrakeLagMain(int* pTargetIndex, int CurrentTime, int ValueData, int ValueOld) {
	if (ValueData != ValueOld) {
		BrakeChangeTime.push_back(CurrentTime);
		BrakeValue.push_back(ValueData);
	}
	for (unsigned int i = 0; i <= BrakeChangeTime.size() + 1; i++) {
		if (BrakeValue.size() != NULL) {
			if (CurrentTime - BrakeChangeTime[i - 2] >= 750) {
				*pTargetIndex = BrakeValue[i - 2];
				if (BrakeChangeTime.size() > 9) {
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
	for (unsigned int n = 0; n <= PowerChangeTime.size() + 1; n++) {
		if (PowerValue.size() != NULL) {
			if (CurrentTime - PowerChangeTime[n - 2] >= 750) {
				*pTargetIndex = PowerValue[n - 2];
				if (PowerChangeTime.size() > 6) {
					PowerChangeTime.erase(PowerChangeTime.begin());
					PowerValue.erase(PowerValue.begin());
				}
			}
		}
	}
}
