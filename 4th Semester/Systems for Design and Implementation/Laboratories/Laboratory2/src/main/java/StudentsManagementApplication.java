import com.google.common.collect.ArrayListMultimap;
import com.google.common.collect.Multimap;

import java.util.*;

public class StudentsManagementApplication {
    public static Multimap<Integer, String> generateGroups(int groupsCount, String... names) {
        Multimap<Integer, String> groups = ArrayListMultimap.create();
        for (int i = 0; i < names.length; ++i) {
            groups.put(i % groupsCount + 1, names[i]);
        }
        return groups;
    }

    public static List<Integer> getGroupsWithMostStudents(Multimap<Integer, String> groups) {
        return groups.asMap().entrySet().stream()
                .filter(group -> group.getValue().size() == groups.asMap().values().stream()
                        .max(Comparator.comparingInt(Collection::size)).orElse(List.of()).size())
                .map(Map.Entry::getKey).toList();
    }

    public static void main(String[] args) {
        System.out.println(generateGroups(2, "Mihai", "Alexandru", "Vlad", "Andrei", "Rares"));
    }
}
