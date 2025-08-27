/************************************************************************************************************************************************/
/* Удобное архивирование для командной строки                                                                                                   */
/* 14-08-2005                                                                                                                                   */
/* Visual Studio C++ 2022                                                                                                                       */
/************************************************************************************************************************************************/

#include <iostream>
#include <Windows.h>
#include <stdlib.h >
#include <fstream>
#include <filesystem>

#pragma warning(disable: 4996) //_CRT_SECURE_NO_WARNINGS

using namespace std;

/***********************************************************************************************************************************************
 *** Показываем сообщение на экране /
 ***********************************************************************************************************************************************/
static void ShowMessage(string msg) {
    std::cout << "*****************************************************************************************************************************\n";
    std::cout << msg << endl;
    std::cout << "*****************************************************************************************************************************\n";
}

int main(int argc, char* argv[]) {

    /* очищаем экран (clean screen) */
    system("cls");
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    time_t t = time(0); // get time now
    struct tm* now = localtime(&t);
    char buffer[80];
    strftime(buffer, 80, "%d-%m-%Y @ %H-%M", now);
    std::cout << buffer << endl;

    /* разбор командной строки (command line parsing) */
    if (argc == 1) { // если в аргументах только имя программы
        ShowMessage("There are not enough parameters to execute... (не хватает параметров для выполнения!)");
        system("pause");
        exit(EXIT_FAILURE); // or  EXIT_FAILURE or EXIT_SUCCESS
    }

    string path_dest, path_source;
    /* разбор командной строки (путь к архиву) */
    if (argc >= 2) { // значит есть аргументы
        path_dest = argv[1];
    }

    /* разбор командной строки (то что надо архивировать) */
    if (argc >= 3) { // значит есть аргументы
        path_source = argv[2];
        std::cout << path_source << endl;
    }

    /* проверяем является ли путь к архиву абсолютным, находи в имени архива подстроку ":\" */
    /* работает */
    if (path_dest.find(":\\") == std::string::npos) // если не найдено (константа std::string::npos) добавляем путь
    {
        string tmp = path_dest;
        path_dest = "D:\\" + tmp;
        std::cout << "dest-->" + path_dest + "\n" + "source -->" + path_source + "\n";
    }

    std::string program = "7z.exe ";
    std::string parameters = " u -bsp1 -ssw " + path_dest + " " + "G:\\!Arc";

    std::string command = program + " " + parameters;
    std::cout << command + "\n";

    int result = system(command.c_str());
    return 0;
}

