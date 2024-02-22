using System.Collections;

public class MyCustomCollection<T> : ICustomCollection<T>, IEnumerable<T>
{
    public MyCustomCollection()
    {
        Head = new Node(default(T));
        Element = Head;
    }

    private class Node
    {
        public T Data;
        public Node Next;

        public Node(T Data)
        {
            this.Data = Data;
            Next = null;
        }
    }

    private Node Head;
    private Node Element;

    public int Count
    {
        get
        {
            int count = 0;
            Node current = Head;
            while (current.Next != null)
            {
                count++;
                current = current.Next;
            }
            return count;
        }
    }

    public T this[int index]
    {
        get
        {
            if (index >= Count)
            {
                throw new IndexOutOfRangeException();
            }
            Node current = Head.Next;
            for (int i = 0; i < index; i++)
            {
                current = current.Next;
            }
            return current.Data;
        }
        set
        {
            if (index >= Count)
            {
                throw new IndexOutOfRangeException();
            }
            Node current = Head.Next;
            for (int i = 0; i < index; i++)
            {
                current = current.Next;
            }
            current.Data = value;
        }
    }

    public void Reset()
    {
        Element = Head.Next;
    }

    public void Next()
    {
        if (Element.Next != null) Element = Element.Next;
        else Reset();
    }

    public T Current()
    {
        return Element.Data;
    }

    public void Add(T item)
    {
        Node current = Head;
        while (current.Next != null)
        {
            current = current.Next;
        }
        current.Next = new Node(item);
    }

    public void Remove(T item)
    {
        try
        {
            Node Current = Head;
            while (Current.Next != null && !object.Equals(Current.Next.Data, item))
            {
                Current = Current.Next;
            }

            if (Current.Next != null)
            {
                Current.Next = Current.Next.Next;

                if (object.Equals(Element.Data, item))
                    Element = Current.Next == null ? Head : Current.Next;
            }

            else
            {
                throw new ObjectNotFound();
            }
        }
        catch (ObjectNotFound)
        {
            Console.WriteLine("This object not found");
        }
    }

    public T RemoveCurrent()
    {
        if (Element == Head)
            throw new InvalidOperationException();

        Node Current = Head;

        while (Current.Next != Element)
        {
            Current = Current.Next;
        }

        T removedData = Element.Data;

        Current.Next = Current.Next.Next;

        Element = Current.Next == null ? Head : Current.Next;

        return removedData;
    }

    public IEnumerator<T> GetEnumerator()
    {
        Node Current = Head.Next;
        while (Current != null)
        {
            yield return Current.Data;
            Current = Current.Next;
        }
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        Node Current = Head.Next;
        while (Current != null)
        {
            yield return Current.Data;
            Current = Current.Next;
        }
    }
}
