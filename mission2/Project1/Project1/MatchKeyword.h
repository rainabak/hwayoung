#pragma once

#include <vector>
#include <string>
#include "CalSimilarity.h"
#include <algorithm>
#include <fstream>
#include <iostream>

static const int DAYOFWEEK_MAX = 7;
static const int DAYTYPES = 2;

const int WEEKDAY = 0;	// ���� ( �� ~ �� )
const int WEEKEND = 1;	// �ָ� ( ��, �� )

struct Node {
    std::string w;
    std::string wk;
};

struct Node2 {
    std::string keyword;
    int point;

    bool operator<(const Node2& other) const {
        return point < other.point;
    }
};

// Ű���� ��Ī ( �Ϻ� HIT / ���� HIT / �Ѵ� �ƴ�. ) ������, ���絵 �� �� ��ü ���� ó��
class MatchKeyword{
private:
    int UZ = 0;
    std::string dayOfWeeks[DAYOFWEEK_MAX] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    std::vector<Node2> weekBest[DAYOFWEEK_MAX];
    std::vector<Node2> weekTypeBest[DAYTYPES];

    CalSimilarity calSimilarity;

    void get_day_index(std::string& day, int& weekIndex, int& weekTypeIndex);
    bool is_complete_hit(int weekIndex, std::string& keyWord, long long& weekPointMax, int weekTypeIndex, long long& weekTypePointMax);
    void reArrange(long long weekPointMax, long long weekTypePointMax);
    std::string find_match_hit(int weekIndex, int weekTypeIndex, std::string keyWord);
    void other_hit(int weekIndex, int weekTypeIndex, std::string& keyWord, int point);

public:
    std::string find_best_match_keyword(std::string keyWord, std::string dayOfWeek);
    int read_match_keyword(std::string filename);
};
