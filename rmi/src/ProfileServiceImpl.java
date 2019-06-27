import java.util.ArrayList;
import java.util.List;

public class ProfileServiceImpl implements ProfileService {

    // database in memory
    private static final List<Profile> profiles = new ArrayList<>();

    public ProfileServiceImpl() {
        createDatabase();
    }

    // populating database
    private void createDatabase() {
        Profile profile = new Profile();
        profile.setFirstName("Maria");
        profile.setLastName("Silva");
        profile.setEmail("maria_silva@gmail.com");
        profile.setCity("Melbourne");
        profile.setCourse("Computer Science");

        List<String> experiences = new ArrayList<>();
        experiences.add("Data Analysis");

        profile.setExperiences(experiences);

        List<String> skills = new ArrayList<>();
        skills.add("Microsoft Intern for 1 year");

        profile.setSkills(skills);

        profiles.add(profile);

        Profile profile2 = new Profile();
        profile2.setFirstName("Sean");
        profile2.setLastName("Parkis");
        profile2.setEmail("sean_parkins@gmail.com");
        profile2.setCity("London");
        profile2.setCourse("Music");

        List<String> experiences2 = new ArrayList<>();
        experiences2.add("Play in the city theater");
        experiences2.add("Play drums on a rock band");

        profile2.setExperiences(experiences2);

        List<String> skills2 = new ArrayList<>();
        skills2.add("Piano");
        skills2.add("Guitar");

        profile2.setSkills(skills2);

        profiles.add(profile2);

        Profile profile3 = new Profile();
        profile3.setFirstName("Jane");
        profile3.setLastName("Doe");
        profile3.setEmail("jane.doe@gmail.com");
        profile3.setCity("Copenhagen");
        profile3.setCourse("Architecture");

        List<String> experiences3 = new ArrayList<>();
        experiences3.add("Intern Architect");
        experiences3.add("Affordable Housing Project");

        profile3.setExperiences(experiences3);

        List<String> skills3 = new ArrayList<>();
        skills3.add("Graphics");
        skills3.add("3D Modeling");
        skills3.add("Platforms");

        profile3.setSkills(skills3);

        profiles.add(profile3);

        Profile profile4 = new Profile();
        profile4.setFirstName("Robson");
        profile4.setLastName("Faker");
        profile4.setEmail("robson.faker@yahoo.com");
        profile4.setCity("Sacramento");
        profile4.setCourse("Management");

        List<String> experiences4 = new ArrayList<>();
        experiences4.add("Taco Bells");

        profile4.setExperiences(experiences4);

        List<String> skills4 = new ArrayList<>();
        skills4.add("Team Leadership");
        skills4.add("Schedule Management");

        profile4.setSkills(skills4);

        profiles.add(profile4);
    }

    // profile methods
    @Override
    public List<Profile> getProfilesByCourse(String course) {
        long start = System.nanoTime();
        List<Profile> result = new ArrayList<>();
        for (Profile profile : profiles) {
            if (profile.getCourse().equals(course)) {
                result.add(profile);
            }
        }
        long stop = System.nanoTime();
        System.out.println("getProfilesByCourse - " + (stop - start) + " ns");
        return result;
    }

    @Override
    public List<String> getSkillsByCity(String city) {
        long start = System.nanoTime();
        List<String> result = new ArrayList<>();
        for (Profile profile : profiles) {
            if (profile.getCity().equals(city)) {
                result.addAll(profile.getSkills());
            }
        }
        long stop = System.nanoTime();
        System.out.println("getSkillsByCity - " + (stop - start) + " ns");
        return result;
    }

    @Override
    public Boolean addExperience(String email, String experience) {
        long start = System.nanoTime();
        for (Profile profile : profiles) {
            if (profile.getEmail().equals(email)) {
                profile.addExperience(experience);

                long stop = System.nanoTime();
                System.out.println("addExperience - " + (stop - start) + " ns");

                return true;
            }
        }
        long stop = System.nanoTime();
        System.out.println("addExperience - " + (stop - start) + " ns");

        return false;
    }

    @Override
    public List<String> getExperience(String email) {
        long start = System.nanoTime();
        List<String> result = new ArrayList<>();
        for (Profile profile : profiles) {
            if (profile.getEmail().equals(email)) {
                long stop = System.nanoTime();
                System.out.println("getExperience - " + (stop - start) + " ns");

                return profile.getExperiences();
            }
        }

        long stop = System.nanoTime();
        System.out.println("getExperience - " + (stop - start) + " ns");
        return result;
    }

    @Override
    public List<Profile> getAllProfiles() {
        long start = System.nanoTime();
        List<Profile> result = profiles;

        long stop = System.nanoTime();
        System.out.println("getAllProfiles - " + (stop - start) + " ns");

        return result;
    }

    @Override
    public Profile getProfile(String email) {
        long start = System.nanoTime();
        for (Profile profile : profiles) {
            if (profile.getEmail().equals(email)) {
                long stop = System.nanoTime();
                System.out.println("getProfile - " + (stop - start) + " ns");

                return profile;
            }
        }
        long stop = System.nanoTime();
        System.out.println("getProfile - " + (stop - start) + " ns");

        return null;
    }
}