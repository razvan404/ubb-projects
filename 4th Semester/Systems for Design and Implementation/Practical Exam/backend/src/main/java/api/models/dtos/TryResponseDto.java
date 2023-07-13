package api.models.dtos;

import jakarta.annotation.sql.DataSourceDefinition;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

@AllArgsConstructor
@NoArgsConstructor
@Data
public class TryResponseDto implements Serializable {
    private Integer word1idx;
    private String word1;
    private Integer word2idx;
    private String word2;
    private boolean finished;
}
