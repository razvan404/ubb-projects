import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class CarsDBRepository implements CarRepository{

    private JdbcUtils dbUtils;



    private static final Logger logger = LogManager.getLogger();

    public CarsDBRepository(Properties props) {
        logger.info("Initializing CarsDBRepository with properties: {} ",props);
        dbUtils=new JdbcUtils(props);
    }

    @Override
    public List<Car> findByManufacturer(String manufacturerN) {
        logger.traceEntry();
        List<Car> cars = new ArrayList<>();

        try (Connection con = dbUtils.getConnection()) {
            PreparedStatement preStmt = con.prepareStatement(
                    "SELECT * FROM cars WHERE manufacturer = ?"
            );
            preStmt.setString(1, manufacturerN);
            try (ResultSet resultSet = preStmt.executeQuery()) {
                while (resultSet.next()) {
                    int id = resultSet.getInt("car_id");
                    String manufacturer = resultSet.getString("manufacturer");
                    String model = resultSet.getString("model");
                    int year = resultSet.getInt("year");
                    Car car = new Car(manufacturer, model, year);
                    car.setId(id);
                    cars.add(car);
                }
            }
        } catch (SQLException ex) {
            logger.error(ex);
            System.err.println("Error BD " + ex);
        }
        logger.traceExit(cars);
        return cars;
    }

    @Override
    public List<Car> findBetweenYears(int min, int max) {
        logger.traceEntry();
        List<Car> cars = new ArrayList<>();

        try (Connection con = dbUtils.getConnection()) {
            PreparedStatement preStmt = con.prepareStatement(
                    "SELECT * FROM cars WHERE year >= ? AND year <= ?"
            );
            preStmt.setInt(1, min);
            preStmt.setInt(2, max);
            try (ResultSet resultSet = preStmt.executeQuery()) {
                while (resultSet.next()) {
                    int id = resultSet.getInt("car_id");
                    String manufacturer = resultSet.getString("manufacturer");
                    String model = resultSet.getString("model");
                    int year = resultSet.getInt("year");
                    Car car = new Car(manufacturer, model, year);
                    car.setId(id);
                    cars.add(car);
                }
            }
        } catch (SQLException ex) {
            logger.error(ex);
            System.err.println("Error BD " + ex);
        }
        logger.traceExit(cars);
        return cars;
    }

    @Override
    public void add(Car elem) {
        logger.traceEntry("saving task {}", elem);
        try (Connection con = dbUtils.getConnection()) {
            PreparedStatement preStmt = con.prepareStatement(
                    "INSERT INTO cars (manufacturer, model, year) " +
                            "VALUES (?, ?, ?)");
            preStmt.setString(1, elem.getManufacturer());
            preStmt.setString(2, elem.getModel());
            preStmt.setInt(3, elem.getYear());

            int result = preStmt.executeUpdate();
            logger.trace("Saving {} instances", result);
        } catch (SQLException ex) {
            logger.error(ex);
            System.err.println("Error DB: " + ex);
        }
        logger.traceExit();
    }

    @Override
    public void update(Integer integer, Car elem) {
        logger.traceEntry("update task {}", elem);
        try (Connection con = dbUtils.getConnection()) {
            PreparedStatement preStmt = con.prepareStatement(
                    "UPDATE cars " +
                            "SET manufacturer = ?, model = ?, year = ? " +
                            "WHERE car_id = ?");
            preStmt.setString(1, elem.getManufacturer());
            preStmt.setString(2, elem.getModel());
            preStmt.setInt(3, elem.getYear());
            preStmt.setInt(4, integer);

            int result = preStmt.executeUpdate();
            logger.trace("Update {} instances", result);
        } catch (SQLException ex) {
            logger.error(ex);
            System.err.println("Error DB: " + ex);
        }
        logger.traceExit();
    }

    @Override
    public Iterable<Car> findAll() {
        logger.traceEntry();
        List<Car> cars = new ArrayList<>();

        try (Connection con = dbUtils.getConnection()) {
            PreparedStatement preStmt = con.prepareStatement(
                    "SELECT * FROM cars"
            );
            try (ResultSet resultSet = preStmt.executeQuery()) {
                while (resultSet.next()) {
                    int id = resultSet.getInt("car_id");
                    String manufacturer = resultSet.getString("manufacturer");
                    String model = resultSet.getString("model");
                    int year = resultSet.getInt("year");
                    Car car = new Car(manufacturer, model, year);
                    car.setId(id);
                    cars.add(car);
                }
            }
        } catch (SQLException ex) {
            logger.error(ex);
            System.err.println("Error BD " + ex);
        }
        logger.traceExit(cars);
        return cars;
    }
}
