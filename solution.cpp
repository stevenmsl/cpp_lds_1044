#include "solution.h"
#include "util.h"
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <unordered_map>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <bitset>
using namespace sol1032;
using namespace std;

/*takeaways
  - use Rabin-Karp so we can efficiently identify if s has duplicate
    substrings of a given length
  - use binary search to guess what the length of the duplicate
    substring should be

*/

/* Rabin-Karp */
string Solution::_find(const string &s, int len, vector<int> &power)
{
  if (len == 0)
    return "";
  int n = s.size(), cur = 0, M = 1e7 + 7;

  /* record the start positions of substrings that have
     a length of "len" and are mapped to the same hash
     number
     - there might be collisions
  */
  auto hash = unordered_map<int, vector<int>>();

  /*calculate the hash */
  for (auto i = 0; i < len; i++)
    cur = (cur * 26 + (s[i] - 'a')) % M;
  /* cur is the hash for s[0..len-1]
     - so the start position is 0
  */
  hash[cur] = {0};
  /* use sliding window to find the next substring
     of length "len"
     - i starts with the index that is right after
       the very last char within the window
  */
  for (auto i = len; i < n; i++)
  {
    auto first = s[i - len] - 'a';
    /* remove the first char from the hash
       - notice the one we remove is the
         most significant digit
       - ba -> a
       - you need to subtract 1^26 from the hash
    */
    /*
      - why plus M? the subtraction might yield negative
        number
    */
    cur = ((cur - first * power[len - 1]) % M + M) % M;
    /* add in the current char as the very last char of
       the new window
    */
    cur = (cur * 26 + (s[i] - 'a')) % M;
    /* cur now contains the hash of the substring represented by the
       new window
    */

    /*  i-len+1 is the start position of the new window*/
    auto newStart = i - len + 1;

    if (!hash.count(cur))
      /* new hash
       */
      hash[cur] = {newStart};
    else
    {
      for (auto start : hash[cur])
        /* we have to make sure they are the same string
           - we might have collisions given that
             we do a module on the hash while
             generating it
           - multiple strings might be mapped
             to the same hash
        */
        if (s.substr(start, len) == s.substr(newStart, len))
          return s.substr(start, len);
      hash[cur].push_back({newStart});
    }
  }

  return "";
}

string Solution::find(string s)
{
  int n = s.size(), lo = 0, high = n, M = 1e7 + 7;
  string result = "";

  auto power = vector<int>{1};
  /* 1, 26^1, 26^2... */
  for (auto i = 1; i < n; i++)
    power[i] = power[i - 1] * 26 % M;

  /* guess how long the duplicate substring will be
     - start from the mid
     - we can go longer or shorter depends
       on the finding
     - notice high starts with n not n-1
       as we want to find the mid point
       for the length not trying to access
       the "s" itself
     - high =6, lo = 0, so we can start
       from looking for substring that has
       a length of (6-0)/2 = 3
  */

  while (lo < high)
  {
    auto mid = lo + (high - lo) / 2;
    auto found = _find(s, mid, power);
    if (found > result)
    {
      result = found;
      /* aim for longer substring */
      lo = mid + 1;
    }
    else
      high = mid;
  }

  return result;
}