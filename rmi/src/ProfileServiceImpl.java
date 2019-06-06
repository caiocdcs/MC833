import java.util.ArrayList;
import java.util.List;

public class ProfileServiceImpl implements ProfileService {

    // database in memory
    private static final List<Profile> profiles = new ArrayList<>();

    public ProfileServiceImpl() {
        Profile profile = new Profile();
        profile.setFirstName("Maria");
        profile.setLastName("Silva");
        profile.setEmail("maria_silva@gmail.com");
        profile.setCity("Campinas");
        profile.setCourse("Computacao");

        List<String> experiences = new ArrayList<>();
        experiences.add("Análise de Dados");

        profile.setExperiences(experiences);

        List<String> skills = new ArrayList<>();
        skills.add("Estágio de 1 ano na Empresa X");

        profile.setSkills(skills);

        profiles.add(profile);
    }

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