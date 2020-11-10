#include "inf_int.h"

/*
Originally written by
컴퓨터공학부
정진경
*/

inf_int::inf_int()
{
	this->digits = new char[2];	// 동적할당

	this->digits[0] = '0';		// default 값 0 설정
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) {		// 음수 처리
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0) {			// 숫자를 문자열로 변환하는 과정
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) {	// 숫자의 절댓값이 0일 경우
		new (this) inf_int();	// 생성자 재호출...gcc에서 컴파일에러가 있다고 함. inf_int()의 경우 별개의 인스턴스가 생성됨. 
	}
	else {
		buf[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buf);
	}
}

inf_int::inf_int(const char* str)
{
	// to be filled 
	int temp_length = strlen(str);


	// 부호 처리
	if (str[0] == '-') {
		this->thesign = false;
	}
	else {
		this->thesign = true;
	}

	// "100"이 들어왔다면 내부 표현에 맞게 "001"로 변환
	// ex) "-1053" -> thesign=false, digits="3501", len=4
	this->digits = new char[temp_length + 1];

	int i = 0;
	if (this->thesign == false) {
		temp_length--; //음수 부호의 위치 무시

		while (i < temp_length) {
			this->digits[i] = str[temp_length - i];

			i++;
		}
	}
	else {
		while (i < temp_length) {
			this->digits[i] = str[temp_length - (i + 1)];

			i++;
		}
	}

	this->digits[temp_length] = '\0';
	this->length = temp_length;

	if (this->length == 1 && digits[0] == '0') {
		new (this) inf_int();
	}
}

inf_int::inf_int(const inf_int& a) {
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;
}

inf_int::~inf_int() {
	delete digits;		// 메모리 할당 해제
}

