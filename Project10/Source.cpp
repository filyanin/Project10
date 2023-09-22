#include <iostream>
#include <list>
#include <algorithm>
#include <ctime>
#include <random>
#include <set>

void print(int element) {
    std::cout << element << " ";
}

int main() {

    setlocale(LC_ALL, "RUSSIAN");

    std::vector<int> integerList(10); // ������� ������ �� 10 ���������

    std::srand(time(0u));

    // ���������� generate ��� ���������� ������ ���������� ����������
    std::generate(integerList.begin(), integerList.end(), []()->int {
        return int(rand()) % 10;
        });

    // ������� ������, � ������� ����� ����������� �������� ��������������� ��������
    std::vector<int> sortedArray(5);

    std::cout << "1. std::partial_sort_copy ��� �������, ���������� ��� ������ ������������� � ���������� ������ ������� generate\n" <<
        "�������� ����������� ������: " << std::endl;
    std::for_each(integerList.begin(), integerList.end(), print);
    
    // �������� std::partial_sort_copy ��� ��������� ���������� � �����������
    std::partial_sort_copy(integerList.begin(), integerList.end(),
        sortedArray.begin(), sortedArray.end());
    std::cout << "\n��������������� ������ (5 ���������):" << std::endl;
    std::for_each(sortedArray.begin(), sortedArray.end(), print);


    int valueToFind = 3;
    std::cout << "\n\n2. lower_bound, upper_bound, set::lower_bound, set::upper_bound � ��� �������������� ������� �� 10 ���������\n" <<
        " 1) ���������� lower_bound � upper_bound ��� ��������� ������� ��� �����: " << valueToFind << std::endl;
    std::cout << "  ��������������� ������: ";
    std::sort(integerList.begin(), integerList.end());
    std::for_each(integerList.begin(), integerList.end(), print);

    auto it = std::lower_bound(integerList.begin(), integerList.end(), valueToFind);
    std::cout << "\n  lower_bound ��� " << valueToFind << " �� ������� " << (it - integerList.begin()) << std::endl;
    
    auto upper = std::upper_bound(integerList.begin(), integerList.end(), valueToFind);
    std::cout << "  upper_bound ��� " << valueToFind << " �� ������� " << (upper - integerList.begin()) << std::endl;
    

    std::cout << "\n 2) ���������� set::lower_bound, set::upper_bound ��� ��������� " << std::endl;
    std::set<int> s;
    std::generate_n(std::inserter(s, s.begin()), 10, [&]() { return int(rand()) % 10; });
    std::cout << "  �������� ��������� (����������� 10 �����, ��-�� ���������� ��������� ������): ";
    std::for_each(s.begin(), s.end(), print);

    auto lower_set = s.lower_bound(valueToFind);
    auto upper_set = s.upper_bound(valueToFind);

    std::cout << "\n  lower_bound ��� " << valueToFind << " = " << *lower_set << std::endl;
    std::cout << "  upper_bound ��� " << valueToFind << " = " << *upper_set << std::endl;

    std::set<int> s_new = { 0,1,3 };

    std::cout << "\n\n3. includes � set_difference � ��� ������ ��������� � ������������� ��������� ������� (��������) �������������� ��������� � �������� ������������ ��������� ��������������\n" <<
        " ����� ���������: ";
    std::for_each(s_new.begin(), s_new.end(), print);

    bool isSubset = std::includes(s.begin(), s.end(),
        s_new.begin(), s_new.end());

    if (isSubset) {
        std::cout << "\n ����� ��������� �������� ������������� �������." << std::endl;
    }
    else {
        std::cout << "\n ����� ��������� �� �������� ������������� �������." << std::endl;
    }

    std::vector<int> difference1;
    std::set_difference(s.begin(), s.end(),
        s_new.begin(), s_new.end(),
        std::back_inserter(difference1));

    std::cout << " ������� ����� ������ � ������ �����������: ";
    std::for_each(difference1.begin(), difference1.end(), print);


    std::vector<int> difference2;
    std::set_difference(s_new.begin(), s_new.end(),
        s.begin(), s.end(),
        std::back_inserter(difference2));

    std::cout << "\n ������� ����� ������ � ������ �����������: ";
    std::for_each(difference2.begin(), difference2.end(), print);
    return 0;
}
