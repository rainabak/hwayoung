#include "gmock/gmock.h"
#include "MatchKeyword.h"

TEST(Group, banane) {
	MatchKeyword keyword;
	keyword.find_best_match_keyword("banana", "Tue");
	keyword.find_best_match_keyword("banana", "Tue");
	keyword.find_best_match_keyword("banane", "Tue");
	std::string result = keyword.find_best_match_keyword("banana", "Tue");
	EXPECT_EQ("banana", result);
}

TEST(Group, google) {
	MatchKeyword keyword;
	keyword.find_best_match_keyword("google", "Tue");
	keyword.find_best_match_keyword("google", "Tue");
	keyword.find_best_match_keyword("boogle", "Tue");
	std::string result = keyword.find_best_match_keyword("google", "Tue");
	EXPECT_EQ("google", result);
}

TEST(Group, weenend) {
	MatchKeyword keyword;
	keyword.find_best_match_keyword("review", "sat");
	std::string result = keyword.find_best_match_keyword("review", "sat");
	EXPECT_EQ("review", result);
}

TEST(Group, weenend_complete) {
	MatchKeyword keyword;
	keyword.find_best_match_keyword("review", "sat");
	keyword.find_best_match_keyword("review", "sat");
	keyword.find_best_match_keyword("review", "Tue");
	std::string result = keyword.find_best_match_keyword("review", "sat");
	EXPECT_EQ("review", result);
}

TEST(Group, rearrange) {
	MatchKeyword keyword;
	for(int i=0; i<100; ++i)	keyword.find_best_match_keyword("rearrange", "sat");
	std::string result = keyword.find_best_match_keyword("rearrange", "sat");
	EXPECT_EQ("rearrange", result);
}

TEST(Group, pepper_saturday) {
	MatchKeyword keyword;
	keyword.read_match_keyword("keyword_weekday_500.txt");
	std::string result = keyword.find_best_match_keyword("peppee", "saturday");
	EXPECT_EQ("pepper", result);
}

TEST(Group, pizza_friday) {
	MatchKeyword keyword;
	keyword.read_match_keyword("keyword_weekday_500.txt");
	std::string result = keyword.find_best_match_keyword("pizza", "friday");
	EXPECT_EQ("pizza", result);
}

TEST(Group, shrimp_wednesday) {
	MatchKeyword keyword;
	keyword.read_match_keyword("keyword_weekday_500.txt");
	std::string result = keyword.find_best_match_keyword("shrimp", "wednesday");
	EXPECT_EQ("shrimp", result);
}

TEST(Group, read_500) {
	MatchKeyword keyword;
	int result = keyword.read_match_keyword("keyword_weekday_500.txt");
	EXPECT_EQ(500, result);
}

int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}