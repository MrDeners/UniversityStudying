using System.Collections.Generic;
using System.IO;

namespace _253501_Maliush_Lab._4
{
    public class Program
    {
        public static void Main ()
        {
            FolderCreatingAndPreparing();
            GetFileFromFolder();

            List<Art> arts = new()
            {
                new Art("Picasso", 1987, true),
                new Art("Dali", 1965, false),
                new Art("MonaLisa", 1834, false),
                new Art("Gomer", 1200, true),
                new Art("Anastasia", 2021, true)
            };
            AddToFile(arts);
            FileRenaming("MyArts.txt", "NewArts.txt");
            List<Art> artsTwo = new();
            GetFromFile(artsTwo);
            Compare(artsTwo);
            OutputAllCollections(arts, artsTwo);
            SortingByYear(arts);
        }

        public static void FolderCreatingAndPreparing()
        {
            Directory.CreateDirectory("/Users/macbook/BSUIR/Лабораторные/C#/253501_Maliush_Lab.4/Files");
            ClearFolder("/Users/macbook/BSUIR/Лабораторные/C#/253501_Maliush_Lab.4/Files");
            int name = 0;
            short numOfExtension = 0;
            Random random = new();
            for (short i = 0; i < 10; i++)
            {
                name = random.Next(0, int.MaxValue);

                
                numOfExtension = (short)random.Next(1, 4);

                switch (numOfExtension)
                {
                    case 1:
                        File.Create($"/Users/macbook/BSUIR/Лабораторные/C#/253501_Maliush_Lab.4/Files/{name}.txt");
                        break;
                    case 2:
                        File.Create($"/Users/macbook/BSUIR/Лабораторные/C#/253501_Maliush_Lab.4/Files/{name}.rtf");
                        break;
                    case 3:
                        File.Create($"/Users/macbook/BSUIR/Лабораторные/C#/253501_Maliush_Lab.4/Files/{name}.dat");
                        break;
                    case 4:
                        File.Create($"/Users/macbook/BSUIR/Лабораторные/C#/253501_Maliush_Lab.4/Files/{name}.inf");
                        break;
                }
            }
        }

        public static void ClearFolder(string FolderName)
        {
            DirectoryInfo dir = new DirectoryInfo(FolderName);

            foreach (FileInfo fi in dir.GetFiles())
            {
                fi.Delete();
            }

            foreach (DirectoryInfo di in dir.GetDirectories())
            {
                ClearFolder(di.FullName);
                di.Delete();
            }
        }

        public static void GetFileFromFolder()
        {
            List<string> files = Directory.GetFiles("/Users/macbook/BSUIR/Лабораторные/C#/253501_Maliush_Lab.4/Files").Select(Path.GetFileName).ToList();
            foreach (string i in files)
            {
                string[] parts = i.Split('.', 2);
                Console.WriteLine($"File <{parts[0]}> has extension <.{parts[1]}>");
            }
        }

        public static void AddToFile(List<Art> arts)
        {
            FileService fileService = new();
            fileService.SaveData(arts, "MyArts.txt");
        }

        public static void FileRenaming(string oldFileName, string newFileName)
        {
            if (File.Exists(newFileName))
            {
                File.Delete(newFileName);
            }
                File.Move(oldFileName, newFileName);
        }

        public static void GetFromFile(List<Art> arts)
        {
            FileService fileService = new();
            arts.AddRange(fileService.ReadFile("NewArts.txt"));
        }

        public static void Compare(List<Art> arts)
        {
            MyCustomComparer comparer = new();
            List<Art> sortedArts = arts.OrderBy(x => x, comparer).ToList();
            arts.Clear();
            arts.AddRange(sortedArts);
        }

        public static void OutputAllCollections(List<Art> artsOne, List<Art> artsTwo)
        {
            Console.WriteLine();
            Console.WriteLine("Old don't sorted collection:");
            foreach (Art i in artsOne)
            {
                i.GetInformation();
            }
            Console.WriteLine();
            Console.WriteLine("New sorted collection:");
            foreach (Art i in artsTwo)
            {
                i.GetInformation();
            }
        }

        public static void SortingByYear(List<Art> arts)
        {
            List<Art> sortedArts = arts.OrderByDescending(x => x.GetYearOfCreating()).ToList();
            arts.Clear();
            arts.AddRange(sortedArts);

            Console.WriteLine();
            Console.WriteLine("Sorted by Year of Creating collection:");
            foreach (Art i in arts)
            {
                i.GetInformation();
            }
        }
    }
}