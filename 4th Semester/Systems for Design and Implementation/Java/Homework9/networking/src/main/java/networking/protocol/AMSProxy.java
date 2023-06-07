package networking.protocol;

import models.Ride;
import services.ServiceException;
import services.ServicesAMS;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class AMSProxy implements ServicesAMS {
    private final String host;
    private final int port;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private final BlockingQueue<Response> qResponses;
    private volatile boolean finished;

    public AMSProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qResponses = new LinkedBlockingQueue<>();
        initializeConnection();
    }

    private void initializeConnection() {
        try {
            connection=new Socket(host,port);
            output=new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input=new ObjectInputStream(connection.getInputStream());
            finished=false;
            startReader();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void startReader(){
        Thread tw=new Thread(new ReaderThread());
        tw.start();
    }

    private boolean isUpdate(Response response){
        return response.type() == ResponseType.RIDE_CREATED;
    }

    private class ReaderThread implements Runnable{
        public void run() {
            while (!finished){
                try {
                    Object response=input.readObject();
                    System.out.println("response received "+response);
                    if (!isUpdate((Response)response)){
                        try {
                            qResponses.put((Response)response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException|ClassNotFoundException e) {
                    System.out.println("Reading error "+e);
                }
            }
        }
    }

    private void closeConnection() {
        finished=true;
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendRequest(Request request) {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            System.err.println("Error sending object " + e);
        }

    }

    private Response readResponse() {
        Response response=null;
        try{
            response = qResponses.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }

    @Override
    public List<Ride> getRides() {
        Request request = new Request.Builder().type(RequestType.GET_RIDES).build();
        sendRequest(request);
        Response response = readResponse();
        return (List<Ride>)response.data();
    }

    @Override
    public void createRide(Ride ride) throws ServiceException {
        Request request = new Request.Builder().type(RequestType.CREATE_RIDE).data(ride).build();
        sendRequest(request);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            closeConnection();
            throw new ServiceException(err);
        }
    }
}
