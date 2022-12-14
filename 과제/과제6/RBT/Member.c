#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RedBlackTree.h"
#include "Member.h"
#pragma warning(disable:4996)
void gotoxy(int x, int y);
void clock(int time);


/*******************************************************************************
								UI 관련함수
*******************************************************************************/

// 문자 가운데 정렬
void alignCenter(char txt[])
{
	int i;
	int size = (strlen(WIDTH) - strlen(txt)) / 2;
	for (i = 0; i < size; i++)
	{
		printf(" ");
	}
	printf("%s", txt);
}

// 색상 글자 출력
void textColor(char txt[], int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | color);
	printf("%s", txt);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 8);
}

// 텍스트상자 출력
void printBox(char txt[])
{
	int i,j,k;
	char width2[] = "┌───────────────────┐";
	int size1 = (strlen(WIDTH) - strlen(width2)) / 2;
	int size2 = (strlen(width2)-4 - strlen(txt)) / 2;

	alignCenter("┏━━━━━━━━━━━━━━━━━━━┓\n");
	alignCenter("┃                                      ┃\n");

	for (i = 0; i < size1; i++)
	{
		printf(" ");
	}
	printf("┃");
	for (j = 0; j < size2; j++)
	{
		printf(" ");
	}
	printf("%s", txt);
	for (k = 0; k < size2; k++)
	{
		printf(" ");
	}
	printf("┃\n");

	alignCenter("┃           (예:1, 아니오:0)           ┃\n");
	
	alignCenter("┃                                      ┃\n");
	alignCenter("┗━━━━━━━━━━━━━━━━━━━┛\n");
}



/*******************************************************************************
							회원관리메뉴 관련함수
*******************************************************************************/

// 텍스트 문서에서 데이터 로드
void roadData(FILE *fp, Tree *RBT, Tree *RBTForName)
{
	Member *data = NULL;
	Node *curNode = NULL, *curNodeForName = NULL;
	char buff[1024];
	int i = 0;
	char *id, *name, *addr, *phone;


	while (fgets(buff, sizeof(buff), fp))
	{
		buff[strlen(buff) - 1] = '\0';	// 버퍼의 마지막 개행을 공백문자로 바꿈

		// 데이터 파일의 첫 행(열머리) 제외
		if (i == 0){
			i++;
			continue;
		}

		// 버퍼의 문자열을 탭으로 나누어 데이터에 저장
		id = strtok(buff, "\t");
		name = strtok(NULL, "\t");
		addr = strtok(NULL, "\t");
		phone = strtok(NULL, "\t");

		// 데이터를 Member 구조체에 저장
		data = malloc(sizeof(Member));
		data->id = atoi(id);
		strcpy(data->name, name);
		strcpy(data->addr, addr);
		strcpy(data->phone, phone);

		// 구조체에 공간 및 데이터 할당
		curNode = createMember(RBT,data);
		curNodeForName = createMember(RBTForName,data);

		// 구조체를 트리에 삽입
		insertNode(RBT, curNode, 0);
		insertNode(RBTForName, curNodeForName, 1);
	}

	return;
}


// 메뉴1 : 회원보기
void menu1_member_view(Tree *tree)
{
	int input;
	system("cls");

	printf("\n");
	alignCenter("────────────────\n");
	alignCenter("1. 회원 목록\n");
	alignCenter("────────────────\n");
	printf("\n");
	printf("\t\t\t아이디\t\t 이름\t\t  휴대전화\t\t\t  주소\n");

	printTree(tree, tree->root);

	printf("\n");
	alignCenter("───────MENU───────\n");
	alignCenter("0. 종료\n");
	alignCenter("────────────────\n");

	alignCenter("버튼을 입력하세요 : ");
	scanf("%d", &input);
	switch (input)
	{
	case 0:
		return;
	}

	return;
}

// 메뉴2 : 회원추가
void menu2_member_add(Tree *tree, Tree *treeForName)
{
	int id = 0;
	char buff[256];
	char name[10], addr[256], phone[15];
	Node *newNode, *newNodeForName;
	Member *data;
	int nameIsValid,phoneIsValid, addrIsValid;
	
	system("cls");

	printf("\n");
	alignCenter("────────────────\n");
	alignCenter("2. 회원 추가\n");
	alignCenter("────────────────\n");
	alignCenter("0을 입력하면 취소됩니다.");

	// ID : 자동생성
	printf("\n\n");
	id = findLastId(tree)+1;
	alignCenter("ID : ");
	printf("%d", id);

	// name
	do
	{
		printf("\n\n");
		alignCenter("이름 : ");
		scanf_s("%s", &buff, 256);
		if (!strcmp(buff, "0")) return;
		nameIsValid = isValidName(buff);

	} while (!nameIsValid);
	strcpy(name, buff);

	// address
	do{
		printf("\n");
		alignCenter("주소 : ");
		fflush(stdin);
		gets_s(buff, 256);
		if (!strcmp(buff, "0")) return;
		addrIsValid = isValidAddr(buff);

	} while (!addrIsValid);
	strcpy(addr, buff);

	// phone number
	do{
		printf("\n");
		alignCenter("전화번호 : ");;
		scanf_s("%s", &phone, 15);
		if (!strcmp(phone,"0")) return;
		phoneIsValid = isValidPhone(phone);

	} while (!phoneIsValid);

	// 데이터를 Member 구조체에 저장
	data = malloc(sizeof(Member));
	data->id = id;
	strcpy(data->name, name);
	strcpy(data->addr, addr);
	strcpy(data->phone, phone);

	// 트리 노드 구조체에 공간 및 데이터 할당
	newNode = createMember(tree,data);
	newNodeForName = createMember(treeForName,data);

	// 구조체를 트리에 삽입
	insertNode(tree, newNode, 0);



	insertNode(treeForName, newNodeForName, 1);

	return;
}

