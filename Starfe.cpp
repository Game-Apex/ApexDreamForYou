#include "Globals.h"
#include"Driver.h"
#include"Offsets.h"

// ���Բ�ֵ����
Vector3 Lerp(Vector3 start, Vector3 end, float t)
{
    return {
        start.x + (end.x - start.x) * t,
        start.y + (end.y - start.y) * t,
        start.z + (end.z - start.z) * t
    };
}


void Starfe() {
    bool lastGrappleAttached = true;
    float lasttraversalProgress = -1;


    int lastonWall = 0;
    int lastonWalloff = 0;
    int walljumpNow = 0;

  


    while (true) {
        // ȫ���Ҹ��Ƶ� ��׼�������ܸ��� std::this_thread::sleep_for(std::chrono::milliseconds(20)); �Һ��滻
        Sleep(1);
        if (var::EnableStrfe) {
            if (var::Autto_Grapple) {
                // �Զ�������
                bool GrappleAttached = Read<int>(ProcessId, LocalPlayer + OFFSET_GRAPPLE + OFFSET_GRAPPLE_ATTACHED);
                if (!lastGrappleAttached && GrappleAttached) {
                    Write<int>(ProcessId, GameBase + OFFSET_IN_JUMP + 0x8, 5);
                    Sleep(300);
                    Write<int>(ProcessId, GameBase + OFFSET_IN_JUMP + 0x8, 4);
                }
                lastGrappleAttached = GrappleAttached;
            }
            //if (var::superGulide) {
            //   // �Զ�SG
            //   float traversalProgress = Read<float>(ProcessId, LocalPlayer + OFFSET_TRAVERSAL_PROGRESS);
            //   float travelsalStartTime = Read<float>(ProcessId, LocalPlayer + OFFSET_TRAVERSAL_START_TIME);
            //   float Worldtime = Read<float>(ProcessId, LocalPlayer + OFFSET_TIME_BASE);

            ///*   if ((lasttraversalProgress != traversalProgress)) {
            //       ts = false;
            //  }
            //  else {
            //        ts = true;
            //   }*/
            //   if (traversalProgress > 0.91f && (lasttraversalProgress != traversalProgress) && (lasttraversalProgress >= 0)) {
            //        if (!inSuperGlide) {
            //            std::thread sg(SuperGlide);
            //           sg.detach();
            //        }
            //   }
            //   lasttraversalProgress = traversalProgress;
            //}
            //if (nts) {
            //    // �Զ�TS
            //    if (!(Read<int>(ProcessId, LocalPlayer + m_fFlags) & 0x1)) { // �Ƿ��ڵ���
            //        do {
            //            if (ts) {
            //                int forward = Read<int>(ProcessId, ModuleAddress + in_forward); // ��������ڰ��µİ������ظ�����
            //                int backward = Read<int>(ProcessId, ModuleAddress + in_backward);
            //                int moveleft = Read<int>(ProcessId, ModuleAddress + in_moveleft);
            //                int moveright = Read<int>(ProcessId, ModuleAddress + in_moveright);

            //                printf("TS: W<%d>,S<%d>,A<%d>,D<%d>\n", forward, backward, moveleft, moveright);
            //                forward&& ts ? Write<int>(ProcessId, ModuleAddress + in_forward + 0x8, 4) : 0;
            //                backward&& ts ? Write<int>(ProcessId, ModuleAddress + in_backward + 0x8, 4) : 0;
            //                moveleft&& ts ? Write<int>(ProcessId, ModuleAddress + in_moveleft + 0x8, 4) : 0;
            //                moveright&& ts ? Write<int>(ProcessId, ModuleAddress + in_moveright + 0x8, 4) : 0;
            //                Sleep(8);
            //                forward&& ts ? Write<int>(ProcessId, ModuleAddress + in_forward + 0x8, 5) : 0;
            //                backward&& ts ? Write<int>(ProcessId, ModuleAddress + in_backward + 0x8, 5) : 0;
            //                moveleft&& ts ? Write<int>(ProcessId, ModuleAddress + in_moveleft + 0x8, 5) : 0;
            //                moveright&& ts ? Write<int>(ProcessId, ModuleAddress + in_moveright + 0x8, 5) : 0;
            //                Sleep(8);

            //            }
            //        } while (!(Read<int>(ProcessId, LocalPlayer + m_fFlags) & 0x1)); // ��غ�ԭ״̬
            //        if (!Read<int>(ProcessId, ModuleAddress + in_forward)) {
            //            Write<int>(ProcessId, ModuleAddress + in_forward + 0x8, 4);
            //        }
            //        if (!Read<int>(ProcessId, ModuleAddress + in_backward)) {
            //            Write<int>(ProcessId, ModuleAddress + in_backward + 0x8, 4);
            //        }
            //        if (!Read<int>(ProcessId, ModuleAddress + in_moveleft)) {
            //            Write<int>(ProcessId, ModuleAddress + in_moveleft + 0x8, 4);
            //        }
            //        if (!Read<int>(ProcessId, ModuleAddress + in_moveright)) {
            //            Write<int>(ProcessId, ModuleAddress + in_moveright + 0x8, 4);
            //        }
            //    }
            //}
            if (var::RadbbitJump) {
                if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                    Write<int>(ProcessId, GameBase + OFFSET_IN_JUMP + 0x8, 5);
                    Write<int>(ProcessId, GameBase + OFFSET_IN_FORWARD + 0x8, 5);
                    Sleep(10);
                    Write<int>(ProcessId, GameBase + OFFSET_IN_JUMP + 0x8, 4);
                    Write<int>(ProcessId, GameBase + OFFSET_IN_FORWARD + 0x8, 4);
                }
            }





            bool eKeyPressed = false;

            // �����ѭ��������߼���������´���
            if (var::RoppleJump) {
                // ���E���Ƿ񱻰���
                if (GetAsyncKeyState(aimkey3) & 0x8000) {
                  
                    if (!eKeyPressed) {
                        eKeyPressed = true;

                        // ִ����Ĳ���
                        Write<int>(ProcessId, GameBase + OFFSET_IN_JUMP + 0x8, 5);
                        Sleep(10);
                        Write<int>(ProcessId, GameBase + OFFSET_IN_JUMP + 0x8, 4);
                    }
                }
                else {
                    // ���E��û�б����£������ñ�־����Ϊfalse
                    eKeyPressed = false;
                }
            }
        }
        if (var::FullMap)
        {
            if (GetAsyncKeyState(aimkey6) & 0x8000) {

                uintptr_t pLocal = Read<uintptr_t>(ProcessId, GameBase + OFFSET_LOCAL_ENT);

                int defTeam = Read<int>(ProcessId, pLocal + OFFSET_TEAM);

                for (uintptr_t i = 0; i <= 10000; i++)
                {
                    Write<int>(ProcessId, pLocal + OFFSET_TEAM, 1);
                }

                for (uintptr_t i = 0; i <= 10000; i++)
                {
                    Write<int>(ProcessId, pLocal + OFFSET_TEAM, defTeam);
                }
            }
        

        }
        if (var::Security) {
            if (GetAsyncKeyState(aimkey7) & 0x8000) {
                for (int i = 0; i <= 5; i++) {
                    uintptr_t pLocal = Read<uintptr_t>(ProcessId, GameBase + OFFSET_LOCAL_ENT);

                    int oldteam = Read<int>(ProcessId, pLocal + OFFSET_TEAM);

                    for (int i = 1; i <= 32; i++)
                    {
                        Write<int>(ProcessId, pLocal + OFFSET_TEAM, i);
                    }

                    Write<int>(ProcessId, pLocal + OFFSET_TEAM, oldteam);
                }
             
           }
           
        }
   
        

    }
}