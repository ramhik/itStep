////#include <iostream>
////#include <windows.h>
////#include <io.h>
////#include <stdio.h>
////#include "files.h"
////using namespace std;
////
//////Функция копирования файла
////bool CopyFile(char* source, char* destination) {
////
////    const int size = 65536;
////    FILE* src, * dest;
////
////    //Открытие Файла
////
////    if (!(src = fopen(source, "rb"))) {
////        return false;
////    }
////
////    //Получение дескриптора файла
////
////    int handle = _fileno(src);
////    //выделение памяти под буффер
////    char* data = new char[size];
////    if (!data) {
////        return false;
////    }
////    //Открытие файла, куда будет производиться копирование
////    if (!(dest = fopen(destination, "wb"))) {
////        delete[]data;
////        return false;
////    }
////    int realsize;
////    while (!feof(src)) {
////        //Чтение данных из файла
////        realsize = fread(data, sizeof(char), size, src);
////        //Запись данных в файл
////        fwrite(data, sizeof(char), realsize, dest);
////    }
////    //Закрытие файлов
////    fclose(src);
////    fclose(dest);
////    return true;
////}
////
//
//int main() {
//    setlocale(LC_ALL, "rus");
//   /* const char* sourse = "text_from.txt";
//    const char* destination = "test_to.txt";
//
//    try
//    {
//        CopyFile(sourse, destination);
//    }
//    catch (exception& exp)
//    {
//        cout << "Error in CopyFile -> " << exp.what() << endl;
//    }*/
//   /* try
//    {
//        char source[_MAX_PATH];
//        char destination[_MAX_PATH];
//        char answer[20];
//
//        cout<<"\nВведите путь и название копируемого файлу : \n";
//        cin.getline(source, _MAX_PATH);
//        if (_access(source, 00) == -1) {
//            throw("\nУказан неверный путь или название файла\n");
//        }
//        cout<<"\nВведите путь и название нового файла:\n";
//        cin.getline(destination, _MAX_PATH);
//        if (_access(destination, 00) == 0) {
//            cout<<"\nТакой Файл уже существует перезаписать его(1 - Да / 2 - Нет) ? \n";
//            cin.getline(answer, 20);
//            if (!strcmp(answer, "2")) {
//                throw("\nОперация отменена\n");
//            }
//            else if (strcmp(answer, "1")) {
//                throw("\nНеправильный ввод\n");
//            }
//            if (_access(destination, 02) == -1) {
//                throw("\nНет доступа к записи.\n");
//            }
//        }
//        if (!CopyFile(source, destination)) {
//            throw("\nОшибка при работе с файлом\n");
//        }
//    }
//    catch (exception& exp) {
//        cout << "Error in Copy file ->" << exp.what() << endl;
//    }*/
//
//}
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <time.h>
#include <sys\locking.h>
#include <string.h>
#include <ctype.h>
using namespace std;
//Максимальная длина слова
#define MAX_WORD_LENGTH 21
//Кол-во попыток
int Tries = 6;
//Кол-во угаданных слов
int CountWords = 0;
//Загрузка слова
bool LoadWord(FILE* file, char* word)
{
	int i = 0;
	char s[MAX_WORD_LENGTH] = { 0 };
	//Кол-во слов в файле
	static int count = -1;
	if (count == -1)
	{
		//Подсчет количества слов
		while (!feof(file))
		{
			fgets(s, MAX_WORD_LENGTH, file);
			count++;
		}
		//Слов нет?
		if (count == 0)
			return false;
		//Возврат файлового указателя в начало файла 
		fseek(file, 0, 0);
	}
	//Случайное слово
	int n = rand() % count;
	//Поиск слова
	while (i <= n)
	{
		fgets(s, MAX_WORD_LENGTH, file);
		i++;
	}
	//Определяем длину слова
	int wordlen = strlen(s);
	//Минимальная длина слова 2 буквы
	if (wordlen <= 1)
		return false;
	//Убираем Enter (в DOS'е 2 байта 13 10)
	if (s[wordlen - 1] == 10)
		s[wordlen - 2] = 0;
	else if (s[wordlen - 1] == 13)
		s[wordlen - 1] = 0;
	//Копируем слово
	strcpy(word, s);
	//Получаем дескриптор файла
	int hFile = _fileno(file);
	//Вычисляем размер файла
	int size = _filelength(hFile);

	//Блокировка файла
	fseek(file, 0, 0);
	_locking(hFile, _LK_NBLCK, size);
	return true;
}
//Игра
void Game(char* word)
{
	//Перевод в большие буквы
	strupr(word);
	int len = strlen(word);
	//Строка-копия
	char* copy = new char[len + 1];
	memset(copy, '*', len);
	copy[len] = 0;
	//Алфавит + пробелы
	char letters[52];
	int i, j = 0;
	for (i = 0; i < 26; i++)
	{
		letters[j++] = i + 'A';
		letters[j++] = ' ';
	}
	//Замыкающий ноль
	letters[51] = 0;
	//Буква
	char letter;
	char* pos;
	bool replace = false;
	do {
		//Очистка экрана
		system("cls");
		cout << copy << endl << endl;
		cout << letters << endl << endl;
		cout << "Count of tries: " << Tries << endl << endl;
			if (Tries == 6) {
				cout << " $$$$$$$$$$$$$$$$$$$$$$\n";
				cout << " $                    $\n";
				cout << endl;
			}
			else if (Tries == 5) {
				cout << "        $$$$$$$$$$$$$$\n";
				cout << "		     $\n";
				cout << "		     $\n";
				cout << "		     $\n";
				cout << "		     $\n";
				cout << "		     $\n";
				cout << " $$$$$$$$$$$$$$$$$$$$$\n";
				cout << " $                   $\n";
				cout << endl;
			}
			else if (Tries == 4) {
				cout << "       $$$$$$$$$$$$$$$$\n";
				cout << "	|	      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << " $$$$$$$$$$$$$$$$$$$$$$\n";
				cout << " $                    $\n";
				cout << endl;
			}
			else if (Tries == 3) {
				cout << "       $$$$$$$$$$$$$$$$\n";
				cout << "	|	      $\n";
				cout << "	0	      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << " $$$$$$$$$$$$$$$$$$$$$$\n";
				cout << " $                    $\n";
				cout << endl;
			}
			else if (Tries == 2) {
				cout << "       $$$$$$$$$$$$$$$$\n";
				cout << "	|	      $\n";
				cout << "	0	      $\n";
				cout << "  / |  \\       $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << "		      $\n";
				cout << " $$$$$$$$$$$$$$$$$$$$$$\n";
				cout << " $                    $\n";
				cout << endl;
			}
		cout << "Input any letter:\t";
		cin >> letter;
		//Звуковой сигнал
		Beep(500, 200);
		//if(letter >= 'A' && letter <= 'Z'
		//|| letter >= 'a' && letter <= 'z')
		//Буква?
		if (!isalpha(letter))
		{
			cout << "It's not a letter" << endl;
			//Задержка на 1 секунду
			Sleep(1000);
			continue;
		}
		//Перевод буквы в большую
		letter = toupper(letter);
		//Поиск буквы в алфавите
		pos = strchr(letters, letter);
		//Такая буква уже была
		if (pos == 0)
		{
			cout << "This letter have been already pressed" << endl;
				Sleep(1000);
			continue;
		}
		else
		{
			//Убираем букву из алфавита 
			pos[0] = ' ';
		}
		//Поиск буквы в слове
		for (i = 0; i < len; i++)
		{
			if (word[i] == letter)
			{
				copy[i] = letter;
				replace = true;
			}
		}
		if (replace == false)
			Tries--;
		else
			replace = false;
		//Условие победы
		if (strcmp(word, copy) == 0)
		{
			system("cls");
			cout << copy << endl << endl;
			cout << letters << endl << endl;
			cout << "Count of tries: " << Tries <<
				endl << endl;
			cout << "Congratulation !!!" << endl;
			CountWords++;
			break;
		}
	} while (Tries != 0);
	delete[] copy;
}

