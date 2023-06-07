package start;

import networking.utils.AMSConcurrentServer;
import networking.utils.AbstractServer;
import networking.utils.ServerException;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class StartServerAMS {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("spring-server.xml");
        AbstractServer server = context.getBean("chatTCPServer", AMSConcurrentServer.class);
        try {
            server.start();
        } catch (ServerException e) {
            System.err.println("Error starting the server" + e.getMessage());
        }
    }
}
