package network.dto;

import models.User;

public class ModelsDTOFactory {
    public static UserDTO modelToDto(User user) {
        return new UserDTO(user.getID(), user.getUsername(), user.getPassword());
    }

    public static User dtoToModel(UserDTO userDTO) {
        return new User(userDTO.getID(), userDTO.getUsername(), userDTO.getPassword());
    }
}
