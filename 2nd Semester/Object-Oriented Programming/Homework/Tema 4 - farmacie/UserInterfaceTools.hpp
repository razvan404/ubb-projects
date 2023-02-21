#pragma once
#pragma warning (disable: 26493) // Don't use C-style casts (type,4).

#include <vector>
#include <iostream>

#include "Exceptions.h"

using std::cin;
using std::cout;
using std::to_string;

#define elif  else if

#define COLOR_RED		(string)"\033[00;31m"
#define COLOR_GREEN		(string)"\033[00;32m"
#define COLOR_YELLOW	(string)"\033[00;33m"
#define COLOR_BLUE		(string)"\033[00;34m"
#define COLOR_MAGENTA	(string)"\033[00;35m"
#define COLOR_CYAN		(string)"\033[00;36m"
#define COLOR_WHITE		(string)"\033[00;37m"
#define COLOR_RESET		(string)"\033[00;38m"

#define COLOR_NEON_RED		(string)"\033[05;31m"
#define COLOR_NEON_GREEN	(string)"\033[05;32m"
#define COLOR_NEON_YELLOW	(string)"\033[05;33m"
#define COLOR_NEON_BLUE		(string)"\033[05;34m"
#define COLOR_NEON_MAGENTA	(string)"\033[05;35m"
#define COLOR_NEON_CYAN		(string)"\033[05;36m"
#define COLOW_NEON_WHITE	(string)"\033[05;37m"

inline string rainbowHash(int i) {
	switch (i % 6) {
	case 0:
		return COLOR_RED;
	case 1:
		return COLOR_YELLOW;
	case 2:
		return COLOR_GREEN;
	case 3:
		return COLOR_CYAN;
	case 4:
		return COLOR_BLUE;
	case 5:
		return COLOR_MAGENTA;
	default:
		return COLOR_RESET;
	}
}

inline string rainbowText(string text) {
	string rainbow;
	int skipped = 0;
	for (unsigned i = 0; i < text.size(); ++i) {
		if (text.at(i) == ' ') {
			skipped++;
		}
		rainbow += rainbowHash(i - skipped) + text.at(i);
	}
	rainbow += COLOR_RESET;
	return rainbow;
}

inline int readInteger() {
	string buffer;
	fflush(stdin);
	getline(cin, buffer);

	unsigned start = 0;
	if (buffer.at(start) == '-') {
		start++;
		if (buffer.size() == 1) {
			throw InvalidInput("The input should be an integer!");
		}
	}
	for (unsigned i = start; i < buffer.size(); ++i) {
		if (buffer.at(i) < '0' || buffer.at(i) > '9') {
			throw InvalidInput("The input should be an integer!");
		}
	}

	return stoi(buffer);
}
inline double readDouble() {
	string buffer;
	fflush(stdin);
	getline(cin, buffer);
	
	unsigned start = 0;
	bool onepoint = false;
	if (buffer.at(start) == '-') {
		start++;
		if (buffer.size() == 1) {
			throw InvalidInput("The input should be a real number!");
		}
	}
	for (unsigned i = start; i < buffer.size(); ++i) {
		if (buffer.at(i) < '0' || buffer.at(i) > '9') {
			if (buffer.at(i) == '.' && onepoint == false) {
				onepoint = true;
			}
			elif(buffer.at(i) == ',' && onepoint == false) {
				onepoint = true;
				buffer.at(i) = '.';
			}
			else {
				throw InvalidInput("The input should be a real number!");
			}
		}
	}

	return stod(buffer);
}
inline string readString() {
	string buffer;
	fflush(stdin);
	getline(cin, buffer);

	if (buffer.size() == 0) {
		throw InvalidInput("The input should be a string!");
	}

	return buffer;
}

inline string multipleStrings(string text, int numberOfAppearances) {
	string ans = "";
	while (numberOfAppearances > 0) {
		ans += text;
		--numberOfAppearances;
	}
	return ans;
}

inline string doubleToPriceString(double price) {
	const string wholePart = to_string(int(price));
	string decimalPart = to_string(int((price - int(price)) * 100));
	decimalPart = multipleStrings("0", 2 - decimalPart.size()) + decimalPart;
	if (int(price) >= 1000) {
		const string upperPart = to_string(int(price) / 1000);
		string lowerPart = to_string(int(price) % 1000);
		lowerPart = multipleStrings("0", 3 - lowerPart.size()) + lowerPart;
		return "$" + upperPart + "." + lowerPart + "," + decimalPart;
	}
	return "$" + wholePart + "," + decimalPart;
}

inline string doubleToPriceString(double price, string $COLOR) {
	const string wholePart = to_string(int(price));
	string decimalPart = to_string(int((price - int(price)) * 100));
	decimalPart = multipleStrings("0", 2 - decimalPart.size()) + decimalPart;
	if (int(price) >= 1000) {
		const string upperPart = to_string(int(price) / 1000);
		string lowerPart = to_string(int(price) % 1000);
		lowerPart = multipleStrings("0", 3 - lowerPart.size()) + lowerPart;
		return $COLOR + "$" + COLOR_RESET + upperPart + "." + lowerPart + "," + decimalPart;
	}
	return $COLOR + "$" + COLOR_RESET + wholePart + "," + decimalPart;
}

inline string centerText(string text, int coverage) {
	const int needSpace = coverage - text.size();
	if (needSpace <= 0) return text;
	return multipleStrings(" ", needSpace / 2) + text + multipleStrings(" ", needSpace / 2 + needSpace % 2);
}

inline string halfCenterText(string text, int coverage) {
	const int needSpace = coverage - text.size();
	if (needSpace <= 0) return text;
	return multipleStrings(" ", needSpace / 2) + text;
}

inline void writeMiddle(string text, int ignoredCaractersCount = 0) {
	cout << centerText(text, 120 + ignoredCaractersCount) << '\n';
}

inline void writeMiddle(string text, string color, int ignoredCaractersCount = 0) {
	cout << centerText(color + text + COLOR_RESET, 136 + ignoredCaractersCount) << '\n';
}

inline void writeHalfMiddle(string text, int ignoredCaractersCount = 0) {
	cout << halfCenterText(text, 118 + ignoredCaractersCount);
}

inline void writeHalfMiddle(string text, string color, int ignoredCaractersCount = 0) {
	cout << halfCenterText(color + text + COLOR_RESET, 134 + ignoredCaractersCount);
}

inline void clearScreen() noexcept {
	system("cls");
}

inline void newLine() noexcept {
	system("echo:");
}
