using System.Xml.Linq;
using System.Xml.Serialization;
using System.IO;
using System.Text.Json;
using System;

namespace _253501_Maliush_Lab5;

public class Serializer : ISerializer
{
    public IEnumerable<Restaurant> DeSerializeByLINQ(string fileName)
    {
        XDocument XMLDoc = XDocument.Load(fileName);
        List<Restaurant> restaurants = XMLDoc.Root.Elements("Restaurant")
        .Select(restaurant => new Restaurant
        {
            Name = (string)restaurant.Element("Name"),
            Kitchen = new Kitchen
            {
                Square = (int)restaurant.Element("Kitchen").Element("Square"),
                AmountOfWorker = (short)restaurant.Element("Kitchen").Element("AmountOfWorker")
            }
        }).ToList();
        return restaurants;
    }

    public IEnumerable<Restaurant> DeSerializeJSON(string fileName)
    { 
        var stream = new StreamReader(fileName);
        var json = stream.ReadToEnd();
        List<Restaurant>? restaurants = JsonSerializer.Deserialize<List<Restaurant>>(json);
        return restaurants;
    }

    public IEnumerable<Restaurant> DeSerializeXML(string fileName)
    {
        var stream = new StreamReader(fileName);
        var XMLSerialzer = new XmlSerializer(typeof(List<Restaurant>));
        List<Restaurant>? restaurants = XMLSerialzer.Deserialize(stream) as List<Restaurant>;
        return restaurants;
    }

    public void SerializeByLINQ(IEnumerable<Restaurant> restaurants, string fileName)
    {
        var XMLDoc = new XDocument(new XDeclaration("1.0", "utf-8", "yes"),
            new XElement("Restaurants",
                restaurants.Select(restaurant =>
                    new XElement("Restaurant",
                        new XElement("Name", restaurant.Name),
                            new XElement("Kitchen",
                                new XElement("Square", restaurant.Kitchen.Square),
                                new XElement("AmountOfWorker", restaurant.Kitchen.AmountOfWorker))))));
        XMLDoc.Save(fileName);

    }

    public void SerializeJSON(IEnumerable<Restaurant> restaurants, string fileName)
    {
        using var stream = File.CreateText(fileName);

        string JSON = JsonSerializer.Serialize(restaurants);
        stream.WriteLine(JSON);
        stream.Close();
    }

    public void SerializeXML(IEnumerable<Restaurant> restaurants, string fileName)
    {
        using var stream = new StreamWriter(fileName);

        var XMLSerializer = new XmlSerializer(typeof(List<Restaurant>));
        XMLSerializer.Serialize(stream, restaurants);
        stream.Close();
    }

}

