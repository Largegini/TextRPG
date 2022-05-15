// scanf함수의 보안관련 오류를 안 띄우기위해 사용
#define _CRT_SECURE_NO_WARNINGS		

// 헤더파일을 사용하기위해 선언
#include <stdio.h>		
#include <stdlib.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include <Windows.h>


const int Scene_Logo = 0;
const int Scene_Menu = 1;
const int Scene_Stage = 2;
const int Scene_Exit = 3;
const int Scene_END = 4;

// Scene전환을 위해 전역변수로 선언
int SceneState = 0;
int iStage = 0;

//구조체안에는 사용자가 사용하고 싶은 것을 넣어서 용도별로 구축한다
// Status 구조체
typedef struct tagInfo
{
	int Gold;

	int HP;
	int MaxHP;
	int MP;
	int MaxMP;
	// 도망능력관련된 스탯이며 후에 플레이어와 몬스터의 선공 후공을 결정하기위한 스탯
	int Speed;

	int EXP;
	short Level;

	float Att;
	float Def;

}INFO;

//  객체 구조체
typedef struct tagObject
{
	char* Name;

	int State;
	//몬스터 번호(퀘스트를 위한 선언)
	int Num;
	int Kills;

	INFO Info;

}Object;

typedef struct tagEquipment
{
	int Price;
	int Stock;

	INFO Info;
	Object object;
}EQUIPMENT;

typedef struct tagEffect
{
	INFO Info;
}EFFECT;

typedef struct tagItem
{
	Object Object;
	EQUIPMENT Equipment;
	EFFECT Effect;
}ITEM;

typedef struct tagInventory
{
	EQUIPMENT Equipment;
	ITEM item;
	INFO Info;
}INVENTORY;

typedef struct tagSkill
{
	int Type;
	int Cost;

	float Damege;

	Object object;

}SKILL;

typedef struct tagPlayerSkill
{
	short Grade;

	SKILL Skill;

}PLAYERSKILL;

// 함수 전방 선언
char* SetName();

void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void LogoScene();
void MenuScene();
void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void EndingScene();

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void GraveYardBackGround(int BGNum);
void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void Castle(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void NecromancerTower(Object* Player, Object* Enemy, EQUIPMENT* Equipment);

void DungeonEnterence(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void Dungeon(Object* Player, Object* Enemy, EQUIPMENT* Equipment, int EnemyIndex, int EventCount, Object* Quest, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void DungeonBackGround();
void Shop(Object* Player, INVENTORY* Inventory);
void ShopBackGround();
void Guild(Object* Player, Object* Quest, Object* Enemy, EQUIPMENT* Equipment);
void InitializeQuest(Object* Quest, int QuestIndex, int Stage);
void QuestState(Object* Quest, Object* Enemy, int _Choice);
void LevelUp(Object* Player, EQUIPMENT* Equipment);
void Forge(Object* Player, EQUIPMENT* Equipment);
void Training(Object* Player, EQUIPMENT* Equipment, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill);

void InitializeObjectPlayer(Object* Player);
void PlayerScene(Object* Player, INVENTORY* Inventory);

void InitializeObjectEnemy(Object* Enemy, int EnemyIndex);
int EnemyScene(Object* Enemy, int EnemyIndex);

void InitializeEquipment(EQUIPMENT* Equipment, int EquipmentIndex);
void InitializeObjectInventory(INVENTORY* Inventory, int ItemIndex);
void InitializeSkill(SKILL* Skill, int SkillNum);

short Battle(Object* Player, Object* Enemy, int EnemyIndex, Object* Quest, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill);
void Status(Object* Player, Object* Enemy, int EnemyIndex);
void PlayerStatus(Object* Player, int State);
void EnemyStatus(Object* Enemy, int EnemyIndex);
void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex);
void EnemyAttack(Object* Player, Object* Enemy, int EnamyIndex);
void Equip(Object* Player, EQUIPMENT* Equipment, int EquipmentNum);
void Reinforce(Object* Player, EQUIPMENT* Equipment, int EquipmentID);
short GameOver();

void SetPosition(int _x, int _y, char* _str, int _Color=15);
void SetColor(int _Color);
void HideCursor();



int main(void)
{
	// ** 커서를 안보이게 함
	HideCursor();

	//콘솔창의 사이즈를 설정
	system("mode con:cols=120 lines=30");

	//콘솔창의 이름을 설정
	system("title 안정연 Adventure Beginning v0.1");

	Object* Player = (Object*)malloc(sizeof(Object));		//PLAYER 동적할당
	InitializeObjectPlayer(Player);							//초기화//ENEMY 동적할당



	int Max = 30;
	Object* Enemy;
	Enemy = (Object*)malloc(sizeof(Object) * Max);
	for (int i = 0; i < Max; i++)
	{
		InitializeObjectEnemy(Enemy, i);							//초기화
	}


	Max = 4;
	Object* Quest;
	Quest = (Object*)malloc(sizeof(Object) * Max);



	Max = 29;
	EQUIPMENT* Equipment;
	Equipment = (EQUIPMENT*)malloc(sizeof(EQUIPMENT) * Max);

	for (int i = 0; i < Max; i++)
	{
		InitializeEquipment(Equipment, i);
	}


	Max = 4;
	INVENTORY* Inventory;
	Inventory = (INVENTORY*)malloc(sizeof(INVENTORY) * Max);
	for (int i = 0; i < Max; i++)
	{
		InitializeObjectInventory(Inventory, i);							//초기화
	}


	Max = 16;
	SKILL* Skill;
	Skill = (SKILL*)malloc(sizeof(SKILL) * Max);

	for (int i = 0; i < Max; i++)
	{
		InitializeSkill(Skill, i);
	}


	Max = 4;
	PLAYERSKILL* PlayerSkill = (PLAYERSKILL*)malloc(sizeof(PLAYERSKILL) * Max);

	PlayerSkill->Grade = 0;

	while (true)
	{
		//콘솔창에 있는 모든내용을 지움
		system("cls");
		//** 게임 루프
		//  함수 SceneManger에 넣어 작동 한다
		SceneManager(Player, Enemy, Equipment, Inventory, Quest,Skill, PlayerSkill);
	}

	return 0;
}

//플레이어 이름을 설정하는 함수
char* SetName()
{
	//문자열을 입력받기위한 임의의 배열 선언
	//포인터로는 문자열을 입력받을 수 없기 때문에 임의의 배열을 선언한다.
	char Buffer[128] = "";

	printf_s("지금 눈 뜬 그대 이름은 무엇인가?\n");
	Sleep(1000);

	printf_s("내 이름은...\n");
	Sleep(500);

	printf_s("이름을 입력하십시오. : ");

	//문자열을 입력 받음.
	scanf("%s", Buffer);

	// ** 입력받은 값은 배열이나 반환 값은 캐릭터 포인터형(char*)이므로 문자열을 복사해야함.
	// ** 문자열을 복사 하기위해 포인터가 가르키는 공간에 입력받은 문자열이 들어갈 만큼의 크기로 메모리 할당
	char* pName = (char*)malloc(strlen(Buffer) + 1);	//문자열은 형변환을 해야함, NULL값을 넣어주기 위해 +1을 한다

	// Buffer가 받은 문자열을 포인터pName에 문자열 복사
	strcpy(pName, Buffer);

	// 포인터 값 반환
	return pName;
}

// Scene구성
void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	switch (SceneState)									//변수에 따라 Scene을 실행하기위한 switch문
	{
	case Scene_Logo:
		LogoScene();									// LogoScene 실행
		break;

	case Scene_Menu:
		MenuScene();									// MenuScene 실행
		break;

	case Scene_Stage:
		StageScene(Player, Enemy, Equipment, Inventory, Quest, Skill, PlayerSkill);						// StageScene 실행
		break;

	case Scene_Exit:									//종료

		exit(NULL);
		break;
	case Scene_END:
		EndingScene();
		exit(NULL);
		break;
	}
}

void LogoScene()										//LogoScene
{
	int Width = (120 / 2 - (strlen(" __    _____ _____ _____ ") / 2));
	int Height = 5;

	SetPosition(Width, Height, (char*)" __    _____ _____ _____ ");
	SetPosition(Width, Height + 1, (char*)"|  |  |     |   __|     |");
	SetPosition(Width, Height + 2, (char*)"|  |__|  |  |  |  |  |  |");
	SetPosition(Width, Height + 3, (char*)"|_____|_____|_____|_____|");

	Sleep(3000);
	//다음Scene으로 가기위한 변수 값 증가
	SceneState++;
}

void MenuScene()
{
	//입력을 받기위한 변수
	int iChoice = 0;

	printf_s("Adventure Beginning \n");
	printf_s("1.게임시작\n2.종료\n입력 :");
	scanf("%d", &iChoice);

	//iChoice값에 따라 씬을 넘어가거나 종료함
	switch (iChoice)
	{
	case 1:												//1을 입력하면 다음 씬을 진행
		SceneState++;
		break;

	case 2:											//2를 입력하면 종료
		SceneState = Scene_Exit;
		break;

	default:											//1과 2가아닌 입력을 받았을 경우 처리하기위함
		printf_s("잘못된 입력입니다! 강제 시작합니다.\n");
		SceneState++;
		break;
	}

}

void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	int Width = 0;
	int Height = 0;
	// ** 모듈화 함수만들어 용도별로 사용할 수 있게
	
	for (int i = 0; i < sizeof(int); i++)
	{
		InitializeQuest(Quest, i, iStage);
	}

	switch (iStage)
	{
	case 0:
		//** 묘지
		GraveYard(Player, Enemy, Equipment, Inventory, Skill, PlayerSkill);
		iStage++;
		break;

	case 1:
		Width = (120 / 2 - (strlen(".........................................................................................................................") / 2));
		Height = 5;
		
		SetPosition(Width, Height,	   (char*)".......................................................................................................................");
		SetPosition(Width, Height + 1, (char*)"..####...#####...##..##..######..##..##..######..##..##..#####...######..#####.........######...####...##...##..##..##.");
		SetPosition(Width, Height + 2, (char*)".##..##..##..##..##..##..##......###.##....##....##..##..##..##..##......##..##..........##....##..##..##...##..###.##.");
		SetPosition(Width, Height + 3, (char*)".######..##..##..##..##..####....##.###....##....##..##..#####...####....#####...........##....##..##..##.#.##..##.###.");
		SetPosition(Width, Height + 4, (char*)".##..##..##..##...####...##......##..##....##....##..##..##..##..##......##..##..........##....##..##..#######..##..##.");
		SetPosition(Width, Height + 5, (char*)".##..##..#####.....##....######..##..##....##.....####...##..##..######..##..##..........##.....####....##.##...##..##.");
		SetPosition(Width, Height + 6, (char*)".......................................................................................................................");
		Sleep(2000);
		// ** 모험가 마을
		AdventurerVillage(Player, Enemy, Equipment, Inventory, Quest, Skill, PlayerSkill);
		break;
		/*
			case 2:
				// ** 왕성
				Castle(Player, Enemy, Equipment);
				break;

			case 3:
				// ** 사령술사의 탑
				NecromancerTower(Player, Enemy, Equipment);
				break;
		*/
	case 4:
		break;
	}
	// ** 이동
	//  * * * 입력(Input)
	//  * * * 플레이어 좌표데이터 수집
	//  * * * 게임 공간의 크기 데이터 수집
	//  * * * 각종 오브젝트들의 이동속도 데이터 수집
}

void EndingScene()
{
	printf_s("우두머리인 오우거를 쓰러뜨리자 고블린과 오크의 무리는 뿔뿔이 흩어졌고,\n");
	Sleep(500);
	printf_s("마을에는 평화가 찾아왔다\n");
	Sleep(500);
	printf_s("To be Continue?");
}

// 플레이어
void InitializeObjectPlayer(Object* Player)
{
	//PLAYER의 객체 정보를 초기화한다

	Player->Info.HP = 100;
	Player->Info.MaxHP = 100;
	Player->Info.MP = 30;
	Player->Info.MaxMP = 30;
	Player->Info.Att = 10;
	Player->Info.Def = 5;
	Player->Info.Speed = 10;
	Player->Info.Level = 1;
	Player->Info.EXP = 0;
	Player->Info.Gold = 0;
}


void PlayerScene(Object* Player, INVENTORY* Inventory)
{
	printf_s("아이템명\t가격\t갯수\n");
	for (int i = 0; i < 1; i++)
	{
		if (Inventory[i].Equipment.Stock > 0)
			printf_s("%d. %s\t\t%d G\t\t%d\n", i + 1, Inventory[i].item.Object.Name, Inventory[i].Equipment.Price, Inventory[i].Equipment.Stock);
	}
}


