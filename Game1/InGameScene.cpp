#include "stdafx.h"
#include "InGameScene.h"
#include "LobbyScene.h"
//각자 작업 영역 header 파일 추가해주시면됩니다!



InGameScene::InGameScene()
{
	MainCam = Camera::Create();
	MainCam->LoadFile("MainCam.xml");
	Map = VillageMap::Create();
	player = new Player();



	//playerAim = UI::Create();
	optionUI = UI::Create("option");
	optionUI->LoadFile("optionUI.xml");

	soundUI = UI::Create("sound");
	soundUI->LoadFile("soundUI.xml");
	
	Ingamethema = new Sound();
	Ingamethema->AddSound("mainthema.mp3","mainthema", true);
	Ingamethema->SetVolume("mainthema",0.2f);
	
	//아직 xml 추가안했음 이미지 작업후 xml 유아이 저장예정
	//playerAim->LoadFile("playerAim.xml");
	
	optionUI->visible = false;
	soundUI->visible = false;
	optionOpen = false;
	soundOn = true;

	CurrentTime = 0.0f;
	zombieSpwanTime = 10.0f;

	Monster* mob = new Monster();
	Vector3 randomSpwan = Vector3(RANDOM->Float(-100, 100), 0, RANDOM->Float(-100, 100));
	mob->Init(randomSpwan);
	monster.push_back(mob);



	MainCam->mainCamSpeed = 30.0f;
	MainCam->viewport.x = 0.0f;
	MainCam->viewport.y = 0.0f;
	MainCam->viewport.width = App.GetWidth();
	MainCam->viewport.height = App.GetHeight();
	MainCam->width = App.GetWidth();
	MainCam->height = App.GetHeight();
	Camera::main = MainCam;

	//사운드

}

InGameScene::~InGameScene()
{
	
	
	Map->Release();
}

void InGameScene::Init()
{
	Map->Init();
	player->Init();
	Ingamethema->Play("mainthema");
}

void InGameScene::Release()
{

}

void InGameScene::Update()
{

	if (INPUT->KeyDown(VK_ESCAPE))
	{
		optionOpen = !optionOpen;
		optionUI->visible = !optionUI->visible;
		soundUI->visible = !soundUI->visible;
	}


	if (!optionOpen)
	{
		Map->Update();
		player->PlayerControl();
		player->Update();
		for (auto monsterPtr : monster)
		{
			monsterPtr->Update();
		}
		Camera::main->Update();
		//메인 카메라 컨트롤
		Camera::ControlMainCam();


	}


	ImGui::Begin("Hierarchy");
	MainCam->RenderHierarchy();
	//Map->Hierarchy();
	player->RenderHierarchy();
	for (auto monsterPtr : monster)
	{
		monsterPtr->RenderHierarchy();
	}
	optionUI->RenderHierarchy();
	soundUI->RenderHierarchy();
	ImGui::End();

	//시간으로 좀비생성
	/*if (TIMER->GetTick(CurrentTime, zombieSpwanTime))
	{
		for (int i = 0; i < 10; i++)
		{
		Zombie* zombie = new Zombie();
		Vector3 randomSpwan = Vector3(RANDOM->Float(-100, 100), 0, RANDOM->Float(-100, 100));
		zombie->Init(randomSpwan);
		zombies.push_back(zombie);
		}
	}*/





	optionUI->Update();
	soundUI->Update();
}

void InGameScene::LateUpdate()
{
	Map->LateUpdate();
	player->CollidePlayerToFloor(Map);
	Map->WallCollision(player->GetActor());

	
	
	//사운드 ui 설정
	{
		
		if ((soundUI->visible and soundUI->MouseOver() and soundOn))
		{
			if (INPUT->KeyDown(VK_LBUTTON))
			{
				soundOn = false;
				soundUI->texture = RESOURCE->textures.Load("soundoff.png");
				cout << "사운드꺼짐" << endl;
				Ingamethema->Pause("mainthema");
			}
		}
		else if ((soundUI->visible and soundUI->MouseOver() and !soundOn))
		{
			if (INPUT->KeyDown(VK_LBUTTON))
			{
				soundOn = true;
				soundUI->texture = RESOURCE->textures.Load("soundon.png");
				cout << "사운드켜짐" << endl;
				Ingamethema->Resume("mainthema");
			}
		}
	}

}

void InGameScene::PreRender()
{

}

void InGameScene::Render()
{
	//객체들 랜더 모아주세요 
	Camera::main->Set();
	//MainCam->Set();
	Map->Render();
	player->Render();
	for (auto monsterPtr : monster)
	{
		monsterPtr->Render();
	}
	optionUI->Render();
	soundUI->Render();
}

void InGameScene::ResizeScreen()
{
	//카메라 화면비 조정 
	MainCam->viewport.x = 0.0f;
	MainCam->viewport.y = 0.0f;
	MainCam->viewport.width = App.GetWidth();
	MainCam->viewport.height = App.GetHeight();
	MainCam->width = App.GetWidth();
	MainCam->height = App.GetHeight();

	Map->ResizeScreen();
}
