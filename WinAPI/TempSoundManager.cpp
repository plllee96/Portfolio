#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init()
{
	return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();
	//mciSendString() : ���� ��ġ�� ���ɾ �����Ͽ� �ʿ��� ��ġ�� ������Ű�� �Լ�
	//���ڿ� ���ɾ�, ��ȯ�� ���ڿ�, ��ȯ�� ����, �ڵ� �ݹ�
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type waveaudio alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();
	
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
	//SND_NODEFAULT : ���� �� ������  ������� ���� �ʰڴ�.
	//�����̸�.wave,�ڵ�(NULL ->���ϸ��� ����Ѵ�.),sound : �ɼ�|�ɼ�|�ɼ�
	//������ �ϰ� ������ �ݺ��� �߻� ->SND_ASYNC�� �Ҵ����� ������ ���� �ڵ尡 ������� ����.
	//SND_ASYNC : ����ϸ鼭 ���� �ڵ� ����(�񵿱������� �۵��϶�� �÷���)
	//���ſ�
	//PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	PlaySound(fileName, NULL, SND_ASYNC);

}

void TempSoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::stopMp3WithKey(string key)
{
	string first = "stop ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}