// 적
void InitializeObjectEnemy(Object* Enemy, int EnemyIndex)
{
	switch (EnemyIndex)
	{
		//묘지
	case 0:
		Enemy[EnemyIndex].Name = (char*)"쥐";
		Enemy[EnemyIndex].Info.HP = 10;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 7;
		Enemy[EnemyIndex].Info.Def = 5;
		Enemy[EnemyIndex].Info.Speed = 5;
		Enemy[EnemyIndex].Info.EXP = 1;
		Enemy[EnemyIndex].Info.Gold = 2;
		break;

	case 1:
		Enemy[EnemyIndex].Name = (char*)"엉성한 기사";
		Enemy[EnemyIndex].Info.HP = 25;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 10;
		Enemy[EnemyIndex].Info.Def = 10;
		Enemy[EnemyIndex].Info.Speed = 5;
		Enemy[EnemyIndex].Info.EXP = 5;
		Enemy[EnemyIndex].Info.Gold = 10;
		break;

		//모험가 마을
			// 소너스 평야
	case 2:
		Enemy[EnemyIndex].Name = (char*)"슬라임";
		Enemy[EnemyIndex].Info.HP = 35;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 12;
		Enemy[EnemyIndex].Info.Def = 10;
		Enemy[EnemyIndex].Info.Speed = 5;
		Enemy[EnemyIndex].Info.EXP = 4;
		Enemy[EnemyIndex].Info.Gold = 4;
		break;
	case 3:
		Enemy[EnemyIndex].Name = (char*)"고블린";
		Enemy[EnemyIndex].Info.HP = 35;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 14;
		Enemy[EnemyIndex].Info.Def = 8;
		Enemy[EnemyIndex].Info.Speed = 11;
		Enemy[EnemyIndex].Info.EXP = 4;
		Enemy[EnemyIndex].Info.Gold = 4;
		break;
	case 4:
		Enemy[EnemyIndex].Name = (char*)"모험가";
		Enemy[EnemyIndex].Info.HP = 50;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 17;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 9;
		Enemy[EnemyIndex].Info.EXP = 10;
		Enemy[EnemyIndex].Info.Gold = 8;
		break;
	case 5:
		Enemy[EnemyIndex].Name = (char*)"도적";
		Enemy[EnemyIndex].Info.HP = 50;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 17;
		Enemy[EnemyIndex].Info.Def = 12;
		Enemy[EnemyIndex].Info.Speed = 9;
		Enemy[EnemyIndex].Info.EXP = 10;
		Enemy[EnemyIndex].Info.Gold = 10;
		break;
	case 6:
		Enemy[EnemyIndex].Name = (char*)"고블린전사";
		Enemy[EnemyIndex].Info.HP = 45;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 17;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 9;
		Enemy[EnemyIndex].Info.EXP = 18;
		Enemy[EnemyIndex].Info.Gold = 15;
		break;
	case 7:
		Enemy[EnemyIndex].Name = (char*)"고블린투척병";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 20;
		Enemy[EnemyIndex].Info.Def = 10;
		Enemy[EnemyIndex].Info.Speed = 12;
		Enemy[EnemyIndex].Info.EXP = 18;
		Enemy[EnemyIndex].Info.Gold = 15;
		break;
	case 8:
		Enemy[EnemyIndex].Name = (char*)"고블린라이더";
		Enemy[EnemyIndex].Info.HP = 70;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 25;
		Enemy[EnemyIndex].Info.Def = 20;
		Enemy[EnemyIndex].Info.Speed = 15;
		Enemy[EnemyIndex].Info.EXP = 25;
		Enemy[EnemyIndex].Info.Gold = 30;
		break;
	case 9:
		Enemy[EnemyIndex].Name = (char*)"오크";
		Enemy[EnemyIndex].Info.HP = 60;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 20;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 10;
		Enemy[EnemyIndex].Info.EXP = 25;
		Enemy[EnemyIndex].Info.Gold = 20;
		break;
	case 10:
		Enemy[EnemyIndex].Name = (char*)"오크전사";
		Enemy[EnemyIndex].Info.HP = 75;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 27;
		Enemy[EnemyIndex].Info.Def = 20;
		Enemy[EnemyIndex].Info.Speed = 12;
		Enemy[EnemyIndex].Info.EXP = 28;
		Enemy[EnemyIndex].Info.Gold = 24;
		break;
	case 11:
		Enemy[EnemyIndex].Name = (char*)"오크주술사";
		Enemy[EnemyIndex].Info.HP = 50;
		Enemy[EnemyIndex].Info.MP = 100;
		Enemy[EnemyIndex].Info.Att = 40;
		Enemy[EnemyIndex].Info.Def = 10;
		Enemy[EnemyIndex].Info.Speed = 5;
		Enemy[EnemyIndex].Info.EXP = 30;
		Enemy[EnemyIndex].Info.Gold = 30;
		break;
	case 12:
		Enemy[EnemyIndex].Name = (char*)"오우거";
		Enemy[EnemyIndex].Info.HP = 120; 
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 37;
		Enemy[EnemyIndex].Info.Def = 17;
		Enemy[EnemyIndex].Info.Speed = 5;
		Enemy[EnemyIndex].Info.EXP = 200;
		Enemy[EnemyIndex].Info.Gold = 500;
		break;

		//왕성
	case 13:
		Enemy[EnemyIndex].Name = (char*)"병사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 14:
		Enemy[EnemyIndex].Name = (char*)"기사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 15:
		Enemy[EnemyIndex].Name = (char*)"마법사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 16:
		Enemy[EnemyIndex].Name = (char*)"사제";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 17:
		Enemy[EnemyIndex].Name = (char*)"성기사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 18:
		Enemy[EnemyIndex].Name = (char*)"마검사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 19:
		Enemy[EnemyIndex].Name = (char*)"불의정령";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 20:
		Enemy[EnemyIndex].Name = (char*)"물의정령";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 21:
		Enemy[EnemyIndex].Name = (char*)"바람정령";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 22:
		Enemy[EnemyIndex].Name = (char*)"땅의정령";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 23:
		Enemy[EnemyIndex].Name = (char*)"정령사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;

		//사령술사의 탑
	case 24:
		Enemy[EnemyIndex].Name = (char*)"해골";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 25:
		Enemy[EnemyIndex].Name = (char*)"해골병사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 26:
		Enemy[EnemyIndex].Name = (char*)"해골궁수";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 27:
		Enemy[EnemyIndex].Name = (char*)"리치";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 28:
		Enemy[EnemyIndex].Name = (char*)"좀비";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 29:
		Enemy[EnemyIndex].Name = (char*)"흑마법사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 30:
		Enemy[EnemyIndex].Name = (char*)"사령술사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;


	}


}

int EnemyScene(Object* Enemy, int EnemyIndex)
{
	int Battle = 1;

	// 적 패배
	if (Enemy[EnemyIndex].Info.HP <= 0)
	{
		printf_s("%s을(를) 쓰러뜨렸다!\n", Enemy[EnemyIndex].Name);
		Sleep(500);

		printf_s("경험치 %d을(를) 얻었다!\n", Enemy[EnemyIndex].Info.EXP);
		
		Sleep(500);

		printf_s("골드 %d을(를) 얻었다!\n", Enemy[EnemyIndex].Info.Gold);
		Sleep(500);
		Battle = 0;

	}
	return Battle;
}

void InitializeEquipment(EQUIPMENT* Equipment, int EquipmentIndex)
{
	// *****	0 = 검 1 = 도끼 2 = 창 3 = 활
	// *****	4 = 머리 5 = 상의 6 = 하의 7 = 발 8 = 장갑 9 = 징표
	switch (EquipmentIndex)
	{
	case 0:
		Equipment[EquipmentIndex].object.Name = (char*)"오래된 검";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 4;
		Equipment[EquipmentIndex].Info.Def = 1;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 1:
		Equipment[EquipmentIndex].object.Name = (char*)"오래된 도끼";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 5;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = -1;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 2:
		Equipment[EquipmentIndex].object.Name = (char*)"오래된 창";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 4;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = 1;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 3:
		Equipment[EquipmentIndex].object.Name = (char*)"오래된 활";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 5;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 4:
		Equipment[EquipmentIndex].object.Name = (char*)"허름한 투구";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 1;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 90;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 5:
		Equipment[EquipmentIndex].object.Name = (char*)"허름한 갑옷";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 1;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 90;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 6:
		Equipment[EquipmentIndex].object.Name = (char*)"허름한 각반";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 1;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 90;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 7:
		Equipment[EquipmentIndex].object.Name = (char*)"허름한 장화";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 1;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 90;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 8:
		Equipment[EquipmentIndex].object.Name = (char*)"허름한 장갑";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 1;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 90;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 9:
		Equipment[EquipmentIndex].object.Name = (char*)"견습 모험가의 징표";
		Equipment[EquipmentIndex].Info.MaxHP = 50;
		Equipment[EquipmentIndex].Info.MaxMP = 25;
		Equipment[EquipmentIndex].Info.Att = 2;
		Equipment[EquipmentIndex].Info.Def = 2;
		Equipment[EquipmentIndex].Info.Speed = 1;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 10:
		Equipment[EquipmentIndex].object.Name = (char*)"철제 검";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 12;
		Equipment[EquipmentIndex].Info.Def = 2;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 500;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 11:
		Equipment[EquipmentIndex].object.Name = (char*)"쇠도끼";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 15;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = -3;
		Equipment[EquipmentIndex].Info.Gold = 500;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 12:
		Equipment[EquipmentIndex].object.Name = (char*)"장창";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 12;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = 2;
		Equipment[EquipmentIndex].Info.Gold = 500;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 13:
		Equipment[EquipmentIndex].object.Name = (char*)"단궁";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 15;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 500;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 14:
		Equipment[EquipmentIndex].object.Name = (char*)"가죽 투구";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 4;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 15:
		Equipment[EquipmentIndex].object.Name = (char*)"가죽 갑옷";
		Equipment[EquipmentIndex].Info.MaxHP = 10;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 5;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 16:
		Equipment[EquipmentIndex].object.Name = (char*)"가죽 각반";
		Equipment[EquipmentIndex].Info.MaxHP = 10;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 5;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 17:
		Equipment[EquipmentIndex].object.Name = (char*)"가죽 장화";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 2;
		Equipment[EquipmentIndex].Info.Speed = 1;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 18:
		Equipment[EquipmentIndex].object.Name = (char*)"가죽 장갑";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 1;
		Equipment[EquipmentIndex].Info.Def = 2;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].Info.Gold = 200;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 19:
		Equipment[EquipmentIndex].object.Name = (char*)"모험가의 징표";
		Equipment[EquipmentIndex].Info.MaxHP = 50;
		Equipment[EquipmentIndex].Info.MaxMP = 25;
		Equipment[EquipmentIndex].Info.Att = 2;
		Equipment[EquipmentIndex].Info.Def = 2;
		Equipment[EquipmentIndex].Info.Speed = 2;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 20:
		Equipment[EquipmentIndex].object.Name = (char*)"강철 검";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 24;
		Equipment[EquipmentIndex].Info.Def = 4;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 21:
		Equipment[EquipmentIndex].object.Name = (char*)"강철 도끼";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 30;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = -4;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 22:
		Equipment[EquipmentIndex].object.Name = (char*)"강철 창";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 24;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = 4;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 23:
		Equipment[EquipmentIndex].object.Name = (char*)"합성 단궁";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 30;
		Equipment[EquipmentIndex].Info.Def = 0;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 24:
		Equipment[EquipmentIndex].object.Name = (char*)"판금 투구";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 8;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 25:
		Equipment[EquipmentIndex].object.Name = (char*)"판금 갑옷";
		Equipment[EquipmentIndex].Info.MaxHP = 20;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 10;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 26:
		Equipment[EquipmentIndex].object.Name = (char*)"판금 각반";
		Equipment[EquipmentIndex].Info.MaxHP = 20;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 10;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 27:
		Equipment[EquipmentIndex].object.Name = (char*)"판금 장화";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 0;
		Equipment[EquipmentIndex].Info.Def = 4;
		Equipment[EquipmentIndex].Info.Speed = 2;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 28:
		Equipment[EquipmentIndex].object.Name = (char*)"판금 장갑";
		Equipment[EquipmentIndex].Info.MaxHP = 0;
		Equipment[EquipmentIndex].Info.MaxMP = 0;
		Equipment[EquipmentIndex].Info.Att = 2;
		Equipment[EquipmentIndex].Info.Def = 4;
		Equipment[EquipmentIndex].Info.Speed = 0;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	case 29:
		Equipment[EquipmentIndex].object.Name = (char*)"숙련 모험가의 징표";
		Equipment[EquipmentIndex].Info.MaxHP = 100;
		Equipment[EquipmentIndex].Info.MaxMP = 50;
		Equipment[EquipmentIndex].Info.Att = 4;
		Equipment[EquipmentIndex].Info.Def = 4;
		Equipment[EquipmentIndex].Info.Speed = 3;
		Equipment[EquipmentIndex].object.State = 0;
		break;
	}
}

