using System;

namespace OnwardTravel.Client
{
    public enum UserEvent
    {
        RESERVATION_CREATED
    }
    public class ClientEventArgs : EventArgs
    {
        public UserEvent UserEventType { get; }
        public object Data { get; }

        public ClientEventArgs(UserEvent userEvent, object data)
        {
            UserEventType = userEvent;
            Data = data;
        }
    }
}
