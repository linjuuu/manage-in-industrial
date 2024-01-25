#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS


// ITEM의 수, 버퍼의 크기 설정
#define MAX_ITEM 100
#define bufferSize 200


//-------------------전역변수 설정------------------
// 
//파일 입출력 변수
FILE* fpIn, * fpOut;
//물품 정보 변수 
char itemName[30];
int itemPrice;
int employeeNumber;
int hourByCost;
int workHour;

// 물품의 정보를 담을 구조체 설정
struct itemInfo {
    char itemName[20];
    int itemPrice;
    int employeeNumber;
    int hourByCost;
    int workHour;
    int profit;
};
struct itemInfo item[MAX_ITEM];

// 현재 저장된 아이템의 갯수를 설정
int itemCount = 0;


//---------------------------------------------




// 입력이 들어온 내용을 구조체에 등록하는 함수 
void enrollItem()
{
    strcpy_s(item[itemCount].itemName,30, itemName);
    item[itemCount].itemPrice = itemPrice;
    item[itemCount].employeeNumber = employeeNumber;
    item[itemCount].hourByCost = hourByCost;
    item[itemCount].employeeNumber = employeeNumber;
    item[itemCount].workHour = workHour;
    item[itemCount].profit = itemPrice - (employeeNumber * hourByCost * workHour);
    itemCount++;
}

//현재 아이템 목록을 출력 
void printItemList()
{
    printf("\n현재 아이템 목록\n\n");
    for (int i = 0; i < itemCount; i++)
        printf("%-d %s\n", i + 1, item[i].itemName);
}


//물품의 정보를 출력하는 함수 
void printItemInfo(int itemNum)
{

    printf("\n제품 이름 : %s\n제품 판매 가격 : %d원\n생산자 수 : %d명\n생산자 시급 : %d원\n근무시간 : %d시간\n개당 순이익 : %d\n\n",
        item[itemNum].itemName, item[itemNum].itemPrice, item[itemNum].employeeNumber, item[itemNum].hourByCost, item[itemNum].workHour, item[itemNum].profit);
}


//변경할 항목을 입력받아 변경 하는 함수, 순이익을 재정산한다. 
void updateItem(int itemNum)
{
    while (1)
    {
        int choose;
        printf("\n-----------------------------------현재 수치------------------------------------------------\n");
        printItemInfo(itemNum);
        printf("생산자 수 변경 : 1 | 시급 변경 : 2 | 근무 시간 변경 : 3 | 물품 금액 변경 : 4\n입력 : ");
        scanf_s("%d", &choose);
        printf("--------------------------------------------------------------------------------------------\n");


        int newProfit = 0;

        if (choose == 1)
        {
            fprintf(fpOut, "%s의 정보 update -->  ", item[itemNum].itemName);
            printf("\n변경할 생산자 수를 입력하세요 : ");
            scanf_s("%d", &employeeNumber);
            newProfit = item[itemNum].itemPrice - (employeeNumber * item[itemNum].hourByCost * item[itemNum].workHour);
            fprintf(fpOut, "%s의 생산자 수를 %d에서 %d 로 변경하여 ", item[itemNum].itemName, item[itemNum].employeeNumber, employeeNumber);
            item[itemNum].employeeNumber = employeeNumber;
        }

        else if (choose == 2)
        {
            fprintf(fpOut, "%s의 정보 update -->  ", item[itemNum].itemName);
            printf("\n변경할 시급 액수를 입력하세요 : ");
            scanf_s("%d", &hourByCost);
            newProfit = item[itemNum].itemPrice - (item[itemNum].employeeNumber * hourByCost * item[itemNum].workHour);
            fprintf(fpOut, "%s의 시급을 %d에서 %d 로 변경하여 ", item[itemNum].itemName, item[itemNum].itemPrice, itemPrice);
            item[itemNum].hourByCost = hourByCost;
        }

        else if (choose == 3)
        {
            fprintf(fpOut, "%s의 정보 update -->  ", item[itemNum].itemName);
            printf("\n변경할 근무시간을 입력하세요 : ");
            scanf_s("%d", &workHour);
            newProfit = item[itemNum].itemPrice - (item[itemNum].employeeNumber * item[itemNum].hourByCost * workHour);
            fprintf(fpOut, "%s의 근무시간을 %d에서 %d 로 변경하여 ", item[itemNum].itemName, item[itemNum].workHour, workHour);
            item[itemNum].workHour = workHour;
        }

        else if (choose == 4)
        {
            fprintf(fpOut, "%s의 정보 update -->  ", item[itemNum].itemName);
            printf("\n변경할 물품금액 입력하세요 : ");
            scanf_s("%d", &itemPrice);
            newProfit = itemPrice - (item[itemNum].employeeNumber * item[itemNum].hourByCost * item[itemNum].workHour);
            fprintf(fpOut, "%s의 가격을 %d에서 %d 로 변경하여 ", item[itemNum].itemName, item[itemNum].itemPrice, itemPrice);
            item[itemNum].itemPrice = itemPrice;
        }
        else
        {
            printf("잘못된 입력입니다. 다시 입력해주세요\n");
            continue;
        }
        fprintf(fpOut, "순이익이 %d원에서 %d원으로 %d원 만큼 변경 되였습니다.\n", item[itemNum].profit, newProfit, newProfit - item[itemNum].profit);
        printf("\n순이익이 %d원에서 %d원으로 %d원 만큼 변경 되였습니다.\n", item[itemNum].profit, newProfit, newProfit - item[itemNum].profit);
        item[itemNum].profit = newProfit;


        printf("\n%s의 수정을 종료하시려면 0, 아니면 1을 입력해주세요.\n입력: ", item[itemNum].itemName);
        scanf_s("%d", &choose);
        if (choose == 0)
            return;
    }

}




