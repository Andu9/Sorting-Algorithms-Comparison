#include <iostream>
#include <vector>
#include <random>
#include <fstream>
    using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");
    int partition(vector<int>& nums,int low, int high)
    {
        int i=low-1;
        int pivot=nums[high];
        for(int j=low;j<high;j++)
        {
            if(nums[j]<=pivot)
            {
                i++;
                swap(nums[i],nums[j]);
            }
        }
        swap(nums[i+1],nums[high]);
        return i+1;
    }

    void quicksort(vector<int>& nums,int low, int high)
    {
        if(low<high)
        {
            int pivot=partition(nums,low,high);
            quicksort(nums,low,pivot-1);
            quicksort(nums,pivot+1,high);

        }
    }

    vector<int> sortArray(vector<int>& nums) {
        quicksort(nums,0,nums.size()-1);
        return nums;
    }

int main()
    {
        int n;
        fin>>n;
        vector<int> nums(n+1);
        for(int i=1;i<=n;i++)
        {
            fin>>nums[i];
        }

        vector<int> result=sortArray(nums);
        for(int i=1;i<result.size();i++)
        {
           fout<<result[i]<<" ";
        }
        return 0;
    }

