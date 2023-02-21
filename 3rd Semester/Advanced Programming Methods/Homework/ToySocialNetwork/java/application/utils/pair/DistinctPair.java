package application.utils.pair;

public class DistinctPair<E extends Comparable<E>> extends Pair<E, E> {
    /**
     * Constructs a new Pair based on 2 comparable entities, the first one in the pair will be the smaller one.
     *
     * @param first the first entity
     * @param second the second entity
     */
    public DistinctPair(E first, E second) {
        super(first.compareTo(second) < 0 ? first : second,
                first.compareTo(second) < 0 ? second : first);
    }
}
