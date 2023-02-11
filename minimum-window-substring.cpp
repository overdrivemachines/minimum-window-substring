#include <iostream>
#include <map>
#include <unordered_set>

using namespace std;

// return a substring of s such that all chars of t are in it
// the substring should be of the smallest length possible
string minWindow(string s, string t) {
  map<char, int> t_map;
  map<char, int> window_map;
  int left_index = 0, right_index;
  char left_char, right_char;  // characters at s[left_index] and s[right_index]
  int s_length = s.length(), t_length = t.length();
  int have_chars = 0, need_chars;
  int min_window_length = s_length;
  int min_window_left_index, min_window_right_index;

  cout << "s = " << s << " t = " << t << "\n";

  if (t_length > s_length)
    return "";

  // t_map contains the count of each character in t
  for (char c : t)
    t_map[c]++;
  // t_map[c] = (t_map.count(c)) ? (t_map[c] + 1) : 1;
  need_chars = t_map.size();

  cout << "Need Chars: " << need_chars << "\n";

  left_char = s[0];
  for (right_index = 0; right_index < s_length - 1; right_index++) {
    // window string is s[left_index..right_index]
    // window string = s.substr(left_index, (right_index - left_index))

    // s = "AAZZZAAABBBCCCCC", t = "BBBCCCA"

    right_char = s[right_index];
    // if t_map['A'] > 0, add 'A' to window_map
    if (t_map.count(right_char)) {
      window_map[right_char]++;
      if (window_map[right_char] == t_map[right_char]) {
        // if window_map['A'] == t_map['A'] increament have_chars
        have_chars++;

        // Check if window is valid
        if (have_chars == need_chars) {
          // Valid window
          cout << "Valid Window: " << left_index << "-" << right_index << ": " << s.substr(left_index, right_index - left_index + 1) << "\n";

          // check if current window is smaller in length than previously found valid window
          if ((right_index - left_index) < min_window_length) {
            // current window is the shortest valid window seen so far
            min_window_length = right_index - left_index + 1;
            min_window_left_index = left_index;
            min_window_right_index = right_index;

            // move the left index until have_chars is less than need_chars
            while ((left_index <= right_index) && (have_chars == need_chars)) {
              left_char = s[left_index];
              if (window_map[left_char] > t_map[left_char]) {
                left_index++;
                window_map[left_char]--;
              }
            }
          }
        }
      }
    }

    // check if window is valid.
    // for a window to be valid it must contain all the characters in t
  }

  return "";
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

string minWindowSlow(string s, string t) {
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
