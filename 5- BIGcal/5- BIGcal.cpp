//chon str az gens pointer hast va faghat address on yeki str ro save mikone. baraye copy meghdar str-e vorodi bayad this.str ro new card va maghadir ro tosh copy kard
#include <iostream>
#include <limits.h>
#pragma warning(disable:4996)
using namespace std;
#define SIZE 150
#define MUL_MAX_SIZE SIZE*2

int get_int_len(long long int num) {
	int len = 0;
	while (num) {
		num /= 10;
		len++;
	}
	return len;
}

char* int_to_char(long long int num) {
	int len = get_int_len(num);
	char* str = new char[len + 2];
	for (int i = 0; i < len; i++) {
		str[len - 1 - i] = num % 10 + '0';
		num /= 10;
	}
	str[len] = '\0';
	return str;

}


class number {
private:
	char* str;
	int size;
public:
	//constructor 1
	number() :str(new char[SIZE]), size(0) { str[0] = '0'; str[1] = '\0'; }

	//constructor 2
	number(const char* s, int l) {

		size = l;

		if (strlen(str) != l) {
			cerr << "the number length isn't correct";
			exit(0);
		}

		str = new char[max(SIZE, l)];
		strcpy(str, s);

	}

	//constructor 3
	number(const char* s) {
		str = new char[max((int)strlen(s), SIZE)];
		strcpy(str, s);
		size = strlen(str);
	}

	//copy constructor
	number(const number& that) {
		str = new char[max(that.size, SIZE)];
		size = that.size;
		strcpy(this->str, that.str);
	}

	//destructor
	~number() { delete[] str; }

	//copy(=)
	number operator=(const number& that) {
		size = that.size;
		strcpy(this->str, that.str);
		return *this;
	}

	//assign(=)
	int operator== (number that) const {
		if (this->size != that.size || strcmp(this->str, that.str)/*!=0*/)
			return 0;
		else
			return 1;
	}

	//return i-th digit from left
	int operator[](int i) const {
		if (i >= 0 && i < size)
			return str[i];
		else
			return -1;
	}


	number operator+(const number that) const {

		char* ans = sum(this->str, that.str);
		number to_return(ans);
		delete[] ans;
		return to_return;
	}
	number operator+(long long num) const {

		char* num_str = int_to_char(num);
		char* ans = sum(this->str, num_str);
		number to_return(ans);
		delete[] ans;
		delete[] num_str;
		return to_return;
	}



	number operator-(const number that) const {

		char* ans = sub(this->str, that.str);
		number to_return(ans);
		delete[] ans;
		return to_return;
	}
	number operator-(long long num) const {

		char* num_str = int_to_char(num);
		char* ans = sub(this->str, num_str);
		number to_return(ans);
		delete[] ans;
		delete[] num_str;
		return to_return;
	}

	number operator*(const number that) const {

		char* ans = mul(this->str, that.str);
		number to_return(ans);
		delete[] ans;
		return to_return;
	}
	number operator*(long long num) const {

		char* num_str = int_to_char(num);
		char* ans = mul(this->str, num_str);
		number to_return(ans);
		delete[] ans;
		delete[] num_str;
		return to_return;
	}

	char* get_num_str() { return str; }





