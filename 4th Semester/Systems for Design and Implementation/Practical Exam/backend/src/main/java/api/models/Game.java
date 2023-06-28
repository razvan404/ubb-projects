package api.models;

import jakarta.persistence.*;
import lombok.*;
import org.hibernate.annotations.CreationTimestamp;

import java.time.LocalDateTime;
import java.util.List;
import java.util.UUID;

@AllArgsConstructor
@NoArgsConstructor
@Data
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
@Entity
public class Game extends Identifiable<UUID> {
    @ManyToMany(fetch = FetchType.EAGER)
    public List<Word> configuration;
    @ManyToOne(fetch = FetchType.EAGER)
    public Player player;
    @OneToMany(fetch = FetchType.EAGER)
    public List<Try> tries;
    public Integer score = 0;
    @CreationTimestamp
    private LocalDateTime startedAt;
    private LocalDateTime finishedAt;
}