void InitializeObjectInventory(INVENTORY* Inventory, int ItemIndex)
{
	switch (ItemIndex)
	{
	case 0:
		Inventory[ItemIndex].item.Object.Name = (char*)"뼛가루";
		Inventory[ItemIndex].item.Effect.Info.HP = 20;
		Inventory[ItemIndex].item.Effect.Info.MP = 0;
		Inventory[ItemIndex].Equipment.Price = 5;
		Inventory[ItemIndex].Equipment.Stock = 0;
		break;

	case 1:
		Inventory[ItemIndex].item.Object.Name = (char*)"마력의 이슬";
		Inventory[ItemIndex].item.Effect.Info.HP = 0;
		Inventory[ItemIndex].item.Effect.Info.MP = 10;
		Inventory[ItemIndex].Equipment.Price = 3;
		Inventory[ItemIndex].Equipment.Stock = 0;
		break;
	}
}

void InitializeSkill(SKILL* Skill, int SkillNum)
{
	// 0 = 방어력기반 1 = 상대 현재체력 기반 2 = 속도기반 3 = 공격력  
	switch (SkillNum)
	{
	case 0:
		Skill[SkillNum].object.Name = (char*)"마력 베기";
		Skill[SkillNum].Damege = 1.5f;
		Skill[SkillNum].Cost = 10;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 20;
		break;

	case 1:
		Skill[SkillNum].object.Name = (char*)"쪼개버린다 널!";
		Skill[SkillNum].Damege = 0.2f;
		Skill[SkillNum].Cost = 15;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 20;
		break;

	case 2:
		Skill[SkillNum].object.Name = (char*)"진격 찌르기";
		Skill[SkillNum].Damege = 2.0f;
		Skill[SkillNum].Cost = 8;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 20;
		break;

	case 3:
		Skill[SkillNum].object.Name = (char*)"마력 화살";
		Skill[SkillNum].Damege = 1.2f;
		Skill[SkillNum].Cost = 10;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 20;
		break;

	case 4:
		Skill[SkillNum].object.Name = (char*)"회전 베기";
		Skill[SkillNum].Damege = 2.0f;
		Skill[SkillNum].Cost = 20;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 100;
		break;

	case 5:
		Skill[SkillNum].object.Name = (char*)"분쇄한다 널!";
		Skill[SkillNum].Damege = 0.4f;
		Skill[SkillNum].Cost = 25;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 100;
		break;

	case 6:
		Skill[SkillNum].object.Name = (char*)"삼조격";
		Skill[SkillNum].Damege = 2.4f;
		Skill[SkillNum].Cost = 16;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 100;
		break;

	case 7:
		Skill[SkillNum].object.Name = (char*)"환영 화살";
		Skill[SkillNum].Damege = 1.4f;
		Skill[SkillNum].Cost = 20;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 100;
		break;

	case 8:
		Skill[SkillNum].object.Name = (char*)"달빛 난무";
		Skill[SkillNum].Damege = 2.5f;
		Skill[SkillNum].Cost = 35;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 300;
		break;

	case 9:
		Skill[SkillNum].object.Name = (char*)"다 씹어먹어주마!";
		Skill[SkillNum].Damege = 0.6f;
		Skill[SkillNum].Cost = 30;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 300;
		break;

	case 10:
		Skill[SkillNum].object.Name = (char*)"자상 난무";
		Skill[SkillNum].Damege = 3.0f;
		Skill[SkillNum].Cost = 24;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 300;
		break;

	case 11:
		Skill[SkillNum].object.Name = (char*)"취약점 사격";
		Skill[SkillNum].Damege = 1.6f;
		Skill[SkillNum].Cost = 30;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 300;
		break;

	case 12:
		Skill[SkillNum].object.Name = (char*)"언리미티드 소드";
		Skill[SkillNum].Damege = 3.0f;
		Skill[SkillNum].Cost = 45;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 500;
		break;

	case 13:
		Skill[SkillNum].object.Name = (char*)"남자는 등으로 말한다";
		Skill[SkillNum].Damege = 0.8f;
		Skill[SkillNum].Cost = 45;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 500;
		break;

	case 14:
		Skill[SkillNum].object.Name = (char*)"극신속격";
		Skill[SkillNum].Damege = 4.0f;
		Skill[SkillNum].Cost = 32;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 500;
		break;

	case 15:
		Skill[SkillNum].object.Name = (char*)"최종병기 활";
		Skill[SkillNum].Damege = 2.0f;
		Skill[SkillNum].Cost = 45;
		Skill[SkillNum].Type = SkillNum % 4;
		Skill[SkillNum].object.Info.EXP = 500;
		break;

	case 16:
		Skill[SkillNum].object.Name = (char*)"드레인 터치";
		Skill[SkillNum].Damege = 0.8f;
		Skill[SkillNum].Cost = 5;
		Skill[SkillNum].Type = 5;
		break;
	}

}

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	const int Grave = 0;
	const int FindWeapon = 1;
	const int Guard = 2;

	int iChoice = 0;
	int iStartWeapon = 0;

	srand(time(NULL));

	

	int Width(120 / 2 - (strlen("........................................................................") / 2));
	int Height = 5;

	SetPosition(Width, Height, (char*)"........................................................................", 12);
	SetPosition(Width, Height + 1, (char*)"..%%%%...%%%%%....%%%%...%%..%%..%%%%%%..%%..%%...%%%%...%%%%%...%%%%%..", 12);
	SetPosition(Width, Height + 2, (char*)".%%......%%..%%..%%..%%..%%..%%..%%.......%%%%...%%..%%..%%..%%..%%..%%.", 12);
	SetPosition(Width, Height + 3, (char*)".%%.%%%..%%%%%...%%%%%%..%%..%%..%%%%......%%....%%%%%%..%%%%%...%%..%%.", 12);
	SetPosition(Width, Height + 4, (char*)".%%..%%..%%..%%..%%..%%...%%%%...%%........%%....%%..%%..%%..%%..%%..%%.", 12);
	SetPosition(Width, Height + 5, (char*)"..%%%%...%%..%%..%%..%%....%%....%%%%%%....%%....%%..%%..%%..%%..%%%%%..", 12);
	SetPosition(Width, Height + 6, (char*)"........................................................................", 12);

	Sleep(1500);

	system("cls");

	SetColor(15);

	GraveYardBackGround(Grave);

	Player->Name = SetName();
	Sleep(500);

	GraveYardBackGround(Grave);

	GraveYardBackGround(FindWeapon);
	printf_s("내가 일어난 곳에 뭔가 있는거 같다\n");
	printf_s("1.가져간다 2.그냥 놔둔다 입력: ");
	scanf_s("%d", &iChoice);

	switch (iChoice)
	{
	case 1:
		GraveYardBackGround(Grave);

		//시작 장비를 무작위로 부여
		iStartWeapon = rand() % 4;

		//장비 이미지
		Equip(Player, Equipment, iStartWeapon);

		GraveYardBackGround(Grave);

		printf_s("%s\n우선 마을로 가서 정보를 모아야겠어\n", Player->Name);
		Sleep(1000);

		GraveYardBackGround(Grave);
		//던전 0 진행
		Dungeon(Player, Enemy, Equipment, 0, 5, 0, Inventory, Skill, PlayerSkill);

		break;

	default:
		printf_s("%s\n우선 마을로 가서 정보를 모아야겠어\n", Player->Name);

		GraveYardBackGround(Grave);
		//던전 0 진행
		Dungeon(Player, Enemy, Equipment, 0, 5, 0, Inventory, Skill, PlayerSkill);

		break;
	}

	GraveYardBackGround(Guard);
	printf_s("\n경비병\n\n멈추십시오! 못 보던 분이신데...");
	Sleep(1000);

	GraveYardBackGround(Guard);
	printf_s("\n%s\n ...", Player->Name);
	Sleep(1000);

	GraveYardBackGround(Guard);
	printf_s("\n경비병\n\n혹시 모험가가 되려고 오신겁니까?");
	Sleep(1000);

	GraveYardBackGround(Guard);
	printf_s("\n%s\n\n 그렇다", Player->Name);
	Sleep(1000);

	GraveYardBackGround(Guard);
	printf_s("\n경비병\n\n환영합니다! 이 곳은 모험가들의 마을 솜니움입니다.\n");
	Sleep(500);
	printf_s("모험가가 되고싶으면 길드에 먼저 등록 하시면 됩니다.");
	Sleep(1000);

	system("cls");

}

