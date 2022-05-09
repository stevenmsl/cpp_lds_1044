
#ifndef SOLUTION_H
#define SOLUTION_H

#include "node.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <string>
#include <stack>

using namespace std;
namespace sol1032
{

  class Solution
  {
  private:
    string _find(const string &s, int len, vector<int> &power);

  public:
    string find(string s);
  };
}
#endif