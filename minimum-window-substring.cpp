#include <iostream>
#include <unordered_set>

using namespace std;

// return a substring of s such that all chars of t are in it
// the substring should be of the smallest length possible
string minWindow(string s, string t) {
  string result;
  string tOriginal = t;
  // cout << "s = " << s << endl;
  // cout << "t = " << t << endl;

  // if t is longer than s, return ""
  if (t.length() > s.length())
    return "";

  // if s and t are equal, return s
  if (s.compare(t) == 0)
    return s;

  // if s contains t, return t
  std::size_t foundPos = s.find(t);
  if (foundPos != std::string::npos)
    return t;

  // s = "ADOBECODEBANC", t = "ABC"

  // Find first matching character in s
  int leftPos = 0;
  // int i, j;
  bool flag = false;
  for (leftPos = 0; leftPos < s.length(); leftPos++) {
    // check if s[leftPos] is present in t
    foundPos = t.find_first_of(s[leftPos]);
    if (foundPos != string::npos) {
      // found s[leftPos] character in t, so we need to remove that char from t and exit the loop
      t.erase(foundPos, 1);
      flag = true;
      break;
    }
  }

  // no character of t is found in s
  if (flag == false) {
    // cout << "no character of t is found in s\n";
    return "";
  }

  // cout << "s length: " << s.length() << "\n";
  // cout << "leftPos: " << leftPos << "\n";
  // cout << "t length: " << t.length() << "\n";

  int sCharsLeft = s.length() - leftPos - 1;
  int tLength = t.length();

  // cout << s.length() - leftPos - 1 - t.length() << "\n";
  // cout << sCharsLeft - tLength << "\n";

  if (sCharsLeft - tLength < 0)
    return "";

  // s = "ADOBECODEBANC", t = "ABC"
  // s = "ADOBECODEBANC", t = "BC"
  int windowLength;
  int minWindowLength = s.length() + 1;
  int minWindowStartPos = 0;
  // int nextLeftPos= 0;
  // cout << s[leftPos] << leftPos << ": ";
  // bool foundAllTChars = false;

  // move rightPos until we find all the characters in t
  for (int rightPos = leftPos + 1; rightPos < s.length(); rightPos++) {
    // check if s[rightPos] is present in t
    foundPos = t.find_first_of(s[rightPos]);
    if (foundPos != string::npos) {
      // found s[rightPos] in t, so erase that char from t
      // cout << s[rightPos] << rightPos << " ";
      t.erase(foundPos, 1);

      if (t.empty()) {
        windowLength = rightPos - leftPos + 1;
        if (windowLength < minWindowLength) {
          minWindowLength = windowLength;
          minWindowStartPos = leftPos;
        }

        // cout << "window length: " << windowLength << "\n";

        // increment leftPos until s[leftPos] is present in t
        while (leftPos < s.length()) {
          leftPos++;
          t = tOriginal;
          // check if s[leftPos] is in t
          foundPos = t.find_first_of(s[leftPos]);
          if (foundPos != string::npos) {
            // Found s[leftPos] in t
            rightPos = leftPos;
            t.erase(foundPos, 1);
            // cout << s[leftPos] << leftPos << ": ";

            // exit while loop
            break;
          }
        }
      }
    }
  }

  if (!t.empty() && (minWindowLength == s.length() + 1)) {
    // not all of t's characters were found in s
    return "";
  }

  // cout << "\n";
  // cout << "minWindowStartPos: " << minWindowStartPos << "\n";
  // cout << "minWindowLength: " << minWindowLength << "\n";
  return s.substr(minWindowStartPos, minWindowLength);
}

int main(int argc, char const *argv[]) {
  string s;
  string t;
  // cout << minWindow("hello", "hello") << "\n";
  // cout << minWindow("hello", "hellwewo") << "\n";
  // cout << minWindow("worldhelloworld", "hello") << "\n";
  // cout << minWindow("helloworld", "jack") << "\n";
  // cout << minWindow("ADOBECODEBANC", "ABC") << "\n";
  // cout << minWindow("AAAAF", "FGH") << "\n";
  // cout << minWindow("bba", "ab") << "\n";
  // cout << minWindow("babb", "baba") << "\n";
  cout << minWindow("AAZZZAAABBBCCCCC", "BBBCCCA") << "\n";

  return 0;
}
