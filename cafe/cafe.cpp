#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum MENU // 메뉴
{
	DRINK_AMERICANO,
	DRINK_CAFELATTE,
	DRINK_ESPRESSO,
	DRINK_LEMONADE,
	DRINK_GREENTEALATTE,
	DESERT_NEWYORKCHEESECAKE,
	DESERT_CHOCOLATECAKE,
	DESERT_CHOCOCOOKIE,
	DESERT_PLANEBAGLE,
	DESERT_BLUEVERYBAGLE,
	ACCESARY_CUP,
	ACCESARY_TUMBLR,
	ACCESARY_NOTE,
	MENU_END,
};

// 메뉴이름
string name[MENU_END] = { " 아메리카노   ", " 카페라떼     ", " 에스프레소   ", " 레모네이드   ", " 그린티라떼   ",
							  " 뉴욕치즈케잌 ", " 초코릿케잌   ", " 초코쿠키     ", " 플레인베이글 ",
				  "블루베리베이글", "컵            ", "텀블러        ", "노트          " };
int price[MENU_END] = { 4000, 4500, 3500, 4000, 4500, 5000, 5000, 2500, 3500, 4500, 10000, 15000, 3500 }; // 가격
static int tablenumber = 1; // 테이블 넘버

class CTable // 테이블 클래스
{
private:
	int m_tablenumber; // 테이블 넘버
	vector<long> m_vecnOrder; // 주문내역
	vector<int> m_vecnQuantity; // 주문수량
public:
	int GetTableNumber(); // 테이블 넘버
	void SetTableNumber(int tablenumber); // 테이블 넘버 저장
	long GetOrder(int index); // 주문내역 보기
	void SetOrder(long value, int quantity); // 주문내역 저장
	int GetOrderCount(); // 주문내역 개수
	int GetQuantity(int index); // 수량 보기
};

int CTable::GetTableNumber()
{
	return m_tablenumber;
}

void CTable::SetTableNumber(int number)
{
	m_tablenumber = number;
}

long CTable::GetOrder(int index)
{
	if ((int)m_vecnOrder.size() - 1 < index) // 예외처리
	{
		return -1;
	}

	return m_vecnOrder[index];
}

void CTable::SetOrder(long value, int quantity) // 주문내역과 수량 저장
{
	m_vecnOrder.push_back(value);
	m_vecnQuantity.push_back(quantity);
}

int CTable::GetOrderCount()
{
	return (int)m_vecnOrder.size();
}

int CTable::GetQuantity(int index)
{
	if ((int)m_vecnQuantity.size() - 1 < index) // 예외처리
	{
		return -1;
	}

	return m_vecnQuantity[index];
}

int mainmenu() // 메인메뉴
{
	int input = 0;

	while (1)
	{
		cout << "1. 메뉴보기" << endl;
		cout << "2. 테이블 추가(주문)" << endl;
		cout << "3. 테이블 삭제(계산)" << endl;
		cout << "4. 현재 상태 보기" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << " >> ";
		cin >> input;

		if (input >= 1 && input <= 5) // 1~5 사이 숫자만 입력
		{
			break;
		}
		else
		{
			cout << "1 ~ 5 사이 숫자만 입력가능합니다." << endl;
		}
	}

	return input;
}

void showmenu() // 모든 메뉴를  출력해준다.
{
	cout << "============== 메 뉴 ==============" << endl;
	int i = 0;
	for (i = DRINK_AMERICANO; i < MENU_END; i++)
	{
		cout << i + 1 << ". " << name[i] << "\t\t" << price[i] << " 원 " << endl;
	}
	cout << endl;
}

void showcurrent(vector<CTable *> vecTable, int straw, int tissue, int balance) // 현재상태 표시
{
	// 재고 표시
	cout << "=============================" << endl;
	cout << "현재 스트로우 재고 : " << straw << " 개" << endl;
	cout << "현재 티슈 재고 : " << tissue << " 개" << endl;
	cout << "현재 잔고 : " << balance << " 원" << endl;
	cout << "=============================" << endl << endl;

	if ((int)vecTable.size() > 0)
	{
		// 테이블 상황 표시
		cout << "=============================" << endl;
		cout << "현재 테이블 상황" << endl;

		for (int i = 0; i < (int)vecTable.size(); i++)
		{
			cout << "-----------------------------" << endl;
			cout << i + 1 << "번 테이블" << endl;

			// 개수, 수량, 가격까지 표시
			for (int j = 0; j < vecTable[i]->GetOrderCount(); j++)
			{
				int order = vecTable[i]->GetOrder(j);
				int quantity = vecTable[i]->GetQuantity(j);

				cout << j + 1 << ". " << name[order] << "(" << quantity << "개, " << price[order] * quantity << "원)" << endl;
			}
			cout << "-----------------------------" << endl << endl;
		}
		cout << "=============================" << endl << endl;
	}
}

