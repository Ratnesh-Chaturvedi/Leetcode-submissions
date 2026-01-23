
// notes to understand
/*

// we can use the pq or set because they can give us the minimum pair 
// we use set <sum,i> here // here i -> index of the pair first element

Approach->
step1->
// 2 array bananaye-> i->prevIndex,ii->nextIndex => jo current element ka previousn and next index ko store karega 
// count karenge number of bad pair -> a>b then (a,b) is the bad pair 
here the number of badpair can be atmost n-1,n=>size of array

step2->
// ab hum set mai se minimum pair nikal lenge 
// pair index representation -> (first,second)
// minimum pair ka sum jo hai wo hum index {first} par store kar denge and we have to
update the prevIndex and nextIdx array accordingly ->
// here two index also created
first_left ->index previous to first
second_right->index next to second
//update array
array[first]=sum of minimum bad pair(a,b) 
// here we do not delete the element we just update thte element and the prevIndewx and nextIndex mapping in the those array
prevIndex[second]=first
nextIdx[first_left]=first; // this will be same because we update the sum at the first index
// also delete those indexed from the set which usage the minpair indexes
subcases->
here subcase can be appeared like ki jo new element hai as a sum wo apne aage wale pair ke sath good pair bana raha hai ya bad pair so we ahve to update the badpair cound accodinngly 

// like -> (8,a,b) 
// here-> 8>a+b badpair--;  or 8<a+b badpair++
/like (a,b,100)  a+b>100 badpair++ or a+b<100 badpair--

// we can increase the count of operation when the minimum pair extract and updation performend on the data 

//return the cnt of operation perfromend 

*/

//code

using ll = long long;
class Solution {
public:
      int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();

        //{a, b, c, d} --> {a, b+c, d}
        vector<ll> temp(n);
        for(int i = 0; i < n; i++)
            temp[i] = nums[i];
             // sum and the index ->(sum,first)
        set<pair<ll, int>> minPairSet;

        vector<int> nextIndex(n);
        vector<int> prevIndex(n);

        for(int i = 0; i < n; i++) {
            nextIndex[i] = i+1;
            prevIndex[i] = i-1;
        }

        int badPairs = 0;
        for(int i = 0; i < n-1; i++) {
            if(temp[i] > temp[i+1]) {
                badPairs++;
            }
            minPairSet.insert({temp[i] + temp[i+1], i});
        }

        int operations = 0;

        while(badPairs > 0) {
            int first  = minPairSet.begin()->second;
            int second = nextIndex[first];

            int first_left   = prevIndex[first];
            int second_right = nextIndex[second];

                    // delete the min pair from the set
            minPairSet.erase(begin(minPairSet));

            if(temp[first] > temp[second]) {
                badPairs--;
            }

            //{d, (a, b)}
            if(first_left >= 0) {
                // ie->pehle wo bad pair tha ab good pair ban gya
                if(temp[first_left] > temp[first] &&
                temp[first_left] <= temp[first] + temp[second]) {
                    badPairs--;
                }
                  // pehle good pair tha ab bad ban gya
                else if(temp[first_left] <= temp[first] &&
                temp[first_left] > temp[first] + temp[second]) {
                    badPairs++;
                }
            }

            //{(a, b), d}
            if (second_right < n) {
                //initally->good pair -> after sum -> bad pair
                if (temp[second_right] >= temp[second] &&
                    temp[second_right] < temp[first] + temp[second]) {
                    badPairs++;
                }
                   // pehle bad pair tha ab good ban gya
                else if (temp[second_right] < temp[second] &&
                         temp[second_right] >= temp[first] + temp[second]) {
                    badPairs--;
                }
            }
             // deleting those pair which usage the first and second index
            if(first_left >= 0) {
                minPairSet.erase({temp[first_left] + temp[first], first_left});
                minPairSet.insert({temp[first_left] + temp[first] + temp[second], first_left});
            }

            if(second_right < n) {
                minPairSet.erase({temp[second] + temp[second_right], second});
                minPairSet.insert({temp[first] + temp[second] + temp[second_right], first});
                prevIndex[second_right] = first;
            }

            nextIndex[first] = second_right;
            temp[first] += temp[second];

            operations++;
        }

        return operations;
    }
};
