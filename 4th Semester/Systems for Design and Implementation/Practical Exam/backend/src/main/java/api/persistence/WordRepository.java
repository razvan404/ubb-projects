package api.persistence;

import api.models.Word;

import java.util.List;

public interface WordRepository extends CrudRepository<java.util.UUID, Word> {
    List<Word> findRandomWords(int count);
}
