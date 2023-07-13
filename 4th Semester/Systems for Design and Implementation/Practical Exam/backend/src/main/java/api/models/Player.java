package api.models;

import lombok.*;

import jakarta.persistence.*;
import java.util.UUID;

@AllArgsConstructor
@NoArgsConstructor
@Data
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
@Entity
public class Player extends Identifiable<UUID> {
    @Column(unique = true)
    private String alias;
}