	static char* sub(char* a, char* b) {




		int len1, len2, temp;

		bool cond = false;

		len1 = strlen(a);
		len2 = strlen(b);

		if (len2 > len1) {


			char* temp = a;
			a = b;
			b = temp;
			int tmp = len2;
			len2 = len1;
			len1 = tmp;
		}
		if (len2 == len1) {
			for (int p = 0; p < len1; p++) {
				if (a[p] == b[p]) {
					continue;
				}
				else if (a[p] < b[p]) {
					char* temp = a;
					a = b;
					b = temp;
					int tmp = len2;
					len2 = len1;
					len1 = tmp;
					break;
				}
				else
					break;

			}

		}


		char* ans = new char[len1 + 2];


		if (!strcmp(a, b)) {
			ans[0] = '0';
			ans[1] = '\0';

			return ans;
		}
		else {
			ans[len1] = '\0';
			for (int n = len1 - 1, m = len2 - 1; n >= 0; n--, m--) {
				if (m >= 0) {
					temp = a[n] - b[m];
					if (cond) {
						temp -= 1;
						cond = false;
					}
					if (temp >= 0) {
						ans[n] = temp + '0';
					}
					else {
						cond = true;
						temp += 10;
						ans[n] = temp + '0';
					}
				}
				else {
					if (cond) {
						temp = a[n] - 1 - '0';
						cond = false;
						if (temp < 0) {
							cond = true;
							temp += 10;

						}
						ans[n] = temp + '0';

					}
					else {
						ans[n] = a[n];
					}

				}
			}





			ans[len1] = '\0';
			while (ans[0] - '0' == 0) {
				for (int k = 0; k < len1; k++) {
					ans[k] = ans[k + 1];

				}
			}

		}


		return ans;
	}
	static char* sum(char* a, char* b) {

		int len1, len2, temp;
		char* ans;
		bool overflow = false;

		len1 = strlen(a);
		len2 = strlen(b);
		if (len2 > len1) {


			char* temp = a;
			a = b;
			b = temp;
			int tmp = len2;
			len2 = len1;
			len1 = tmp;
		}
		ans = new char[len1 + 2];

		ans[len1 + 1] = '\0';
		for (int n = len1 - 1, m = len2 - 1; n >= 0; n--, m--) {
			if (m >= 0) {
				temp = a[n] + b[m] - '0' * 2;
				if (overflow) {
					temp += 1;
					overflow = false;
				}
				if (temp < 10) {
					ans[n + 1] = temp + '0';
				}
				else {
					overflow = true;
					temp -= 10;
					ans[n + 1] = temp + '0';
				}
			}
			else {
				if (overflow) {
					temp = a[n] + 1 - '0';
					overflow = false;
					if (temp > 9) {
						overflow = true;
						temp -= 10;

					}
					ans[n + 1] = temp + '0';

				}
				else {
					ans[n + 1] = a[n];
				}

			}
		}
		if (overflow)ans[0] = 1 + '0';
		else {
			for (int k = 0; k < len1; k++) {
				ans[k] = ans[k + 1];

			}
			ans[len1] = '\0';
		}

		return ans;

	}
	static char* mul(char* a, char* b) {

		char* tempstr;
		char* ans = new char[SIZE];

		char* cp;

		ans[0] = '0';
		ans[0] = '\0';
		int len1, len2, temp, cIndex = SIZE - 2, ctr0 = 0;
		short strg = 0;

		len1 = strlen(a);
		len2 = strlen(b);
		if (len2 > len1) {

			char* temp = a;
			a = b;
			b = temp;
			int tmp = len2;
			len2 = len1;
			len1 = tmp;
		}


		for (int n = len2 - 1; n >= 0; n--, ctr0++) {//b[n]

			cIndex = SIZE - 2;
			cp = new char[SIZE]();
			tempstr = new char[SIZE + 1]();
			if (ctr0)strcpy(cp, ans);


			for (int m = len1 - 1; m >= 0; m--) {//a[m]
				temp = (b[n] - '0') * (a[m] - '0');

				if (strg) { temp += strg; strg = 0; }

				if (temp > 9) {
					tempstr[cIndex] = temp % 10 + '0';
					cIndex--;
					strg = temp / 10;
				}
				else {
					tempstr[cIndex] = temp + '0';
					cIndex--;
				}

			}
			int limit = len1;
			if (strg) { tempstr[cIndex] = strg + '0'; strg = 0; cIndex--; limit++; }



			int counter = 0;
			for (int i = 0; tempstr[i] == NULL; i++) {
				counter++;
			}
			for (int k = 0; k < limit; k++) {
				tempstr[k] = tempstr[k + counter];

			}



			{
				int l = strlen(tempstr);
				tempstr[l + ctr0] = '\0';

				for (int p = 0; p < ctr0; p++) {

					tempstr[l + p] = '0';

				}
			}


			delete[] ans;
			ans = sum(tempstr, cp);
			delete[] tempstr;
			delete[] cp;
		}

		return ans;



	}
};

number operator+(long long num, const number num_obj) {
	return num_obj + num;
}

number operator-(long long num, const number num_obj) {
	return num_obj - num;
}
number operator*(long long num, const number num_obj) {
	return num_obj * num;
}

ostream& operator<<(ostream& out, number num_obj) {
	out << num_obj.get_num_str();
	return out;
}

int main() {

	number a("9");
	number b("81565191561");
	number c = a + 9;
	cout << a << " + " << b << " = " << c << endl;

	number d, e;
	d = 9 + a;
	e = d + 9;

	cout << 9 << " + " << a << " = " << d << endl;
	cout << d << " + " << 9 << " = " << e << endl;

	number f("10000"), g("5000");
	cout << f << " - " << g << " = " << f - g << endl;
	cout << g - f << endl;


	number h("11378975456"), i("1324679850");
	cout << h << " * " << i << " = " << h * i << endl;



	return 0;
}

