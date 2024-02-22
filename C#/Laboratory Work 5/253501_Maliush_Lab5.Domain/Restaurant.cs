using System;
namespace _253501_Maliush_Lab5;

public class Restaurant : IEquatable<Restaurant>
{
	public Kitchen Kitchen { get; set; }
    public string Name { get; set; }

    public Restaurant() { }
    public Restaurant(int volume, short amountOfWorker, string name)
    {
        Kitchen = new(volume, amountOfWorker);
        Name = name;
    }

    public bool Equals(Restaurant? other)
    {
        if (other == null) return false;
        return Name.Equals(other.Name) && Kitchen.Equals(other.Kitchen);
    }
}

