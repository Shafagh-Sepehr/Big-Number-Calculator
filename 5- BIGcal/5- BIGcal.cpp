//chon str az gens pointer hast va faghat address on yeki str ro save mikone. baraye copy meghdar str-e vorodi bayad this.str ro new card va maghadir ro tosh copy kard


#include <iostream>
#include <limits.h>
#pragma warning(disable:4996)
using namespace std;


#define SIZE 150//not so important, set it to 0 and nothing'l go wrong
#define MUL_MAX_SIZE SIZE

int get_int_len(long long int num) {
	int len = 0;
	while (num) {
		num /= 10;
		len++;
	}
	return len;
}

char* int_to_char(long long int num) {//you sould manually free the returned pointer's memory after use
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
	number() :str(new char[SIZE + 1]), size(0) { str[0] = '0'; str[1] = '\0'; }

	//constructor 2
	number(const char* s, int l) {

		size = l;

		if (strlen(str) != l) {
			cerr << "the number length isn't correct";
			exit(0);
		}

		str = new char[max(SIZE, l) + 1];
		strcpy(str, s);

	}

	//converting constructor
	number(const char* s) {
		str = new char[max((int)strlen(s), SIZE) + 1];
		strcpy(str, s);
		size = strlen(str);
	}

	//converting constructor
	number(long long num) {
		size = get_int_len(num);
		str = new char[SIZE + 1];
		char* num_str = int_to_char(num);
		strcpy(str, num_str);
		delete[] num_str;
	}

	//copy constructor
	number(const number& that) {
		str = new char[max(that.size, SIZE) + 1];
		size = that.size;
		strcpy(this->str, that.str);
	}

	//destructor
	~number() { delete[] str; }

	//copy(=)
	number operator=(const number& that) {
		size = that.size;
		if (size > SIZE) {
			str = new char[size + 1];
		}
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


	operator string() { return string(str); }

	number operator+(const number that) const {

		char* ans = sum(this->str, that.str);
		number to_return(ans);
		delete[] ans;
		return to_return;
	}


	number operator-(const number that) const {

		char* ans = sub(this->str, that.str);
		number to_return(ans);
		delete[] ans;
		return to_return;
	}


	number operator*(const number that) const {

		char* ans = mul(this->str, that.str);
		number to_return(ans);
		delete[] ans;
		return to_return;
	}


	number& operator-=(const number that) {
		(*this) = (*this) - that;
		return *this;
	}

	number& operator+=(const number that) {
		(*this) = (*this) + that;
		return *this;
	}

	number& operator*=(const number that) {
		(*this) = (*this) * that;
		return *this;
	}


	int operator<=(const number that)const {
		if (this->size < that.size)
			return 1;
		else if (this->size > that.size)
			return 0;
		else
			for (int i = 0; i < size; i++)
				if ((*this)[i] == that[i])
					continue;
				else if ((*this)[i] < that[i])
					return 1;
				else
					return 0;
		return 1;
	}
	int operator>=(const number that)const {
		if (this->size < that.size)
			return 0;
		else if (this->size > that.size)
			return 1;
		else
			for (int i = 0; i < size; i++)
				if ((*this)[i] == that[i])
					continue;
				else if ((*this)[i] < that[i])
					return 0;
				else
					return 1;
		return 1;
	}
	int operator<(const number that)const {
		if (this->size < that.size)
			return 1;
		else if (this->size > that.size)
			return 0;
		else
			for (int i = 0; i < size; i++)
				if ((*this)[i] == that[i])
					continue;
				else if ((*this)[i] < that[i])
					return 1;
				else
					return 0;
		return 0;
	}
	int operator>(const number that)const {
		if (this->size < that.size)
			return 0;
		else if (this->size > that.size)
			return 1;
		else
			for (int i = 0; i < size; i++)
				if ((*this)[i] == that[i])
					continue;
				else if ((*this)[i] < that[i])
					return 0;
				else
					return 1;
		return 0;
	}


	/*number operator+(long long num) const {

		char* num_str = int_to_char(num);
		char* ans = sum(this->str, num_str);
		number to_return(ans);
		delete[] ans;
		delete[] num_str;
		return to_return;
	}*/
	;
	/*number operator-(long long num) const {

			char* num_str = int_to_char(num);
			char* ans = sub(this->str, num_str);
			number to_return(ans);
			delete[] ans;
			delete[] num_str;
			return to_return;
		}*/
	;
	/*number operator*(long long num) const {

				char* num_str = int_to_char(num);
				char* ans = mul(this->str, num_str);
				number to_return(ans);
				delete[] ans;
				delete[] num_str;
				return to_return;
			}*/
	;
	/*int operator<=(long long num) const {
				char* num_str = int_to_char(num);
				int num_len = get_int_len(num);
				int ans = -1;
				if (this->size < num_len) {
					ans = 1;
				}
				else if (this->size > num_len)
					ans = 0;
				else
					for (int i = 0; i < size; i++)
						if ((*this)[i] == num_str[i])
							continue;
						else if ((*this)[i] < num_str[i])
							ans = 1;
						else
							ans = 0;
				if (ans == -1)
					ans = 1;
				delete[] num_str;
				return ans;
			}*/
	;
	/*int operator>=(long long num) const {
				char* num_str = int_to_char(num);
				int num_len = get_int_len(num);
				int ans = -1;
				if (this->size < num_len)
					ans = 0;
				else if (this->size > num_len)
					ans = 1;
				else
					for (int i = 0; i < size; i++)
						if ((*this)[i] == num_str[i])
							continue;
						else if ((*this)[i] < num_str[i])
							ans = 0;
						else
							ans = 1;
				if (ans == -1)
					ans = 1;
				delete[] num_str;
				return ans;
			}*/
	;
	/*int operator<(long long num) const {
				char* num_str = int_to_char(num);
				int num_len = get_int_len(num);
				int ans = -1;
				if (this->size < num_len)
					ans = 1;
				else if (this->size > num_len)
					ans = 0;
				else
					for (int i = 0; i < size; i++)
						if ((*this)[i] == num_str[i])
							continue;
						else if ((*this)[i] < num_str[i])
							ans = 1;
						else
							ans = 0;
				if (ans == -1)
					ans = 0;
				delete[] num_str;
				return ans;
			}*/
	;
	/*int operator>(long long num) const {
				char* num_str = int_to_char(num);
				int num_len = get_int_len(num);
				int ans = -1;
				if (this->size < num_len)
					ans = 0;
				else if (this->size > num_len)
					ans = 1;
				else
					for (int i = 0; i < size; i++)
						if ((*this)[i] == num_str[i])
							continue;
						else if ((*this)[i] < num_str[i])
							ans = 0;
						else
							ans = 1;
				if (ans == -1)
					ans = 0;
				delete[] num_str;
				return ans;
			}*/



	char* get_num_str() { return str; }




	//you sould manually free the returned pointer's memory for bellow methods after use
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
		int len1, len2, temp, cIndex, ctr0 = 0, new_size;

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
		new_size = max(len1 * 2 + 5, MUL_MAX_SIZE);


		char* tempstr;
		char* ans = new char[new_size];

		char* cp;

		ans[0] = '0';
		ans[0] = '\0';

		short strg = 0;




		for (int n = len2 - 1; n >= 0; n--, ctr0++) {//b[n]

			cIndex = new_size - 2;
			cp = new char[new_size]();
			tempstr = new char[new_size + 1]();
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

number operator+(long long num, const number num_obj) { return num_obj + num; }
number operator-(long long num, const number num_obj) { return num_obj - num; }
number operator*(long long num, const number num_obj) { return num_obj * num; }
int operator<=(long long num, const number num_obj) { return num_obj >= num; }
int operator>=(long long num, const number num_obj) { return num_obj <= num; }
int operator<(long long num, const number num_obj) { return num_obj > num; }
int operator>(long long num, const number num_obj) { return num_obj < num; }


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
	cout << h << " * " << i << " = " << h * i << endl << endl;

	number z1("5"), z2("555"), z3("545"), z4("555");
	cout << (z1 < z2) << endl;
	cout << (z1 > z2) << endl;
	cout << (z2 < z4) << endl;
	cout << (z2 <= z4) << endl;
	cout << (z2 >= z4) << endl;
	cout << (z2 > z3) << endl << endl;

	cout << (z1 < 555) << endl;
	cout << (5 > z2) << endl;
	cout << (555 < z4) << endl;
	cout << (z2 <= 555) << endl;
	cout << (z2 >= 555) << endl;
	cout << (555 > z3) << endl << endl;

	number x(10), x1(5), x2(2);

	(x -= x1) -= x2;
	cout << x << endl << x1 << endl << x2 << endl << endl;

	number y("50000000000000000000002");
	cout << string(y) << endl << endl;

	number f1("3348643512315"), f2("87897846551331"), f3("32132131654777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777776122222222222222222221254576456222222222234534313498745321321564"), f4("1321320654987645541326412312312333333333333333333333337777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777612222222222222222222125457645777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777761222222222222222222212545764533333333333333123123123123131233654984651245467943");

	cout << (f3 *= f4 -= f1 += f2) << endl << endl;
	return 0;
}