// 메뉴3 : 회원수정
void menu3_member_modify(Tree *tree, Tree *treeForName)
{
	int input, key;
	char nameKey[256];
	Node *delMember = NULL;
	Member *delData = NULL;
	char buff[256],name[10],addr[256],phone[20];
	Node *newNodeForName;
	int nameIsValid, phoneIsValid, addrIsValid;


	do{
		system("cls");

		printf("\n");
		alignCenter("────────────────\n");
		alignCenter("3. 회원 수정\n");
		alignCenter("────────────────\n");

		alignCenter("어떤 키워드로 검색하시겠습니까?\n\n");

		alignCenter("1. 아이디검색\n");
		alignCenter("2. 이름검색\n");
		alignCenter("0. 종료\n\n");
		alignCenter("버튼을 입력하세요  : ");
		scanf("%d", &input);


		// 검색 키워드 입력
		do
		{
			alignCenter("────────────────\n");
			if (input == 0) return;

			if (input == 1)
			{
				printf("\n");
				alignCenter("아이디를 입력하세요 : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				printf("\n");
				alignCenter("이름을 입력하세요 : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0,nameKey);
			}
			if (delMember == NULL)
			{
				system("cls");
				printf("\n");
				alignCenter("────────────────\n");
				alignCenter("3. 회원 수정\n");
				alignCenter("────────────────\n");

				textColor("\t\t\t\t\t   * 오류 : 키워드를 찾을 수 없습니다.\n\n", 12);

				alignCenter("1. 아이디검색\n");
				alignCenter("2. 이름검색\n");
				alignCenter("0. 종료\n\n");
				alignCenter("버튼을 입력하세요  : ");
				scanf("%d", &input);
			}
		} while (delMember == NULL);

		// 기존 데이터 백업
		delData = delMember->data;
		strcpy(name, delData->name);
		strcpy(addr, delData->addr);
		strcpy(phone, delData->phone);

		// 회원 정보 보여줌
		system("cls");

		printf("\n");
		alignCenter("────────────────\n");
		alignCenter("3. 회원 수정\n");
		alignCenter("────────────────\n");
		printf("\n");
		alignCenter("찾은 회원 정보\n\n");
		printf("\t\t\t\t  %d\t%s\t%s\t%s\t\n\n", delData->id, name, addr, phone);
		
		// 수정할 정보 입력
		alignCenter("────────────────\n");
		alignCenter("어떤 정보를 수정하시겠습니까?\n");
		printf("\n");
		alignCenter("1. 이름\n");
		alignCenter("2. 주소\n");
		alignCenter("3. 전화번호\n");
		alignCenter("0. 취소\n");
		printf("\n");
		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);
		if (input == 0) return;

		alignCenter("────────────────\n");
		switch (input)
		{
		case 1:
			// name
			do{
				printf("\n\n");
				alignCenter("이름 : ");
				scanf_s("%s", &buff, 256);
				if (!strcmp(buff, "0")) return;
				nameIsValid = isValidName(buff);
			} while (!nameIsValid);
			strcpy(name, buff);
			break;

		case 2:
			// address
			do{
				printf("\n\n");
				alignCenter("주소 : ");
				fflush(stdin);
				gets_s(buff, 256);
				if (!strcmp(buff, "0")) return;
				addrIsValid = isValidAddr(buff);
			} while (!addrIsValid);
			strcpy(addr, buff);
			break;

		case 3:
			// phone number
			do{
				printf("\n\n");
				alignCenter("전화번호 : ");;
				scanf_s("%s", &buff, 15);
				if (!strcmp(buff, "0")) return;
				phoneIsValid = isValidPhone(buff);

			} while (!phoneIsValid);
			strcpy(phone, buff);
			break;
		case 0:
			return;
		}

		// 기존 데이터 삭제
		delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
		deleteNode(treeForName, delMember);

		// 구조체에 공간 및 데이터 할당
		newNodeForName = createMember(treeForName, delData);
		newNodeForName->data = delData;

		strcpy(delData->name, name);
		strcpy(delData->addr, addr);
		strcpy(delData->phone, phone);

		// 구조체를 트리에 삽입
		insertNode(treeForName, newNodeForName,1);
		treeFixUp(treeForName, newNodeForName);

		// 종료 UI
		printf("\n");
		alignCenter("성공적으로 수정되었습니다.\n");
		printf("\n");
		printBox("계속 수정하시겠습니까?");

		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);

	} while (input != 0);

	return;
}


// 메뉴4 : 회원삭제
void menu4_member_delete(Tree *tree, Tree *treeForName)
{
	int input, key;
	char nameKey[256];
	Node *delMember = NULL;
	Member *delData = NULL;


	do{
		system("cls");

		printf("\n");
		alignCenter("────────────────\n");
		alignCenter("4. 회원 삭제\n");
		alignCenter("────────────────\n");

		alignCenter("어떤 키워드로 검색하시겠습니까?\n\n");
		alignCenter("1. 아이디검색\n");
		alignCenter("2. 이름검색\n");
		alignCenter("0. 종료\n\n");
		alignCenter("버튼을 입력하세요  : ");
		scanf("%d", &input);

		printf("\n");
		alignCenter("────────────────\n");
		printf("\n");

		do
		{
			if (input == 0) return;

			if (input == 1)
			{
				alignCenter("검색할 아이디를 입력하세요 : ");
				scanf("%d", &key);
				delMember = searchValue(tree, tree->root, key,'\0');
			}
			else if (input == 2)
			{
				alignCenter("검색할 이름을 입력하세요 : ");
				scanf("%s", nameKey);
				delMember = searchValue(treeForName, treeForName->root, 0, nameKey);
			}
			if (delMember == NULL)
			{
				system("cls");

				printf("\n");
				alignCenter("────────────────\n");
				alignCenter("4. 회원 삭제\n");
				alignCenter("────────────────\n");

				textColor("\t\t\t\t\t   * 오류 : 키워드를 찾을 수 없습니다.\n\n", 12);
				alignCenter("1. 아이디검색\n");
				alignCenter("2. 이름검색\n");
				alignCenter("0. 종료\n");
				printf("\n");
				alignCenter("버튼을 입력하세요  : ");
				scanf("%d", &input);
				printf("\n");
				alignCenter("────────────────\n");
				printf("\n");

			}
		} while (delMember == NULL);

		delData = delMember->data;

		printf("\n\n");
		alignCenter("────────────────\n");
		alignCenter("찾은 회원 정보\n");
		alignCenter("────────────────\n");
		printf("\n\t\t\t\t%d\t%s\t%s\t%s\t\n\n", delData->id, delData->name, delData->addr, delData->phone);
		printBox("삭제하시겠습니까? ");
		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);

		if (input == 1)
		{	

			// ID 트리에서 삭제
			delMember = searchValue(tree, tree->root, delData->id,'\0');
			deleteNode(tree, delMember);

			// 이름 트리에서 삭제
			delMember = searchValue(treeForName, treeForName->root, 0, delData->name);
			deleteNode(treeForName, delMember);

			free(delData);
		}
		else
		{
			alignCenter("사용자가 취소하였습니다.\n");
		}

		printf("\n");
		alignCenter("MENU\n");
		alignCenter("1. 재실행\n");
		alignCenter("0. 종료\n");

		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);

	} while (input != 0);

	return;
}


