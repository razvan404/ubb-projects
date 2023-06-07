package ams;

import org.springframework.jms.core.JmsOperations;
import services.Notification;
import services.NotificationReceiver;
import services.NotificationSubscriber;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class NotificationReceiverImpl implements NotificationReceiver {
    private final JmsOperations jmsOperations;
    private boolean running;
    ExecutorService service;
    NotificationSubscriber subscriber;

    public NotificationReceiverImpl(JmsOperations operations) {
        jmsOperations = operations;
    }

    @Override
    public void start(NotificationSubscriber subscriber) {
        System.out.println("Starting notification receiver ...");
        running = true;
        this.subscriber = subscriber;
        service = Executors.newSingleThreadExecutor();
        service.submit(this::run);
    }

    private void run() {
        while (running) {
            Notification notif = (Notification) jmsOperations.receiveAndConvert();
            System.out.println("Received notification..." + notif);
            subscriber.notificationReceived(notif);
        }
    }

    @Override
    public void stop() {
        running=false;
        try {
            service.awaitTermination(100, TimeUnit.MILLISECONDS);
            service.shutdown();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Stopped notification receiver");
    }
}
