class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int steps = 0;
        int currentWater = capacity;
        
        for (int i = 0; i < plants.size(); ++i){
            if (currentWater >= plants[i]) {
                steps += 1;
                currentWater -= plants[i];
            }else{
                steps += (2 * i + 1);
                currentWater = capacity - plants[i];

            }
        }

        return steps;
    }
};