#include <iostream>
#include <unordered_set>

using namespace std;

// return a substring of s such that all chars of t are in it
// the substring should be of the smallest length possible
string minWindow(string s, string t) {
  string result;
  cout << "s = " << s << endl;
  cout << "t = " << t << endl;

  // if t is longer than s, return ""
  if (t.length() > s.length())
    return "";

  // if s and t are equal, return s
  if (s.compare(t) == 0)
    return s;

  // if s contains t, return t
  std::size_t found = s.find(t);
  if (found != std::string::npos)
    return t;

  // s = "ADOBECODEBANC", t = "ABC"

  // Find first matching character in s
  int leftPos = 0;
  int i, j;
  bool flag = false;
  for (i = 0; i < s.length(); i++) {
    for (j = 0; j < t.length(); j++) {
      if (t[j] == s[i]) {
        // we have found the first matching character, so now we need to exit out of both loops
        leftPos = i;
        flag = true;
        break;
      }
    }
    if (flag == true)
      break;
  }

  // no character of t is found in s
  if (flag == false) {
    cout << "no character of t is found in s\n";
    return "";
  }

  int windowLength;
  // int rightPos = leftPos;

  // s = "ADOBECODEBANC", t = "ABC"
  // s = "ADOBECODEBANC", t = "BC"

  cout << s[leftPos] << leftPos << ": ";
  bool foundAllTChars = false;
  // move i until we find all the characters in t
  for (i = leftPos; i < s.length(); i++) {
    // check if s[i] matches any letter in t
    for (j = 0; j < t.length(); j++) {
      if (t[j] == s[i]) {
        // remove t[j] from t
        t.erase(j, 1);
        cout << s[i] << i << " ";
        if (t.empty())
          foundAllTChars = true;
        break;
      }
    }
    if (foundAllTChars) {
      // t is empty
      cout << "Window Length: " << i - leftPos + 1 << "\n";
      break;
    }
  }

  return result;
}

int main(int argc, char const *argv[]) {
  // cout << minWindow("hello", "hello") << "\n";
  // cout << minWindow("hello", "hellwewo") << "\n";
  // cout << minWindow("worldhelloworld", "hello") << "\n";
  // cout << minWindow("helloworld", "jack") << "\n";
  cout << minWindow("ADOBECODEBANC", "ABC") << "\n";

  return 0;
}
