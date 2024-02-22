namespace Domain;
using System.Text.Json;

public class FileService<T> : IFileService<T> where T : class
{
    public IEnumerable<T> ReadFile(string fileName)
    {
        var stream = new StreamReader(fileName);

        var json = stream.ReadToEnd();
        IEnumerable<T>? objects = JsonSerializer.Deserialize<IEnumerable<T>>(json);
        return objects;

    }

    public void SaveData(IEnumerable<T> data, string fileName)
    {
        using var stream = File.CreateText(fileName);

        string json = JsonSerializer.Serialize(data);
        stream.WriteLine(json);
    }
}


