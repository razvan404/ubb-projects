package factory;

import domain.container.Container;
import domain.container.ContainerStrategy;

public interface Factory {

    Container createContainer(ContainerStrategy strategy);
}
