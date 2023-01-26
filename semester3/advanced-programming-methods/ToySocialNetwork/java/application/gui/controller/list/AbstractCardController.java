package application.gui.controller.list;

import application.gui.controller.windows.InterfaceWindow;

public abstract class AbstractCardController<E> extends InterfaceWindow {
    public abstract void setEntity(E entity);
    public abstract void build();
}
