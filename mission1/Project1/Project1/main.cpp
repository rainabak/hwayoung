#include "gmock/gmock.h"
#include "fix_keyword.h"

int main() {
	//testing::InitGoogleMock();
	//return RUN_ALL_TESTS();
	FixKeyword fixKeyword;
	fixKeyword.read_match_keyword();

	return 0;
}