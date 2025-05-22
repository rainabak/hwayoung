## 요구사항(D1 ~ D5)
 1. 함수 레벨리팩토링
  D1 - 가독성있는 코드로 메서드추상화, 가독성좋은네이밍사용 <br>
  D2 - Regression Test를 위한 Unit Test 개발
 2. 확장성을 고려한설계
  D3 - 유사도 검사 방법이바뀌더라도기존코드에변경이없도록한다. 
 3. 디자인 패턴사용하기
  D4 - 리팩토링에 디자인 패턴을적용한다.
 4. 코드 커버리지 100%
   D5 - 리팩토링이 끝난 코드에, 코드 커버리지가100% 되어야 한다

[ 진행 사항 ]
- [x] D1

     - similer 함수 리턴 타입 전부 bool 형식으로 수정
     - input2 함수 명을 find_best_match_keyword 로 변경
     - input2 내부 코드 길이가 길어서 모듈화
         -> get_day_index : 월~일, 주중/주말 인덱스 찾는 함수
         -> is_complete_hit : 완벽HIT 확인하는 함수
         -> reArrange : 재정렬 작업
         -> find_match_hit : 찰떡HIT 확인하는 함수
         -> other_hit : 완벽 HIT / 찰떡 HIT 둘다 아닌경우 확인하는 함수.

     - twoBest => weekTypeBest : 주중/주말의 종류를 확인하는 변수라고 생각하고 변경.
     - dayOfWeeks :  { "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" } 선언
     - DAYOFWEEK_MAX : 요일 갯수 7
     - DAYTYPES : 주중/주말 종류 갯수 2
     - w => keyword : 검색어로 keyword 가 더 어울림... 
       
- [ ] D2
- [ ] D3
- [ ] D4
- [ ] D5
