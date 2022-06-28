#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <vector>
#include <queue>
using namespace std;

int begin_index, end_index, counter = 0;

int** newroads(int n) // создаем и заполняем случайным образом матрицу дорог (0/1)
{
	int** mas;
	mas = new int* [n];
	for (int i = 0; i < n; i++)mas[i] = new int[n];
	int counter = n / 2 + 1;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
		{
			bool flag = 0;
			if (i == j)mas[i][j] = 0;
			else if (counter > 0)flag = -1 + rand() % 2;
			mas[i][j] = mas[j][i] = flag;
		}
	return mas;
}

void displayroads(int** mas, int n) //вывод таблицы смежности на экран 
{
	char letter = 'A';
	cout << "  ";
	for (int i = 0; i < n; i++) {
		cout << letter << " ";
		letter++;
	}
	cout << endl;
	letter = 'A';
	for (int i = 0; i < n; i++) {
		cout << letter << " ";
		for (int j = 0; j < n; j++)
			cout << mas[i][j] << " ";
		letter++;
		cout << endl;
	}
	cout << endl << endl;
}

bool travel(int** mas, int n)
{
	vector<bool> used(n);// ставим метку, те мы на эту дорогу заходили 
	vector<int> from(n);// весь путь 
	queue<int> q;// очередь, в которую из матрицы записываем города

	q.push(begin_index);//начинаем (кладем первый город)
	from[begin_index] = -1;
	used[begin_index] = 1;

	while (!q.empty()) { // если пройдем весь путь, то очередь будет пустой, и тогда заканчиваем 
		int t = q.front(); // обращаемся к первому элементу очереди
		q.pop(); // удаляем первый элемент очереди
		for (int i = 0; i < n; ++i)if (!used[i] && mas[t][i]) { //если вершина не использовалась и в матрице не ноль
			used[i] = 1;//помечаем что зашли
			q.push(i); // добавления в очередь нового элемента (след город)
			from[i] = t; // путь по городам запоминаем во фром 
		}
	}
	if (end_index == begin_index) return 1;// если одинаковые 
	if (!used[end_index])return 0;//если в конечной точке ноль, значит мы не дошли 
	vector<int>ans; //вектор, в кот хранится путь кратчайший, из фром копируем,  изменяя значения
	for (int i = end_index; ; ) {
		if (i == -1)break;
		ans.push_back(from[i] + 1); //вставляем в конец 
		i = from[i];
	}
	if (!(ans.size() - 1))return 1; // на пустоту проверка 
}
bool recursion(int** mas, int n, int i = 0, int j = 0)
{
	for (; i < n; i++)
	{
		for (; j < n; j++)
		{
			if (counter < 4 && mas[i][j])
			{
				counter += 1;
				mas[i][j] = mas[j][i] = 0;//тк дороги зеркальны 
				if (travel(mas, n))recursion(mas, n, i, j + 1);//трэвэл проверяет можем ли мы идти и заново начинаем 
				else return 1;
				counter -= 1;// на один шаг назад возвращаемся 
				mas[i][j] = mas[j][i] = 1;//возвращаем значение дороге, если не нашли путь 
			}
		}
	}
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int N;
	do {
		if (counter > 0)cout << "Неккоректный ввод!";
		cout << "Введите кол-во дорог (не менее 5):";
		cin >> N;
		counter++;
	} while (N <= 4);
	int** roads = newroads(N);
	cout << "Построена сиситема дорог" << endl;
	displayroads(roads, N);

	cout << "Введите начальный город: "; cin >> begin_index;
	cout << "Введите конечный город: "; cin >> end_index;
	begin_index -= 1;
	end_index -= 1;
	counter = 0;
	if (recursion(roads, N)) {
		cout << "Задание выполнено успешно!Получена новая система дорог:" << endl;
		displayroads(roads, N);
	}
	else cout << "Для данной системы дорог задача не выполнима!";

	cout << endl << endl;
	for (int i = 0; i < N; i++)delete[] roads[i];
	delete[] roads;
	system("pause");
	return 1;
}