#include "MatchKeyword.h"

void MatchKeyword::get_day_index(std::string& day, int& weekIndex, int& weekTypeIndex)
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

bool MatchKeyword::is_complete_hit(int weekIndex, std::string& keyWord, long long& weekPointMax, int weekTypeIndex, long long& weekTypePointMax)
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

void MatchKeyword::reArrange(long long weekPointMax, long long weekTypePointMax)
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

std::string MatchKeyword::find_match_hit(int weekIndex, int weekTypeIndex, std::string keyWord) {
	for (Node2& node : weekBest[weekIndex]) {
		if (calSimilarity.IsSimiler(node.keyword, keyWord)) {
			return node.keyword;
		}
	}

	for (Node2& node : weekTypeBest[weekTypeIndex]) {
		if (calSimilarity.IsSimiler(node.keyword, keyWord)) {
			return node.keyword;
		}
	}
	return "";
}

void MatchKeyword::other_hit(int weekIndex, int weekTypeIndex, std::string& keyWord, int point)
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

std::string MatchKeyword::find_best_match_keyword(std::string keyWord, std::string dayOfWeek){
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
	if (is_complete_hit(weekIndex, keyWord, dayPointMax, weekTypeIndex, weekPointMax)) {
		return keyWord;
	}

	// 재정렬 작업
	reArrange(dayPointMax, weekPointMax);


	// 찰떡 HIT
	std::string findW = find_match_hit(weekIndex, weekTypeIndex, keyWord);
	if (findW != "") {
		return findW;
	}

	//완벽 HIT / 찰떡 HIT 둘다 아닌경우
	other_hit(weekIndex, weekTypeIndex, keyWord, point);

	return keyWord;
}

int MatchKeyword::read_match_keyword( std::string filename) {
	int cnt = 0;

	std::ifstream fin{ filename }; //500개 데이터 입력    -   "keyword_weekday_500.txt"
	// 파일 열기 실패 
	if (fin.is_open() == false) {
		return cnt;
	}

	for (int i = 0; i < 500; i++) {
		std::string keyword, day;
		fin >> keyword >> day;
		std::string ret = find_best_match_keyword(keyword, day);
		if (keyword == ret) cnt++;
		//std::cout << (i + 1) << " : " << ret << "\n";
	}
	return cnt;
}