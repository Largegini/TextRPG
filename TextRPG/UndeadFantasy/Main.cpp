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

int Check = 1;

// Scene전환을 위해 전역변수로 선언
int SceneState = 0;

//구조체안에는 사용자가 사용하고 싶은 것을 넣어서 용도별로 구축한다
// Status 구조체
typedef struct tagInfo
{

	int HP;
	int MP;

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


	INFO Info;

}Object;

typedef struct tagEquipment
{
	int Price;
	INFO Info;
	Object object;
}EQUIPMENT;

typedef struct tagItem
{
	int Price;
}ITEM;

typedef struct tagInventory
{
	int Space;
	int Stock;

}INVENTORY;

// 함수 전방 선언
char* SetName();

void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void LogoScene();
void MenuScene();
void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment);

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void GraveYardBackGround();
void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void Castle(Object* Player, Object* Enemy, EQUIPMENT* Equipment);
void NecromancerTower(Object* Player, Object* Enemy, EQUIPMENT* Equipment);

void Dungeon(Object* Player, Object* Enemy, int EnemyIndex, int EventCount);

void InitializeObjectPlayer(Object* Player);
void PlayerScene(Object* Playe);

void InitializeObjectEnemy(Object* Enemy, int EnemyIndex);
void EnemyScene(Object* Enemy);

void InitializeEquipment(EQUIPMENT* Equipment);

void Battle(Object* Player, Object* Enemy, int EnemyIndex);
void Status(Object* Player, Object* Enemy, int EnemyIndex);
void PlayerStatus(Object* Player);
void EnemyStatus(Object* Enemy, int EnemyIndex);
void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex);
void EnemyAttack(Object* Player, Object* Enemy, int EnamyIndex);

void SetPosition(int _x, int _y, char* _str, int _Color = 2);
void SetColor(int _Color);
void HideCursor();



int main(void)
{
	// ** 커서를 안보이게 함
	HideCursor();

	//콘솔창의 사이즈를 설정
	system("mode con:cols=120 lines=30");

	//콘솔창의 이름을 설정
	system("title 안정연 Undead Fantasy v0.1");

	Object* Player = (Object*)malloc(sizeof(Object));		//PLAYER 동적할당
	InitializeObjectPlayer(Player);							//초기화//ENEMY 동적할당

	int Max = 30;
	Object* Enemy;
	Enemy = (Object*)malloc(sizeof(Object) * 32);
	for (int i = 0; i < 30; i++)
	{
		InitializeObjectEnemy(Enemy, i);							//초기화
	}
	EQUIPMENT* Equipment;
	Equipment = (EQUIPMENT*)malloc(sizeof(EQUIPMENT) * 4);
	InitializeEquipment(Equipment);

	// GetTickCount 1/1000부터 점점 증가
//DWORD dwTime = GetTickCount(); // typedef unsigned long DWORD
//int Delay = 1000;

	while (true)
	{
		//Scene을 실행하기 위한 변수 초기화

		// ** 1초마다 실행되는 루프
		// 처음에는 0+1000 < GetTickCount()
	//	if (dwTime + Delay < GetTickCount())	
	//	{
			//GetTickCount가 1000보다 커졌을때 대입
	//		dwTime = GetTickCount(); //dwTime = 1001

			//콘솔창에 있는 모든내용을 지움
		system("cls");

		//** 게임 루프
		//  함수 SceneManger에 넣어 작동 한다
		SceneManager(Player, Enemy, Equipment);
		//	}
	}
	/*
	* /***** 포인터는 주소만 받는다 데이터는 대입 불가
	int iNumber = 10;
	int* pNumber = (int*)malloc(sizeof(int));

	// 힙 영역에 값을 넣기위해 pNumber 앞에 * 를 넣는다
	*pNumber = iNumber;
	//힙영역의 주소 = iNumber ;

	// 콜 바이 밸류
	void ABC(int _i,int _n)
	{
		_i =100;										//i_Number1에서 복사해온 값 10을 100으로 변경
		_n = 200;										//i_Number2에서 복사해온 값 20을 200으로 변경

		printf_s("ABC _i : %d",_i);
		printf_s("ABC _n : %d",_n);
	}

	// 콜 바이 래퍼런스
	void DEF (int* _i,int* _n)
	{
		_i = 100;										//i_Number1의 주소로 접근해 값 10을 100으로 변경
		_n = 100;										//i_Number2의 주소로 접근해 값 10을 200으로 변경
		printf_s("ABC *_i : %d", *_i);
		printf_s("ABC *_n : %d", *_n);
	}

	void main()
	{
		int iNumber1 = 10;
		int iNumber2 = 20;

		printf_f("iNumber1: %d\n", &iNumber1);			//iNumber1의 주소값 출력
		printf_f("iNumber2: %d\n\n", &iNumber2);		//iNumber2의 주소값 출력

		// 콜 바이 밸류
		ABC(iNumber1, iNumber2);						// iNumber1,iNumber2의 값을 함수 ABC의 매개변수 _i,_n에 복사
		printf_f("ABC iNumber1: %d\n",iNumber1);		// iNumber1에 저장 되어있는 값은 변하지 않았으므로 10출력
		printf_f("ABC iNumber2: %d\n\n",iNumber2);		// iNumber2에 저장 되어있는 값은 변하지 않았으므로 20출력

		// 콜 바이 래퍼런스
		DEF(&iNumber1, &iNumber2);						// iNumber1, iNumber2의 주소를 함수 DEF의 매개변수 *_i, *_n에 복사
		printf_f("DEF iNumber1: %d\n",iNumber1);		// iNumber1에 저장 되어있는 값이 변했으므로 100출력
		printf_f("DEF iNumber2: %d\n\n",iNumber2);		// iNumber2에 저장 되어있는 값이 변했으므로 200출력
	}





	while (Loop)
	{


	}
	*/


	return 0;
}

