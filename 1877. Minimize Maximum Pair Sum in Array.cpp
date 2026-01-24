    class Solution {
public:
// we have to minimise the specific pair sum 
// so we can do like-> we can pair up the max element with min element 
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int i = 0, j = n - 1;
        int maxi = 0;
        while (i< j) {
            maxi = max(maxi, nums[i] + nums[j]);
            i++;
            j--;
        }
        return maxi;
    }
};