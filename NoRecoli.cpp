#include<iostream>
#include"NoRecoli.h"
#include"Driver.h"
#include"Globals.h"
#include "Offsets.h"
#include <thread>





void NoRecoi()
{
	while (true)
	{
		if (var::EnableNoRecoli)
		{

			if (!LocalPlayer) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			//Sleep(20);//������޺���������Դ����ͨ�õġ���˯���и�bug���ӽǶ�̫���ˣ�ֱ�Ӹ�����������ȥ�ˡ���˯��һ�£��Ͳ�������ȥ����ֱ��һ����
			int attack = Read<int>(ProcessId, GameBase + OFFSET_IN_ATTACK);
		
			if (attack) {
				Vector2 RecoilVec = Read<Vector2>(ProcessId, LocalPlayer + OFFSET_AIMPUNCH);
		
				RecoilVec.x *= 0.01 * var::NoRecoliRate;
				RecoilVec.y *= 0.01 * var::NoRecoliRate;
		
				Vector2 RecoilMove = RecoilVec * (1.0 / 0.022) / Read<FLOAT>(ProcessId, GameBase + mouse_sensitivity + 0x60);
				if (RecoilMove.x != 0 || RecoilMove.y != 0) {
			
					mouse_event(1, RecoilMove.y, -RecoilMove.x, 0, 0);
			
				}
			}
			


		}
	}




}