//chon str az gens pointer hast va faghat address on yeki str ro save mikone. baraye copy meghdar str-e vorodi bayad this.str ro new card va maghadir ro tosh copy kard


#include <iostream>
#include <limits.h>
#include <string>
#include <string.h>
#include <sstream>
#pragma warning(disable:4996)
using namespace std;

#define SIZE 1500
#define MUL_MAX_SIZE SIZE*2



void khikhi(char* khi, int a) {
	khi[a - 1] = khi[a];

}

int mypow(unsigned long long int a, unsigned long long int b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	return a * mypow(a, b - 1);
}

int get_int_len(long long int num) { return to_string(num).length(); }

char* int_to_char(long long int num) {//you sould manually free the returned pointer's memory after use
	stringstream box;
	box << num;
	char* str = new char[get_int_len(num) + 2];
	box >> str;
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
		size = strlen(s);
		str = new char[max(size, SIZE) + 1];
		strcpy(str, s);

	}

	//converting constructor
	number(const string s) {
		size = s.length();
		str = new char[max(size, SIZE) + 1];
		strcpy(str, s.c_str());
	}

	//converting constructor
	number(long long num) {
		size = get_int_len(num);
		str = new char[SIZE + 1];
		char* num_str = int_to_char(num);
		strcpy(str, num_str);
		delete[] num_str;
	}

	//converting constructor for 0
	number(int num) {
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

	//compare(=)
	int operator== (number that) const {
		if (this->size != that.size || strcmp(this->str, that.str)/*!=0*/)
			return 0;
		else
			return 1;
	}


	int operator!= (number that) const {
		if (this->size != that.size || strcmp(this->str, that.str)/*!=0*/)
			return 1;
		else
			return 0;
	}

	//return i-th digit from left
	int operator[](int i) const {
		if (i >= 0 && i < size)
			return str[i] - '0';
		else
			return -1;
	}


	explicit operator string() const { return string(str); }
	explicit operator long long int() const {
		number temp = (*this) % LLONG_MAX;
		long long num;
		stringstream box;
		box << temp.get_num_str();
		box >> num;
		return num;
	}

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
	number operator/(const number that) const {

		char* ans = div(this->str, that.str);
		number to_return(ans);
		delete[] ans;
		return to_return;
	}
	number operator%(const number that) const {
		number to_return = (*this) - (that * ((*this) / that));
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
	number& operator/=(const number that) {
		(*this) = (*this) / that;
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

	const number operator--() {
		(*this) -= 1;
		return (*this);
	}
	const number operator--(int) {
		(*this) -= 1;
		return (*this);
	}
	const number operator++() {
		(*this) += 1;
		return (*this);
	}
	const number operator++(int) {
		(*this) += 1;
		return (*this);
	}

	number operator>>(int a)const {
		int to_be_dived_by = mypow(2, a);
		number to_be_returned = (*this) / to_be_dived_by;
		return to_be_returned;
	}
	number operator>>=(int a) {
		int to_be_dived_by = mypow(2, a);
		(*this) = (*this) / to_be_dived_by;
		return (*this);
	}
	number operator<<(int a)const {
		int to_be_dived_by = mypow(2, a);
		number to_be_returned = (*this) * to_be_dived_by;
		return to_be_returned;
	}
	number operator<<=(int a) {
		int to_be_dived_by = mypow(2, a);
		(*this) = (*this) * to_be_dived_by;
		return (*this);
	}


	//READ
	//bellow are operator+,-,*,/,>,<,<=,>= overloaded for long long int,
	//but as the convertor constructor converts long long these aren't necessary anymore
	//age bekhtere naboodeshon nomre kam kardin pasesh bdin :))
	/*number operator+(long long num) const {

		char* num_str = int_to_char(num);
		char* ans = sum(this->str, num_str);
		number to_return(ans);
		delete[] ans;
		delete[] num_str;
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

	number operator*(long long num) const {

		char* num_str = int_to_char(num);
		char* ans = mul(this->str, num_str);
		number to_return(ans);
		delete[] ans;
		delete[] num_str;
		return to_return;
	}

	int operator<=(long long num) const {
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
	}

	int operator>=(long long num) const {
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
	}

	int operator<(long long num) const {
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
	}

	int operator>(long long num) const {
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



	char* get_num_str() const { return str; }




	//you sould manually free the returned pointer's memory for bellow methods after use
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
	static char* mul(char* a, char* b) {

		if (!strcmp(a, "0") || !strcmp(b, "0")) {
			char* ans = new char[SIZE];
			ans[0] = '0';
			ans[1] = '\0';
			return ans;
		}


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
		ans[1] = '\0';

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
	static char* div(char* a, char* b) {

		if (strcmp("0", b) == 0) {
			cerr << "!!!!!!! division by zero !!!!!!! ERROR";
			exit(0);
		}


		char* fin = new char[SIZE];
		char* save = new char[SIZE];
		char* fi = new char[SIZE];
		char* ficop = new char[SIZE];
		char* ofasele = new char[SIZE];
		char* kh1 = new char[SIZE];
		char* kharj = new char[SIZE];
		char* kharjsave = new char[SIZE];
		int len1, len2, temp;
		unsigned long long int kharejGhesmat = 0, u = 0, kh = 1, ukh;
		bool cond = true;

		kharj[0] = '0';
		kharj[1] = '\0';
		ofasele[0] = '1';
		ofasele[1] = '\0';
		kh1[0] = '1';
		kh1[1] = '\0';
		strcpy(fin, b);
		strcpy(fi, b);


		len1 = strlen(a);
		len2 = strlen(b);
		if ((number)b > (number)a) {
			char* zero = new char[SIZE];
			zero[0] = '0'; zero[1] = '\0';

			delete[] fin;
			delete[] save;
			delete[] fi;
			delete[] ficop;
			delete[] ofasele;
			delete[] kh1;
			delete[] kharj;
			delete[] kharjsave;

			return zero;
		}

		int o = len1 - len2 - 1;

		if (o > 0) {

			kh = mypow(10, o + 1);
			for (int i = 0; i < o + 1; i++) {
				kh1[i + 1] = '0';
				kh1[i + 2] = '\0';
				ukh = i + 2;
			}
			for (int i = 0; i < o; i++) {
				ofasele[i + 1] = '0';
				ofasele[i + 2] = '\0';
				u = i + 2;
			}



		}
		else {
			kh = 1;
		}





		strcpy(ficop, fin);
		bool yj = true;


		while (u > 0 || yj) {

			yj = false;
			if (u >= 1) {
				ofasele[u] = '\0';
				u--;
				kh /= 10;
				khikhi(kh1, ukh); ukh--;
				delete[] ficop;
				ficop = mul(b, ofasele);
			}



			while (cond) {



				strcpy(save, fin);


				delete[] fin;
				fin = sum(ficop, fi);



				strcpy(fi, fin);

				len2 = strlen(fin);


				if (len2 > len1) {
					cond = false;
				}
				if (len2 == len1) {
					for (int p = 0; p < len1; p++) {
						if (a[p] == fin[p]) {
							continue;
						}
						else if (a[p] < fin[p]) {
							cond = false;
							break;
						}
						else
							break;
					}

				}
				kharejGhesmat += kh;
				strcpy(kharjsave, kharj);


				char* kharjtemp = sum(kharj, kh1);;
				delete[] kharj;
				kharj = kharjtemp;


			}
			kharejGhesmat -= kh;
			strcpy(kharj, kharjsave);
			strcpy(fin, save);
			strcpy(fi, save);
			cond = true;

		}






		char* one = new char[3];
		one[0] = '1'; one[1] = '\0';


		char* final_ans = new char[SIZE];
		final_ans = sum(kharj, one);


		delete[] fin;
		delete[] save;
		delete[] fi;
		delete[] ficop;
		delete[] ofasele;
		delete[] kh1;
		delete[] kharj;
		delete[] kharjsave;


		return final_ans;
	}

};


number operator+(const long long num, const number num_obj) { return num_obj + num; }
number operator-(const long long num, const number num_obj) { return (number)num - num_obj; }
number operator*(const long long num, const number num_obj) { return num_obj * num; }
number operator/(const long long num, const number num_obj) { return (number)num / num_obj; }
number operator%(const long long num, const number num_obj) { return (number)num % num_obj; }
int operator<=(const long long num, const number num_obj) { return num_obj >= num; }
int operator>=(const long long num, const number num_obj) { return num_obj <= num; }
int operator<(const long long num, const number num_obj) { return num_obj > num; }
int operator>(const long long num, const number num_obj) { return num_obj < num; }


ostream& operator<<(ostream& out, const number num_obj) {
	out << num_obj.get_num_str();
	return out;
}

istream& operator>>(istream& in, number& num_obj) {
	char buffer[SIZE];
	in >> buffer;
	number temp(buffer);
	num_obj = temp;
	return in;
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

	number f1("3348643512315"), f2("87897846551331"), f3("32132131654777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777776122222222222222222221254576456222222222234534313498745321321564"),
		f4("1321320654987645541326412312312333333333333333333333337777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777612222222222222222222125457645777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777761222222222222222222212545764533333333333333123123123123131233654984651245467943");

	cout << (f3 *= f4 -= f1 += f2) << endl << endl;

	/*number in1, in2;
	cin >> in1 >> in2;
	cout << in1 << " * " << in2 << " = " << in1 * in2 << endl << endl;*/

	for (number i(0); i < 21; i++) {
		cout << i << endl;
	}


	number p1(1000), p2(3);
	cout << endl << p1 / p2 << endl << endl;

	number p3(255);
	cout << p3 << " >> " << 1 << " = " << (p3 >> 1) << endl;
	cout << p3 << " >> " << 3 << " = " << (p3 >> 3) << endl;
	p3 >>= 2;
	cout << p3 << endl;
	p3 <<= 5;
	cout << p3 << endl;
	cout << (p3 << 11) << endl << endl;
	cout << p3 * 0 << endl;
	cout << long long int(p3) << endl;

	number p4(LLONG_MAX);
	p4--;
	cout << long long int(p4) << endl;

	string str = string(p4);
	cout << endl << str << endl << endl;

	number p5(12), p6(12), p7(13);
	if (p6 == p7)
		cout << "p6 == p7" << endl;
	else if (p5 == p6)
		cout << "p5 == p6" << endl;

	if (p6 != p7)
		cout << "p6 != p7" << endl;

	cout << p6[0] << "  " << p6[1] << endl;


	p6--;


	cout << "p6-- = " << p6 << endl;
	p5 = p6--;
	return 0;
}