void addtable(vector<CTable *> &vecTable, int &straw, int &tissue) // 테이블 추가
{
	cout << "주문 하시겠습니까?" << endl;

	showmenu(); // 메뉴를 보여준다.

	int selectmenu = 0;

	CTable* table = new CTable;

	while (1)
	{
		while (1) // 음식 주문
		{
			cout << "번호를 선택해주세요(주문끝:0) : ";
			cin >> selectmenu;

			if (selectmenu >= 0 && selectmenu <= MENU_END)
			{
				break;
			}
			else
			{
				cout << "메뉴의 번호를 선택해주세요" << endl;
			}
		}

		if (selectmenu == 0) // 0 입력하면 그만 주문
		{
			if (table->GetOrderCount() > 0)
			{
				vecTable.push_back(table);
				tablenumber++;
			}

			break;
		}
		else
		{
			int menuquantity = 0;

			while (1) // 수량을 선택
			{
				cout << "개수를 선택해주세요 : ";
				cin >> menuquantity;

				if (selectmenu > 0)
				{
					break;
				}
				else
				{
					cout << "1개 이상 입력해주세요" << endl;
				}
			}

			table->SetTableNumber(tablenumber); // 테이블 넘버 입력
			table->SetOrder(selectmenu - 1, menuquantity); // 선택한 음식과 수량 저장

			// 음식 종류 일 경우엔 재고 수량을 줄인다.
			if (selectmenu - 1 >= DRINK_AMERICANO && selectmenu - 1 <= DESERT_BLUEVERYBAGLE)
			{
				straw -= menuquantity;
				tissue--;
			}
		}
	}
}

void removetable(vector<CTable *> &vecTable, int &balance) // 테이블 삭제(계산)
{
	int tablenumber = 0;

	// 계산할 테이블번호 입력
	cout << "계산할 테이블의 번호를 입력하세요 : ";
	cin >> tablenumber;

	// 입력한 번호가 있는지 확인
	bool exist = false;
	int index = 0;
	for (int i = 0; i < (int)vecTable.size(); i++)
	{
		if (tablenumber == vecTable[i]->GetTableNumber())
		{
			exist = true;
			index = i;
			break;
		}
	}

	if (exist == true)
	{
		// 해당 테이블의 주문내역을 보고 가격을 계산해서 잔고에 더한다.
		for (int i = 0; i < vecTable[index]->GetOrderCount(); i++)
		{
			int order = vecTable[index]->GetOrder(i);
			int quantity = vecTable[index]->GetQuantity(i);

			balance += (price[order] * quantity);
		}

		vecTable.erase(vecTable.begin() + index); // 해당 테이블 정보를 지운다.

		cout << "계산이 완료되었습니다" << endl;
	}
	else
	{
		cout << "입력하신 테이블 번호가 없습니다" << endl;
	}
}

int main()
{
	vector<CTable *> vecTable;

	int straw = 100; // 빨대
	int tissue = 100; // 티슈
	int balance = 100000; // 잔고

	while (1)
	{
		int input = mainmenu();

		if (input == 1) // 메뉴보기
		{
			showmenu();
		}
		else if (input == 2) // 테이블 추가(주문)
		{
			addtable(vecTable, straw, tissue);
		}
		else if (input == 3) // 테이블 삭제(계산)
		{
			showcurrent(vecTable, straw, tissue, balance);
			removetable(vecTable, balance);
		}
		else if (input == 4) // 현재 상태 보기
		{
			showcurrent(vecTable, straw, tissue, balance);
		}
		else if (input == 5) // 프로그램 종료
		{
			break;
		}
	}

	return 0;
}