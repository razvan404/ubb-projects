package application.models;

public class Client extends Entity<Long> {
    private final String name;
    private final int fidelityGrade;
    private final int age;
    private final ClientHobbies hobbies;

    public Client(Long aLong, String name, int fidelityGrade, int age, ClientHobbies hobbies) {
        super(aLong);
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.age = age;
        this.hobbies = hobbies;
    }

    public String getName() {
        return name;
    }

    public int getFidelityGrade() {
        return fidelityGrade;
    }

    public int getAge() {
        return age;
    }

    public ClientHobbies getHobbies() {
        return hobbies;
    }
}