//** 묘지 배경
void GraveYardBackGround(int BGNum)
{
	int Width = 0;
	int Height = 0;
	switch (BGNum)
	{
		case 0:
		system("cls");
		Width = (120 / 2 - (strlen("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWOl:;,,:odokWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM") / 2));
		Height = 0;

		SetPosition(Width, Height, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX:   .lKNWxoXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 1, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNc    oWMMKlkWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 2, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMk.   ,KMMWxlXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 3, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN:   .xWMMKclkOOxddkXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 4, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWx'.  :XMMWd,cdxxxxlcKMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 5, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNKOxl'.   ;KMMMNKKNWMMMO;dWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 6, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM0c,;;:cllodOXWMMMMMMMMMMW0:lNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 7, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMO.  :KWMMMMMMMMMMMWKkkkkkkkKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 8, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNc  .OMMMMWNKO0WMMNdo0KNWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 9, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM0:..;dxxdc'. .OMMWkxNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 10, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWX0OOKKXx.   lWMM0d0MMMMMMMMMMMMMNOkNMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 11, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNc   ,KMMNdxWMMMMMWWMMMMM0::KMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 12, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMk.  .xWMMOdXMMMMKo:cdKWMKclXWMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 13, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMX:   :XMMXx0MMMMXc..'oXMNxdod0NMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 14, (char*)"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNOkKWMMMMMMMMMMMMMMMx.  .kMMMkxNMNK0oldkKWMXk0kl:dNMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 15, (char*)"MMMMMMMMMMMWK0KNNWMMMMMMMMMMMMMMMMMMMMMMMMMMNOl;c0WMMMMMMMMMMMMMX:   cNMMKdOXl,;;cocldOd;d0xokNMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 16, (char*)"MMMMMMMMMMMWNXNX00XWMMMMMMMMMMMMMMMMMMMMMMMNKO0O::KMWNWMMMMXOOXMWx.  .OMMWxxNOol':Oo'';ok0XWMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 17, (char*)"MMMMMMMMMMMMMMMMMWNXWWWMMMMMN0KXOxxxk0WMMMMMWNKOxO0Od:xWMMMNKdckNK;   lNMM0xXWWXdo0kc;;xXXNWMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 18, (char*)"MMMMMMWWMMMMMMMMMWNNW0odXWWXd',ccclox0NMWNXWMWKO0Oo;,.cNN0XWWXx:cd:.  '0MMNxlxO0d:lol:ldocoONMMMMMMMMMMMMMMMMMMMMMMMMMMM");
		SetPosition(Width, Height + 19, (char*)"MMMMMMXkk0KNWMMMNOxOOdcl0Kkkx,.;xkdc;cldOd:d0Oxkxc,;:.:KOdkOOxoc,;:.   oWMMOlc'cc.',,;xXXXXXXXNWWWMWNNWMMMMWMMMMMMMMMMMM");
		SetPosition(Width, Height + 20, (char*)"MMMMMMMNXXK0Okkkdllc,':oxxol;'':xXOl';oodo,':codccc,',:o;..;oxkd:;c,.  ,KMMKdl,..cl,:::oocoxolloxKW0k00KNWKkKMMMMWNNMMMM");
		SetPosition(Width, Height + 21, (char*)"MMMWNNWWKxdkkl;;ok0Kxl:coll:',okxo'...'''..  .coc:cldxc'..,ccoOk:ckc.. .xMMWd..  :::;.',';kXXX00XXK0XWN0xkkx0KKOxxdk00WM");
		SetPosition(Width, Height + 22, (char*)"WWWNxOXOdc:coolxXNOkdol::;c;.....          .'',:c:;,oOlcl;:oddo:';Ok,'. lNMMO....,''',,..,:;lkddddkOOkddllxdlc:;'coxdxKN");
		SetPosition(Width, Height + 23, (char*)"kxKNKkxlodxO0Oocdo'                            .',,,'::;,,lxOO:';oKKc.. ;KMMNl'..::',,'.....':;.'lloc::;;,..,,:,,dxkXWMM");
		SetPosition(Width, Height + 24, (char*)"------------------------------------------------------------------------------------------------------------------------");
		break;

		case 1:
			system("cls");
			Width = (120 / 2 - (strlen("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@") / 2));
			Height = 0;

			SetPosition(Width, Height, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
			SetPosition(Width, Height + 1, (char*)"@@@@@@@@@@@@@@@@@@@@ @@@ @@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@");
			SetPosition(Width, Height + 2, (char*)"@@@@@@@@@@@@@@@@@@@@@  @ @@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@");
			SetPosition(Width, Height + 3, (char*)" @@@@@@@@@@@@@@@@@@@@@@  @ @@@@@@@@@ @@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@@@@@@  @@@@@@");
			SetPosition(Width, Height + 4, (char*)"  @@@@@@@@@@@@@@@@@@@@@   @  @@@@@@  @@@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@@@@@@@@@  @@@@@");
			SetPosition(Width, Height + 5, (char*)"   @@@@@@@@@@@@@@@@@@@@   @    @@@  @@@@@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       @@@@@@@@@@ @@@@@@@ @@@@@@  @@@@");
			SetPosition(Width, Height + 6, (char*)"   @@@@@@@@@@@@@@@@@@@    @     @@  @@@@@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       @@@@@@@@@@  @@@@@@  @@@@@@   @@@");
			SetPosition(Width, Height + 7, (char*)"   @@@@@@ @@@@@@@@@@@@    @     @@  @@@@@@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@ @@@@@@  @@@@@@@@   @@");
			SetPosition(Width, Height + 8, (char*)"    @@@@ @@@@@@@  @@@@     @   @    @@@@@@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@ @  @  @@@  @@@@@@@@   @@");
			SetPosition(Width, Height + 9, (char*)"    @@@  @@@@@@@  @@@      @  @     @ @@@@@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        @@@@@@@@@@   @     @@@@@@@@@@   @@");
			SetPosition(Width, Height + 10, (char*)"    @   @@@@@@@@   @@       @@@    @   @@@@     @@@@@@@@@@@@@ @@@@@@@@@@@@@@@        @@@@@@@@@@@  @@@      @@@@@@@@    @");
			SetPosition(Width, Height + 11, (char*)"   @    @@@@@@@    @        @      @    @@@      @@@@@@@@@ @@ @@ @@@@@@@@@@@        @  @@@@@@@@@  @@@@@     @@@@@@@    @");
			SetPosition(Width, Height + 12, (char*)"   @   @@@@@@@@     @       @      @      @      @@@@@@@@@@     @@@@@@@@@@@        @    @@@@@@@@  @@@@ @    @@@@@@@     ");
			SetPosition(Width, Height + 13, (char*)"  @    @@@@@@@      @      @       @      @      @@@@@@@@@       @@@@@@@@@@       @      @@@@@@   @@@@  @    @@@@@      ");
			SetPosition(Width, Height + 14, (char*)" @      @@@@@@      @      @      @       @       @@@@@@@@@     @@@@@@@@@@        @       @@@@@   @@@@  @    @@@@@      ");
			SetPosition(Width, Height + 15, (char*)" @       @@@@        @    @       @       @       @@@@@@@@ @@ @@ @@@@@@@@@       @@        @@@   @@@@    @    @@@@      ");
			SetPosition(Width, Height + 16, (char*)"@         @@         @    @        @     @        @@@@@@@@@@@ @@@@@@@@@@@        @@        @@    @@@@    @    @@@@      ");
			SetPosition(Width, Height + 17, (char*)"          @          @    @        @     @        @@@@@@@@@@@@@@@@@@@@@@@       @@@@        @    @@@@    @    @@@       ");
			SetPosition(Width, Height + 18, (char*)"          @          @   @          @   @          @@@@@@@@@@@@@@@@@@@@@        @@@@       @@    @@@      @    @@       ");
			SetPosition(Width, Height + 19, (char*)"         @          @    @           @ @           @@@@@@@@@@@@@@@@@@@@@         @@@@       @     @@      @    @@       ");
			SetPosition(Width, Height + 20, (char*)"------------------------------------------------------------------------------------------------------------------------");
			break;

		case 2:
			system("cls");
			Width = (120 / 2 - (strlen("            @            ") / 2));
			Height = 0;

			SetPosition(Width, Height, (char*)"            @            ");
			SetPosition(Width, Height + 1, (char*)"            @            ");
			SetPosition(Width, Height + 2, (char*)"  @@,       @            ");
			SetPosition(Width, Height + 3, (char*)" @@.@*      @            ");
			SetPosition(Width, Height + 4, (char*)"@@@  @  @@@@@            ");
			SetPosition(Width, Height + 5, (char*)"@@ @:@@@@@@@@            ");
			SetPosition(Width, Height + 6, (char*)"@@    @@@@@@@            ");
			SetPosition(Width, Height + 7, (char*)" @@@;@@@@@@@@      ;;    ");
			SetPosition(Width, Height + 8, (char*)" .@@@@@@@@@@@    @@@@@@  ");
			SetPosition(Width, Height + 9, (char*)"   @@@=    @@     @@@-   ");
			SetPosition(Width, Height + 10, (char*)"            @      @@    ");
			SetPosition(Width, Height + 11, (char*)"            @     .@@.   ");
			SetPosition(Width, Height + 12, (char*)"            @  ;@@@@@@@: ");
			SetPosition(Width, Height + 13, (char*)"            @@@@@@@@@@@@ ");
			SetPosition(Width, Height + 14, (char*)"            @    =@@@@@@ ");
			SetPosition(Width, Height + 15, (char*)"            @     @@@. @@");
			SetPosition(Width, Height + 16, (char*)"            @     @@@  @@");
			SetPosition(Width, Height + 17, (char*)"            @    #@@@@  @");
			SetPosition(Width, Height + 18, (char*)"            @    @@@@@.  ");
			SetPosition(Width, Height + 19, (char*)"            @    @@ $@   ");
			SetPosition(Width, Height + 20, (char*)"            @    @   @   ");
			SetPosition(Width, Height + 21, (char*)"            @    @   @   ");
			SetPosition(Width, Height + 22, (char*)"            @   :-   ~@  ");
			SetPosition(Width, Height + 23, (char*)"            @   @     @  ");
			SetPosition(Width, Height + 24, (char*)"            @  @@     @@ ");
			break;
	}
	
}

void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	int iSelect = 0;

	const int Village = 1;

	while (iStage == 1)
	{
		printf_s("어디로 갈까?\n1.모험가 길드 2.상가 3.대장간 4.훈련장 5.내 정보 6.마을 밖으로 간다\n입력: ");

		scanf("%d", &iSelect);

		switch (iSelect)
		{
			//퀘스트 NPC
		case 1:
			system("cls");
			Guild(Player, Quest, Enemy, Equipment);
			break;
			//상점
		case 2:
			system("cls");
			Shop(Player, Inventory);
			break;
			// 강화	
		case 3:
			system("cls");
			Forge(Player, Equipment);
			break;
		case 4:
			system("cls");
			Training(Player, Equipment, Inventory, Skill, PlayerSkill);
			//소지 장비 & 소지 아이템 & 현재 스텟 조회
			break;
		case 5:
			system("cls");
			PlayerStatus(Player, Village);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (Equipment[j + (i * 10)].object.State == 1)
						printf_s("%s\t", Equipment[j + (i * 10)].object.Name);
				}
			}
			break;
			//던전
		case 6:
			system("cls");
			DungeonEnterence(Player, Enemy, Equipment, Inventory, Quest, Skill, PlayerSkill);
			break;
		}
	}
}

void AdventurerVillageBackGround()
{
	int Width = 0;
	int Height = 0;
	

	system("cls");
	Width = (120 / 2 - (strlen("            ~~                              -.                                     ..               ") / 2));
	Height = 0;
	SetPosition(Width, Height, (char*)"            ~~                              -.                                     ..               ");
	SetPosition(Width, Height + 1, (char*)"          --  *                            =.-           *$~     *:               -  ~              ");
	SetPosition(Width, Height + 1, (char*)"         .,,   -             ,~--,.       !!  ::        ;.=#:   =##==#!:~        --   ,~            ");
	SetPosition(Width, Height + 1, (char*)"        .;  ~  ..         .-,,     =.    :     ~.~     -..,*#. ~!-#*;!:,-=         .;               ");
	SetPosition(Width, Height + 1, (char*)"        =  ,     :         :,     ~.*-  --.-.~   ;,    .~!!=#.,$;~-=*~~:=#-     ,   .    .          ");
	SetPosition(Width, Height + 1, (char*)"        =     ;  ,:   .-. ,~     ~   ;- ~:~ ,  -. *      ,: = ;=~, :;!*==*$    !  ~                 ");
	SetPosition(Width, Height + 1, (char*)"        ,-, !:*  ,,   ;~-.:;!=$$$     .:,,. .,!,  !    . .,;$ .;   :;-~~,.:    .  ~!~.;  .          ");
	SetPosition(Width, Height + 1, (char*)"         ::-:.~: ~    *## ~        =:  ,!. !:;,. !     ,   !#.,:!*;:$;:::~~    ~ ~;!=:-.:           ");
	SetPosition(Width, Height + 1, (char*)"          ,$;~-=**    :$* .        #*   ~.!.~~.==;     ,  .*#.,:!;#:=    .-    . *,-$ ~;            ");
	SetPosition(Width, Height + 1, (char*)"         ~-~*: .~~~~--;$=  ,-    ,,#= : ,~;,:.,. .     ,  .;#.-*=!$:=,  .~-  ~  .~,-~: ,,           ");
	SetPosition(Width, Height + 1, (char*)"         :;~*:~~~:~:;- .- .;--;::!=**!:=**=:~~!;;;     ,  !*#*,  !*;~!,..:   *   , ,;*              ");
	SetPosition(Width, Height + 1, (char*)"         !  ,  .   !~.-:*;:;:**  .= ,~~-,-*-,:...!     *$$#$~   .! --!;:!::~~=:~-:--!=~~            ");
	SetPosition(Width, Height + 1, (char*)"        .-     -.,~!=-;==~-,=.,. .=  .,~,--~.,..,:.:-~:        ::- -:-~~:;=~;==~;;;-;=::-           ");
	SetPosition(Width, Height + 1, (char*)"                             ,                        ~;-*=-,.                                      ");
	SetPosition(Width, Height + 1, (char*)"                                        .::~    .,,,.                                               ");
	SetPosition(Width, Height + 1, (char*)"                                       ~- ,                                                         ");
	SetPosition(Width, Height + 1, (char*)"                                            ,                                                       ");
	SetPosition(Width, Height + 1, (char*)"                           .,-,.         ,~~                                                        ");
}

void Castle(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}

void NecromancerTower(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}

void DungeonEnterence(Object* Player, Object* Enemy, EQUIPMENT* Equipment, INVENTORY* Inventory, Object* Quest, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	int StageNumber = 0;
	
	printf_s("어디로 갈까?\n");
	switch (iStage)
	{
	case 1:
		printf_s("1.소너스 평야\n2.도적단 야영지\n3.고블린취락\n4.오크거주지\n5.오우거야영지\n(6.돌아간다)\n입력 : ");

		//모험가 마을 1~5
		scanf("%d", &StageNumber);
		if (StageNumber > 0 && StageNumber < 6)
		{
			Dungeon(Player, Enemy, Equipment, StageNumber, 5, Quest, Inventory, Skill, PlayerSkill);
			break;
		}

		else
			break;
		
	}
	/*
		case 2:
			printf_s("1.\n2.\n3.\n4.\n5.\n(6.돌아간다)\n입력 : ");

			//왕성 6~10
			scanf("%d", &StageNumber);
			StageNumber += 5;
			if (StageNumber > 0 && StageNumber < 6)
			{
				Dungeon(Player, Enemy, Equipment, StageNumber, 5, Quest, Inventory, Skill, PlayerSkill);
			}
			break;

		case 3:
			printf_s("1.\n2.\n3.\n4.\n5.\n(6.돌아간다)\n입력 : ");

			//사령술사의 탑 11~15
			scanf("%d", &StageNumber);
			StageNumber += 15;
			if (StageNumber > 0 && StageNumber < 6)
			{
				Dungeon(Player, Enemy, Equipment, StageNumber, 5, Quest, Inventory, Skill, PlayerSkill);
			}
			break;
		*/
}

