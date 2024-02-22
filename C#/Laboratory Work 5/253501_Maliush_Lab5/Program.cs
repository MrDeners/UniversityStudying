namespace _253501_Maliush_Lab5;
public static class Program
{
    public static void Main ()
    {
        var restaurants = new List<Restaurant>
        {
            new(134, 12, "MCDonalds"),  
            new(20, 1, "KFC"),
            new(190, 8, "Burger King"),
            new(154, 10, "SMACHNA DI KROPKA"),
            new(13, 11, "Vasilki")
        };
        var serializer = new Serializer();

        serializer.SerializeByLINQ(restaurants, "XML-LINQ.xml");
        serializer.SerializeJSON(restaurants, "JSON.json");
        serializer.SerializeXML(restaurants, "XML.xml");

        var newRestaurantsXML = (List<Restaurant>)serializer.DeSerializeXML("XML.xml");
        var newRestaurantsJSON = (List<Restaurant>)serializer.DeSerializeJSON("JSON.json");
        var newRestaurantsLINQtoXML = serializer.DeSerializeByLINQ("XML-LINQ.xml");

        bool areEqual = restaurants.SequenceEqual(newRestaurantsXML);
        Console.WriteLine($"XML: {areEqual}");
        areEqual = restaurants.SequenceEqual(newRestaurantsJSON);
        Console.WriteLine($"JSON: {areEqual}");
        areEqual = restaurants.SequenceEqual(newRestaurantsLINQtoXML);
        Console.WriteLine($"LINQtoXML: {areEqual}");


        Console.ReadLine();
    }
}