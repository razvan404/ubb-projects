package start;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@ComponentScan("api")
@SpringBootApplication
public class StartWebServices {
    public static void main(String[] args) {
        SpringApplication.run(StartWebServices.class, args);
    }
}