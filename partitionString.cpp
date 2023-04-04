/*
2405. Optimal Partition of String

Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.

Return the minimum number of substrings in such a partition.

Note that each character should belong to exactly one substring in a partition.

Constraints:

1 <= s.length <= 10^5
s consists of only English lowercase letters.
*/

class Solution {
public:
    int partitionString(string s) {

        int count { 1 }; //count starts at 1 since the length of s > 0
        bool characters[26] {false};
        for(auto ch: s)
        {
            if(characters[ch - 'a'] == true)
            {
                ++count;
                memset(characters, false, sizeof(characters)); // new substring; reset bool array
            }
            characters[ch - 'a'] = true;
        }
        return count;
    }
};