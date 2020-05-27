class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int left = 0;
        int right = rotateArray.size()-1;
        if(left > right) return -1;
        if(rotateArray[left] < rotateArray[right]) return rotateArray[0];
        while(left < right){
            int mid = (left+right)/2;
            if(rotateArray[left] < rotateArray[mid]){
                left = mid;
            }
            else if (rotateArray[mid] < rotateArray[right]){
                right = mid;
            }
            else left++;
        }
        return rotateArray[right];
    }
};
