using System.Reflection;
namespace _253501_Maliush_Lab6;

static public class Program
{
    static public void Main()
    {
        var employees = new List<Employee>
        {
            new ("Vladislav" , 1850, true),
            new ("Alexander" , 1850, true),
            new ("Konstantin" , 850, false),
            new ("Maxim" , 1000, false),
            new ("Anastasia" , 1250, false),
            new ("Angelina" , 1350, false)
        };

        Assembly Domain = Assembly.LoadFrom("/Users/macbook/BSUIR/Лабораторные/C#/Lab6/Lab6/bin/Debug/net7.0/domain.dll");
        Type? TypeFileService = Domain.GetType("Domain.FileService`1");
        Type? constructed = TypeFileService.MakeGenericType(typeof(Employee));
        Object? FileService = Activator.CreateInstance(constructed);

        MethodInfo Method = constructed.GetMethod("SaveData");
        Method.Invoke(FileService, new object[] {employees, "Employees.json" });
    }
}