// 메뉴5 : 회원검색
void menu5_member_search(Tree *tree, Tree *treeForName)
{
	int input, key;
	char nameKey[256];
	Node *searchMember = NULL;
	Member *searchData = NULL;


	do{
		system("cls");

		printf("\n");
		alignCenter("────────────────\n");
		alignCenter("5. 회원 검색\n");
		alignCenter("────────────────\n");

		alignCenter("어떤 키워드로 검색하시겠습니까?\n\n");
		alignCenter("1. 아이디검색\n");
		alignCenter("2. 이름검색\n");
		alignCenter("0. 종료\n\n");
		alignCenter("버튼을 입력하세요  : ");
		scanf("%d", &input);

		printf("\n");
		alignCenter("────────────────\n");
		printf("\n");

		do
		{
			if (input == 0) return;

			if (input == 1)
			{
				alignCenter("검색할 아이디를 입력하세요 : ");
				scanf("%d", &key);
				searchMember = searchValue(tree, tree->root, key, '\0');
			}
			else if (input == 2)
			{
				alignCenter("검색할 이름을 입력하세요 : ");
				scanf("%s", nameKey);
				searchMember = searchValue(treeForName, treeForName->root, 0, nameKey);
			}
			if (searchMember == NULL)
			{
				system("cls");

				printf("\n");
				alignCenter("────────────────\n");
				alignCenter("5. 회원 검색\n");
				alignCenter("────────────────\n");
				textColor("\t\t\t\t\t   * 오류 : 키워드를 찾을 수 없습니다.\n\n", 12);
				alignCenter("1. 아이디검색\n");
				alignCenter("2. 이름검색\n");
				alignCenter("0. 종료\n");
				printf("\n");
				alignCenter("버튼을 입력하세요  : ");
				scanf("%d", &input);
				printf("\n");
				alignCenter("────────────────\n");
				printf("\n");
			}
		} while (searchMember == NULL);

		searchData = searchMember->data;

		printf("\n\n");
		alignCenter("────────────────\n");
		alignCenter("찾은 회원 정보\n");
		alignCenter("────────────────\n");
		printf("\n\t\t\t\t%d\t%s\t%s\t%s\t\n\n", searchData->id, searchData->name, searchData->addr, searchData->phone);

		printf("\n");
		alignCenter("MENU\n");
		alignCenter("1. 재실행\n");
		alignCenter("0. 종료\n");

		alignCenter("버튼을 입력하세요 : ");
		scanf("%d", &input);

	} while (input != 0);

	return;
}


void menu6_data_save(Tree *tree)
{
	FILE *fp;
	int input;
	fp = fopen("data.txt", "w");

	system("cls");

	printf("\n");
	alignCenter("────────────────\n");
	alignCenter("6. 파일 저장\n");
	alignCenter("────────────────\n");

	printBox("저장하시겠습니까? ");
	alignCenter("버튼을 입력하세요 : ");
	scanf("%d", &input);
	if (input == 0) return;

	fprintf(fp, "회원 아이디\t회원이름\t회원주소\t핸드폰 번호\n");
	fprintTree(fp, tree, tree->root);

	fclose(fp);

	printf("\n\n");

	alignCenter("성공적으로 저장되었습니다\n\n");

	printf(WIDTH);
	printf("\n");

	alignCenter("종료하려면 아무 키나 입력하세요.");
	scanf("%d", &input);

	return;
}

