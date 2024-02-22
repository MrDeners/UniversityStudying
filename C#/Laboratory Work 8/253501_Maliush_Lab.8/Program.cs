using Domain;

public class Program
{
    public static async Task Main()
    {
        var arts= new List<Art>();
        short unicID = 1;
        string name = GetRandomName();
        string nameOfAuthor = GetRandomNameOfAuthor();
        var stream = new MemoryStream();
        var streamService = new StreamService<Art>();
        var progress = new Progress<string> (message =>
        {
            Console.WriteLine(message);
        });
        var progressReport = new Progress<ProgressReport>(report =>
        {
            Console.WriteLine($"Поток {report.ThreadId}: {report.PercentageComplete.ToString("F1")}%");
        });
        string fileName = "File.txt";


        for (short i = 0; i < 10; i++)
        {
            Art art = new();
            art.ID = unicID;
            art.Name = name;
            art.NameOfAuthor = nameOfAuthor;
            arts.Add(art);
            ++unicID;
            name = GetRandomName();
            nameOfAuthor = GetRandomNameOfAuthor();
        }

        Console.WriteLine($"[THREAD]  {Thread.CurrentThread.ManagedThreadId}      Start the Program");

        //streamService.WriteToStreamAsync(stream, arts, progress);
        //Thread.Sleep(200);
        //streamService.CopyFromStreamAsync(stream, fileName, progress);

         streamService.WriteToStreamAsync(stream, arts, progress, progressReport);
           Thread.Sleep(20);
         /*var t2 =*/ streamService.CopyFromStreamAsync(stream, fileName, progress, progressReport);


        //Task.WaitAll()

        //await t2;
        //var statisticsData = 
            
        int result = await streamService.GetStatisticsAsync(fileName, x =>
                x.NameOfAuthor == "John Smith");
        Console.WriteLine($"Objects, that complete the conditions: {result}");
    }

    public static string GetRandomName()
    {
        var random = new Random();
        var Names = new List<string>
        {
            "Sunset at Sea", "Mountain Landscape", "Blooming Garden", "Night City", "Portrait of a Lady", "Dancing Lilies", "Winter Dawn", "Summer Rain", "Autumn Park", "Spring Flower",
            "Endless Sea", "Quiet Ocean", "Starry Sky", "Shining Lighthouse", "Ancient Castle", "Secret Garden", "Mysterious Forest", "Sunny Meadow", "Moonlit Lake", "Desert Mirage",
            "Snowy Peaks", "Tropical Paradise", "Enchanted Forest", "Golden Fields", "Silver Moon", "Emerald Waves", "Ruby Sunset", "Sapphire Night", "Amethyst Dreams", "Opal Clouds",
            "Rose Garden", "Lily Pond", "Daisy Field", "Sunflower Sunshine", "Orchid Oasis", "Tulip Twirl", "Daffodil Dance", "Iris Illusion", "Poppy Parade", "Violet Valley",
            "Peony Party", "Marigold Magic", "Lavender Lullaby", "Jasmine Joy", "Blossom Bliss", "Flower Fantasy", "Petunia Parade", "Dahlia Delight", "Carnation Carnival", "Aster Adventure",
            "Hydrangea Heaven", "Magnolia Melody", "Zinnia Zenith", "Begonia Burst", "Geranium Galaxy", "Camellia Cosmos", "Azalea Aura", "Chrysanthemum Charm", "Freesia Fable", "Gardenia Glory",
            "Lotus Luminary", "Narcissus Nirvana", "Pansy Panorama", "Rhododendron Radiance", "Snapdragon Symphony", "Tiger Lily Tapestry", "Wisteria Whirl", "Yucca Yonder", "Xerophyte Xanadu", "Water Lily Wonderland",
            "Quince Quilt", "Pomegranate Promise", "Olive Odyssey", "Nectarine Nebula", "Mulberry Mirage", "Lemon Labyrinth", "Kiwi Kaleidoscope", "Jujube Journey", "Indian Fig Infinity", "Honeydew Horizon",
            "Grapefruit Galaxy", "Fig Fantasy", "Elderberry Echo", "Durian Dawn", "Cucumber Cosmos", "Blueberry Bliss", "Apricot Aura", "Apple Ascend", "Avocado Adventure", "Almond Afterglow", "Banana Bliss",
            "Coconut Cloud", "Date Delight", "Eggfruit Euphoria", "Feijoa Fantasy", "Guava Galaxy", "Hackberry Harmony", "Imbe Infinity", "Jackfruit Joy", "Kiwano Kingdom",
            "Lime Lagoon", "Mango Mirage", "Nance Nebula", "Orange Odyssey", "Papaya Paradise", "Quince Quest", "Raspberry Radiance", "Strawberry Symphony", "Tangerine Tranquility", "Ugli Fruit Universe",
            "Voavanga Voyage", "Watermelon Whirl", "Xigua Xanadu", "Yellow Passionfruit Yonder", "Zucchini Zenith"
        };

        return new string(Names[random.Next(Names.Count)]);
    }

    public static string GetRandomNameOfAuthor()
    {
        var random = new Random();
        var Names = new List<string>
        {
            "John Smith", "Jane Doe", "Michael Johnson", "Emily Williams", "David Brown", "Emma Jones", "Christopher Davis", "Olivia Miller", "James Wilson", "Ava Moore", "Robert Taylor",
            "Isabella Thomas", "William Anderson", "Sophia Jackson", "Joseph White", "Mia Harris", "Charles Martin", "Charlotte Thompson", "Thomas Garcia", "Amelia Martinez", "Daniel Robinson",
            "Harper Clark", "Matthew Rodriguez", "Evelyn Lewis", "George Walker", "Abigail Hall", "Henry Young", "Madison Allen", "Richard Hernandez", "Ella Wright", "Patricia King", "Elizabeth Scott",
            "Jennifer Green", "Linda Adams", "Barbara Nelson", "Susan Baker", "Jessica Hill", "Sarah Mitchell", "Karen Ramirez", "Nancy Perez" 
        };

        return new string(Names[random.Next(Names.Count)]);
    }
}