void Dungeon(Object* Player, Object* Enemy, EQUIPMENT* Equipment, int EnemyIndex, int EventCount, Object* Quest, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	const int Grave = 0;
	short Walk = 1;
	int Loop = 0;

	int RandomEnemy = 0;

	srand(time(NULL));

	while (Walk)
	{
		switch (iStage)
		{
		case 0:
		{
			//** 던전 스테이지 진행
			if (Loop < EventCount)
			{
				system("cls");

				DungeonBackGround();
				for (int i = 0; i < 3; i++)
				{
					printf(".");
					Sleep(333);
				}

				++Loop;

				//적 조우
			
				if (Loop == 3)
				{
					Status(Player, Enemy, 1);

					printf_s("%s\n멈춰라! 묘지를 서성이다니 수상한 녀석이군\n", Enemy[1].Name);
					Sleep(500);
					printf_s("가진 것을 다 내놓으면 모른척 해줄 수 있다!\n");
					Sleep(1000);

					system("cls");
					Status(Player, Enemy, 1);
					Battle(Player, Enemy, 1, Quest, Inventory, Skill, PlayerSkill);

					DungeonBackGround();
					printf_s("%s\n흐음 이 녀석 약하네..\n", Player->Name);
					Sleep(500);
					printf_s("기사인 줄 알았는데 그냥 갑옷을 주워서 행세를 했을뿐인가..\n");
					Sleep(500);
					printf_s("내가 잘 써주지\n");
					Sleep(1000);

					DungeonBackGround();
					//초기 방어구
					for (int i = 4; i < 9; i++)
					{
						Equip(Player, Equipment, i);
					}
				}

				else
				{
					Status(Player, Enemy, EnemyIndex);
					Battle(Player, Enemy, EnemyIndex, Quest, Inventory, Skill, PlayerSkill);
				}
			}

			else if (Loop >= EventCount)
				Walk = 0;

			break;
		}
		case 1:
		{
			if (Loop < EventCount)
			{
				system("cls");

				for (int i = 0; i < 3; i++)
				{
					printf(".");
					Sleep(333);
				}

				++Loop;

				switch (EnemyIndex)
				{
				case 1:
					RandomEnemy = (rand() % 2) + 2;
					Status(Player, Enemy, RandomEnemy);
					Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory, Skill, PlayerSkill);
					break;

				case 2:
					RandomEnemy = (rand() % 3) + 3;
					Status(Player, Enemy, RandomEnemy);
					Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory, Skill, PlayerSkill);
					break;

				case 3:
					RandomEnemy = rand() % 3 + 6;
					Status(Player, Enemy, RandomEnemy);
					Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory, Skill, PlayerSkill);
					break;

				case 4:
					RandomEnemy = rand() % 3 + 9;
					Status(Player, Enemy, RandomEnemy);
					Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory, Skill, PlayerSkill);
					break;

				case 5:

					Loop = 5;

					RandomEnemy = rand() % 2 + 10;

					if (Loop == EventCount)
					{
						Status(Player, Enemy, 12);
						Walk = Battle(Player, Enemy, 12, Quest, Inventory, Skill, PlayerSkill);
					}

					else
					{
						Status(Player, Enemy, RandomEnemy);
						Walk = Battle(Player, Enemy, RandomEnemy, Quest, Inventory, Skill, PlayerSkill);
					}
					break;
				}
			}

			else if (Loop >= EventCount)
				Walk = 0;

			break;
		}
		}
	}

}

void DungeonBackGround()
{
	system("cls");
	int Width = (120 / 2 - (strlen("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@!!@@@@@@@@@@@@@@@@@@@ * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@") / 2));
	int Height = 0;

	SetPosition(Width, Height, (char*)    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@!!@@@@@@@@@@@@@@@@@@@ * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 1, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:                #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 2, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*               =@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 3, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-             ,$@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 4, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@!@@@@@@@@@=             ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 5, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-.-,!#,@#~-!           -#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 6, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-                      ~@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 7, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-                     ,@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 8, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-                     !:-$@@*@@=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 9, (char*)"~*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-                     -  ~@~,$!=@@@@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 10, (char*)" ~!=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:                         .  . #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 11, (char*)" -:*@.@@@@@@@@@@@@@@@@@@@@;@@@@@@@@@@@@@@@@$                              #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.", 2);
	SetPosition(Width, Height + 12, (char*)"   , .@:-@#-@@@@@@@@@@@~*# ~#@@@@@@@@@@@@@@@.                             #@@@@@@@@@@@$$#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@~", 2);
	SetPosition(Width, Height + 13, (char*)"     .=  #;.*@#:@@@@@@@- ;  ~@@@@@@@@@@@@@@@.                            :@@@@@@@@@@@*,-=!@@@@@@@@@@@@@@@@@@@@@@@@@@@@!", 2);
	SetPosition(Width, Height + 14, (char*)"      ,  #  ;$-.@@@@@@@~     #@@@@@@@@@@@@@@.                            =@@@@@@@@@@@!  ; @;@!@@!@@@@@@@@@@@@@@@@@@@@@.", 2);
	SetPosition(Width, Height + 15, (char*)"         .   . .@@@@@@@$     #@@@@@@@@@@@@@@.                            =@@@@@@@@@@@#    .-@-##~@@@@@@@@#-$:$@@@@@@@@.", 2);
	SetPosition(Width, Height + 16, (char*)"               .@@@@@@@@.    #@@@@@@@@@@@@@@,                            =@@@@@@@@@@@#        ~$ ;@.@@@@@# .  @@@@@@@@.", 2);
	SetPosition(Width, Height + 17, (char*)"               :@@@@@@@@.,---@@@@@@@@@@@@@@@@@@@$=================$@@@@@@@@@@@@@@@@@@@---------, ~, @@@@@@,   @@@@@@@@.", 2);
	SetPosition(Width, Height + 18, (char*)"               =@@@@@@@@!$@@@@@@@@@@@@@@@@@@@@@@-                 -@@@@@@@@@@@@@@@@@@@@@@@@@@@@=!;;;@@@@@@=  ~@@@@@@@@.", 2);
	SetPosition(Width, Height + 19, (char*)"           .;**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$                 .*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#*;#@@@@@@@@~", 2);
	SetPosition(Width, Height + 20, (char*)"       ~$###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.                 ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$", 2);
	SetPosition(Width, Height + 21, (char*)"  ..$@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.                 ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 22, (char*)"-;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.                .*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 23, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*                 :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 24, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-                .#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", 2);
	SetPosition(Width, Height + 25, (char*)"-----------------------------------------------------------------------------------------------------------------------", 2);

}

void Guild(Object* Player, Object* Quest, Object* Enemy, EQUIPMENT* Equipment)
{
	int iChoice = 0;
	int QChoice = 0;

	int Continue = 1;


	//접수원 이미지
	printf_s("어서오세요!\n");
	printf_s("이 곳은 모험가 길드입니다.\n");
	printf_s("의뢰를 받거나 모험가 등급을 올릴 수 있어요\n");
	//접수원 이미지

	while (Continue)
	{
		printf_s("1.의뢰\t2.승급\t3.등급 조회\t4.돌아간다\n입력 :");
		scanf("%d", &iChoice);

		switch (iChoice)
		{

		case 1:
			system("cls");
			//퀘스트목록

				//완료
			for (int i = 0; i < 4; i++)
			{
				if (Quest[i].State == 1 && Quest[i].Kills == Enemy[Quest[i].Num].State)
				{

					Quest[i].State = 2;

					switch (i)
					{
					case 0:
						printf_s("모험가님! %s의뢰를 완수해주셨군요\n여기 보상입니다!\n", Quest[i].Name);
						Sleep(500);
						printf_s("%d Gold를 얻었다!\n", Quest[i].Info.Gold);
						Sleep(500);
						printf_s("%d EXP를 얻었다!\n", Quest[i].Info.EXP);
						Sleep(500);

						Quest[i].Name = (char*)"슬라임 5마리 처치(완료)";
						break;
					case 1:
						printf_s("모험가님! %s의뢰를 완수해주셨군요\n여기 보상입니다!\n", Quest[i].Name);
						Sleep(500);
						printf_s("%d Gold를 얻었다!\n", Quest[i].Info.Gold);
						Sleep(500);
						printf_s("%d EXP를 얻었다!\n", Quest[i].Info.EXP);
						Sleep(500);

						Quest[i].Name = (char*)"고블린 라이더 3마리 처치(완료)";
						break;
					case 2:
						printf_s("모험가님! %s의뢰를 완수해주셨군요\n여기 보상입니다!\n", Quest[i].Name);
						Sleep(500);
						printf_s("%d Gold를 얻었다!\n", Quest[i].Info.Gold);
						Sleep(500);
						printf_s("%d EXP를 얻었다!\n", Quest[i].Info.EXP);
						Sleep(500);

						Quest[i].Name = (char*)"오크 주술사 2마리 처치(완료)";
						break;
					case 3:
						printf_s("오우거를 쓰러뜨려주셨군요! 모험가님 누구도 못해냈던 거에요!\n");
						Quest[i].Name = (char*)"오우거 처치(완료)";
						iStage = 4;
						SceneState = Scene_END;
						break;
					}
					Player->Info.Gold += Quest[i].Info.Gold;
					Player->Info.EXP += Quest[i].Info.EXP;
					system("cls");
				}
			}
			
			if (SceneState == Scene_END)
			{
				Continue = 0;
				break;
			}
			// 0 = 시작 가능 1 = 진행중 2 = 완료
			for (int i = 0; i < 4; i++)
			{
				printf_s("No %d. %s\n", i + 1, Quest[i].Name);
			}

			printf_s("수락할 의뢰의 번호를 입력 해주세요(5 : 돌아간다)\n입력 : ");
			scanf("%d", &QChoice);

			QuestState(Quest, Enemy, QChoice);

			break;

		case 2:
			system("cls");

			//모험가 등급(level)
				//테스트용 경험치
			LevelUp(Player, Equipment);
			break;

		case 3:
			system("cls");

			printf_s("현재 플레이어의 등급은 %d 입니다.\n", Player->Info.Level);
			Sleep(1500);
			break;

		case 4:
			system("cls");

			printf_s("항상 수고많으세요 또 오세요!\n");
			Continue = 0;
			break;
		}
	}
}

void InitializeQuest(Object* Quest, int QuestIndex, int Stage)
{
	if (Stage == 1)
	{
		switch (QuestIndex)
		{
		case 0:
			Quest[QuestIndex].Name = (char*)"슬라임 5 마리 처치";
			Quest[QuestIndex].State = 0;
			Quest[QuestIndex].Num = 2;
			Quest[QuestIndex].Info.Gold = 50;
			Quest[QuestIndex].Info.EXP = 25;
			//퀘스트 완료 조건
			Quest[QuestIndex].Kills = 5;
			break;

		case 1:
			Quest[QuestIndex].Name = (char*)"고블린 라이더 3마리 처치";
			Quest[QuestIndex].State = 0;
			Quest[QuestIndex].Num = 8;
			Quest[QuestIndex].Info.Gold = 100;
			Quest[QuestIndex].Info.EXP = 50;
			Quest[QuestIndex].Kills = 3;
			break;
		case 2:
			Quest[QuestIndex].Name = (char*)"오크 주술사 2마리 처치";
			Quest[QuestIndex].State = 0;
			Quest[QuestIndex].Num = 11;
			Quest[QuestIndex].Info.Gold = 200;
			Quest[QuestIndex].Info.EXP = 100;
			Quest[QuestIndex].Kills = 2;
			break;
		case 3:
			Quest[QuestIndex].Name = (char*)"오우거 처치";
			Quest[QuestIndex].State = 0;
			Quest[QuestIndex].Num = 12;
			Quest[QuestIndex].Info.Gold = 400;
			Quest[QuestIndex].Info.EXP = 200;
			Quest[QuestIndex].Kills = 1;
			break;
			
		}
	}

	/*
	else if (Stage == 2)
	{
		switch (QuestIndex)
		{

		}
	}
	*/
}

void QuestState(Object* Quest, Object* Enemy, int _Choice)
{


	switch (_Choice)
	{
		case 1:
			if (Quest[_Choice - 1].State == 0)
			{
				system("cls");

				printf_s("[접수원]\n");
				printf_s("주변에 슬라임이 급증했어요!\n");
				Sleep(500);
				printf_s("처리해주시면 그만한 보상을 드릴게요\n");
				Quest[_Choice - 1].Name = (char*)"슬라임 5마리 처치(진행중)";
				Quest[_Choice - 1].State = 1;
				Enemy[Quest[_Choice - 1].Num].State = 0;
				break;
			}

			else if (Quest[_Choice - 1].State == 1)
			{
				system("cls");

				printf_s("%s[%d/%d]", Quest[_Choice - 1].Name, Enemy[Quest[_Choice - 1].Num].State, Quest[_Choice - 1].Kills);
				Sleep(1500);
				break;
			}

			else
			{
				system("cls");
				printf_s("이미 완료한 퀘스트 입니다!\n");
				Sleep(1000);
				break;
			}

		case 2:
			if (Quest[_Choice - 1].State == 0)
			{
				system("cls");

				printf_s("[접수원]\n");
				printf_s("큰일이에요! 요즘 고블린 무리중에 늑대를 타고 다니는 개체가 나타났어요\n");
				Sleep(500);
				printf_s("신참 모험가 분들이 고블린 토벌중 마주쳐서 크게 다치는 일이 생기고 있어요\n");
				Sleep(500);
				printf_s("처리해주시면 그만한 보상을 드릴게요\n");
				Sleep(1000);
				
				Quest[_Choice - 1].Name = (char*)"고블린 라이더 3마리 처치(진행중)";
				Quest[_Choice - 1].State = 1;
				Enemy[Quest[_Choice - 1].Num].State = 0;
				break;
			}

			else if (Quest[_Choice - 1].State == 1)
			{
				printf("%s[%d/%d]", Quest[_Choice - 1].Name, Enemy[Quest[_Choice - 1].Num].State, Quest[_Choice - 1].Kills);
				Sleep(1500);
				break;
			}

			else
			{
				printf_s("이미 완료한 퀘스트 입니다!\n");
				Sleep(1000);
				break;
			}

		case 3:
			if (Quest[_Choice - 1].State == 0)
			{
				system("cls");
				printf("[접수원]\n");
				printf_s("큰일이에요! 오크 무리중에 주술을 사용하는 오크가 있다는 제보가 있어요!\n");
				Sleep(500);
				printf_s("피해가 커지기 전에 처치해주실수 있나요?");
				Sleep(1000);

				Quest[_Choice - 1].Name = (char*)"오크 주술사 2마리 처치(진행중)";
				Quest[_Choice - 1].State = 1;
				Enemy[Quest[_Choice - 1].Num].State = 0;
				break;
			}

			else if (Quest[_Choice - 1].State == 1)
			{
				printf("%s[%d/%d]", Quest[_Choice - 1].Name, Enemy[Quest[_Choice - 1].Num].State, Quest[_Choice - 1].Kills);
				Sleep(1500);
				break;
			}

			else
			{
				printf_s("이미 완료한 퀘스트 입니다!\n");
				Sleep(1000);
				break;
			}
		case 4:
			//수락
			if (Quest[_Choice - 1].State == 0)
			{
				system("cls");
				printf("[접수원]\n");
				printf_s("이 의뢰를 받으실려구요?\n");
				printf_s("아무도 이 임무를 하러 가서 돌아오지 못했어요...\n");
				printf_s("그래도 가시겠어요 ?\n");

				Quest[_Choice - 1].Name = (char*)"오우거 처치(진행중)";
				Quest[_Choice - 1].State = 1;
				Enemy[Quest[_Choice - 1].Num].State = 0;
				break;
			}

			else if (Quest[_Choice - 1].State == 1)
			{
			printf("%s[%d/%d]", Quest[_Choice - 1].Name, Enemy[Quest[_Choice - 1].Num].State, Quest[_Choice - 1].Kills);
			break;
			}

			else
			{
			printf_s("이미 완료한 퀘스트 입니다!\n");
			break;
			}
		default :
				break;
	}

}

void LevelUp(Object* Player, EQUIPMENT* Equipment)
{
	int iAgree = 0;

	int iNeedEXP[16];

	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
			iNeedEXP[i] = 10;

		else
			iNeedEXP[i] = iNeedEXP[i - 1] * 2;

	}

	printf_s("현재 플레이어의 등급은 %d 입니다.\n", Player->Info.Level);
	Sleep(500);
	printf_s("승급까지 %d EXP필요합니다.\n", iNeedEXP[Player->Info.Level - 1]);
	Sleep(500);
	printf_s("승급하시겠습니까?(1.예 2.아니요)\n보유EXP : %d\n입력 : ", Player->Info.EXP);
	scanf("%d", &iAgree);

	if (iAgree == 1)
	{
		system("cls");
		//	2Level부터 올라가기위해 필요한 경험치가 iNeed[0]부터 저장 되어있기 때문에
		//	플레이어 현재 Level에서 1을 빼면 된다.
		Player->Info.EXP -= iNeedEXP[Player->Info.Level - 1];
		Player->Info.Level++;

		printf_s("모험가등급이 %d로 올랐다!!\n", Player->Info.Level);
		if (Player->Info.Level == 2)
		{
			system("cls");
			printf("[접수원]\n");
			printf_s("첫 진급 축하드립니다!\n이건 길드에서드리는 선물이에요!\n");
			Sleep(1000);
			Equip(Player, Equipment, 9);
			Player->State = 0;
		}

		else if (Player->Info.Level % 5 == 0)
		{
			switch (Player->State)
			{
			case 0:
				break;
			}
		}

	}
}

void Shop(Object* Player, INVENTORY* Inventory)
{
	int iIndex = 0;

	int iPurchase = 0;
	int iPNumber = 0;

	int iSell = 0;
	int iSNumber = 0;

	int Continue = 1;

	while (Continue)
	{

		ShopBackGround();
		printf_s("어서오시게\n1.산다\t2.판다\t3.돌아간다\n입력 : ");
		scanf("%d", &iIndex);

		switch (iIndex)
		{
		case 1:
			system("cls");

			//상점물건목록
			for (int i = 0; i < 1; i++)
			{
				printf_s("아이템명\t가격\n");
				printf_s("%d. %s\t\t%d G\n", i + 1, Inventory[i].item.Object.Name, Inventory[i].Equipment.Price);

			}
			printf_s("보유금액 : %d\n", Player->Info.Gold);

			printf_s("구매하고 싶은 항목의 번호를 입력하십시오 : ");
			scanf("%d", &iPurchase);

			if (Inventory[iPurchase - 1].Equipment.Stock < 0 && iSell < 33)
			{
				system("cls");

				printf_s("없는 항목 입니다!\n");
			}

			else
			{
				printf_s("몇 개 구매하시겠습니까?(보유중:%d) : ", Inventory[iPurchase - 1].Equipment.Stock);
				scanf("%d", &iPNumber);

				if (Player->Info.Gold < (Inventory[iPurchase - 1].Equipment.Price * iPNumber))
				{
					system("cls");

					printf_s("Gold가 부족합니다.\n");
				}

				else
				{
					system("cls");

					printf_s("%s을(를) %d개 구입했다.\n", Inventory[iPurchase - 1].item.Object.Name, iPNumber);
					Sleep(500);

					printf_s("%d Gold를 지불했다\n", Inventory[iPurchase - 1].Equipment.Price * iPNumber);
					Inventory[iPurchase - 1].Equipment.Stock += iPNumber;
					Player->Info.Gold -= Inventory[iPurchase - 1].Equipment.Price * iPNumber;
					Sleep(1000);
				}
			}

			break;

		case 2:
			system("cls");

			//플레이어 물건목록
			PlayerScene(Player, Inventory);
			printf_s("보유금액 : %d\n", Player->Info.Gold);

			printf_s("판매하고 싶은 항목의 번호를 입력하십시오(33.뒤로) : ");
			scanf("%d", &iSell);

			if (Inventory[iSell - 1].Equipment.Stock < 0)
			{
				system("cls");

				printf_s("없는 항목입니다!\n");
				Sleep(1000);
			}


			else if (iSell < 33)
			{
				system("cls");

				printf_s("몇 개 판매하시겠습니까?(보유중:%d) : ", Inventory[iSell - 1].Equipment.Stock);
				scanf("%d", &iSNumber);

				if (Inventory[iSell - 1].Equipment.Stock < iSNumber)
				{
					system("cls");

					printf_s("가진 것보다 많이 팔 수 없습니다!\n");
					Sleep(1000);
				}

				else
				{
					system("cls");

					printf_s("%s을(를) %d개 판매했다.\n", Inventory[iSell - 1].item.Object.Name, iSNumber);
					Sleep(500);
					printf_s("%d Gold를 얻었다\n", Inventory[iSell - 1].Equipment.Price * iSNumber);
					Inventory[iSell - 1].Equipment.Stock -= iSNumber;
					Player->Info.Gold += Inventory[iSell - 1].Equipment.Price * iSNumber;
					Sleep(1000);
				}

			}
			break;

		case 3:
			system("cls");

			printf_s("고맙네! 또 오시게!\n");
			Sleep(1000);
			Continue = 0;
			break;
		}
	}

}

void ShopBackGround()
{

}

void Forge(Object* Player, EQUIPMENT* Equipment)
{
	short Loop = 1;

	int SelectParts = 0;

	while (Loop)
	{
		printf("Gold만 주면 장비를 더 멋지게 만들어 드리리다!\n");
		Sleep(500);
		//  일의 자리가 0~3무기 4모자 5상의 6하의 7신발 8 장갑
		// 0검 1 도끼 2 창 3 활
		printf("어느 장비를 강화하시겠습니까?\n1.무기\n2.모자\n3.상의\n4.하의\n5.신발\n6.장갑\n7.돌아간다. 입력 : ");
		scanf("%d", &SelectParts);

		if (SelectParts == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (Equipment[j + (10 * i)].object.State == 1)
					{
						system("cls");

						Reinforce(Player, Equipment, i);
					}
				}
			}
		}

		else if (SelectParts < 7 && SelectParts >1)
			for (int i = 0; i < 3; i++)
			{
				

				if (Equipment[(SelectParts + 2) + (i * 10)].object.State == 1)
				{
					system("cls");

					Reinforce(Player, Equipment, SelectParts + 2);
				}
			}

		else
		{
			system("cls");

			printf_s("또 오게나!\n");
			Sleep(1000);
			Loop = 0;
		}
	}
}

