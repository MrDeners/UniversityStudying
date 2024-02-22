using System;
namespace _253501_Maliush_Lab5;

public interface ISerializer
{
    IEnumerable<Restaurant> DeSerializeByLINQ(string fileName);
    IEnumerable<Restaurant> DeSerializeXML(string fileName);
    IEnumerable<Restaurant> DeSerializeJSON(string fileName);
    void SerializeByLINQ(IEnumerable<Restaurant> xxx, string fileName);
    void SerializeXML(IEnumerable<Restaurant> xxx, string fileName);
    void SerializeJSON(IEnumerable<Restaurant> xxx, string fileName);
}

