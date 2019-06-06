import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Server {

    public static void main(String[] args) throws Exception {
        // registering service
        ProfileService server = new ProfileServiceImpl();
        ProfileService stub = (ProfileService) UnicastRemoteObject
                .exportObject(server, 0);

        Registry registry = LocateRegistry.createRegistry(1099);

        registry.rebind("ProfileService", stub);
    }
}
