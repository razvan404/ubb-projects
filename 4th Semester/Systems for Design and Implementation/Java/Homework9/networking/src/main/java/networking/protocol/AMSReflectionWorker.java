package networking.protocol;

import models.Ride;
import services.ServicesAMS;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.List;

public class AMSReflectionWorker implements Runnable {
    private ServicesAMS server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;

    public AMSReflectionWorker(ServicesAMS server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try {
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            connected = true;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    public void run() {
        while(connected) {
            try {
                Object request = input.readObject();
                System.out.println("Received request");
                Response response = handleRequest((Request)request);
                if(response != null) {
                    sendResponse(response);
                }
            } catch(IOException | ClassNotFoundException ex) {
                ex.printStackTrace();
            }
            try {
                Thread.sleep(1000);
            } catch(InterruptedException ex) {
                ex.printStackTrace();
            }
        }
    }

    private Response handleRequest(Request request) {
        Response response=null;
        String handlerName="handle"+(request).type();
        System.out.println("HandlerName "+handlerName);
        try {
            Method method=this.getClass().getDeclaredMethod(handlerName, Request.class);
            response=(Response)method.invoke(this,request);
            System.out.println("Method "+handlerName+ " invoked");
        } catch (NoSuchMethodException | InvocationTargetException | IllegalAccessException e) {
            e.printStackTrace();
        }
        return response;
    }

    private void sendResponse(Response response) throws IOException{
        System.out.println("sending response "+response);
        output.writeObject(response);
        output.flush();
    }

    private Response handleCREATE_RIDE(Request request) {
        System.out.println("Creating ride...");
        try {
            Ride ride = (Ride)request.data();
            server.createRide(ride);
            return new Response.Builder().type(ResponseType.OK).build();
        } catch (Exception ex) {
            return new Response.Builder().type(ResponseType.ERROR).data(ex.getMessage()).build();
        }
    }

    private Response handleGET_RIDES(Request request) {
        System.out.println("Geting rides...");
        try {
            List<Ride> rides = server.getRides();
            return new Response.Builder().type(ResponseType.OK).data(rides).build();
        } catch (Exception ex) {
            return new Response.Builder().type(ResponseType.ERROR).data(ex.getMessage()).build();
        }
    }
}
