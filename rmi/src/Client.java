import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.List;

public class Client {

    public static void main(String[] asd) throws Exception {
        // find service on registry
        Registry registry = LocateRegistry.getRegistry();
        ProfileService server = (ProfileService) registry
                .lookup("ProfileService");

        List<Long> times = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            long start = System.nanoTime();
            System.out.println(server.getProfilesByCourse("Computacao"));
            long stop = System.nanoTime();
            times.add(stop - start);
        }

        for (int i = 0; i < 20; i++) {
            long start = System.nanoTime();
            System.out.println(server.getSkillsByCity("Campinas"));
            long stop = System.nanoTime();
            times.add(stop - start);
        }

        for (int i = 0; i < 20; i++) {
            long start = System.nanoTime();
            System.out.println(server.addExperience("maria_silva@gmail.com", "Teste"));
            long stop = System.nanoTime();
            times.add(stop - start);
        }

        for (int i = 0; i < 20; i++) {
            long start = System.nanoTime();
            System.out.println(server.getExperience("maria_silva@gmail.com"));
            long stop = System.nanoTime();
            times.add(stop - start);
        }

        for (int i = 0; i < 20; i++) {
            long start = System.nanoTime();
            System.out.println(server.getAllProfiles());
            long stop = System.nanoTime();
            times.add(stop - start);
        }

        for (int i = 0; i < 20; i++) {
            long start = System.nanoTime();
            System.out.println(server.getProfile("maria_silva@gmail.com"));
            long stop = System.nanoTime();
            times.add(stop - start);
        }

        for (int i = 0; i < times.size(); i++) {
            if (i % 20 == 0) {
                System.out.print("\n");
            }
            System.out.print(times.get(i) + " ");
        }
    }
}
