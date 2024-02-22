using System;
namespace _253501_Maliush_Lab6;

public class Employee
{
    public int Salary { get; set; }
    public bool IsEpmloyeeOfTheMonth { get; set; }
    public string Name { get; set; }

    public Employee(string name, int salary, bool IsEpmloyeeOfTheMonth)
    {
        Name = new string(name);
    }
}