// 메뉴를 띄우는 함수
void menu()
{
    // 선택한 메뉴, 선택한 물품을 구분할 변수
    int choose;
    int itemNum;

    while (1)
    {
        printf("------------------------------메뉴-----------------------------------\n");
        printf("\n1. 종료 | 2. 제품 정보 확인 |  3. 제품 정보 수정 \nchoose :  ");
        scanf_s("%d", &choose);

        if (choose == 1)
        {
            printf("output.txt 에서 보고서를 확인할 수 있습니다.\n프로그램을 종료합니다.\n");
            break;
        }

        else if (choose == 2)
        {
            // 처음부터 순회하며 아이템 이름을 출력
            printItemList();
            printf("\n몇 번 제품의 정보를 확인할까요 ?\n번호 : ");
            scanf_s("%d", &itemNum);
            if (itemNum > itemCount)
            {
                printf("잘못된 입력입니다. 다시 입력해주세요\n");
                continue;
            }
            printItemInfo(itemNum - 1);
        }
        else if (choose == 3)
        {
            printf("\n몇 번 item의 정보를 수정할까요?\n");
            printItemList();
            printf("choose: ");
            scanf_s("%d", &itemNum);
            updateItem(itemNum - 1);
        }
        else
            printf("잘못된 입력입니다. 다시 입력해주세요\n");
    }
}





int main()
{

    fopen_s(&fpIn,"input.txt", "r");
    fopen_s(&fpOut,"output.txt", "w");

    if (fpIn == NULL || fpOut == NULL)
    {
        printf("파일 열기 실패\n");
        return -1;
    }




    char buffer[bufferSize];
    fgets(buffer, sizeof(char) * bufferSize, fpIn);
    while (1)
    {
        if (fgets(buffer, sizeof(char) * bufferSize, fpIn) == NULL)
            break;
        sscanf_s(buffer, "%s %d %d %d %d", 
            itemName,30, &itemPrice, &employeeNumber, &hourByCost, &workHour);
        enrollItem();
    }




    fprintf(fpOut, "\n\n----------------------보고서------------------------\n");
    //입력이 끝난 후 프로그램 실행
    menu();
    fprintf(fpOut, "\n\n--------------------------------------------------\n");
    return 0;
}