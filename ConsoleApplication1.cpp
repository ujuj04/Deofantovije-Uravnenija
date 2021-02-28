#include <iostream>
using namespace std;

int abs(int a) 
{
	if (a < 0)
		return -a;
	return a;
}

int max(int a, int b) 
{
	if (a > b)
		return a;
	return b;
}

int min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

void swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

int evklid(int a, int b, int& x, int& y) 
{
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = evklid(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool f_p(int a, int b, int c, int& x0, int& y0, int& g) 
{
	g = evklid(abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)   x0 *= -1;
	if (b < 0)   y0 *= -1;
	return true;
}

void change(int& x, int& y, int a, int b, int c) 
{
	x += c * b;
	y -= c * a;
}

int check(int a, int b, int c, int min_x, int max_x, int min_y, int max_y) 
{
	int x, y, g;
	if (!f_p(a, b, c, x, y, g))
		return 0;
	a /= g;  b /= g;

	int b1 = a > 0 ? +1 : -1;
	int b2 = b > 0 ? +1 : -1;

	change(x, y, a, b, (min_x - x) / b);
	if (x < min_x)
		change(x, y, a, b, b2);
	if (x > max_x)
		return 0;
	int l_temp1 = x;

	change(x, y, a, b, (max_x - x) / b);
	if (x > max_x)
		change(x, y, a, b, -b2);
	int r_temp1 = x;

	change(x, y, a, b, -(min_y - y) / a);
	if (y < min_y)
		change(x, y, a, b, -b1);
	if (y > max_y)
		return 0;
	int l_temp2 = x;

	change(x, y, a, b, -(max_y - y) / a);
	if (y > max_y)
		change(x, y, a, b, b1);
	int r_temp2 = x;

	if (l_temp2 > r_temp2)
		swap(l_temp2, r_temp2);
	int left = max(l_temp1, l_temp2);
	int right = min(r_temp1, r_temp2);

	cout << "Вывод по X: " << endl;
	for (int j = right; j <= left; j++) 
	{
		for (int i = min_y; i < max_y; i++) 
		{
			if (((a * i) + (b * j)) == c) 
				cout << "x: " << i << "    " << "y: " << j << endl;
		}
	}

	cout << "Вывод по Y: " << endl;
	for (int i = right; i <= left; i = i + 1) 
	{
		for (int j = min_y; j < max_y; j = j + 1) 
		{
			if (((a * i) + (b * j)) == c)
				cout << "x: " << i << "    " << "y: " << j << endl;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int a, b, c, min_x, max_x, min_y, max_y;
	cout << "Поиск корней диофантового уравнения" << endl;
	cout << "Вид: ax + by = c"<< endl << "Введите a:" << endl;
	cin >> a;
	cout << "Введите b:" << endl;
	cin >> b;
	cout << "Введите c:" << endl;
	cin >> c;
	cout << "Промежутки на которых будут искаться корни " << endl <<  "x - мин" << endl;
	cin >> min_x;
	cout << "x - макс" << endl;
	cin >> max_x;
	cout << "y - мин" << endl;
	cin >> min_y;
	cout << "y - макс" << endl;
	cin >> max_y;
	
	if ((a == 0) & (b == 0)) {
		cout << "uncertainty: a=b=0";
		return 0;
	}
	if (((a == 0) & (b != 0))) {
		if (((min_x <= (c / b)) & (max_x >= (c / b))) & (c % b == 0)) {
			cout << "x: " << c / b << "    " << "y: " << 0;
			return 0;
		}
		return 0;
	}
	else if (((a != 0) & (b == 0))) {
		if (((min_y <= (c / a)) & (max_y >= (c / a))) & (c % a == 0)) {
			cout << "x: " << 0 << "    " << "y: " << c / a;
			return 0;
		}
		return 0;
	}
	else {
		check(a, b, c, min_x, max_x, min_y, max_y);
	}
}
