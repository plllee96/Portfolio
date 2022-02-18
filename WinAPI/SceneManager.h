#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//���߰�
	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	//����ü
	HRESULT changeScene(string sceneName);

	//�ε� ������ �Լ�
	//LPVOID : void* ��(� Ÿ�����ε� ��ȯ����)
	//friend : �� �ܹ����̴�.
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager() {}
	~SceneManager() {}
};