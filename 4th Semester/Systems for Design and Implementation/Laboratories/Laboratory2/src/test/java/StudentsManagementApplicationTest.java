import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class StudentsManagementApplicationTest {

    @Test
    void generateGroups() {
        var firstYearGroups = StudentsManagementApplication.generateGroups(2, "Mihai", "Alexandru", "Vlad", "Andrei", "Rares");
        assertEquals(2, firstYearGroups.keySet().size());
        assertEquals(3, firstYearGroups.get(1).size());
    }

    @Test
    void getGroupsWithMostStudents() {
        var firstYearGroups = StudentsManagementApplication.generateGroups(2, "Mihai", "Alexandru", "Vlad", "Andrei", "Rares");
        assertEquals(1, StudentsManagementApplication.getGroupsWithMostStudents(firstYearGroups).size());
        assertEquals(1, StudentsManagementApplication.getGroupsWithMostStudents(firstYearGroups).get(0));
        var secondYearGroups = StudentsManagementApplication.generateGroups(2, "Mihai", "Alexandru", "Vlad", "Andrei");
        assertEquals(2, StudentsManagementApplication.getGroupsWithMostStudents(secondYearGroups).size());
        assertEquals(1, StudentsManagementApplication.getGroupsWithMostStudents(secondYearGroups).get(0));
        assertEquals(2, StudentsManagementApplication.getGroupsWithMostStudents(secondYearGroups).get(1));
    }
}