package sort;
import java.util.Arrays;

public class sort{
    public static int[] radixSort(int[] nums, int place) {
        // Counting sort
        int max = nums[0];
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > max) {
                max = nums[i];
            }
        }

        int[] countArray = new int[max + 1];
        System.out.println(max);

        for (int i = 0; i < countArray.length; i++) {
            int freq = 0;
            for (int j = 0; j < nums.length; j++) {
                if (nums[j] == i) {
                    freq++;
                }
            }

            if (i == 0) {
                countArray[i] = freq;
            } else {
                countArray[i] = countArray[i - 1] + freq;
            }
        }

        System.out.println(Arrays.toString(countArray));

        int[] sorted = new int[nums.length];
        for (int i = nums.length - 1; i >= 0; i--) {
            sorted[countArray[nums[i]] - 1] = nums[i];
            countArray[nums[i]]--;
        }

        return sorted;
    }

    public static void main(String[] args) {
        int[] arr = {3, 4, 0, 1, 1, 4, 0, 0};
        int[] sorted = radixSort(arr, 0);
        System.out.println(Arrays.toString(sorted));
    }
}