#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol1032;

/*
Input: "banana"
Output: "ana"
*/

tuple<string, string>
testFixture1()
{
  return make_tuple("banana", "ana");
}

/*
Input: "abcd"
Output: ""
*/

tuple<string, string>
testFixture2()
{
  return make_tuple("abcd", "");
}

void test1()
{
  auto f = testFixture1();
  cout << "Expect to see: " << get<1>(f) << endl;
  Solution sol;
  cout << sol.find(get<0>(f)) << endl;
}

void test2()
{
  auto f = testFixture2();
  cout << "Expect to see: \"\" " << get<1>(f) << endl;
  Solution sol;
  cout << sol.find(get<0>(f)) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}