//객체 정보 초기화 함수



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

void SceneManager(Object* Player, Object* Enemy, EQUIPMENT* Equipment)						// Scene구성
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
		StageScene(Player, Enemy, Equipment);						// StageScene 실행
		break;

	case Scene_Exit:									//종료

		exit(NULL);
		break;
	}
}

void LogoScene()										//LogoScene
{
	int Width(120 / 2 - (strlen(" __    _____ _____ _____ ") / 2));
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

	printf_s("Undead Fantasy \n");
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

void StageScene(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{
	int iStage = 0;
	switch (iStage)
	{
	case 0:
		//** 묘지
		GraveYard(Player, Enemy, Equipment);
		break;

	case 1:
		// ** 모험가 마을
		AdventurerVillage(Player, Enemy, Equipment);
		break;

	case 2:
		// ** 왕성
		Castle(Player, Enemy, Equipment);
		break;

	case 3:
		// ** 사령술사의 탑
		NecromancerTower(Player, Enemy, Equipment);
		break;
	}
	// ** 모듈화 함수만들어 용도별로 사용할 수 있게
	// ** 이동
	//  * * * 입력(Input)
	//  * * * 플레이어 좌표데이터 수집
	//  * * * 게임 공간의 크기 데이터 수집
	//  * * * 각종 오브젝트들의 이동속도 데이터 수집

	// ** 전투
	PlayerScene(Player);
	EnemyScene(Enemy);

	// ** 상점
	// 
	// ** 강화
	// 


	/*
	srand(time(NULL));									//rand 함수를 사용하기위한 초기화

	// malloc 함수는 실행이 되면 주소값을 반환한다		** malloc함수의 반환 값을 변수에 대입하지 않으면 메모리 누수가 발생한다.
	//					힙영역에 공간을 만든다
	/*
	*
	* int iNumber=10;
	*
	// 힢 영역에 공간을 만들고 주소값을 포인터 pNumber에 대입
	//pNumber로 힢에 할당된 공간에 접근 가능
	* int*pNumber = (int*) malloc(sizeof(int));
	*
	// 포인터 pNumber에 iNumber의 주소값을 대입
	// ** 더 이상 pNumber로 힢영역에 만든 공간에 접근 불가 하게됨 (메모리 누수)
	* pNumber = &iNumber;
	*



	*/
}


// 플레이어
void InitializeObjectPlayer(Object* Player)
{
	//PLAYER의 객체 정보를 초기화한다

	Player->Info.HP = 100;
	Player->Info.MP = 10;
	Player->Info.Att = 10;
	Player->Info.Def = 10;
	Player->Info.Speed = 10;
	Player->Info.Level = 1;
	Player->Info.EXP = 0;
}


void PlayerScene(Object* Player)
{

}


// 적
void InitializeObjectEnemy(Object* Enemy, int EnemyIndex)
{
	switch (EnemyIndex)
	{
	case 0:
		Enemy[EnemyIndex].Name = (char*)"쥐";
		Enemy[EnemyIndex].Info.HP = 10;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 5;
		Enemy[EnemyIndex].Info.Speed = 5;
		Enemy[EnemyIndex].Info.EXP = 1;
		break;
	case 1:
		Enemy[EnemyIndex].Name = (char*)"시민";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 2:
		Enemy[EnemyIndex].Name = (char*)"모험가";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 3:
		Enemy[EnemyIndex].Name = (char*)"도적";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 4:
		Enemy[EnemyIndex].Name = (char*)"슬라임";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 5:
		Enemy[EnemyIndex].Name = (char*)"고블린";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 6:
		Enemy[EnemyIndex].Name = (char*)"고블린전사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 7:
		Enemy[EnemyIndex].Name = (char*)"고블린투척병";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 8:
		Enemy[EnemyIndex].Name = (char*)"고블린라이더";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 9:
		Enemy[EnemyIndex].Name = (char*)"오크";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 10:
		Enemy[EnemyIndex].Name = (char*)"오크전사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 11:
		Enemy[EnemyIndex].Name = (char*)"오크주술사";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
	case 12:
		Enemy[EnemyIndex].Name = (char*)"오우거";
		Enemy[EnemyIndex].Info.HP = 30;
		Enemy[EnemyIndex].Info.MP = 5;
		Enemy[EnemyIndex].Info.Att = 5;
		Enemy[EnemyIndex].Info.Def = 15;
		Enemy[EnemyIndex].Info.Speed = 5;
		break;
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

void EnemyScene(Object* Enemy)
{

}

void InitializeEquipment(EQUIPMENT* Equipment)
{
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			Equipment[i].object.Name = (char*)"오래된 검";
			Equipment[i].Info.Att = 5;
			break;
		case 1:
			Equipment[i].object.Name = (char*)"오래된 도끼";
			Equipment[i].Info.Att = 7;
			Equipment[i].Info.Speed = -2;
			break;
		case 2:
			Equipment[i].object.Name = (char*)"오래된 창";
			Equipment[i].Info.Att = 4;
			Equipment[i].Info.Speed = 1;
			break;
		case 3:
			Equipment[i].object.Name = (char*)"오래된 활";
			Equipment[i].Info.Att = 5;
			break;
		}
	}
}

void GraveYard(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{
	int iChoice = 0;
	int iStartWeapon = 0;

	srand(time(NULL));

	SetColor(15);

	GraveYardBackGround();

	Player->Name = SetName();
	Sleep(500);

	GraveYardBackGround();

	printf_s("내가 일어난 곳에 뭔가 있는거 같다\n");
	printf_s("1.가져간다 2.그냥 놔둔다 입력: ");
	scanf_s("%d", &iChoice);
	switch (iChoice)
	{
	case 1:
		//시작 장비를 무작위로 부여
		iStartWeapon = rand() % 4;
		printf_s("%s를 발견했다!\n", Equipment[iStartWeapon].object.Name);
		//장비의 공격력을 플레이어 공격력에 더한다
		Player->Info.Att += Equipment[iStartWeapon].Info.Att;
		Sleep(500);

		GraveYardBackGround();

		printf_s("우선 마을로 가서 정보를 모아야겠어\n");
		Sleep(500);

		GraveYardBackGround();
		//던전 0 진행
		Dungeon(Player, Enemy, 0, 5);

		break;

	default:
		printf_s("우선 마을로 가서 정보를 모아야겠어\n");
		break;
	}



}

//** 묘지 배경
void GraveYardBackGround()
{
	system("cls");
	printf_s("                                                                                            #@@@@                       \n");
	printf_s("                                                #@@@$                 $@@@@@$               @   $                       \n");
	printf_s("              $@@@@@@$                          @   @                $@     @@$             @   @                       \n");
	printf_s("            $@@      @@@$                  =$   @   @               $@        @$         @@@@   @@@$                    \n");
	printf_s("           $@           @$                 *@@$ @   @               @          @         @         @                    \n");
	printf_s("           @             @$                @  @@@   @              $@          @$        #         @                    \n");
	printf_s("          $@              @                @    @@$ @              @            @        @@@#   @@@@                    \n");
	printf_s("          @               @                @$   @ @@@@@$          $@            @           @   $                       \n");
	printf_s("          @ $@$=@@@@$ $=  @                 @$  @   @  @@$        @             @           @   @                       \n");
	printf_s("          @ @ @@$   @@@   @                  @@$@   @    @       $@             @           @   @                       \n");
	printf_s("          @$@   @@@$      @                    @@@$ @    @       @              @           @   @                       \n");
	printf_s("     $@@@@@@     $@@      @                     @ @@@    @       @              @          $@@@@@$                      \n");
	printf_s("     @        =@@@        ,$                    @   @@@@@@       @              @       $@@@     @@$              $@@$  \n");
	printf_s("    =@         @@@@$       @                    @   @            @              @      $@          @$         $@@@@  @@@\n");
	printf_s("     @@@$          @$=@=   @                    @   @            @              @     $@            @$      $@@         \n");
	printf_s("       $@          $@      @=@@@@$              @   @            @              @     @              @$   $@@           \n");
	printf_s("      *@    $@@@@@@@       @     @@@@$          @  $@            @              #    $@               @  $@             \n");
	printf_s("     $@@    @              @         @@$        @  ##         *=@@@@@@@@@@@@@@@@@@$ $@                @$=@              \n");
	printf_s("     @@    $@  =@@@@@@@=   @           @$*  $@@@@= =@@@@$     @                   @ @                  @                \n");
	printf_s("    $@@   $@        #      @            #@$ @           @    $@     $@@@@$        @ @                  @$               \n");
}

void AdventurerVillage(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}

void Castle(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}

void NecromancerTower(Object* Player, Object* Enemy, EQUIPMENT* Equipment)
{

}



void Status(Object* Player, Object* Enemy, int EnemyIndex)
{
	system("cls");
	EnemyStatus(Enemy, EnemyIndex);

	printf_s("\n\n");

	PlayerStatus(Player);
}

void PlayerStatus(Object* Player)
{
	//플레이어의 정보를 출력
	printf_s("[Player] : %s\n", Player->Name);
	printf_s("HP : %d\n", Player->Info.HP);
	printf_s("MP : %d\n", Player->Info.MP);
	//printf_s("공격력 : %.2f\n", Player->Info.Att);
	//printf_s("방어력 : %.2f\n", Player->Info.Def);
	//printf_s("레벨 : %d\n", Player->Info.Level);
	//printf_s("경험치 : %d\n", Player->Info.EXP);
}

void EnemyStatus(Object* Enemy, int EnemyIndex)
{
	//몬스터의 정보를 출력
	printf_s("\n%s\n", Enemy[EnemyIndex].Name);
	printf_s("HP : %d\n", Enemy[EnemyIndex].Info.HP);
	printf_s("MP : %d\n", Enemy[EnemyIndex].Info.MP);
	//printf_s("공격력 : %.2f\n", Enemy[EnemyIndex].Info.Att);
	//printf_s("방어력 : %.2f\n", Enemy[EnemyIndex].Info.Def);
	//printf_s("레벨 : %d\n", Enemy[EnemyIndex].Info.Level);
	//printf_s("경험치 : %d\n", Enemy[EnemyIndex].Info.EXP);
}


void Battle(Object* Player, Object* Enemy, int EnemyIndex)
{
	// 전투 반복을 위한 함수
	short Battle = 1;

	//전투
	while (Battle)
	{
		//입력을 받기위한 임의 함수
		int iChoice = 0;
		printf_s("몬스터와 조우했다!!\n1.공격\t2.방어\t3.스킬\t4.도망\n입력 : ");
		scanf_s("%d", &iChoice);

		//입력받은 값에 따른 전투진행
		switch (iChoice)
		{
			//공격을 선택했을 때
		case 1:
			//** 속도가 빠른 개체가 먼저 공격하게한다
			if (Player->Info.Speed > Enemy[EnemyIndex].Info.Speed)
			{
				PlayerAttack(Player, Enemy, EnemyIndex);
				// 공격시 나타나는 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				//플레이어 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				//플레이어 공격 후 몬스터의 공격
				EnemyAttack(Player, Enemy, EnemyIndex);

				//몬스터 공격 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				// 몬스터 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);
			}

			else if (Player->Info.Speed <= Enemy[EnemyIndex].Info.Speed)
			{
				//몬스터의 공격
				EnemyAttack(Player, Enemy, EnemyIndex);

				//몬스터 공격 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				// 몬스터 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				//몬스터 공격 후 플레이어 공격
				PlayerAttack(Player, Enemy, EnemyIndex);
				// 공격시 나타나는 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				//플레이어 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

			}
			break;
			// **방어
		case 2:

			break;
			// ** 스킬
		case 3:
			//** 속도가 빠른 개체가 먼저 공격하게한다
			if (Player->Info.Speed > Enemy[EnemyIndex].Info.Speed)
			{
				PlayerAttack(Player, Enemy, EnemyIndex);
				// 공격시 나타나는 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				//플레이어 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				//플레이어 공격 후 몬스터의 공격
				EnemyAttack(Player, Enemy, EnemyIndex);

				//몬스터 공격 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				// 몬스터 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);
			}

			else if (Player->Info.Speed <= Enemy[EnemyIndex].Info.Speed)
			{
				//몬스터의 공격
				EnemyAttack(Player, Enemy, EnemyIndex);

				//몬스터 공격 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				// 몬스터 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

				//몬스터 공격 후 플레이어 공격
				PlayerAttack(Player, Enemy, EnemyIndex);
				// 공격시 나타나는 문구를 보이기 위한 딜레이 함수
				Sleep(500);

				//플레이어 공격 후 정보창 갱신
				Status(Player, Enemy, EnemyIndex);

			}
			break;

			//도망을 선택했을 때
		case 4:

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
				}
			}

			else
			{
				printf_s("%s는 도망치치 못했다.\n", Player->Name);
				Sleep(500);

				EnemyAttack(Player, Enemy, EnemyIndex);

				Sleep(500);

				Status(Player, Enemy, EnemyIndex);
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
		if (Enemy[EnemyIndex].Info.HP < 0)
		{
			printf_s("%s을(를) 쓰러뜨렸다!\n", Enemy[EnemyIndex].Name);
			Sleep(300);

			printf_s("경험치 %d을(를) 얻었다!\n", Enemy[EnemyIndex].Info.EXP);
			Sleep(300);

			//printf_s("골드 %d을(를) 얻었다!");

			Battle = 0;
			InitializeObjectEnemy(Enemy, EnemyIndex);
		}
	}
}

void PlayerAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("%s의 공격!!\n", Player->Name);
	//플레이어의 공격력과 몬스터의 방어력을 비교하여 데미지를 계산하는 조건문
	if (Player->Info.Att > Enemy[EnemyIndex].Info.Def)
		Enemy[EnemyIndex].Info.HP -= (int)(Player->Info.Att - Enemy[EnemyIndex].Info.Def);
	// 방어력이 더 높을 경우 최소 1의 데미지를 주려고함
	else
		Enemy[EnemyIndex].Info.HP -= 1;
}

void EnemyAttack(Object* Player, Object* Enemy, int EnemyIndex)
{
	printf_s("몬스터의 공격!!\n");
	if (Enemy[EnemyIndex].Info.Att > Player->Info.Def)
		Enemy[EnemyIndex].Info.HP -= (int)(Enemy[EnemyIndex].Info.Att - Player->Info.Def);
	else
		Player->Info.HP -= 1;
}

void Dungeon(Object* Player, Object* Enemy, int EnemyIndex, int EventCount)
{
	short Walk = 1;
	int Loop = 0;
	while (Walk)

	{
		//** 던전 스테이지 진행
		if (Loop < EventCount)
		{
			DWORD dwTime = GetTickCount(); // typedef unsigned long DWORD

			int Delay = 1000;
			for (int i = 0; i < 3; i++)
			{
				printf(".");
				Sleep(333);
			}

			// ** 1초마다 실행되는 루프
			// 처음에는 0+1000 < GetTickCount()
			if (dwTime + Delay < GetTickCount())
			{
				++Loop;
				//GetTickCount가 1000보다 커졌을때 대입
				dwTime = GetTickCount(); //dwTime = 1001

				//적 조우
				//** 3번째 조우는 시민
				if (Loop == 3)
				{
					// 시민을 만났을 때 자신이 언데드라는 걸 알게됨?
					// 변장을 해야할 필요를 느낌
					Status(Player, Enemy, 1);
					Battle(Player, Enemy, 1);
				}

				else
				{
					Status(Player, Enemy, EnemyIndex);
					Battle(Player, Enemy, EnemyIndex);
				}

			}
		}

		else if (Loop > 5)
			Walk = 0;
	}
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