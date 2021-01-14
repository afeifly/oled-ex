#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

constexpr char base64_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

struct InvalidBase64 {};

char base64_char_convert(char c) {
	for (size_t i = 0; i < sizeof(base64_char); ++i)
		if (base64_char[i] == c) return i;
	throw InvalidBase64(); // Invalid base64 character
}
std::vector<char> base64_decode(const std::string& src) {
	std::vector<char> ret;
    ret.reserve(src.length() * 3 / 4);
	for (size_t i = 0; i < src.length(); i += 4) {
		char b1 = base64_char_convert(src[i]);
		char b2 = base64_char_convert(src[i + 1]);

		ret.push_back((b1 << 2) | ((b2 >> 4 & 0b11))); // 1st 6bits, 2nd high 2bits

		if (src[i + 2] == '=') break;
		char b3 = base64_char_convert(src[i + 2]);
		ret.push_back(((b2 & 0b1111) << 4) | ((b3 >> 2) & 0b1111)); // 2nd low 4bits, 3rd high 4bits

		if (src[i + 3] == '=') break;
		char b4 = base64_char_convert(src[i + 3]);
		ret.push_back(((b3 & 0b11) << 6) | b4); // 3rd low 2bits, 4th 6bits
	}
	return ret;
}

std::string bytes_to_string(const std::vector<char>& v) {
	return std::string(v.begin(), v.end());
}
int main() {
	std::cout << ("helloe");

//	std::cout << (bytes_to_string(base64_decode("EQARABEAI/wiBGQIqEAgQCFQIUgiTCREIEAgQCFAIIA=")));
//	std::vector<char> vv = base64_decode("EQARABEAI/wiBGQIqEAgQCFQIUgiTCREIEAgQCFAIIA=");
//
  std::string text = "AAAABH/+RERERERERERERERERDxIBFAEQAR//EAEAAA=";
	std::cout << (bytes_to_string(base64_decode(text)));
	std::vector<char> vv = base64_decode(text);
	std::cout << "size() = " << vv.size();
	std::cout << std::endl;
	for (int i = 0; i<vv.size(); ++i)
	{
		std::cout << std::hex << (0xFF & vv[i]);
		std::cout << std::endl;
	}

	/**
	std::cout << (bytes_to_string(base64_decode("TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"
"IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
"dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"
"dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
"ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4="
"b'EQARABEAI/wiBGQIqEAgQCFQIUgiTCREIEAgQCFAIIA='")));
*/
}
