package api.networking;

import api.models.Player;
import api.models.Try;
import api.models.dtos.TryResponseDto;
import api.networking.observer.WebSocketObserver;
import api.networking.request.Request;
import api.networking.response.Response;
import api.networking.response.ResponseType;
import api.services.Service;
import api.services.exception.ServException;
import api.services.observer.Observer;
import api.utils.JsonParser;
import api.utils.StringTransformer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.Map;

@Component
public class MyWebSocketHandler extends TextWebSocketHandler {
    @Autowired
    private Service service;

    private final Map<String, Observer> sessions = new HashMap<>();
    private final Map<String, Player> players = new HashMap<>();

    @Override
    public void afterConnectionEstablished(WebSocketSession session) throws Exception {
        super.afterConnectionEstablished(session);
        System.out.println("Connection established with " + session.getId());
    }

    @Override
    public void afterConnectionClosed(WebSocketSession session, CloseStatus status) throws Exception {
        super.afterConnectionClosed(session, status);
        System.out.println("Connection closed with " + session.getId());
        if (sessions.containsKey(session.getId())) {
            service.logout(sessions.get(session.getId()));
            sessions.remove(session.getId());
            players.remove(session.getId());
        }
    }

    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        super.handleTextMessage(session, message);
        System.out.println("Message received from " + session.getId() + ": " + message.getPayload());
        Request request = JsonParser.fromJson(message.getPayload(), Request.class);
        try {
            String handlerName = "handle" + StringTransformer.enumToPascalCase(request.getType().toString());
            Method method = getClass().getDeclaredMethod(handlerName, WebSocketSession.class, Request.class);
            Response response = (Response) method.invoke(this, session, request);
            sendResponse(session, response);
        } catch (InvocationTargetException ex) {
            System.err.println(ex.getCause().getClass().getCanonicalName() + ": " + ex.getCause().getMessage());
            sendResponse(session, Response.builder().type(ResponseType.ERROR).data(ex.getCause().getMessage()).build());
        } catch (Exception ex) {
            System.err.println(ex.getClass().getCanonicalName() + ": " + ex.getMessage());
            sendResponse(session, Response.builder().type(ResponseType.ERROR).data(ex.getMessage()).build());
        }
    }

    public void sendResponse(WebSocketSession session, Response response) {
        try {
            System.out.println("Sending response... " + response);
            session.sendMessage(new TextMessage(JsonParser.toJson(response)));
        } catch (IOException ex) {
            System.err.println("Could not send response: " + ex.getMessage());
        }
    }

    public Response handleLogin(WebSocketSession session, Request request) throws ServException, IOException {
        System.out.println("Login request ...");
        Player player = JsonParser.changeType(request.getData(), Player.class);
        Observer observer = new WebSocketObserver(session);
        player = service.login(player, observer);
        sessions.put(session.getId(), observer);
        players.put(session.getId(), player);
        return new Response(ResponseType.OK, player);
    }

    public Response handleFindOnlinePlayers(WebSocketSession session, Request request) {
        System.out.println("Find online players request ...");
        return Response.builder().type(ResponseType.OK).data(service.findOnlinePlayers()).build();
    }

    public Response handleLogout(WebSocketSession session, Request request) {
        System.out.println("Logout request ...");
        service.logout(sessions.get(session.getId()));
        return Response.builder().type(ResponseType.OK).build();
    }

    public Response handleStartGame(WebSocketSession session, Request request) throws ServException {
        System.out.println("Start game request ...");
        service.startGame(players.get(session.getId()));
        return Response.builder().type(ResponseType.OK).build();
    }

    public Response handleTryWord(WebSocketSession session, Request request) throws ServException, IOException {
        System.out.println("Try word request ...");
        Try tried = JsonParser.changeType(request.getData(), Try.class);
        TryResponseDto responseDto = service.tryWord(players.get(session.getId()), tried);
        return Response.builder().type(ResponseType.OK).data(responseDto).build();
    }

    public Response handleFindLeaderboard(WebSocketSession session, Request request) {
        System.out.println("Find leaderboard request ...");
        return Response.builder().type(ResponseType.OK).data(service.findLeaderboard()).build();
    }
}
