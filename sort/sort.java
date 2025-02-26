package sort;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class sort {
    public static ArrayList<Integer> countingSort(ArrayList<Integer> nums, int place) {
        // Counting sort
        int[] countArray = new int[10];

        for (int i = 0; i < nums.size(); i++) {
            countArray[digitAtPlace(nums.get(i), place)]++;
        }

        for (int i = 1; i < countArray.length; i++) {
            countArray[i] = countArray[i] + countArray[i - 1];
        }
            
        Integer[] sorted = new Integer[nums.size()];
        for (int i = nums.size() - 1; i >= 0; i--) {
            int digit = digitAtPlace(nums.get(i), place);
            countArray[digit]--;
            sorted[countArray[digit]] = nums.get(i);
        }

        return new ArrayList<>(Arrays.asList(sorted));
    }

    public static int digitAtPlace(int num, int place) {
        return (int) (num / Math.pow(10, place) % 10);
    }

    public static ArrayList<Integer> radixSort(ArrayList<Integer> nums) {
        int length = (int) Math.ceil(Math.log10(Collections.max(nums))) + 1;
        for (int i = 0; i < length; i++) {
            nums = countingSort(nums, i);
        }
        return nums;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        ArrayList<Integer> posNums = new ArrayList<Integer>(600000);
        ArrayList<Integer> negNums = new ArrayList<Integer>(600000);

        while (in.hasNextLine()) {
            String nextline = in.nextLine().replaceAll("[^0-9-]", "");
            int value = Integer.parseInt(nextline);

            if (value < 0) {
                negNums.add(-value);
            }
            else {
                posNums.add(value);
            }
        }
        
        ArrayList<Integer> posSorted = radixSort(posNums);
        ArrayList<Integer> negSorted = radixSort(negNums);

        for (int i = negSorted.size() - 1; i >= 0; i--) {
            System.out.println(-negSorted.get(i));
        }
        
        for (int i = 0; i < posSorted.size(); i++) {
            System.out.println(posSorted.get(i));
        }
    }
}