void main()
{
	//Открываем файл на чтение в двоичном режиме 
	FILE* f = fopen("E:\\test.txt", "rb");
	//Если файл не открылся
	if (f == 0)
	{
		//Ошибка
		perror("Open");
		return;
	}
	srand(time(0));
	char Word[20];
	//Пытаемся загрузить слово
	if (!LoadWord(f, Word))
	{
		//Если неудачно
		cout << "Error !!!" << endl;
		fclose(f);
		return;
	}
	char answer;
	//Играем, пока не надоест
	do
	{
		Game(Word);
		//Если попыток не осталось, то выход
		if (Tries == 0)
		{
			cout << "Count of words: " << CountWords << endl;
			cout << "Bye-bye" << endl;
			break;
		}
		//Если остались
		cout << "Continue ??? (Y/N)\t";
		cin >> answer;
		//Еще играем?
		if (answer == 'Y' || answer == 'y')
			if (!LoadWord(f, Word))
			{
				cout << "Error !!!" << endl;
				fclose(f);
				return;
			}
	} while (answer == 'Y' || answer == 'y');
	//получаем дескриптор
	int hFile = _fileno(f);
	//Разблокировка файла
	int size = _filelength(hFile);
	fseek(f, 0, 0);
	_locking(hFile, _LK_UNLCK, size);
	fclose(f);
}