void Training(Object* Player, EQUIPMENT* Equipment, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	short Loop = 1;

	int YoN = 0;
	int EquipmentNum = 0;
	printf_s("어서오십시오. 여기는 훈련장\n");
	Sleep(500);
	printf_s("여기서는 스킬을 배울수 있습니다.\n");
	Sleep(500);

	

	while (Loop)
	{
		// 소유한 무기에 따라 배울수 있는 스킬이 다르다
	// 소유한 무기가 무엇인지 알아내기위한 반복문
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				EquipmentNum = j + (i * 10);
				if (Equipment[EquipmentNum].object.State == 1)
				{
					for (int k = 0; k < 4; k++)
					{
						printf_s("%d. %s", k + 1, Skill[EquipmentNum+k*4].object.Name);

						if (Skill[EquipmentNum + k * 4].object.Name == PlayerSkill->Skill.object.Name)
							printf_s("(습득함)\n");
						else
							printf_s("\n");
					}

					printf_s("스킬을 배우시려면 %d EXP가 필요합니다\n", Skill[(PlayerSkill->Grade * 4) + (EquipmentNum % 10)].object.Info.EXP);
					Sleep(500);
					printf_s("보유 EXP: %d\t스킬을 배우시겠습니까?(1.예 2.아니오) :", Player->Info.EXP);
					scanf("%d", &YoN);

					if (YoN == 1 && PlayerSkill->Grade < 4)
					{
						if (Player->Info.EXP >= Skill[(PlayerSkill->Grade * 4) + (i % 10)].object.Info.EXP)
						{
							system("cls");

							Player->Info.EXP -= Skill[(PlayerSkill->Grade * 4) + (i % 10)].object.Info.EXP;

							PlayerSkill[PlayerSkill->Grade].Skill.object.Name = Skill[(PlayerSkill->Grade * 4) + (EquipmentNum % 10)].object.Name;
							PlayerSkill[PlayerSkill->Grade].Skill.Damege = Skill[(PlayerSkill->Grade * 4) + (EquipmentNum % 10)].Damege;
							PlayerSkill[PlayerSkill->Grade].Skill.Cost = Skill[(PlayerSkill->Grade * 4) + (EquipmentNum % 10)].Cost;
							PlayerSkill[PlayerSkill->Grade].Skill.Type = Skill[(PlayerSkill->Grade * 4) + (EquipmentNum % 10)].Type;
							printf_s("%s을(를) 배웠다!\n", PlayerSkill[PlayerSkill->Grade * 4].Skill.object.Name);

							PlayerSkill->Grade++;
							Sleep(1000);
						}

						else
						{
							system("cls");

							printf_s("EXP가 부족합니다!\n");
							Sleep(1000);
						}
					}

					else if (PlayerSkill->Grade >= 4)
					{
						system("cls");

						printf_s("더 이상 배울 수 있는 스킬이 없습니다!\n");
						Sleep(1000);
					}

					else
					{
						system("cls");

						printf_s("안녕히가세요!\n");
						Sleep(1000);
						Loop = 0;
					}
				}
			}
		}
	}
}

void Status(Object* Player, Object* Enemy, int EnemyIndex)
{
	int Battle = 0;
	system("cls");
	EnemyStatus(Enemy, EnemyIndex);

	printf_s("\n\n");

	PlayerStatus(Player, Battle);
}

