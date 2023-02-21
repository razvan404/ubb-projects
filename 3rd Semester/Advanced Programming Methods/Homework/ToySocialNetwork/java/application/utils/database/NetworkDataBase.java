package application.utils.database;

import application.configuration.Config;

/**
 * The class <b>NetworkDataBase</b> is a singleton class to get the DataBase associated to the Toy Social Network.
 */
public class NetworkDataBase extends DataBase {
    private final static NetworkDataBase instance = new NetworkDataBase();
    private NetworkDataBase() {
        super(
                Config.getProperty("network_database_url"),
                Config.getProperty("network_database_username"),
                Config.getProperty("network_database_password"));
    }

    /**
     * @return an instance of the NetworkDataBase
     */
    public static DataBase getInstance() {
        return instance;
    }
}
