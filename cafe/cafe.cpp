#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum MENU // �޴�
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

// �޴��̸�
string name[MENU_END] = { " �Ƹ޸�ī��   ", " ī���     ", " ����������   ", " ������̵�   ", " �׸�Ƽ��   ",
							  " ����ġ���ɟ� ", " ���ڸ��ɟ�   ", " ������Ű     ", " �÷��κ��̱� ",
				  "��纣�����̱�", "��            ", "�Һ�        ", "��Ʈ          " };
int price[MENU_END] = { 4000, 4500, 3500, 4000, 4500, 5000, 5000, 2500, 3500, 4500, 10000, 15000, 3500 }; // ����
static int tablenumber = 1; // ���̺� �ѹ�

class CTable // ���̺� Ŭ����
{
private:
	int m_tablenumber; // ���̺� �ѹ�
	vector<long> m_vecnOrder; // �ֹ�����
	vector<int> m_vecnQuantity; // �ֹ�����
public:
	int GetTableNumber(); // ���̺� �ѹ�
	void SetTableNumber(int tablenumber); // ���̺� �ѹ� ����
	long GetOrder(int index); // �ֹ����� ����
	void SetOrder(long value, int quantity); // �ֹ����� ����
	int GetOrderCount(); // �ֹ����� ����
	int GetQuantity(int index); // ���� ����
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
	if ((int)m_vecnOrder.size() - 1 < index) // ����ó��
	{
		return -1;
	}

	return m_vecnOrder[index];
}

void CTable::SetOrder(long value, int quantity) // �ֹ������� ���� ����
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
	if ((int)m_vecnQuantity.size() - 1 < index) // ����ó��
	{
		return -1;
	}

	return m_vecnQuantity[index];
}

int mainmenu() // ���θ޴�
{
	int input = 0;

	while (1)
	{
		cout << "1. �޴�����" << endl;
		cout << "2. ���̺� �߰�(�ֹ�)" << endl;
		cout << "3. ���̺� ����(���)" << endl;
		cout << "4. ���� ���� ����" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << " >> ";
		cin >> input;

		if (input >= 1 && input <= 5) // 1~5 ���� ���ڸ� �Է�
		{
			break;
		}
		else
		{
			cout << "1 ~ 5 ���� ���ڸ� �Է°����մϴ�." << endl;
		}
	}

	return input;
}

void showmenu() // ��� �޴���  ������ش�.
{
	cout << "============== �� �� ==============" << endl;
	int i = 0;
	for (i = DRINK_AMERICANO; i < MENU_END; i++)
	{
		cout << i + 1 << ". " << name[i] << "\t\t" << price[i] << " �� " << endl;
	}
	cout << endl;
}

void showcurrent(vector<CTable *> vecTable, int straw, int tissue, int balance) // ������� ǥ��
{
	// ��� ǥ��
	cout << "=============================" << endl;
	cout << "���� ��Ʈ�ο� ��� : " << straw << " ��" << endl;
	cout << "���� Ƽ�� ��� : " << tissue << " ��" << endl;
	cout << "���� �ܰ� : " << balance << " ��" << endl;
	cout << "=============================" << endl << endl;

	if ((int)vecTable.size() > 0)
	{
		// ���̺� ��Ȳ ǥ��
		cout << "=============================" << endl;
		cout << "���� ���̺� ��Ȳ" << endl;

		for (int i = 0; i < (int)vecTable.size(); i++)
		{
			cout << "-----------------------------" << endl;
			cout << i + 1 << "�� ���̺�" << endl;

			// ����, ����, ���ݱ��� ǥ��
			for (int j = 0; j < vecTable[i]->GetOrderCount(); j++)
			{
				int order = vecTable[i]->GetOrder(j);
				int quantity = vecTable[i]->GetQuantity(j);

				cout << j + 1 << ". " << name[order] << "(" << quantity << "��, " << price[order] * quantity << "��)" << endl;
			}
			cout << "-----------------------------" << endl << endl;
		}
		cout << "=============================" << endl << endl;
	}
}

void addtable(vector<CTable *> &vecTable, int &straw, int &tissue) // ���̺� �߰�
{
	cout << "�ֹ� �Ͻðڽ��ϱ�?" << endl;

	showmenu(); // �޴��� �����ش�.

	int selectmenu = 0;

	CTable* table = new CTable;

	while (1)
	{
		while (1) // ���� �ֹ�
		{
			cout << "��ȣ�� �������ּ���(�ֹ���:0) : ";
			cin >> selectmenu;

			if (selectmenu >= 0 && selectmenu <= MENU_END)
			{
				break;
			}
			else
			{
				cout << "�޴��� ��ȣ�� �������ּ���" << endl;
			}
		}

		if (selectmenu == 0) // 0 �Է��ϸ� �׸� �ֹ�
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

			while (1) // ������ ����
			{
				cout << "������ �������ּ��� : ";
				cin >> menuquantity;

				if (selectmenu > 0)
				{
					break;
				}
				else
				{
					cout << "1�� �̻� �Է����ּ���" << endl;
				}
			}

			table->SetTableNumber(tablenumber); // ���̺� �ѹ� �Է�
			table->SetOrder(selectmenu - 1, menuquantity); // ������ ���İ� ���� ����

			// ���� ���� �� ��쿣 ��� ������ ���δ�.
			if (selectmenu - 1 >= DRINK_AMERICANO && selectmenu - 1 <= DESERT_BLUEVERYBAGLE)
			{
				straw -= menuquantity;
				tissue--;
			}
		}
	}
}

void removetable(vector<CTable *> &vecTable, int &balance) // ���̺� ����(���)
{
	int tablenumber = 0;

	// ����� ���̺��ȣ �Է�
	cout << "����� ���̺��� ��ȣ�� �Է��ϼ��� : ";
	cin >> tablenumber;

	// �Է��� ��ȣ�� �ִ��� Ȯ��
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
		// �ش� ���̺��� �ֹ������� ���� ������ ����ؼ� �ܰ� ���Ѵ�.
		for (int i = 0; i < vecTable[index]->GetOrderCount(); i++)
		{
			int order = vecTable[index]->GetOrder(i);
			int quantity = vecTable[index]->GetQuantity(i);

			balance += (price[order] * quantity);
		}

		vecTable.erase(vecTable.begin() + index); // �ش� ���̺� ������ �����.

		cout << "����� �Ϸ�Ǿ����ϴ�" << endl;
	}
	else
	{
		cout << "�Է��Ͻ� ���̺� ��ȣ�� �����ϴ�" << endl;
	}
}

int main()
{
	vector<CTable *> vecTable;

	int straw = 100; // ����
	int tissue = 100; // Ƽ��
	int balance = 100000; // �ܰ�

	while (1)
	{
		int input = mainmenu();

		if (input == 1) // �޴�����
		{
			showmenu();
		}
		else if (input == 2) // ���̺� �߰�(�ֹ�)
		{
			addtable(vecTable, straw, tissue);
		}
		else if (input == 3) // ���̺� ����(���)
		{
			showcurrent(vecTable, straw, tissue, balance);
			removetable(vecTable, balance);
		}
		else if (input == 4) // ���� ���� ����
		{
			showcurrent(vecTable, straw, tissue, balance);
		}
		else if (input == 5) // ���α׷� ����
		{
			break;
		}
	}

	return 0;
}