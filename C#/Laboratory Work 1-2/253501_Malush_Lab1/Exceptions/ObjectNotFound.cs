public class ObjectNotFound : Exception
{
    public ObjectNotFound()
    {
    }

    public ObjectNotFound(string message) : base(message)
    {
    }

    public ObjectNotFound(string message, Exception inner) : base(message, inner)
    {
    }
}


