int smallestIndex(int* nums, int numsSize) {
    for(int i = 0; i < numsSize; i++){
        int temp = nums[i];
        int digitSum = 0;

        if(temp == 0){
            digitSum = 0;
        }else{
            while(temp > 0){
                digitSum += temp % 10;
                temp /= 10;
            }
        }
        if (digitSum == i){
            return i;
        }
    }
    return -1;
}