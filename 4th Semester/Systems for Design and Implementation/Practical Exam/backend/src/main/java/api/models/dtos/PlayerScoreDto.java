package api.models.dtos;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.UUID;

@AllArgsConstructor
@NoArgsConstructor
@Data
public class PlayerScoreDto implements Serializable {
    private UUID id;
    private String alias;
    private Integer score;
    private Long seconds;
}