void menu0_close()
{
	system("cls");

	printf("                          :++:                               .. \n"); Sleep(33);
	printf("              :.         =++*                    ...       *+*=\n"); Sleep(33);
	printf("             *++=        :+++             =++******+*:     :+++\n"); Sleep(33);
	printf("             :+++.        :+++.           *+++====:=++*.    :+++=\n"); Sleep(33);
	printf("            .+++:          +++:           .:.      .+++:     =++*.\n"); Sleep(33);
	printf("           .*+++:          ++++             .=+++**++++       ++++::===+++=\n"); Sleep(33);
	printf("          :*+++++=         :+++==+++***    ++++*++==:.        =++++*****++=\n"); Sleep(33);
	printf("         =+++:.++++:        ++++**+++=:   .*++:       ..      ++++.\n"); Sleep(33);
	printf("        +++*:   =*++*=.     ++++           *+++====+*****     .*++:\n"); Sleep(33);
	printf("      .*+++       :+++++.   =+++            =*******+==:       =++*\n"); Sleep(33);
	printf("      *+*+           =++.   .+++:                               *++=\n"); Sleep(33);
	printf("       ..                    +++=                               =*++\n"); Sleep(33);
	printf("                             =+++                      :..        .\n"); Sleep(33);
	printf("                             .+++:                 :+*******+=.\n"); Sleep(33);
	printf("                              *++=                ++++=:::=+++*:          .:         .::           :+=.\n"); Sleep(33);
	printf("                              :++.               :+++.      ++++         +**+        ***:          =**:\n"); Sleep(33);
	printf("                                                  ++++=:...=++*.          ..          .\n"); Sleep(33);
	printf("                                                   :+*+****+++.\n"); Sleep(33);
	printf("                                                      ..::::.                                     .\n"); Sleep(33);
	printf("              :=:                                                                               =*++.\n"); Sleep(33);
	printf("             .*++*.                                               .                              ++++\n"); Sleep(33);
	printf("               =++*             .+*+                            .*+*:                            :+++\n"); Sleep(33);
	printf("           :... +++:     .:.     +++=                            =++*         .:======++=+++=    .+++:\n"); Sleep(33);
	printf("          ******+++++*****+*:    ++++            :**+.            +++=       +**++++******++=     +++=\n"); Sleep(33);
	printf("           :::::::=++=====:.     ++++             ++++            :+++.       ..++++              +++=\n"); Sleep(33);
	printf("                :+++++=:         ++++.::====:     .+++:            +++=         ++++              +++=\n"); Sleep(33);
	printf("              :*+++=:+++*=       ++++********.     +++=            =+++         ++++              +++=::::=====.\n"); Sleep(33);
	printf("              *++=    +++=       ++++...           ++++            =+++         ++++.....::=++:   ++++*********+\n"); Sleep(33);
	printf("              *++=.  =++*.       ++++              ++++======::.   .+++.        :*++**********=   +++=....\n"); Sleep(33);
	printf("              =*++***++*:   .:   ++++              .+*+*********:   +++=          :::::::..       +++=\n"); Sleep(33);
	printf("                .:::==.    =*+*  ++++                        ...    ++++                          +++=\n"); Sleep(33);
	printf("                   :+++    =+++  .==.                               :+++                          +++=\n"); Sleep(33);
	printf("                   .++++***++++                                     .*+*.                         +++=\n"); Sleep(33);
	printf("                    =+++=::=+++                                      .:.                          +++=         =**=\n"); Sleep(33);
	printf("                    .+++:. =++*                                                                   +++=         .==:\n"); Sleep(33);
	printf("                     =*++**++++                                                                   *+*=\n"); Sleep(33);
	printf("                       .::::::                                                                     ..\n"); Sleep(33);

	printf("\n\n"); Sleep(33);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 5);
	printf("+++++++++++++++++++++++++++++++++++++++ii++++++oo++iio++i+oooo++oo+O+88OoO8oooOO8888EEEE8Ooooo++ooooooooooooooooooooooo\n"); Sleep(55);
	printf("++++++++++++++++++++++++++++++++++++o+i++++++oo++o+ioii+ooo++i+++++++oo++iioO8E8E888OOO88OOOOoooooooooooooooooooooooooo\n"); Sleep(55);
	printf("+++++++++++++++++++++++++++++++++++o+i+++o+oOoi+++i+ioo+++iii+i+++i+++iiii+oO888OOO8Ooo+88O88Oo++o+oooooooooooooooooooo\n"); Sleep(55);
	printf("++++++++++++++++++++++++++++++++++o++++oo++o+i++iii+8i+ii=iii++i++i+iiiii+oO++++OooOOoo++oO8O8o+ii++ooo+ooooooooooooooo\n"); Sleep(55);
	printf("+++++++++++++++++++++++++++++++++++++oO+oo++++iiiioOiiii=+++iii++ii=ii+OOO+++iioooo++o+o+i+oOOOo+i+++++o+oooooooooooooo\n"); Sleep(55);
	printf("++++++++++++++++++++++++++++++o+++++Ooooo++i+i+iio+=i=i++iiiiiii==++O8O+o+iii++i++o+++O+++++oOoO+i+oooo+o+ooooooooooooo\n"); Sleep(55);
	printf("+++++++++++++++++++++++++++++o+oo+oooooooi+iiii+O=ii+iiiii=iiii+OOoo+++ii=++iii+iii+i++io+i+ooo++ii+ooo+++ooooooooooooo\n"); Sleep(55);
	printf("++++++++++++++++++++++++++++ooOOoOoooOooiii+ii+++++iiiiiii+oooOo+i+iiii=i+ii+=iii+ii=oii+=++o+oii+ii+o+o+o+oooooooooooo\n"); Sleep(55);
	printf("++++++++++++++++++++++++++++oOO88OooOOO++oo=+oooo++ooooooooo+++==iiiiiiii=i+iiii+=ii++ii+ooOi+++ii+iii+++o+++oooooooooo\n"); Sleep(55);
	printf("+++++++++++++++++++++++++++oo8EE8OO8OOo8OO+O8oOOooo+++iii+ii+=I;=i+iii=i++ii=iii=ii+i++o+Oo+i+++oi++iii++++oooooooooooo\n"); Sleep(55);
	printf("++++++++++++++++++++++++++ooOEEE8888O8E88o88Oo+i++iiiiiiii+iI;;=ii=iii+o+iii+i==i=ii+++++o+i+i+++ii++ii+++++++o+++++ooo\n"); Sleep(55);
	printf("++++++++++++++++++++++++++OOEE#8EEOEEEE88O+iiiiiii+++i++++i;Iiiiii+oo++iiii+i==i=+o++++i+oii+iO++ii+i+ii++i+++++++++++o\n"); Sleep(55);
	printf("++++++++++++++++++++++++++O8E#88E8EEEO88o+iiii+++++++++iii==ii+ooO++i+++++ii===i+++io+ii++i++8+o+i++i+++++oi+++++++++o+\n"); Sleep(55);
	printf("++++++++++++++++++++++++++OE##OE8EEE8E8Oo++oo++++oo++iiiiiiooOOoooo++++++iII=ii++o++++io++++Oo8+ii++oi+++o++i++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++oEEE8E8EEEEE88OO8Ooooooo+iii++ooOOoooo+o+++oo+III=i+++o+i+++i+++ii+o8Oiiio+++++oo+++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++O8E#8EEEEEE8888888OOOo+ii+oOOO8OOoOooOooOoo+iii+i+++++oo+o++io+i=io88ii+iO+i++ooo+++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++E8#EEEEEE888EE88OOOooO8EEEE888OO8O88OO+i===+oooooOOo+++oo+++ooiI=+88+++iOo+o+oOoo+++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++8EEEE#8E8E8E88EO#E#EEE#EEEE8888Ooi;:I=i+oooooooooo++++o++ooOoi;I=+oi+i+ooiooOOOoo+++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++8EEE#8EE88EOE##8#E8OOOooOOO88E88o+iI~.```...~~::;=++++++oooi;:;I=i+i+o++++oOOooo++++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++EEEEEEE8OEOE###E#EO+ii===IIII=IiOEE8oiI~....~:I=ii++++oo+iiI;;=i+++oooo+o+OOooooo+++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++EEEEE8EO88EE#E#E8Oo+oOO+OMM##o+I;I+E#EE8+==+++oooOOOO88ooo+o+o+ii+OEOo+o8ooOo+oo++++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++++8EEEE888EEEEEE#O+i=I;~.``.:;I~=o=;i+EE####M##M#8o+ii+i=iooOEE#E8OooOoO8O8+oEiOoo++++++++++++++\n"); Sleep(55);
	printf("++++++++++++++++++++++++o8EE8888EEEEE8OMo::~~:;;:::~~~~~~;II+#M8E88E##O=IiioEoioi;;;III+8###EE#EOO+8+ooOo++++++++++++++\n"); Sleep(55);
	printf("++++++++++++++++++++++++o8EE888EEE888O=o#.......~::::::::~.~MMo~`:O##8I;;I:=8EE#=OO+=I=io8M+M#E8Eoo+OoOo+++++++++++++++\n"); Sleep(55);
	printf("++++++++++++++++++++++++oEEE8E8E888Oo;~.o8~`  ``........``;MM:    :EM;:;::~.`   ``.I+oooOO#M###88oo8OOOo+++++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++++++++iO#8888888#Oi;~~~.~==+=:.       `~OM+      `OM;`.~::::::::~~:;I==I8EO##O8oOEEOoo++++++++++++++++\n"); Sleep(55);
	printf("++++++++++++++++++++++++8#8EO88E##+;::~~~~~::I=i=+oo+i+8i:  `    ` :O#..~.``....````.~~.oM+oEOO88EE8Oo+++++++++++++++++\n"); Sleep(55);
	printf("+++++++++++++++++oiII==iE#E888EE##=::~~~........~~~::I;~...``    ```IEE.````````    ```oE::88O88EEEo+++++++++++++++++++\n"); Sleep(55);
	printf("+++++ooooooi=;I=I;~`.I++M#E8888E#OI:::~~..........~:;~   ```     ```.;=OO+=:~.```````:8o..;EEEE8E#O++++++++++++++++++++\n"); Sleep(55);
	printf("+iiI:::.`` .::;=i+o+~:;o##EEOE8EEo;::~~~~~......~::~~:.`````      `` `:::;Iioooi++ooiI.`..;E#EOE#8i++++++++++++++++++++\n"); Sleep(55);
	printf(": `..``````.~==I::+o=.~=8ME8E8888o:::~~~~~~~~~~::~.~~:I=I:..```````   ~~~..`    ``````....o#EOEE8i+++++++++++++++++++++\n"); Sleep(55);
	printf("++;.`.``      `.```:I.``+E888E888o:~~~~~~~~~~::~~~....~:I==I~...~;;:~~..~:~...``````.....IE8OEEO+++++++++++++++++++++++\n"); Sleep(55);
	printf(";I;~           `:Ii+oM==oE88EE8OO#:~~~~~~~~~~:~~~~..```..~;i++i=;;::~....:;~~.........~~~88888Oi+++++++++++++++++++++++\n"); Sleep(55);
	printf("  .`.     .~~;:;ooo++O#OEE8E8oo++E+:~~~~~~~...:;iI;::~~~~........```....~~:;:~~~~~~~~~~~+8888Oi++++++++++++++++++++++++\n"); Sleep(55);
	printf("   ;oO+.I;I=I;:I;Oo+=i88OEE8EE+O8##I:~~~~~~...~;#8;;~=~=I:II;::::~~.``.~~::;:~~~~~~~~~~iE88o+++++++++++++++++++++++++++\n"); Sleep(55);
	printf("=:;~+OO=~I:;==~``.~~;;OEoM###Ei==+oo::~~~~~.....`I=:      `. `;.;:;=i8O=:::~.~~~~~~~~~iEo++iiio++++++++++++++++++++++++\n"); Sleep(55);
	printf("Oi:I~ioo.:~`      :IIi+E8E8O8O=II++o+::~~~~~~.....:Ii+O:`         `~=8+:~~...~~~~..~~IEoo=;:~` ~=+o++++++++++++++++++++\n"); Sleep(55);
	printf("==;   +i.    .~~I+=Ooo+8O+o8oOII;i==8;;:::~~~.....~::..;ioOi=i;;~;;:.``.~...~~~..~~~io+;     `~.` `:io+++++++++++++++++\n"); Sleep(55);
	printf("I;;. .~i++IOoOIi+O=+oooEo=++o~```;I;Oi;;:::~~....~.~~::~.``.``.~:~.`....~.~~~~....:88O8+~        `.:~~:=+++++++++++++++\n"); Sleep(55);
	printf(":iOO=;;:OO++O=iOo=;:I~~+i::=i  `.III=oI;:::~......~~~~~::~~:::~.........~~~~~~~.~+#O8EO==+=`      .~:;I:~:=o+++++++++++\n"); Sleep(55);
	printf("iioOOI=ii88:I.:`    ~:~iII.O.  ``;I;I+=I;::~........~~~~~~~~~.........~~~~~~~~:o#Eo++I:=i;:II;~  `.   `IiiI:;io++++++++\n"); Sleep(55);
	printf("++oOo+.` ;=`        ~;;=II o=   .===i++==;::....````.`................~~~~~~:oM888EOI  `~;I;;I~=+=;:` ``.::~`  I+++++++\n"); Sleep(55);
	printf(";~`:;:~  `+i    .~`~;+iii+.=oI  `;I=+oOii=I;~....`````````````````...~~~~~:IIMOEE88OI:.    `.~+o++io8OI.     `.~o++++++\n"); Sleep(55);
	printf("..`.::I``.O+~~;::.;I~i++=i;:IEO=+8888OO++ii=;~..~~.``````````  ``...~~~~I;;:I+i++88;I:I=~    ~;;;i+OOOO:~.  `~;I;:ioi++\n"); Sleep(55);
	printf("`     +I= ~8Ooo+ii:..~:;E88oo8MOI=iiii8o++i=I;:~~~~~.``````````....~~IoEO;;`Ii+Ii. ~;iI:;;;~i;`~;;Ii+O:I~I8+;:.I8+I::;+\n"); Sleep(55);
	printf("Ioo;:I+=~` =i=Iii~~.~~.~E8O=i=O8I ;IIi8O+++iII;::~~~:~~..........~;=OEOoi:~ ooi=~    ~;;I:;+oo+I;IIi: `.i8oOO=;~~;;;:`i\n"); Sleep(55);
	printf("==IIi888ii~==I=: ~::~.:=+ii`.`ioEoooOoOOo++i=I;;;:::::::~~~~~~:IiiiOE+++i+.i8oO=.       `:oo++io88O=   ;I;oi~`      I. \n"); Sleep(55);
	printf(":i;+OE8=i=+88;:~`:~ ~I;=Ooo++oOE8Eo++++8oo++iI;;;;;::::;;I=i++iii+O#i+i+=;o8io+;:~`      :.~;;o888=;=:+I.:       `~oo+i\n"); Sleep(55);
	printf(" ``~O+Eii=8E8O+I=+= ` `+8E8OooiEOo;=iiioOo+++iI;:::::;;;I=iiiii+o8#+++IoiOMi;;Oo+ii;:```:;..:;::i;+;;8OE8:`    .~`` Ii;\n"); Sleep(55);
	printf(";~~I;+=.`IO+8oo88O8.  oi+O+O;=~OoOI=+iiioOo++iiI;;;;;II=iiiii++OE8#i+:`;oME=i~+oo+;i=~   .`.:`.:   :oO8o=:.   .``..=; +\n"); Sleep(55);
	printf("IIO#O+;.`o+o;:i;=o8Ooo+=IooOI=;OoO;~;:;IiOo+ii=========ii++i+o88OEOi=`I+MME=;=~oiII;:;    ` .::IE88o;;I+=;.~~~`  .~I:;o\n"); Sleep(55);
	printf("iEE8Ei+8EEoi;:I `;+8E88;;ooOi:=+O;I+Ooo8IOo+i=======ii++++oEEo8E8o::IOE#88O`  :=;;;II.;;=oo:==IO8O8:=;Oo++=`       +o+\n"); Sleep(55);
	printf("+=88EOOOoo::i+8E8ii++   `.+=+oo8i:;oIO++iiiii+++++o8E#ooO888~IO=EEoooOo  =8ooOOo;;::i=;=;=OO++`  I++.   :;~:`io++\n"); Sleep(55);
	printf(" ~oii~=IE8OOOOOo===O8iooi#iI;~ Io+ii+iOi`;++oo+++++oooO8EEooOOO8i`IM+i+==Io8OIIE8o++o8iII=i::~.`:i=I  =O;` `;=:.`~OI+++\n"); Sleep(55);
	printf("~+ii`~`I=o;:;=oo++iio.~:8#==+OEo`..:~i+oi`:=8OOOOOOO888Eo+oOOoo: iM8o ;IO+8E88=8Oo=i;==` ``.    :+io+oI`~I+o;.~~:=I++++\n"); Sleep(55);
	printf("OoO=+:;+i+::::. `.:I+:~oi+OE8oo+i:` .~;+O= O8OOOOOOO88O+oOOoo+I.i8#8;+ioooOE8+.+ooI=:~~ .::;.i=i+88O8oio+:.  `:~.oooi++\n"); Sleep(55);
	printf("=Oo=iio+oi=I;:   `:;=8E+oi;Iio=+i+i=I;+o+o+8OOOOOOO8oi+oo++o:`  ;88EE+IOooiOo=iOOOioo+o=+i=I;iIIo=+EOO+I~  ~I==i88oiiii\n"); Sleep(55);
	printf("IO=i=Oooo+++o;~.`::+i88EOo+i~ .==Ii+o+iiEOOOooooOOo++o++i++o;   oEEiI`.I.~.:+oo888++ooo=i==I;=:;i+I8O+iiIiiI=+IiI:+iii+\n"); Sleep(55);
	printf("IO.~iOoO++++=~::;I+++88+++o+ `` ~IoOi+O#oOOOOOOOoii++iiiiiio=~;o88=``  `~~:iOo8EEEOo+i+;:.`   ;E++OOooi=:~..` `i:i++iii\n"); Sleep(55);
	printf("iiI~O+o+++++;I;;;i+++=I+ooO=I:`  .~~o8O+++iiii==+o+iiiiii++i;=IIoooOo;I=+=o:`.;ooi~~~:I`     +8Oi++=:        ;+Ii+iiiii\n"); Sleep(55);
	printf("8++=#EOI;II..:;II=i+oO~.I+i=I;II;. +.I+i=====oOO+iiiiiiiiio=:i:+MEoo+iii+i+:. .i==::;::    `O88i;~.~       `~O++i+iiii+\n"); Sleep(55);
	printf("EMEoMM#8;;: `` `.;Ii88i~: ~===I=+IE;;+iiiiiiiiiiiiiiiiii=~~:;8I##O+=iI:~`+O+:~~Ooo++ii;~~~;88o==iii.````.~~~+oi.oiiiiii\n"); Sleep(55);
	printf("oo#o8#O#88i;;I.  .;o8O+I  ` ~:   8+i===I=====iiiii====i+=;iIEo=#o+=..   iOOo=;:oooo+iiI~~i8ooi==I=;.~~~~~~~=+;;:+iiiiii\n"); Sleep(55);
	printf("OI8i~o++oOoo+oO=:=ioM#++I`   .~:O+I==IIIII==ii=======i+i;Iii+ =ii+=..  ;oOoo=I:o+oo+i=IIO8ooi=iii=.~~..... i``=+iiiiiii\n"); Sleep(55);
	printf(". o8=i##Eo+ooooOOooOM#8i=I:.I.`=.:============IIII==iO=;;~`I; o++o+I;~I;IOOoI=:o+oiiI;oioi=I~~~~~         .i =iiiiiiiii\n"); Sleep(55);
	printf("` o+E8EEM88=:.:io+oEME8oII==i~i`==IIIIIIIIIIIIII==i+OI    `i==o++o+;:~..Io+=`..+ii:~:Oo8o+=:::~.    `~:I:i8OO;i+iiiiiii\n"); Sleep(55);

	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 3);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@***@@@@@**@**@@@@@@@@@************@@@*@@@@@**********@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@**@@@*****@@@@@@@@@@@@**********@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****@@**@@@@@@@@@@@@@@@@@@*********@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@****@@@@@@**.*********@@@@@@**@**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@*@@@*@@****@@*****@@@@***.************@@@@@****@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@***@@*@*****************......***********@@@****@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@*@************@****...*******@@@@@@@***@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@*****************.***@@*@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@***********************@@@**********@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@******************@*******@*****......****@@@@@@**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****@@@**...*@******......@.*.........*****@@@@@@@@***@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@*****.@@**...........@.*........********@@@@@@******@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@@@@**..........*@.*.........*******************@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@**@@@*..**.........*@*..........*********************@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@**@*...@@.....***....*@*.  ........****************.....@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@*..**.*@.......*****....................********.*....*@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@@@***...*..................................*******..****@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@@*.....@.....****.*........................*******@****@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@*....*********.............................**********@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*****...***...............................************@@@@@@@@@*@@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@***.**.*******..***.......................************@@@@@@@@@*@@*...*@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..         ....*@@@@... ...**..................************@@@@@@@@@@@@@*.. *@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@*...           .......*@@@@*******................***************@@@@@@@@@@@@@@*.*@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@*  ..........     ......*@@@****....................**************@@@@@@@@@@*@@@@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.... .******............******...................***************@@@@@@@@@...**@@@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@*.      .    ..*@@@*..........*****..................******************@@@@@* ...****@@@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@*.      ....***...    ..............***................*********************@@@. ..********@@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@.     ....*****@@@@*....................****..........****************...*****@* ..***********@@@@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@**@@@*..******@@@@@@@@@@**..........   ...*****.....******************......****. ..***************@@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@********@***@@@@@@@@@*********@@*.... ...  ..***************************.......**. ..*********************\n"); Sleep(33);
	printf("@@@@@@@@@@@*.***.****@@@@@@@@@@@@@@@@****...*@@*.........**************************.......... ...**********************\n"); Sleep(33);
	printf("@@@@@@@@@@@@****@@@@@@@@@@@@@@@@@@@@@@@**...*...*........***********************........... .....**********************\n"); Sleep(33);
	printf("@@@@@@@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.................**********************................****************@******\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...  .............***@@@***********..........  ........***************@*******\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..  .............**.*@@*@@********...................***************@********\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*... . ..........**....  .@@*********... ...........******************@******\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......................   .*@@@@*****. .............*****************@*******\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...............  .. .   ..*@@@******.............****************@*********\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*............   ... ..*@***@@*********.........****************@**********\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*......       ...********************.     .***************@@***********\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.....        .************************.....***************@@************\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.....       .***************************...***************@@************@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@........ .*******************************..**************@*************@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.......************************************************@*************@@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*****....*********************************@@@*************@**************@@\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*******@*************************@@*****@**@@@@@@**********@**************@@@*\n"); Sleep(33);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@************************************@@*********@@@@@@********@***************@@@*\n"); Sleep(33);


	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 4);
	printf("        .......*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.......\n"); Sleep(44);
	printf("      .........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..........\n"); Sleep(44);
	printf("  .............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..............\n"); Sleep(44);
	printf("...............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**.............\n"); Sleep(44);
	printf("...............*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*...............\n"); Sleep(44);
	printf("..............*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@****@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**................\n"); Sleep(44);
	printf("..............*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@******@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**................\n"); Sleep(44);
	printf("..............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*********@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.................\n"); Sleep(44);
	printf(".............*@@@@@@@@@@@@@@@@@@@@@@@@@@@*@*****..******@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.................\n"); Sleep(44);
	printf("............*@@@@@@@@@@@@@@@@@@@****@@@@@@@@@*******.****@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**...............\n"); Sleep(44);
	printf("............*@@@@@@@@@@@@@@@@@@@*************@@@@@@@*******@@*********@@@@@@@@@@@@@@@@@@@@@@@@***..................\n"); Sleep(44);
	printf("............**@@@@@@@@@@@@@@@@**@***..***...*.*****@@@@@**************@@@@@@@@@@@@@@@@@@@@@@@@**....................\n"); Sleep(44);
	printf("............*@@@@@@@@@@@@@@@@**.****@@@@**************@@@@******@@@@@@@@@@**@@@@@@@@@@@@@@@@@@**....................\n"); Sleep(44);
	printf("...........*@@@@@@@@@@@@@@@@**.....@*.***@@@@@@@@@@@@@@@******@@@@@***********@@@@@@@@@@@@@@@@**....................\n"); Sleep(44);
	printf("...........*@@@@@@@@@@@@@@@@**.....@...********@@@@@****@@***@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.....................\n"); Sleep(44);
	printf("............*@@@@@@@@@@@@@@@***....**....****@**@******@@@***@@@**@***@@@@@@@@****@*@@@@@@@@@@@***...................\n"); Sleep(44);
	printf("............*@@@@@@@@@@@@@@****.....***.....***********@@*..**@@****@@@@@@@@*****@@@@@@@@@@@*****....................\n"); Sleep(44);
	printf("...........***@@@@@@@@@@@@@******.....******************.....**@@****************@@@@@@@@@@***.......................\n"); Sleep(44);
	printf("............**@@@@@@@@@@@@*******........*************.......****@***************@@@@@@@@@@**........................\n"); Sleep(44);
	printf("..........**@@@@@@@@@@@@@@*********.....*************........*******************@@@@@@@@@****.......................\n"); Sleep(44);
	printf("......**@@@@@@@@@@@@@@@@@@************************...........****@**************@@@@@@@@@*****......................\n"); Sleep(44);
	printf(".***@@@@@@@@@@@@@@@@@@@@@@@********************.**............*.***************@@@@@@@@@@**..........................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@***************@****..*****.......****************@@@@@@@@@******.........................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@***********************...***@*******@@************@@@@@@@@@@*****............................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@*...****************@@**......**@@@@@@**********@@@@@@@@@@@@@@**...............................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@....**@****************@@****************@@@***@@@@@@@@@@@@@@@@@**.............................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@...*@@*************..******@@@@@@@*...@@@@******@@@@@@@@@@@@@@@@@**..........................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@*...**@@@*******************.....**.....***@@**@@@@@@@@@@@@@@@@@@@@@@**.......................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@....***@@@@****************..   ...*.....**@@@@***@@@@@@@@@@@@@@@@@@@@@@**....................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@.....**@@@@@*********........     ..........*****.*@@@@@@@@@@@@@@@@@@@@@@@@@*................\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@....**@@@@@*****...     .....     ...*.....**...*@@@@@@@@@@@@@@@@@@@@@@@@@@@@**.............\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@*...**@@@@@@****...       ...       .**.***..*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*...........\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..***@@@@@@*. ...        ...       .***.*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.........\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....**@@@@..     ..         .       ..*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**......\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*......*@@..       ..               ...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.......@@*..        ..             ...*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*....\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.........   ..                  ......*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*....  ...     ..                .....**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*....   ..      ..           . ......***@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..........                  ....*******@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.  .......                ....********@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.  ..   ...           ......**********@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.   .     ..         ....*************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@....\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.   .      .....   .....*************@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.          .........********.********@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.          .*......****.......******@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*...\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.          ....................*****@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*..\n"); Sleep(44);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.           .....................***@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\n"); Sleep(44);

	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);
	printf("\n"); Sleep(33);

	system("cls");

	
		system("color F0");
		char* dance[2] = {
			"        Å                   Å\n" //dance[0] 동작 
			"      ／  ＼               ／  ＼\n"
			"     (´Д｀;)/           (´Д｀;)/\n"
			"    / (   へ)            / (   へ)\n"
			"       く                   く\n",
			"         Å                   Å\n" //dance[1] 동작 
			"       ／  ＼               ／  ＼\n"
			"    ＼(;´Д｀)/         ＼(;´Д｀)/\n"
			"       (へ   )              (へ   )\n"
			"            >                    >\n"

		};
		int i,j, delay = 500; /* delay timer [ms] */
		for (j = 0;j < 7;j ++)
		{
			for (i = 0; i < 2; i++)
			{
				system("cls"); // clear screen 
				printf("\n\n\n%s", dance[i]); //dance 출력 
				gotoxy(40, i + 9);
				//   printf("두둠칫\n");
				printf("사랑해요");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 12);
				printf("♥\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 8);
				gotoxy(18, i + 7);
				//   printf("두둠칫\n");
				printf("은종샘\n");
				gotoxy(1, i + 1);
				printf("*\n");
				clock(delay);
			}
		}
		return 0;

	return;
}
		
		void gotoxy(int x, int y)
		{
			COORD Pos = { x - 1, y - 1 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		}
		void clock(int timer)
		{
			Sleep(timer);/* sleep timer [ms] */
		}

/*******************************************************************************
								입력값 유효성 검사
*******************************************************************************/

int isValidName(char txt[])
{
	int isValid = 0;
	if (txt[0] != '\0' && strlen(txt) < 10)
	{
		isValid = 1;
	}

	if (!isValid) textColor("\t\t\t\t\t\t* 오류 : 올바른 이름을 입력하세요.\n", 12);
	
	return isValid;
}
int isValidAddr(char txt[])
{
	int isValid = 0, i = 0;

	while (txt[i] != '\0')
	{
		if (txt[i] != ' ')
		{
			isValid = 1;
			break;
		}
		i++;
	}

	if (!isValid) textColor("\t\t\t\t\t\t* 오류 : 올바른 주소를 입력하세요.\n", 12);

	return isValid;
}
int isValidPhone(char txt[])
{
	int isValid = 1;
	int	n = 0, m = 0, j = 0;

	while (isValid == 1 && txt[j] != '\0')
	{
		if (txt[j] == '-')
		{
			n++;
			if (m == 0)
			{
				isValid = 0;
				break;
			}
			m = 0;
		}
		else if (txt[j] < 48 || txt[j] > 57)
		{
			isValid = 0;
			break;
		}
		else
		{
			m++;
		}
		j++;
	}
	if (n != 2 || m == 0) isValid = 0;

	if (!isValid) textColor("\t\t\t\t\t\t* 오류 : 형식이 올바르지 않습니다.\n", 12);
	
	return isValid;
}