void PlayerStatus(Object* Player, int State)
{
	
	if (State == 0)
	{
		printf_s("[Player] : %s\n", Player->Name);
		printf_s("HP : %d/%d\t[", Player->Info.HP, Player->Info.MaxHP);
		for (int i = 0; i < 10; i++)
		{
			if (Player->Info.HP >= (Player->Info.MaxHP / 10) * i + 1)
			{
				printf_s("■");
			}

			else
			{
				printf("□");
			}
		}
		printf("]\n");

		printf_s("MP : %d/%d\n", Player->Info.MP, Player->Info.MaxMP);
	}

	else if (State == 1)
	{
		printf_s("[Player] : %s\n", Player->Name);
		printf_s("HP : %d/%d\n", Player->Info.HP, Player->Info.MaxHP);
		printf_s("MP : %d/%d\n", Player->Info.MP, Player->Info.MaxMP);
		printf_s("공격력 : %.0f\n", Player->Info.Att);
		printf_s("방어력 : %.0f\n", Player->Info.Def);
		printf_s("민첩 : %d\n", Player->Info.Speed);
		printf_s("모험가 등급 : %d\n", Player->Info.Level);
		printf_s("경험치 : %d\n", Player->Info.EXP);
		printf_s("Gold : %d\n", Player->Info.Gold);
	}
}

void EnemyStatus(Object* Enemy, int EnemyIndex)
{
	//몬스터의 정보를 출력
	printf_s("\n%s\n", Enemy[EnemyIndex].Name);
	printf_s("HP : %d\n", Enemy[EnemyIndex].Info.HP);
	printf_s("MP : %d\n", Enemy[EnemyIndex].Info.MP);
}


short Battle(Object* Player, Object* Enemy, int EnemyIndex, Object* Quest, INVENTORY* Inventory, SKILL* Skill, PLAYERSKILL* PlayerSkill)
{
	// 전투 반복을 위한 함수
	short Battle = 1;
	short Defeat = 1;
	short SLoop = 1;

	int UseItem = 0;
	int SkillSelect = 0;
	int iAgree = 0;

	printf_s("%s이(가) 나타났다!!\n", Enemy[EnemyIndex].Name);
	//전투
	while (Battle)
	{
		//입력을 받기위한 임의 함수
		int iChoice = 0;
		printf("1.공격\t2.방어\t3.스킬\t4.아이템\t5.도망\n입력 : ");
		scanf_s("%d", &iChoice);

		//입력받은 값에 따른 전투진행
		switch (iChoice)
		{
			//공격을 선택했을 때
		case 1:
		{
			//** 속도가 빠른 개체가 먼저 공격하게한다
			if (Player->Info.Speed > Enemy[EnemyIndex].Info.Speed)
			{
				PlayerAttack(Player, Enemy, EnemyIndex);
				// 공격시 나타나는 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				//플레이어 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				Battle = EnemyScene(Enemy, EnemyIndex);
				Player->Info.EXP += Enemy[EnemyIndex].Info.EXP;
				Player->Info.Gold += Enemy[EnemyIndex].Info.Gold;

				if (Battle == 0)
				{
					if (iStage > 0)
					{
						for (int i = 0; i < 4; i++)
						{
							if (Quest[i].State == 1)
							{
								if (EnemyIndex == Quest[i].Num)
								{
									Enemy[EnemyIndex].State++;
								}
							}
						}
					}
					InitializeObjectEnemy(Enemy, EnemyIndex);
					break;
				}

				//플레이어 공격 후 몬스터의 공격
				EnemyAttack(Player, Enemy, EnemyIndex);

				//몬스터 공격 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				// 몬스터 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				//플레이어 죽음
				if (Player->Info.HP <= 0)
				{
					printf_s("%s은(는) 바스라졌다.", Player->Name);
					SceneState = Scene_Logo;
					Battle = 0;
					Sleep(1000);
					Defeat = GameOver();
					break;
				}
			}

			else if (Player->Info.Speed <= Enemy[EnemyIndex].Info.Speed)
			{
				//몬스터의 공격
				EnemyAttack(Player, Enemy, EnemyIndex);

				//몬스터 공격 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				// 몬스터 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				//플레이어 죽음
				if (Player->Info.HP <= 0)
				{
					printf_s("%s은(는) 바스라졌다.\n", Player->Name);
					SceneState = Scene_Logo;
					Battle = 0;
					Sleep(1000);
					Defeat = GameOver();
					break;
				}

				//몬스터 공격 후 플레이어 공격
				PlayerAttack(Player, Enemy, EnemyIndex);
				// 공격시 나타나는 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				//플레이어 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				Battle = EnemyScene(Enemy, EnemyIndex);
				Player->Info.EXP += Enemy[EnemyIndex].Info.EXP;
				Player->Info.Gold += Enemy[EnemyIndex].Info.Gold;

				if (Battle == 0)
				{
					if (iStage > 0)
					{
						for (int i = 0; i < 4; i++)
						{
							if (Quest[i].State == 1)
							{
								if (EnemyIndex == Quest[i].Num)
								{
									Enemy[EnemyIndex].State++;
								}
							}
						}
					}
					InitializeObjectEnemy(Enemy, EnemyIndex);
					break;
				}

			}
			break;
		}
		// **방어
		case 2:
		{
			printf_s("%s은(는) 방어에 집중한다.\n", Player->Name);
			Player->Info.Def *= 2;
			Sleep(500);

			EnemyAttack(Player, Enemy, EnemyIndex);
			Sleep(500);

			Player->Info.Def /= 2;

			Status(Player, Enemy, EnemyIndex);

			if (Player->Info.HP <= 0)
			{
				printf_s("%s은(는) 바스라졌다.\n", Player->Name);
				SceneState = Scene_Logo;
				Battle = 0;
				Sleep(1000);
				Defeat = GameOver();
				break;
			}
			break;
		}
		// ** 스킬
		case 3:
		{
			for (int i = 0; i < 4; i++)
			{
				if (PlayerSkill[i].Skill.Type < 0 && PlayerSkill[i].Skill.Type>3)
				{
					printf_s("배운 스킬이 없습니다!\n");
					break;
				}
			}

			while (SLoop)
			{
				for (int i = 0; i < 4; i++)
				{
					if (PlayerSkill[i].Skill.Type < 0 && PlayerSkill[i].Skill.Type>3)
					{
						printf_s("%d. %s\t", i + 1, PlayerSkill[i].Skill.object.Name);
					}
				}

				printf_s("\n사용할 스킬의 번호를 입력하시오(5.뒤로) :");
				scanf("%d", &SkillSelect);
				switch (PlayerSkill[SkillSelect].Skill.Type)
				{
					case 1:
					{
						printf_s("소모MP:%d\t방어력의 %.1f배의 추가피해를 입힌다.\n", PlayerSkill[SkillSelect - 1].Skill.Cost, PlayerSkill[SkillSelect - 1].Skill.Damege);
						printf_s("%s를 사용 하시겠습니까?(1.예 2.아니요) : ", PlayerSkill[SkillSelect - 1].Skill.object.Name);
						scanf("%d", &iAgree);
						if (iAgree == 1)
						{
							printf_s("%s의 %s!!\n", Player->Name, PlayerSkill[SkillSelect - 1].Skill.object.Name);
							Sleep(500);
							printf_s("%s는 %d만큼의 데미지를 입었다.\n", Enemy[EnemyIndex].Name, (int)(((Player->Info.Def * PlayerSkill[SkillSelect - 1].Skill.Damege) + Player->Info.Att) - Enemy[EnemyIndex].Info.Def));
							Enemy[EnemyIndex].Info.HP -= (int)(((Player->Info.Def * PlayerSkill[SkillSelect - 1].Skill.Damege) + Player->Info.Att) - Enemy[EnemyIndex].Info.Def);

							Sleep(500);

							Status(Player, Enemy, EnemyIndex);

							Battle = EnemyScene(Enemy, EnemyIndex);
							Player->Info.EXP += Enemy[EnemyIndex].Info.EXP;
							Player->Info.Gold += Enemy[EnemyIndex].Info.Gold;

							if (Battle == 0)
							{
								if (iStage > 0)
								{
									for (int i = 0; i < 4; i++)
									{
										if (Quest[i].State == 1)
										{
											if (EnemyIndex == Quest[i].Num)
											{
												Enemy[EnemyIndex].State++;
											}
										}
									}
								}
								InitializeObjectEnemy(Enemy, EnemyIndex);
								break;
							}

							EnemyAttack(Player, Enemy, EnemyIndex);

							Sleep(500);

							Status(Player, Enemy, EnemyIndex);

							if (Player->Info.HP <= 0)
							{
								printf_s("%s은(는) 바스라졌다.", Player->Name);
								SceneState = Scene_Logo;
								Battle = 0;
								Sleep(1000);
								Defeat = GameOver();
								break;
							}
						}
						break;
					}
					case 2:
					{
						printf_s("소모MP:%d\t적의 현재체력의 %.1f배의 피해를 입힌다.(기본데미지%d)\n", PlayerSkill[SkillSelect - 1].Skill.Cost, PlayerSkill[SkillSelect - 1].Skill.Damege, PlayerSkill[SkillSelect].Skill.Cost);
						printf_s("%s를 사용 하시겠습니까?(1.예 2.아니요) : ", PlayerSkill[SkillSelect - 1].Skill.object.Name);
						scanf("%d", &iAgree);
						if (iAgree == 1)
						{
							printf_s("%s의 %s!!\n", Player->Name, PlayerSkill[SkillSelect - 1].Skill.object.Name);
							Sleep(500);
							printf_s("%s는 %d만큼의 데미지를 입었다.\n", Enemy[EnemyIndex].Name, (int)(((Enemy[EnemyIndex].Info.HP * PlayerSkill[SkillSelect - 1].Skill.Damege) + PlayerSkill[SkillSelect].Skill.Cost) - Enemy[EnemyIndex].Info.Def));
							Enemy[EnemyIndex].Info.HP -= (int)(((Enemy[EnemyIndex].Info.HP * PlayerSkill[SkillSelect - 1].Skill.Damege) + PlayerSkill[SkillSelect - 1].Skill.Cost) - Enemy[EnemyIndex].Info.Def);

							Sleep(500);

							Status(Player, Enemy, EnemyIndex);

							Battle = EnemyScene(Enemy, EnemyIndex);
							Player->Info.EXP += Enemy[EnemyIndex].Info.EXP;
							Player->Info.Gold += Enemy[EnemyIndex].Info.Gold;

							if (Battle == 0)
							{
								if (iStage > 0)
								{
									for (int i = 0; i < 4; i++)
									{
										if (Quest[i].State == 1)
										{
											if (EnemyIndex == Quest[i].Num)
											{
												Enemy[EnemyIndex].State++;
											}
										}
									}
								}
								InitializeObjectEnemy(Enemy, EnemyIndex);
								break;
							}

							EnemyAttack(Player, Enemy, EnemyIndex);

							Sleep(500);

							Status(Player, Enemy, EnemyIndex);

							if (Player->Info.HP <= 0)
							{
								printf_s("%s은(는) 바스라졌다.", Player->Name);
								SceneState = Scene_Logo;
								Battle = 0;
								Sleep(1000);
								Defeat = GameOver();
								break;
							}
						}
						break;
					}

					case 3:
					{
						printf_s("소모MP:%d\t속도의 %.1f배의 추가피해를 입힌다.\n", PlayerSkill[SkillSelect - 1].Skill.Cost, PlayerSkill[SkillSelect - 1].Skill.Damege);
						printf_s("%s를 사용 하시겠습니까?(1.예 2.아니요) : ", PlayerSkill[SkillSelect - 1].Skill.object.Name);
						scanf("%d", &iAgree);
						if (iAgree == 1)
						{
							printf_s("%s의 %s!!\n", Player->Name, PlayerSkill[SkillSelect - 1].Skill.object.Name);
							Sleep(500);
							printf_s("%s는 %d만큼의 데미지를 입었다.\n", Enemy[EnemyIndex].Name, (int)(((Player->Info.Speed * PlayerSkill[SkillSelect - 1].Skill.Damege) + Player->Info.Att) - Enemy[EnemyIndex].Info.Def));
							Enemy[EnemyIndex].Info.HP -= (int)(((Player->Info.Speed * PlayerSkill[SkillSelect - 1].Skill.Damege) + Player->Info.Att) - Enemy[EnemyIndex].Info.Def);

							Sleep(500);

							Status(Player, Enemy, EnemyIndex);

							Battle = EnemyScene(Enemy, EnemyIndex);
							Player->Info.EXP += Enemy[EnemyIndex].Info.EXP;
							Player->Info.Gold += Enemy[EnemyIndex].Info.Gold;

							if (Battle == 0)
							{
								if (iStage > 0)
								{
									for (int i = 0; i < 4; i++)
									{
										if (Quest[i].State == 1)
										{
											if (EnemyIndex == Quest[i].Num)
											{
												Enemy[EnemyIndex].State++;
											}
										}
									}
								}
								InitializeObjectEnemy(Enemy, EnemyIndex);
								break;
							}

							EnemyAttack(Player, Enemy, EnemyIndex);

							Sleep(500);

							Status(Player, Enemy, EnemyIndex);

							if (Player->Info.HP <= 0)
							{
								printf_s("%s은(는) 바스라졌다.", Player->Name);
								SceneState = Scene_Logo;
								Battle = 0;
								Sleep(1000);
								Defeat = GameOver();
								break;
							}
						}
						break;
					}

					case 4:
					{
						printf_s("소모MP:%d\t공격력의 %.1f배의 피해를 입힌다.\n", PlayerSkill[SkillSelect - 1].Skill.Cost, PlayerSkill[SkillSelect - 1].Skill.Damege);
						printf_s("%s를 사용 하시겠습니까?(1.예 2.아니요) : ", PlayerSkill[SkillSelect - 1].Skill.object.Name);
						scanf("%d", &iAgree);
						if (iAgree == 1)
						{
							printf_s("%s의 %s!!\n", Player->Name, PlayerSkill[SkillSelect - 1].Skill.object.Name);
							Sleep(500);
							printf_s("%s는 %d만큼의 데미지를 입었다.\n", Enemy[EnemyIndex].Name, (int)((Player->Info.Att * PlayerSkill[SkillSelect - 1].Skill.Damege) - Enemy[EnemyIndex].Info.Def));
							Enemy[EnemyIndex].Info.HP -= (int)((Player->Info.Att * PlayerSkill[SkillSelect - 1].Skill.Damege) - Enemy[EnemyIndex].Info.Def);

							Sleep(500);

							//플레이어 공격 후 정보창 갱신
							Status(Player, Enemy, EnemyIndex);

							Battle = EnemyScene(Enemy, EnemyIndex);
							Player->Info.EXP += Enemy[EnemyIndex].Info.EXP;
							Player->Info.Gold += Enemy[EnemyIndex].Info.Gold;

							if (Battle == 0)
							{
								if (iStage > 0)
								{
									for (int i = 0; i < 4; i++)
									{
										if (Quest[i].State == 1)
										{
											if (EnemyIndex == Quest[i].Num)
											{
												Enemy[EnemyIndex].State++;
											}
										}
									}
								}
								InitializeObjectEnemy(Enemy, EnemyIndex);
								break;
							}

							EnemyAttack(Player, Enemy, EnemyIndex);

							Sleep(500);

							Status(Player, Enemy, EnemyIndex);

							if (Player->Info.HP <= 0)
							{
								printf_s("%s은(는) 바스라졌다.", Player->Name);
								SceneState = Scene_Logo;
								Battle = 0;
								Sleep(1000);
								Defeat = GameOver();
								break;
							}
						}
						break;
					}

					default :
						printf_s("잘못된 입력입니다!!\n 다시 입력 해주십시오\n");
						break;
				}
			}
		}
		//전투 중 아이템 사용
		case 4:
			printf_s("아이템명\t갯수\n");
			for (int i = 0; i < 1; i++)
			{
				if (Inventory[i].Equipment.Stock > 0)
					printf_s("%d. %s\t\t%d\n", i + 1, Inventory[i].item.Object.Name, Inventory[i].Equipment.Stock);
			}
			printf_s("사용하실 아이템의 번호를 입력하세요\n 입력 :");

			scanf("%d", &UseItem);

			if (Inventory[UseItem - 1].Equipment.Stock > 0)
			{
				Inventory[UseItem - 1].Equipment.Stock -= 1;
				printf_s("%s을(를) 사용했다!\n", Inventory[UseItem - 1].item.Object.Name);
				Sleep(500);

				if (Inventory[UseItem - 1].item.Effect.Info.HP > 0)
				{
					if (Player->Info.HP + Inventory[UseItem - 1].item.Effect.Info.HP < Player->Info.MaxHP)
					{
						printf_s("체력을 %d만큼 회복했다!\n", Inventory[UseItem - 1].item.Effect.Info.HP);
						Player->Info.HP += Inventory[UseItem - 1].item.Effect.Info.HP;
						Sleep(500);
					}

					else if (Player->Info.HP + Inventory[UseItem - 1].item.Effect.Info.HP > Player->Info.MaxHP)
					{
						printf_s("체력을 %d만큼 회복했다!\n", Player->Info.MaxHP - Player->Info.HP);
						Player->Info.HP = Player->Info.MaxHP;
						Sleep(500);
					}

					else if (Player->Info.HP == Player->Info.MaxHP)
					{
						printf_s("이미 체력이 가득 찬 상태입니다.\n");
					}
				}

				else if (Inventory[UseItem - 1].item.Effect.Info.MP > 0)
				{
					if (Player->Info.MP + Inventory[UseItem - 1].item.Effect.Info.MP < Player->Info.MaxMP)
					{
						printf_s("마력을 %d만큼 회복했다!\n", Inventory[UseItem - 1].item.Effect.Info.MP);
						Player->Info.MP += Inventory[UseItem - 1].item.Effect.Info.MP;
						Sleep(500);
					}

					else if (Player->Info.MP + Inventory[UseItem - 1].item.Effect.Info.MP > Player->Info.MaxMP)
					{
						printf_s("마력을 %d만큼 회복했다!\n", Player->Info.MaxMP - Player->Info.MP);
						Player->Info.MP = Player->Info.MaxMP;
						Sleep(500);
					}

					else if (Player->Info.MP == Player->Info.MaxMP)
					{
						printf_s("이미 마력이 가득 찬 상태입니다.\n");
					}
				}

				EnemyAttack(Player, Enemy, EnemyIndex);
				Sleep(500);

				Status(Player, Enemy, EnemyIndex);

				if (Player->Info.HP <= 0)
				{
					printf_s("%s은(는) 바스라졌다.\n", Player->Name);
					SceneState = Scene_Logo;
					Battle = 0;
					Sleep(1000);
					Defeat = GameOver();
					break;
				}
			}

			else
			{
				printf_s("소지하지않은 항목입니다!\n");
			}
			break;

			//도망을 선택했을 때
		case 5:

			//플레이어의 Speed 가 적보다 높을 때 도망칠수 있게 함
			if (Player->Info.Speed > Enemy[EnemyIndex].Info.Speed)
			{
				//도망도 확률로 할 수있게 함
				//주사위 굴리는 시스템 채용
				if (rand() % 6 > 2)
				{
					printf_s("%s(은)는 도망쳤다.\n", Player->Name);

					//전투 종료 루프해제
					Battle = 0;

					// 도망 시 적의 정보 초기화
					InitializeObjectEnemy(Enemy, EnemyIndex);

					//도망문구를 보이기위한 딜레이
					Sleep(500);
				}

				// 도망 실패 시
				else
				{
					printf_s("%s는 도망치치 못했다.\n", Player->Name);

					// 도망치지 못했을 때 문구를 보이기위한 딜레이
					Sleep(500);

					// 도망 실패 시 턴 소모로 몬스터의 공격을 받게하기위함
					EnemyAttack(Player, Enemy, EnemyIndex);
					Sleep(500);

					Status(Player, Enemy, EnemyIndex);

					if (Player->Info.HP <= 0)
					{
						printf_s("%s은(는) 바스라졌다.\n", Player->Name);
						SceneState = Scene_Logo;
						Battle = 0;
						Sleep(1000);
						Defeat = GameOver();
						break;
					}
				}
			}

			else
			{
				printf_s("%s가 빨라 도망갈수 없다!\n", Enemy[EnemyIndex].Name);
				Sleep(500);

				EnemyAttack(Player, Enemy, EnemyIndex);

				Sleep(500);

				Status(Player, Enemy, EnemyIndex);

				if (Player->Info.HP <= 0)
				{
					printf_s("%s은(는) 바스라졌다.\n", Player->Name);
					SceneState = Scene_Logo;
					Battle = 0;
					Sleep(1000);
					Defeat = GameOver();
					break;
				}
			}
			break;

			// 잘못된 입력시 턴 소모 하게 만들기 위함
		default:
			printf_s("잘못된 입력입니다! ");
			EnemyAttack(Player, Enemy, EnemyIndex);

			Sleep(500);

			Status(Player, Enemy, EnemyIndex);
			break;
		}

	}

	return Defeat;
}

