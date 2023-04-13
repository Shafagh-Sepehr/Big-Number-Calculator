//chon str az gens pointer hast va faghat address on yeki str ro save mikone. baraye copy meghdar str-e vorodi bayad this.str ro new card va maghadir ro tosh copy kard
#include <iostream>
#include <limits.h>
#pragma warning(disable:4996)
using namespace std;
#define SIZE 101

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
	number() :str(new char[SIZE]), size(0) { str[0] = '0'; str[1] = '\0'; }

	number(const char* s, int l) :str(new char[SIZE]), size(l) {
		strcpy(str, s);
		if (strlen(str) != l) {
			cerr << "the number length isn't correct";
			exit(0);
		}
	}

	number(const char* s) :str(new char[SIZE]) { strcpy(str, s); size = strlen(str); }

	number(number& that) : str(new char[SIZE]), size(that.size) { strcpy(this->str, that.str); }


	~number() { delete[] str; }

	number operator=(const number& that) {
		size = that.size;
		strcpy(this->str, that.str);
		return *this;
	}

	int operator== (number that) const {
		if (this->size != that.size || strcmp(this->str, that.str)/*!=0*/)
			return 0;
		else
			return 1;
	}

	int operator[](int i) const { return str[i]; }

	number& operator+(const number that) {

		char* ans = sum(this->str, that.str);
		number* to_return = new number(ans);
		delete[] ans;
		return *to_return;
	}

	number& operator+(long long int num) {

		char* num_str = int_to_char(num);
		char* ans = sum(this->str, num_str);
		number* to_return = new number(ans);
		delete[] ans;
		delete[] num_str;
		return *to_return;
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



	char* get_num_str() { return str; }
};

number& operator+(long long num, number num_obj) {
	return num_obj + num;
}


int main() {

	number a("9");
	number b("81565191561");
	number c = a + b;
	cout << a.get_num_str() << " + " << b.get_num_str() << " = " << c.get_num_str();

	number d, e;
	d = 9 + a;
	e = a + 9;






	return 0;
}

