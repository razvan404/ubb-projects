import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    public static List<Integer> getUnallottedUsers(List<List<Integer>> bids, int totalShares) {
        bids.sort((a, b) -> {
            if (!a.get(2).equals(b.get(2))) {
                return b.get(2) - a.get(2); // descrescator dupa bid share
            }
            return a.get(3) - b.get(3); // crescator dupa timestamp
        });
        int firstUnallocated = bids.size();
        for (int i = 0; i < bids.size(); i++) {
            if (i + 1 < bids.size() && bids.get(i).get(2) == bids.get(i + 1).get(2)) {
                int last = 0;
                totalShares -= bids.get(i).get(1);
                if (totalShares <= 0) {
                    firstUnallocated = i + 1;
                    break;
                }
                for (int j = i + 1; j < bids.size() && totalShares > 0; j++) {
                    if (bids.get(j).get(2) != bids.get(i).get(2)) {
                        last = j - 1;
                        break;
                    }
                    totalShares -= 1;
                    if (totalShares <= 0) {
                        firstUnallocated = j + 1;
                        break;
                    }
                }
                if (totalShares <= 0) {
                    break;
                }
                for (int j = i; j <= last; j++) {
                    totalShares -= bids.get(j).get(1) - 1;
                }
                if (totalShares <= 0) {
                    firstUnallocated = last + 1;
                    break;
                }
            }
            else {
                totalShares -= bids.get(i).get(1);
                if (totalShares <= 0) {
                    firstUnallocated = i + 1;
                    break;
                }
            }
        }
        List<Integer> unallottedUsers = new ArrayList<>();
        for (int i = firstUnallocated; i < bids.size(); i++) {
            unallottedUsers.add(bids.get(i).get(0));
        }
        unallottedUsers.sort(Integer::compareTo);
        return unallottedUsers;
    }
    public static void main(String[] args) {
        List<List<Integer>> bids = new ArrayList<>();
        List<Integer> bid1 = new ArrayList<>();
        bid1.add(1);
        bid1.add(5);
        bid1.add(5);
        bid1.add(0);

        List<Integer> bid2 = new ArrayList<>();
        bid2.add(2);
        bid2.add(7);
        bid2.add(8);
        bid2.add(1);

        List<Integer> bid3 = new ArrayList<>();
        bid3.add(3);
        bid3.add(7);
        bid3.add(5);
        bid3.add(1);

        List<Integer> bid4 = new ArrayList<>();
        bid4.add(4);
        bid4.add(10);
        bid4.add(3);
        bid4.add(3);

        bids.add(bid1);
        bids.add(bid2);
        bids.add(bid3);
        bids.add(bid4);

        System.out.println(getUnallottedUsers(bids, 18));
    }
}