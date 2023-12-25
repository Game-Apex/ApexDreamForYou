#include"Pch.h"
#include "FeatureManager.h"




void GameLogicThread(FeatureManager& featureManager) {
	while (true) {
		featureManager.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));; // ���Ƹ���Ƶ��
	}
}


int main()
{


	//InitDriver
	bool Success=InitDriver();
	if (Success) {
		printf("InitDriver Success\n");
	}
	else {
		printf("InitDriver Failed\n");
		return 0;
	}

	//GetGameHwnd
	printf("Please open game\n");
	do
	{
		GameHwnd = FindWindowA(NULL,"Apex Legends");
		if (!GameHwnd) std::this_thread::sleep_for(std::chrono::seconds(1));;
	} while (!GameHwnd);

	GetWindowThreadProcessId(GameHwnd, &ProcessId);


	
	GameBase= GetModuleAddress(ProcessId, "r5apex.exe");



	//EntityLoop
	std::thread ENTITYLOOP(EntityLoop);
	ENTITYLOOP.detach();

	FeatureManager featureManager;
	// ������������Ϸ�߼��߳�
	std::thread gameLogicThread(GameLogicThread, std::ref(featureManager));
	gameLogicThread.detach();


	initAngleX();//��ʼ���Ƕ�


	Render();

}