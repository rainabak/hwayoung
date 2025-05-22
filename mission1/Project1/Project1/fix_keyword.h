#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

//   D1 - 가독성있는 코드로 메서드추상화, 가독성좋은네이밍사용

using namespace std;

struct Node {
	string w;
	string wk;
};

struct Node2 {
	string keyword;
	int point;

	bool operator<(const Node2& other) const {
		return point < other.point;
	}
};

static const int DAYOFWEEK_MAX = 7;
static const int DAYTYPES = 2;

const string dayOfWeeks[DAYOFWEEK_MAX] = { "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };

const int WEEKDAY = 0;	// 주중 ( 월 ~ 금 )
const int WEEKEND = 1;	// 주말 ( 토, 일 )

class FixKeyword {
public:
	FixKeyword() {}
	void read_match_keyword();

private:
	vector<Node2> weekBest[DAYOFWEEK_MAX]; //월 ~ 금
	vector<Node2> weekTypeBest[DAYTYPES]; //평일, 주말

	int UZ = 9;

	int levenshtein(const std::string& a, const std::string& b);
	bool similer(const std::string& a, const std::string& b);
	bool is_complete_hit(int weekIndex, std::string& keyWord, long long& weekPointMax, int weekTypeIndex, long long& weekTypePointMax);
	void get_day_index(std::string& day, int& weekIndex, int& weekTypeIndex);
	void reArrange(long long weekPointMax, long long weekTypePointMax);
	string find_match_hit(int weekIndex, int weekTypeIndex, string keyWord);
	void other_hit(int weekIndex, int weekTypeIndex, std::string& keyWord, int point);
	string find_best_match_keyword(string keyWord, string dayOfWeek);
};