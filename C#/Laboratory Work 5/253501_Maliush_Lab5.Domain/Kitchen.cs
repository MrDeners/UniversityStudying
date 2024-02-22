namespace _253501_Maliush_Lab5;

public class Kitchen : IEquatable<Kitchen>
{
    //List<string> staffName;
    public int Square { get; set; } 
    public short AmountOfWorker { get; set; }
    public Kitchen() { }
    public Kitchen(int Square, short AmountOfWorker)
    {
        this.Square = Square;
        this.AmountOfWorker = AmountOfWorker;
    }

    public bool Equals(Kitchen? other)
    {
        if (other == null) return false;
        return Square.Equals(other.Square) && AmountOfWorker.Equals(other.AmountOfWorker);
    }
}

