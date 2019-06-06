import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface ProfileService extends Remote {

    List<Profile> getProfilesByCourse(String course) throws RemoteException;
    List<String> getSkillsByCity(String city) throws RemoteException;
    Boolean addExperience(String email, String experience) throws RemoteException;
    List<String> getExperience(String email) throws RemoteException;
    List<Profile> getAllProfiles() throws RemoteException;
    Profile getProfile(String email) throws RemoteException;
}