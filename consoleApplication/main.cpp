#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

/*
 * Тестовая программа, выводящая рандомную строку раз в секунду
*/

int main(int argc, char *argv[]) {
    std::srand(std::time(0));

    std::vector<std::string> strings = {
        "Привет, мир!",
        "Случайная строка",
        "Бесконечный вывод",
        "C++ консольное приложение",
        "Секундное обновление",
        "Двойная \n строка",
        "Error: строка с ошибкой"
    };

    while (true) {
        int index = rand() % strings.size();

        std::cout << strings[index] << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
