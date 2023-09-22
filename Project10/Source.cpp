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

    std::vector<int> integerList(10); // Создаем список из 10 элементов

    std::srand(time(0u));

    // Используем generate для заполнения списка случайными значениями
    std::generate(integerList.begin(), integerList.end(), []()->int {
        return int(rand()) % 10;
        });

    // Создаем массив, в который будут скопированы частично отсортированные элементы
    std::vector<int> sortedArray(5);

    std::cout << "1. std::partial_sort_copy для массива, созданного при помощи рассмотренной в предыдущем модуле функции generate\n" <<
        "Элементы полученного списка: " << std::endl;
    std::for_each(integerList.begin(), integerList.end(), print);
    
    // Вызываем std::partial_sort_copy для частичной сортировки и копирования
    std::partial_sort_copy(integerList.begin(), integerList.end(),
        sortedArray.begin(), sortedArray.end());
    std::cout << "\nОтсортированный массив (5 элементов):" << std::endl;
    std::for_each(sortedArray.begin(), sortedArray.end(), print);


    int valueToFind = 3;
    std::cout << "\n\n2. lower_bound, upper_bound, set::lower_bound, set::upper_bound — для целочисленного массива из 10 элементов\n" <<
        " 1) Рассмотрим lower_bound и upper_bound для исходного массива для числа: " << valueToFind << std::endl;
    std::cout << "  Отсортированный массив: ";
    std::sort(integerList.begin(), integerList.end());
    std::for_each(integerList.begin(), integerList.end(), print);

    auto it = std::lower_bound(integerList.begin(), integerList.end(), valueToFind);
    std::cout << "\n  lower_bound для " << valueToFind << " на позиции " << (it - integerList.begin()) << std::endl;
    
    auto upper = std::upper_bound(integerList.begin(), integerList.end(), valueToFind);
    std::cout << "  upper_bound для " << valueToFind << " на позиции " << (upper - integerList.begin()) << std::endl;
    

    std::cout << "\n 2) Рассмотрим set::lower_bound, set::upper_bound для множества " << std::endl;
    std::set<int> s;
    std::generate_n(std::inserter(s, s.begin()), 10, [&]() { return int(rand()) % 10; });
    std::cout << "  Создадим множество (сгенерируем 10 чисел, из-за повторений получется меньше): ";
    std::for_each(s.begin(), s.end(), print);

    auto lower_set = s.lower_bound(valueToFind);
    auto upper_set = s.upper_bound(valueToFind);

    std::cout << "\n  lower_bound для " << valueToFind << " = " << *lower_set << std::endl;
    std::cout << "  upper_bound для " << valueToFind << " = " << *upper_set << std::endl;

    std::set<int> s_new = { 0,1,3 };

    std::cout << "\n\n3. includes и set_difference — для поиска вхождения в сортированное множество другого (меньшего) сортированного множества и переноса отличающихся элементов соответственно\n" <<
        " Новое множество: ";
    std::for_each(s_new.begin(), s_new.end(), print);

    bool isSubset = std::includes(s.begin(), s.end(),
        s_new.begin(), s_new.end());

    if (isSubset) {
        std::cout << "\n Новое множество является подмножеством старого." << std::endl;
    }
    else {
        std::cout << "\n Новое множество не является подмножеством старого." << std::endl;
    }

    std::vector<int> difference1;
    std::set_difference(s.begin(), s.end(),
        s_new.begin(), s_new.end(),
        std::back_inserter(difference1));

    std::cout << " Разница между первым и вторым множествами: ";
    std::for_each(difference1.begin(), difference1.end(), print);


    std::vector<int> difference2;
    std::set_difference(s_new.begin(), s_new.end(),
        s.begin(), s.end(),
        std::back_inserter(difference2));

    std::cout << "\n Разница между вторым и первым множествами: ";
    std::for_each(difference2.begin(), difference2.end(), print);
    return 0;
}
