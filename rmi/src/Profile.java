import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Profile implements Serializable {

    private static final long serialVersionUID = 2870269705752324738L;

    private String firstName;
    private String lastName;
    private String email;
    private String city;
    private String course;
    private List<String> skills;
    private List<String> experiences;

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
    }

    public List<String> getSkills() {
        return skills;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setSkills(List<String> skills) {
        this.skills = skills;
    }

    public List<String> getExperiences() {
        return experiences;
    }

    public void setExperiences(List<String> experiences) {
        this.experiences = experiences;
    }

    public void addExperience(String experience) {
        if (experiences == null) {
            experiences = new ArrayList<>();
        }
        experiences.add(experience);
    }

    @Override
    public String toString() {
        return "Profile{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", email='" + email + '\'' +
                ", city='" + city + '\'' +
                ", course='" + course + '\'' +
                ", skills=" + skills +
                ", experiences=" + experiences +
                '}';
    }
}