inf_int& inf_int::operator=(const inf_int& a)
{
	if (this->digits) {
		delete this->digits;		// 이미 문자열이 있을 경우 제거.
	}
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// 부호가 같고, 절댓값이 일치해야함.
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	// to be filled
	// 절대값 비교
	if ((a.thesign == b.thesign) && (a.thesign == true)) { // 둘 다 양수일 경우 절댓값 비교한 것을 그대로 return
		if (strcmp(a.digits, b.digits) > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else if ((a.thesign == b.thesign) && (a.thesign == false)) { // 둘 다 음수일 경우 절댓값 비교의 것을 반전하여 return
		if (strcmp(a.digits, b.digits) > 0) {
			return false;
		}
		else {
			return true;
		}
	}
	else { // 부호가 다를 경우, a가 양수일 경우 b는 음수, a가 음수일 경우 b는 양수이기에 a의 부호진리값을 반환하면 됨
		if (a.thesign == true && b.thesign == false) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// 이항의 부호가 같을 경우 + 연산자로 연산
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		c.CheckZero();

		return c;
	}
	else {	// 이항의 부호가 다를 경우 - 연산자로 연산
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
	// to be filled
	inf_int c;
	unsigned int i;

	if (a.thesign == true && b.thesign == false) { //a: +, b: -
		c = b;
		c.thesign = true;

		return c = a + c;
	}
	else if (a.thesign == false && b.thesign == true) { //a: -, b: +
		c = b;
		c.thesign = false;

		return c = a + c;
	}
	else { // 이항의 부호가 같은 경우
		if (a.length > b.length) {
			if (a.thesign == true) { //a: +, b: +
				//a - b, thesign: true
				c = a;

				for (i = 0; i < b.length; i++) {
					c.Subtract(b.digits[i], i + 1);
				}

				return c;
			}
			else { //a: -, b: -
				//b - a, thesign: false
				c = b;

				for (i = 0; i < a.length; i++) {
					c.Subtract(a.digits[i], i + 1);
				}

				c.CheckZero();
				return c;
			}
		}
		else if (a.length < b.length) {
			if (a.thesign == true) { //a: +, b: +
				//b - a, thesign: false
				c = b;

				for (i = 0; i < a.length; i++) {
					c.Subtract(a.digits[i], i + 1);
				}

				c.thesign = false;

				c.CheckZero();
				return c;
			}
			else { //a: -, b: -
				//a - b, thesign: true
				c = b;

				for (i = 0; i < a.length; i++) {
					c.Subtract(a.digits[i], i + 1);
				}

				c.thesign = true;
				return c;
			}
		}
		else { //길이가 같은 경우
			if (strcmp(a.digits, b.digits) >= 0) { //절대값 a가 절대값 b보다 더 크거나 같을때, a: +, b: +, thesign: true / a: -, b: -, thesign: false
				c = a;

				for (i = 0; i < b.length; i++) {
					c.Subtract(b.digits[i], i + 1);
				}

				c.CheckZero();
				return c;
			}
			else { //절대값 a가 절대값 b보다 작을 때, a: +, b: +, thesign: false / a: -, b: -, thesign: true
				c = b;

				for (i = 0; i < a.length; i++) {
					c.Subtract(a.digits[i], i + 1);
				}

				c.thesign = !c.thesign;
				c.CheckZero();
				return c;
			}
		}
	}
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
	// to be filled
	inf_int c;
	unsigned int i;
	unsigned int j;
	char temp_num_a;
	char temp_num_b;
	int temp_num_mul;

	//a, b중 0이 있는 경우
	if ((a.length == 1 && a.digits[0] == '0') || (b.length == 1 && b.digits[0] == '0')) {
		return c;
	}

	for (i = 0; i < a.length; i++) {
		for (j = 0; j < b.length; j++) {
			temp_num_a = a.digits[i];
			temp_num_b = b.digits[j];

			temp_num_mul = (temp_num_a - '0') * (temp_num_b - '0');

			c.Add(temp_num_mul % 10 + '0', (i + j) + 1);
			temp_num_mul /= 10;
			if (temp_num_mul != 0) {
				c.Add(temp_num_mul % 10 + '0', (i + j) + 2);
			}

			if (c.digits[i + j] > '9') {
				c.Subtract('9' + 1, (i + j) + 1);
				c.Add('1', (i + j) + 2);
			}
		}
	}

	if (a.thesign == b.thesign) c.thesign = true;
	else c.thesign = false;

	return c;
}


std::ostream& operator<<(std::ostream& out, const inf_int& a)
{
	int i;

	if (a.thesign == false) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}

void inf_int::Add(const char num, const unsigned int index)	// a의 index 자리수에 n을 더한다. 0<=n<=9, ex) a가 391일때, a.Add(2, 2)의 결과는 411
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// 할당 실패 예외처리
			std::cout << "Memory reallocation failed, the program will terminate." << std::endl;

			exit(0);
		}

		this->length = index;					// 길이 지정
		this->digits[this->length] = '\0';	// 널문자 삽입
	}

	if (this->digits[index - 1] < '0') {	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// 값 연산


	if (this->digits[index - 1] > '9') {	// 자리올림이 발생할 경우
		this->digits[index - 1] -= 10;	// 현재 자릿수에서 (아스키값) 10을 빼고
		Add('1', index + 1);			// 윗자리에 1을 더한다
	}
}

void inf_int::Subtract(const char num, const unsigned int index)	// a의 index 자리수에 n을 뺀다. 0<=n<=9, ex) a가 391일때, a.Add(2, 2)의 결과는 411
{
	if (this->digits[index - 1] < '0') {	// 연산 전에 '0'보다 작은 아스키값인 경우 0으로 채움. 쓰여지지 않았던 새로운 자리수일 경우 발생
		this->digits[index - 1] += 10;
		this->digits[index] -= 1;
	}

	this->digits[index - 1] -= num - '0';	// 값 연산


	if (this->digits[index - 1] < '0') {	// 자리내림이 발생할 경우
		this->digits[index - 1] += 10;	// 현재 자릿수에서 (아스키값) 10을 더하고
		Subtract('1', index + 1);			// 윗자리에 1을 뺀다
	}
}

void inf_int::CheckZero() 
{
	unsigned int i;
	for (i = 0; i < this->length; i++) {
		if (this->digits[i] != '0') { //0이 하나라도 있다면 non-zero이기 때문에 종료
			return;
		}
	}

	//모두 0인 경우, 즉 0인 경우
	new (this) inf_int();
}