void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("%s의 공격!!\n", Player->Name);
	Sleep(500);
	//플레이어의 공격력과 몬스터의 방어력을 비교하여 데미지를 계산하는 조건문
	if (Player->Info.Att > Enemy[EnemyIndex].Info.Def)
	{
		printf_s("%s는 %d만큼의 데미지를 받았다!\n", Enemy[EnemyIndex].Name, (int)(Player->Info.Att - Enemy[EnemyIndex].Info.Def));
		Enemy[EnemyIndex].Info.HP -= (int)(Player->Info.Att - Enemy[EnemyIndex].Info.Def);
	}
	// 방어력이 더 높을 경우 최소 1의 데미지를 주려고함
	else
	{
		printf_s("%s는 1만큼의 데미지를 받았다!\n", Enemy[EnemyIndex].Name);
		Enemy[EnemyIndex].Info.HP -= 1;
	}
}

void EnemyAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("%s의 공격!!\n", Enemy[EnemyIndex].Name);
	Sleep(500);
	if (Enemy[EnemyIndex].Info.Att > Player->Info.Def)
	{
		printf_s("%s는 %d만큼의 데미지를 입었다!\n", Player->Name, (int)(Enemy[EnemyIndex].Info.Att - Player->Info.Def));
		Player->Info.HP -= (int)(Enemy[EnemyIndex].Info.Att - Player->Info.Def);
	}
	else
		Player->Info.HP -= 1;
}

void Equip(Object* Player, EQUIPMENT* Equipment, int EquipmentNum)
{
	printf_s("%s 을(를) 얻었다!\n", Equipment[EquipmentNum].object.Name);

	Player->Info.MaxHP += Equipment[EquipmentNum].Info.MaxHP;
	Player->Info.MaxMP += Equipment[EquipmentNum].Info.MaxMP;
	Player->Info.Att += Equipment[EquipmentNum].Info.Att;
	Player->Info.Def += Equipment[EquipmentNum].Info.Def;
	Player->Info.Speed += Equipment[EquipmentNum].Info.Speed;
	Equipment[EquipmentNum].object.State = 1;

	Sleep(1000);
}

void Reinforce(Object* Player, EQUIPMENT* Equipment, int EquipmentID)
{
	int iAgree = 0;
	for (EquipmentID; EquipmentID < 30; EquipmentID++)
	{
		if (Equipment[EquipmentID].object.State == 1)
		{
			printf_s("%s를 강화 하겠나?\n", Equipment[EquipmentID].object.Name);
			Sleep(500);
			printf_s("보유Gold : %d\t%d Gold필요하네(1.예 2.아니요) : ", Player->Info.Gold, Equipment[EquipmentID].Info.Gold);
		}
	}
	scanf(" %d", &iAgree);

	if (iAgree == 1)
	{
		Equipment[EquipmentID].object.State = 0;
		Equip(Player, Equipment, EquipmentID + 10);
		Player->Info.Gold -= Equipment[EquipmentID].Info.Gold;
	}

}

short GameOver()
{
	system("cls");

	int Width = 120 / 2 - (strlen("===================================================================") / 2);
	int Height = 5;

	SetPosition(Width, Height, (char*)"===================================================================");
	SetPosition(Width, Height + 1, (char*)"==      =============================    ==========================");
	SetPosition(Width, Height + 2, (char*)"=   ==   ===========================  ==  =========================");
	SetPosition(Width, Height + 3, (char*)"=  ====  ==========================  ====  ========================");
	SetPosition(Width, Height + 4, (char*)"=  =========   ===  =  = ====   ===  ====  ==  =  ===   ===  =   ==");
	SetPosition(Width, Height + 5, (char*)"=  ========  =  ==        ==  =  ==  ====  ==  =  ==  =  ==    =  =");
	SetPosition(Width, Height + 6, (char*)"=  ===   =====  ==  =  =  ==     ==  ====  ===   ===     ==  ======");
	SetPosition(Width, Height + 7, (char*)"=  ====  ===    ==  =  =  ==  =====  ====  ===   ===  =====  ======");
	SetPosition(Width, Height + 8, (char*)"=   ==   ==  =  ==  =  =  ==  =  ===  ==  ===== ====  =  ==  ======");
	SetPosition(Width, Height + 9, (char*)"==      ====    ==  =  =  ===   =====    ====== =====   ===  ======");
	SetPosition(Width, Height + 10, (char*)"===================================================================");
	Sleep(1000);

	iStage = 0;
	return 0;
}



void SetPosition(int _x, int _y, char* _str, int _Color)
{
	//SetConsoleCursorPosition 함수의 매개 변수에 들어가야 하기때문에 선언
	COORD Pos = { _x,_y };	//short형이다.

	//콘솔 커서 위치 변경 함수
	//매개변수에 각각 핸들값, 변수 Pos값이 들어가야 한다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}

void SetColor(int _Color)
{
	//텍스트 색 변경
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}