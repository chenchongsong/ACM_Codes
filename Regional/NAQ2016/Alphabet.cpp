#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

string trans[100] = {
	"@",
	"8",
	"(",
	"|)",
	"3",
	"#",
	"6",
	"[-]",
	"|",
	"_|",
	"|<",
	"1",
	"[]\\/[]",
	"[]\\[]",
	"0",
	"|D",
	"(,)",
	"|Z",
	"$",
	"']['",
	"|_|",
	"\\/",
	"\\/\\/",
	"}{",
	"`/",
	"2"
};
string s;
int main() {
	getline(cin, s);
	for (int i=0; i<s.size(); i++) {
		if (('a'<=s[i]&&s[i]<='z') || ('A'<=s[i]&&s[i]<='Z')) {
			cout << trans[(s[i]>='a'?s[i]-32:s[i])-'A'];
		}
		else cout << s[i];
	}
	puts("");
	return 0;

}