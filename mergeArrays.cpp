/*
You are given two 2D integer arrays nums1 and nums2.

nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
Each array contains unique ids and is sorted in ascending order by id.

Merge the two arrays into one array that is sorted in ascending order by id, respecting the following conditions:

Only ids that appear in at least one of the two arrays should be included in the resulting array.
Each id should be included only once and its value should be the sum of the values of this id in the two arrays. If the id does not exist in one of the two arrays then its value in that array is considered to be 0.
Return the resulting array. The returned array must be sorted in ascending order by id.

*/

class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        vector<vector<int>> merged;
        
        auto it1 {nums1.begin()};
        auto it2 {nums2.begin()};        
        while(it1 != nums1.cend() && it2 != nums2.cend())
        {
            int id1 {it1->at(0)};
            int id2 {it2->at(0)};
            int value;
            // add numbers if the id exists in both arrays, otherwise add the lower id
            if(id1 == id2)
            {
                value = it1->at(1) + it2->at(1);
                ++it1;
                ++it2;
                merged.push_back(vector<int> {id1, value});
            }
            else if(id1 < id2)
            {
                value = it1->at(1);
                ++it1;
                merged.push_back(vector<int> {id1, value});
            }
            else
            {
                value = it2->at(1);
                ++it2;
                merged.push_back(vector<int> {id2, value});
            }

        }
        // add any numbers remaining in an array
        while(it1 != nums1.cend())
        {
            merged.push_back(vector<int> {it1->at(0), it1->at(1)});
            ++it1;
        }
        
        while(it2 != nums2.cend())
        {
            merged.push_back(vector<int> {it2->at(0), it2->at(1)});
            ++it2;
        }
        return merged;
    }
};