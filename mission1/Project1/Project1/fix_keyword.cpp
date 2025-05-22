//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <map>
//#include <algorithm>
//#include "fix_keyword.h"
//
////   D1 - 가독성있는 코드로 메서드추상화, 가독성좋은네이밍사용
//
#include "fix_keyword.h"

using namespace std;

// 레벤슈타인 거리 계산 알고리즘 (문자열 유사도 검사)
int FixKeyword::levenshtein(const std::string& a, const std::string& b) {
	const size_t len_a = a.size();
	const size_t len_b = b.size();

	std::vector<std::vector<int>> d(len_a + 1, std::vector<int>(len_b + 1));

	for (size_t i = 0; i <= len_a; ++i) d[i][0] = i;
	for (size_t j = 0; j <= len_b; ++j) d[0][j] = j;

	for (size_t i = 1; i <= len_a; ++i) {
		for (size_t j = 1; j <= len_b; ++j) {
			if (a[i - 1] == b[j - 1])
				d[i][j] = d[i - 1][j - 1];
			else
				d[i][j] = 1 + std::min({ d[i - 1][j], d[i][j - 1], d[i - 1][j - 1] });
		}
	}
	return d[len_a][len_b];
}

// 점수 환산
bool FixKeyword::similer(const std::string& a, const std::string& b) {
	if (a.empty() && b.empty()) return true;
	if (a.empty() || b.empty()) return false;

	int dist = levenshtein(a, b);
	int max_len = std::max(a.length(), b.length());
	// 유사도 비율 (1.0: 완전히 같음, 0.0: 전혀 다름)
	double similarity = 1.0 - (double)dist / max_len;
	
	int score = 1 + static_cast<int>(similarity * 99);
	
	if (score >= 80) return true;
	return false;
}

bool FixKeyword::is_complete_hit(int weekIndex, std::string& keyWord, long long& weekPointMax, int weekTypeIndex, long long& weekTypePointMax)
{
	if (weekIndex < 0)	return false;
	if (weekIndex >= DAYOFWEEK_MAX)	return false;

	for (Node2& node : weekBest[weekIndex]) {
		if (node.keyword == keyWord) {
			weekPointMax = node.point + (node.point * 0.1);
			node.point += (node.point * 0.1);
			return true;
		}
	}

	for (Node2& node : weekTypeBest[weekTypeIndex]) {
		if (node.keyword == keyWord) {
			weekTypePointMax = node.point + (node.point * 0.1);
			node.point += (node.point * 0.1);
			break;
		}
	}

	return false;
}

void FixKeyword::get_day_index(std::string& day, int& weekIndex, int& weekTypeIndex)
{
	for (int i = 0; i < DAYOFWEEK_MAX; ++i) {
		if (dayOfWeeks[i] == day) {
			weekIndex = i;

			//평일 / 주말	
			if (weekIndex >= 0 && weekIndex <= 4) weekTypeIndex = WEEKDAY;
			else weekTypeIndex = WEEKEND;
			
			return;
		}
	}
}

void FixKeyword::reArrange(long long weekPointMax, long long weekTypePointMax)
{
	if (UZ >= 2100000000 || weekPointMax >= 2100000000 || weekTypePointMax >= 2100000000) {
		UZ = 9;
		for (int i = 0; i < 5; i++) {
			int num = 1;
			for (Node2& node : weekBest[i]) {
				node.point = num;
				num++;
			}
		}
		for (int i = 0; i < DAYTYPES; i++) {
			int num = 1;
			for (Node2& node : weekTypeBest[i]) {
				node.point = num;
				num++;
			}
		}
	}
}

string FixKeyword::find_match_hit(int weekIndex, int weekTypeIndex, string keyWord) {
	for (Node2& node : weekBest[weekIndex]) {
		if (similer(node.keyword, keyWord)) {
			return node.keyword;
		}
	}

	for (Node2& node : weekTypeBest[weekTypeIndex]) {
		if (similer(node.keyword, keyWord)) {
			return node.keyword;
		}
	}
	return "";
}

void FixKeyword::other_case(int weekIndex, int weekTypeIndex, std::string& keyWord, int point)
{
	// 주중
	if (weekBest[weekIndex].size() < 10) {
		weekBest[weekIndex].push_back({ keyWord, point });
		std::sort(weekBest[weekIndex].begin(), weekBest[weekIndex].end());
	}

	if (weekTypeBest[weekTypeIndex].size() < 10) {
		weekTypeBest[weekTypeIndex].push_back({ keyWord, point });
		std::sort(weekTypeBest[weekTypeIndex].begin(), weekTypeBest[weekTypeIndex].end());
	}

	if (weekBest[weekIndex].size() == 10) {
		if (weekBest[weekIndex].back().point < point) {
			weekBest[weekIndex].pop_back();
			weekBest[weekIndex].push_back({ keyWord, point });
			std::sort(weekBest[weekIndex].begin(), weekBest[weekIndex].end());
		}
	}

	if (weekTypeBest[weekTypeIndex].size() == 10) {
		if (weekTypeBest[weekTypeIndex].back().point < point) {
			weekTypeBest[weekTypeIndex].pop_back();
			weekTypeBest[weekTypeIndex].push_back({ keyWord, point });
			std::sort(weekTypeBest[weekTypeIndex].begin(), weekTypeBest[weekTypeIndex].end());
		}
	}
}

string FixKeyword::find_best_match_keyword(string keyWord, string dayOfWeek) {
	UZ++;

	int weekIndex = 0;
	int weekTypeIndex = 0;

	get_day_index(dayOfWeek, weekIndex, weekTypeIndex);

	int point = UZ;

	//관리 목록에 존재하는지 확인
	//관리되는 키워드이면 점수가 증가

	long long int dayPointMax = 0;
	long long int weekPointMax = 0;

	// 완벽HIT
	if(is_complete_hit(weekIndex, keyWord, dayPointMax, weekTypeIndex, weekPointMax)){
		return keyWord;
	}

	// 재정렬 작업
	reArrange(dayPointMax, weekPointMax);


	// 찰떡 HIT
	string findW = find_match_hit(weekIndex, weekTypeIndex, keyWord);
	if (findW != "") {
		return findW;
	}

	//완벽 HIT / 찰떡 HIT 둘다 아닌경우
	other_case(weekIndex, weekTypeIndex, keyWord, point);

	return keyWord;
}

void FixKeyword::read_match_keyword() {
	ifstream fin{ "keyword_weekday_500.txt" }; //500개 데이터 입력
	// 파일 열기 실패 
	if (fin.is_open() == false) {
		return;
	}

	for (int i = 0; i < 500; i++) {
		string keyword, day;
		fin >> keyword >> day;
		string ret = find_best_match_keyword(keyword, day);
		std::cout << (i+1) << " : " << ret << "\n";
	}
}