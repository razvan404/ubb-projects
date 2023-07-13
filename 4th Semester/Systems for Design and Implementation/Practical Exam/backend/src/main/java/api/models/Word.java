package api.models;

import jakarta.persistence.Entity;
import lombok.*;

import java.util.List;
import java.util.UUID;

@AllArgsConstructor
@NoArgsConstructor
@Data
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
@Entity
public class Word extends Identifiable<UUID> {
    private String word;
}
