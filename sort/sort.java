package sort;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class sort{
    public static int[] countingSort(int[] nums, int place) {
        // Counting sort
        int max = digitAtPlace(nums[0], place);
        for (int i = 0; i < nums.length; i++) {
            if (digitAtPlace(nums[i], place) > max) {
                max = digitAtPlace(nums[i], place);
            }
        }

        int[] countArray = new int[max + 1];

        for (int i = 0; i < countArray.length; i++) {
            int freq = 0;
            for (int j = 0; j < nums.length; j++) {
                if (digitAtPlace(nums[j], place) == i) {
                    freq++;
                }
            }

            if (i == 0) {
                countArray[i] = freq;
            } else {
                countArray[i] = countArray[i - 1] + freq;
            }
        }

        int[] sorted = new int[nums.length];
        for (int i = nums.length - 1; i >= 0; i--) {
            sorted[countArray[digitAtPlace(nums[i], place)] - 1] = nums[i];
            countArray[digitAtPlace(nums[i], place)]--;
        }

        return sorted;
    }

    public static int digitAtPlace(int num, int place) {
        return (int) (num / Math.pow(10, place) % 10);
    }

    public static int[] radixSort(int[] nums) {
        int length = (int) (Math.log(nums[0]));
        for (int i = 0; i < length; i++) {
            nums = countingSort(nums, i);
        }
        return nums;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        ArrayList<Integer> input = new ArrayList<Integer>();
        int numPos = 0;
        int numNeg = 0;
        while (in.hasNextLine()) {
            String nextline = in.nextLine().replaceAll("[^0-9-]", "");
            input.add(Integer.parseInt(nextline));
            int value = Integer.parseInt(nextline);
            if (value< 0) {
                numNeg++;
            }
            else {
                numPos++;
            }
        }
        

        int[] posInput = new int[numPos];
        int[] negInput = new int[numNeg];
        int posCounter = 0;
        int negCounter = 0;
        for (int i = 0; i < input.size(); i++) {
            if (input.get(i) < 0) {
                negInput[negCounter] = -input.get(i);
                negCounter++;
            }
            else {
                posInput[posCounter] = input.get(i);
                posCounter++;
            }
        }
        int[] posSorted;
        int[] negSorted;
        if (posCounter != 0) {
            posSorted = radixSort(posInput);
        }
        else {
            posSorted = new int[0];
        }

        if (negCounter != 0) {
            negSorted = radixSort(negInput);
        }
        else {
            negSorted = new int[0];
        }

        int[] output = new int[posSorted.length+negSorted.length];

        negCounter = negSorted.length - 1;
        int counter = 0;
        while (counter < input.size()) {
            if (counter < negSorted.length) {
                output[counter] = -negSorted[negCounter];
                negCounter--;
            }
            else {
                output[counter] = posSorted[counter - negSorted.length];
            }
            counter += 1;
        }

        
        for (int i = 0; i < output.length; i++) {
            System.out.println(output[i]);
        }
    }
}